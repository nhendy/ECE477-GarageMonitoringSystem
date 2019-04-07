
#include "FT_Platform.h"
#include "FT_Gpu_Hal.h"
#include "FT_Esd_Primitives.h"
#include "FT_Esd_Dl.h"
#include "FT_Esd_Widget.h"

extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;

#define FT_ESD_DL_END 0

// Rectangle Gradient drawing with some logic to convert from radius to line width and width height to positions to simplify usage
ft_void_t Ft_Esd_Render_RectangleF_Gradient(
ft_int32_f4_t x, ft_int32_f4_t y, 
ft_int32_f4_t w, ft_int32_f4_t h, 
ft_argb32_t color1, ft_argb32_t color2,
ft_int16_t direction)
{
	ft_int16_t x0 = x >> 4;
	ft_int16_t y0 = y >> 4;
	ft_int16_t w1 = w >> 4;
	ft_int16_t h1 = h >> 4;

	FT_Esd_Render_Rect_Grad(x0, y0, w1, h1, color1, color2, direction);	
}

// Rectangle drawing with some logic to convert from radius to line width and width height to positions to simplify usage
ft_void_t Ft_Esd_Render_RectangleF(ft_int32_f4_t x, ft_int32_f4_t y, ft_int32_f4_t w, ft_int32_f4_t h, ft_int32_f4_t radius, ft_argb32_t color)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_int32_t width = radius + 8;
	ft_int32_t x0 = x + radius;
	ft_int32_t y0 = y + radius;
	ft_int32_t x1 = x + w - 16 - radius;
	ft_int32_t y1 = y + h - 16 - radius;
	Ft_Esd_Dl_COLOR_ARGB(color);
	Ft_Esd_Dl_LINE_WIDTH(width);
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(RECTS));
#if (BT_EVE_MODEL >= 0x0810)
	Ft_Esd_Dl_VERTEX_FORMAT(4);
#endif
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x0, y0));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x1, y1));
#if FT_ESD_DL_END
	Ft_Gpu_Hal_WrCmd32(phost, END());
#endif
}

ft_void_t Ft_Esd_Render_LineF(ft_int32_f4_t x0, ft_int32_f4_t y0, ft_int32_f4_t x1, ft_int32_f4_t y1, ft_int32_f3_t width, ft_argb32_t color)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	Ft_Esd_Dl_COLOR_ARGB(color);
	Ft_Esd_Dl_LINE_WIDTH(width);
	Ft_Gpu_Hal_WrCmd32(phost, BEGIN(LINES));
#if (BT_EVE_MODEL >= 0x0810)
	Ft_Esd_Dl_VERTEX_FORMAT(4);
#endif
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x0, y0));
	Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x1, y1));
#if FT_ESD_DL_END
	Ft_Gpu_Hal_WrCmd32(phost, END());
#endif
}

void Ft_Esd_Dl_Bitmap_Vertex(ft_int16_t x, ft_int16_t y, ft_uint8_t handle, ft_uint16_t cell)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
#if (BT_EVE_MODEL >= 0x0810)
	if (x < 0 || y < 0 || x >= 512 || y >= 512)
	{
		Ft_Esd_Dl_VERTEX_FORMAT(0);
		Ft_Esd_Dl_BITMAP_HANDLE(handle);
		Ft_Esd_Dl_Bitmap_Page(handle, cell >> 7);
		Ft_Esd_Dl_CELL(cell & 0x7F);
		Ft_Gpu_Hal_WrCmd32(phost, VERTEX2F(x, y));
	}
	else
#endif
	{
		Ft_Esd_Dl_Bitmap_Page(handle, cell >> 7);
		Ft_Gpu_Hal_WrCmd32(phost, VERTEX2II(x, y, handle, cell));
	}	
}

// NOTE: This function may only be used within a Ft_Esd_Dl_SAVE_CONTEXT block, because it does not clean up state
// Also Ft_Gpu_CoCmd_LoadIdentity must be called afterwards to fully restore the context
void Ft_Esd_Dl_Bitmap_Vertex_DXT1(ft_int16_t x, ft_int16_t y, ft_uint8_t handle, ft_uint8_t additional, ft_uint16_t cell, ft_uint16_t cells)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	Ft_Gpu_Hal_WrCmd32(phost, BLEND_FUNC(ONE, ZERO));
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(0x55));
	Ft_Esd_Dl_Bitmap_Vertex(x, y, handle, cell);
	Ft_Gpu_Hal_WrCmd32(phost, BLEND_FUNC(ONE, ONE));
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_A(0xAA));
	Ft_Esd_Dl_Bitmap_Vertex(x, y, handle, cell + cells);
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_MASK(1, 1, 1, 0));
	Ft_Gpu_CoCmd_Scale(phost, 4UL * 65536UL, 4UL * 65536UL); // Color pass, scaled up 4x, nearest
	Ft_Gpu_CoCmd_SetMatrix(phost);
	Ft_Gpu_Hal_WrCmd32(phost, BLEND_FUNC(DST_ALPHA, ZERO));
	Ft_Esd_Dl_Bitmap_Vertex(x, y, additional, cell + cells);
	Ft_Gpu_Hal_WrCmd32(phost, BLEND_FUNC(ONE_MINUS_DST_ALPHA, ONE));
	Ft_Esd_Dl_Bitmap_Vertex(x, y, additional, cell);
}

#if (BT_EVE_MODEL >= 0x0810)
// NOTE: This function may only be used within a Ft_Esd_Dl_SAVE_CONTEXT block, because it does not clean up state
void Ft_Esd_Dl_Bitmap_Vertex_PALETTED8(ft_int16_t x, ft_int16_t y, ft_uint8_t handle, ft_uint16_t cell, ft_uint32_t paletteAddr)
{
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	Ft_Esd_Dl_Alpha_Func(ALWAYS,0);
	Ft_Gpu_Hal_WrCmd32(phost, BLEND_FUNC(ONE, ZERO));
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_MASK(0, 0, 0, 1));
	Ft_Esd_Dl_PALETTE_SOURCE(paletteAddr + 3);
	Ft_Esd_Dl_Bitmap_Vertex(x, y, handle, cell);
	Ft_Gpu_Hal_WrCmd32(phost, BLEND_FUNC(DST_ALPHA, ONE_MINUS_DST_ALPHA));
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_MASK(1, 0, 0, 0));
	Ft_Esd_Dl_PALETTE_SOURCE(paletteAddr + 2);
	Ft_Esd_Dl_Bitmap_Vertex(x, y, handle, cell);
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_MASK(0, 1, 0, 0));
	Ft_Esd_Dl_PALETTE_SOURCE(paletteAddr + 1);
	Ft_Esd_Dl_Bitmap_Vertex(x, y, handle, cell);
	Ft_Gpu_Hal_WrCmd32(phost, COLOR_MASK(0, 0, 1, 0));
	Ft_Esd_Dl_PALETTE_SOURCE(paletteAddr);
	Ft_Esd_Dl_Bitmap_Vertex(x, y, handle, cell);

}
#endif

void Ft_Esd_Render_Bitmap(ft_int16_t x, ft_int16_t y, Ft_Esd_BitmapCell bitmapCell, ft_argb32_t c)
{
	if (!bitmapCell.Info)
		return;

	Ft_Esd_BitmapInfo *bitmapInfo = bitmapCell.Info;
	ft_uint16_t cell = bitmapCell.Cell;
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_uint8_t handle = Ft_Esd_Dl_Bitmap_Setup(bitmapInfo);
	
	if (handle != FT_ESD_BITMAPHANDLE_INVALID)
	{
		ft_uint8_t additional = bitmapInfo->AdditionalInfo
			? Ft_Esd_Dl_Bitmap_Setup(bitmapInfo->AdditionalInfo)
			: FT_ESD_BITMAPHANDLE_INVALID;
		
		Ft_Esd_Dl_Bitmap_WidthHeightReset(handle);
		Ft_Esd_Dl_COLOR_ARGB(c);
		Ft_Gpu_Hal_WrCmd32(phost, BEGIN(BITMAPS));
#if (BT_EVE_MODEL >= 0x0810)
		if (bitmapInfo->Format == PALETTED8)
		{
			Ft_Esd_Dl_SAVE_CONTEXT();
			ft_uint32_t paletteAddr = Ft_Esd_LoadPalette(bitmapInfo);
			Ft_Esd_Dl_Bitmap_Vertex_PALETTED8(x, y, handle, cell, paletteAddr);
			if (additional != FT_ESD_BITMAPHANDLE_INVALID)
				Ft_Esd_Dl_Bitmap_Vertex_PALETTED8(x, y, additional, cell, paletteAddr);
			Ft_Esd_Dl_RESTORE_CONTEXT();
		}
		else 
#endif
		if (bitmapInfo->Format == DXT1 && additional != FT_ESD_BITMAPHANDLE_INVALID)
		{
			Ft_Esd_Dl_Bitmap_WidthHeight(additional, bitmapInfo->Width, bitmapInfo->Height);
			Ft_Esd_Dl_SAVE_CONTEXT();
			Ft_Esd_Dl_Bitmap_Vertex_DXT1(x, y, handle, additional, cell, bitmapInfo->Cells);
			Ft_Gpu_CoCmd_LoadIdentity(Ft_Esd_Host);
			Ft_Esd_Dl_RESTORE_CONTEXT();
		}
		else
		{
			Ft_Esd_Dl_Bitmap_Vertex(x, y, handle, cell);
			if (additional != FT_ESD_BITMAPHANDLE_INVALID)
				Ft_Esd_Dl_Bitmap_Vertex(x, y, additional, cell);
		}
#if FT_ESD_DL_END
		Ft_Gpu_Hal_WrCmd32(phost, END());
#endif
	}
}

ft_void_t Ft_Esd_Render_BitmapScaled(ft_int16_t x, ft_int16_t y, Ft_Esd_BitmapCell bitmapCell, ft_argb32_t c, ft_int32_f16_t xscale, ft_int32_f16_t yscale, ft_int32_f16_t xoffset, ft_int32_f16_t yoffset, ft_int16_t width, ft_int16_t height)
{
	if (!bitmapCell.Info)
		return;

	Ft_Esd_BitmapInfo *bitmapInfo = bitmapCell.Info;
	ft_uint16_t cell = bitmapCell.Cell;
	Ft_Gpu_Hal_Context_t *phost = Ft_Esd_Host;
	ft_uint8_t handle = Ft_Esd_Dl_Bitmap_Setup(bitmapInfo);

	if (handle != FT_ESD_BITMAPHANDLE_INVALID)
	{
		ft_uint8_t additional = bitmapInfo->AdditionalInfo
			? Ft_Esd_Dl_Bitmap_Setup(bitmapInfo->AdditionalInfo)
			: FT_ESD_BITMAPHANDLE_INVALID;
		
		Ft_Esd_Dl_Bitmap_WidthHeight(handle, width, height);
		Ft_Esd_Dl_COLOR_ARGB(c);
		Ft_Esd_Dl_SAVE_CONTEXT();
		Ft_Gpu_CoCmd_Translate(Ft_Esd_Host, xoffset, yoffset);
		Ft_Gpu_CoCmd_Scale(Ft_Esd_Host, xscale, yscale);
		Ft_Gpu_CoCmd_SetMatrix(Ft_Esd_Host);
		Ft_Gpu_Hal_WrCmd32(phost, BEGIN(BITMAPS));
#if (BT_EVE_MODEL >= 0x0810)
		if (bitmapInfo->Format == PALETTED8)
		{
			ft_uint32_t paletteAddr = Ft_Esd_LoadPalette(bitmapInfo);
			Ft_Esd_Dl_Bitmap_Vertex_PALETTED8(x, y, handle, cell, paletteAddr);
			if (additional != FT_ESD_BITMAPHANDLE_INVALID)
				Ft_Esd_Dl_Bitmap_Vertex_PALETTED8(x, y, additional, cell, paletteAddr);
		}
		else 
#endif
		if (bitmapInfo->Format == DXT1 && additional != FT_ESD_BITMAPHANDLE_INVALID)
		{
			Ft_Esd_Dl_Bitmap_WidthHeight(additional, width, height);
			Ft_Esd_Dl_Bitmap_Vertex_DXT1(x, y, handle, additional, cell, bitmapInfo->Cells);
		}
		else
		{
			Ft_Esd_Dl_Bitmap_Vertex(x, y, handle, cell);
			if (additional != FT_ESD_BITMAPHANDLE_INVALID)
				Ft_Esd_Dl_Bitmap_Vertex(x, y, additional, cell);
		}
#if FT_ESD_DL_END
		Ft_Gpu_Hal_WrCmd32(phost, END());
#endif
		Ft_Gpu_CoCmd_LoadIdentity(Ft_Esd_Host);
		Ft_Esd_Dl_RESTORE_CONTEXT();
	}
}

// Render bitmap using freeform rectangle within a specified global screen rectangle, freeform is relative to global
ft_void_t Ft_Esd_Render_BitmapFreeform(Ft_Esd_BitmapCell bitmapCell, ft_argb32_t c, Ft_Esd_Rect16 globalRect, Ft_Esd_Rect16 freeformRect, ft_uint8_t minAlpha)
{
	if (!bitmapCell.Info)
		return;
	
	Ft_Esd_Dl_Alpha_Func((minAlpha > 0) ? GEQUAL : ALWAYS, minAlpha);
		
	if (freeformRect.Width == bitmapCell.Info->Width // No scaling
		&& freeformRect.Height == bitmapCell.Info->Height)
	{
		freeformRect.X += globalRect.X;
		freeformRect.Y += globalRect.Y;
		if (Ft_Esd_Rect16_IsInside(freeformRect, globalRect)) // No scissor
		{
			Ft_Esd_Render_Bitmap(freeformRect.X, freeformRect.Y, bitmapCell, c);
		}
		else
		{
			Ft_Esd_Rect16 state = Ft_Esd_Dl_Scissor_Set(globalRect);
			Ft_Esd_Render_Bitmap(freeformRect.X, freeformRect.Y, bitmapCell, c);
			Ft_Esd_Dl_Scissor_Reset(state);
		}
	}
	else
	{
		ft_int32_f16_t xscale = (((ft_int32_f16_t)freeformRect.Width) << 16) / ((ft_int32_f16_t)bitmapCell.Info->Width);
		ft_int32_f16_t yscale = (((ft_int32_f16_t)freeformRect.Height) << 16) / ((ft_int32_f16_t)bitmapCell.Info->Height);
		// ESD_print("scale: %i, %i\n", xscale, yscale);
		Ft_Esd_Render_BitmapScaled(globalRect.X, globalRect.Y, bitmapCell, c, xscale, yscale,
			(((ft_int32_f16_t)freeformRect.X) << 16), (((ft_int32_f16_t)freeformRect.Y) << 16),
			globalRect.Width, globalRect.Height);
	}
	
	Ft_Esd_Dl_Alpha_Func(ALWAYS,0);
}

ft_void_t Ft_Esd_Render_BitmapRotate(Ft_Esd_BitmapCell bitmapCell, ft_argb32_t c, Ft_Esd_Rect16 globalRect, ft_int32_t rotateAngle)
{        
	if (!bitmapCell.Info)
		return;
    
	Ft_Esd_BitmapInfo *bitmapInfo = bitmapCell.Info;   
	ft_uint16_t cell = bitmapCell.Cell;
	ft_uint8_t handle = Ft_Esd_Dl_Bitmap_Setup(bitmapInfo);
          
    ft_int32_t translate_pixels = 2*bitmapInfo->Width*65536;

	if (handle != FT_ESD_BITMAPHANDLE_INVALID)
    {
        ft_int16_t radius = bitmapInfo->Width / 2;    
        
        ft_int16_t x = globalRect.X;
        ft_int16_t y = globalRect.Y;                
        ft_int16_t x_center = bitmapInfo->Width / 2;
        ft_int16_t y_center = bitmapInfo->Height / 2;  
        
        //ESD_print("x=%d,y=%d,x_center_x=%d,certer_y = %d, radius = %d\n",x,y,x_center,y_center,radius);
       
        int tilenumber = 0;
        const int TITLE_SIZE = 64;//Magic number, DONOT CHANGE
        Ft_Esd_Dl_COLOR_ARGB(c);
        Ft_Esd_Dl_SAVE_CONTEXT();
        
        Ft_Esd_Dl_Bitmap_WidthHeight_BILINEAR(handle, TITLE_SIZE, TITLE_SIZE);//Bitmap_Size command
        
        Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BEGIN(BITMAPS));
        
#if (BT_EVE_MODEL >= 0x0810)      
        Ft_Esd_Dl_VERTEX_FORMAT(4);
#endif        
		Ft_Esd_Dl_CELL_Paged(handle, cell);
        for (int dx = (x - radius); dx < (x + radius); dx += TITLE_SIZE){
            for (int dy = (y - radius); dy < (y + radius); dy += TITLE_SIZE){
                //ESD_print("draw tile %d\n",tilenumber ++);
                tilenumber ++;
                Ft_Gpu_CoCmd_LoadIdentity(Ft_Esd_Host);
                Ft_Gpu_CoCmd_Translate(Ft_Esd_Host, (x - dx) << 16, (y - dy) << 16);

                Ft_Gpu_CoCmd_Rotate(Ft_Esd_Host,rotateAngle);
                Ft_Gpu_CoCmd_Translate(Ft_Esd_Host, -x_center << 16, -y_center << 16);
                //Ft_Gpu_CoCmd_Translate(Ft_Esd_Host, -x_center, -y_center);
                
                Ft_Gpu_CoCmd_SetMatrix(Ft_Esd_Host);
                Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2F(dx*16, dy*16));
            }
        }
        //ESD_print("draw tile %d\n",tilenumber);
        Ft_Gpu_CoCmd_LoadIdentity(Ft_Esd_Host);
        Ft_Esd_Dl_RESTORE_CONTEXT();               
	}      
}


// Get scaled size
Ft_Esd_Size16 Ft_Esd_Primitive_GetScaledSize(Ft_Esd_Size16 boundary, Ft_Esd_Size16 original, ft_uint8_t scaling)
{
	switch (scaling)
	{
	case ESD_SCALING_FILL: // Keep Aspect ratio, extend outside rect
	case ESD_SCALING_FIT: // Keep Aspect ratio, stay inside rect
		{
			// There are two real options: scale original to boundary width or scale original to boundary height
			ft_int32_f16_t boundaryRatio = (((ft_int32_f16_t)boundary.Width) << 16) / ((ft_int32_f16_t)boundary.Height);
			ft_int32_f16_t originalRatio = (((ft_int32_f16_t)original.Width) << 16) / ((ft_int32_f16_t)original.Height);
			if (boundaryRatio == originalRatio)
				return boundary;
			ft_bool_t originalWider = originalRatio > boundaryRatio;
			ft_bool_t wantFit = scaling == ESD_SCALING_FIT;
			Ft_Esd_Size16 res;
			if (originalWider ^ wantFit) // (boundary higher && want fill) || (original higher && want fit)
				//                          (original wider && want fill)  || (boundary wider && want fit)
			{
				// Scale to height
				res.Height = boundary.Height;
				ft_int32_f16_t scale = (((ft_int32_f16_t)boundary.Height) << 16) / ((ft_int32_f16_t)original.Height);
				res.Width = (((ft_int32_f16_t)original.Width) * scale) >> 16;
			}
			else
			{
				// Scale to width
				res.Width = boundary.Width;
				ft_int32_f16_t scale = (((ft_int32_f16_t)boundary.Width) << 16) / ((ft_int32_f16_t)original.Width);
				res.Height = (((ft_int32_f16_t)original.Height) * scale) >> 16;
			}
			return res;
		}
	case ESD_SCALING_STRETCH:
		return boundary;
	default: // ESD_SCALING_ORIGINAL
		return original;
	}
}

// Get alignment position
Ft_Esd_Rect16 Ft_Esd_Primitive_GetAlignedRect(Ft_Esd_Size16 boundary, Ft_Esd_Size16 size, ft_uint8_t align)
{
	Ft_Esd_Rect16 res;
	res.Size = size;
	ft_uint8_t halign = ESD_ALIGN_HORIZONTAL(align);
	switch (halign)
	{
	case ESD_ALIGN_LEFTX:
		res.X = 0;
		break;
	case ESD_ALIGN_CENTERX:
		res.X = (boundary.Width - size.Width) >> 1;
		break;
	case ESD_ALIGN_RIGHTX:
		res.X = (boundary.Width - size.Width);
		break;
	default: // ESD_ALIGN_FILLX
		res.X = 0;
		res.Width = boundary.Width;
		break;
	}
	ft_uint8_t valign = ESD_ALIGN_VERTICAL(align);
	switch (valign)
	{
	case ESD_ALIGN_TOPY:
		res.Y = 0;
		break;
	case ESD_ALIGN_CENTERY:
		res.Y = (boundary.Height - size.Height) >> 1;
		break;
	case ESD_ALIGN_BOTTOMY:
		res.Y = (boundary.Height - size.Height);
		break;
	default: // ESD_ALIGN_FILLY
		res.Y = 0;
		res.Height = boundary.Height;
		break;
	}
	return res;
}

/* end of file */
