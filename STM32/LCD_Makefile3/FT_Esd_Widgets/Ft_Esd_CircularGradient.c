
#include "Ft_Esd_Elements.h"
#include "Ft_Esd_Dl.h"
#include "Ft_Esd.h"
#include "Ft_Esd_Widget.h"
#include "Ft_Esd_CircularGradient.h"
#include "Ft_Esd_Primitives.h"

#define FT_ESD_SCRATCHHANDLE 	(15)
#define PIXELS(x)  				int((x) * 16)
#define BITMAP_WIDTH 			512
#define BITMAP_HEIGHT			1
#define BITMAP_TOTAL_SIZE		(BITMAP_WIDTH * BITMAP_HEIGHT)

extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;
extern Ft_Esd_GpuAlloc *Ft_Esd_GAlloc;

static Ft_Esd_GpuHandle pythagGpuHandle;
static Ft_Esd_GpuHandle gaussGpuHandle;
static ft_uint32_t pythag_bitmapAddr = 0xFFFFFFFF;
static ft_uint32_t gauss_bitmapAddr = 0xFFFFFFFF;

static const ft_uint8_t pythag_raw[] = {
/*('file properties: ', 'resolution ', 512, 'x', 1, 'format ', 'L8', 'stride ', 512, ' total size ', 512)*/ 
0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,21,22,23,24,25,26,27,28,29,
29,30,31,32,33,34,35,35,36,37,38,39,40,40,41,42,43,44,45,45,46,47,48,48,49,50,51,52,52,53,54,55,
55,56,57,58,58,59,60,61,61,62,63,63,64,65,65,66,67,68,68,69,70,70,71,72,72,73,74,74,75,75,76,77,
77,78,79,79,80,80,81,82,82,83,83,84,85,85,86,86,87,87,88,88,89,90,90,91,91,92,92,93,93,94,94,95,
95,96,96,97,97,98,98,99,99,100,100,100,101,101,102,102,103,103,104,104,104,105,105,106,106,106,107,107,108,108,108,109,
109,110,110,110,111,111,111,112,112,112,113,113,113,114,114,114,115,115,115,116,116,116,116,117,117,117,118,118,118,118,119,119,
119,119,120,120,120,120,121,121,121,121,121,122,122,122,122,122,123,123,123,123,123,123,124,124,124,124,124,124,125,125,125,125,
125,125,125,125,126,126,126,126,126,126,126,126,126,126,126,126,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,
127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,126,126,126,126,126,126,126,126,126,126,126,126,125,125,125,125,
125,125,125,125,124,124,124,124,124,124,123,123,123,123,123,123,122,122,122,122,122,121,121,121,121,121,120,120,120,120,119,119,
119,119,118,118,118,118,117,117,117,116,116,116,116,115,115,115,114,114,114,113,113,113,112,112,112,111,111,111,110,110,110,109,
109,108,108,108,107,107,106,106,106,105,105,104,104,104,103,103,102,102,101,101,100,100,100,99,99,98,98,97,97,96,96,95,
95,94,94,93,93,92,92,91,91,90,90,89,88,88,87,87,86,86,85,85,84,83,83,82,82,81,80,80,79,79,78,77,
77,76,75,75,74,74,73,72,72,71,70,70,69,68,68,67,66,65,65,64,63,63,62,61,61,60,59,58,58,57,56,55,
55,54,53,52,52,51,50,49,48,48,47,46,45,45,44,43,42,41,40,40,39,38,37,36,35,35,34,33,32,31,30,29,
29,28,27,26,25,24,23,22,21,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,0,    
};


static const ft_uint8_t gauss_raw[] = {
/*('file properties: ', 'resolution ', 512, 'x', 1, 'format ', 'L8', 'stride ', 512, ' total size ', 512)*/ 
93,94,95,96,96,97,98,99,99,100,101,102,102,103,104,105,105,106,107,108,109,109,110,111,112,113,113,114,115,116,117,117,
118,119,120,121,121,122,123,124,125,126,126,127,128,129,130,131,131,132,133,134,135,136,136,137,138,139,140,141,141,142,143,144,
145,146,147,147,148,149,150,151,152,153,153,154,155,156,157,158,159,159,160,161,162,163,164,165,165,166,167,168,169,170,171,171,
172,173,174,175,176,176,177,178,179,180,181,181,182,183,184,185,186,186,187,188,189,190,190,191,192,193,194,194,195,196,197,198,
198,199,200,201,201,202,203,204,204,205,206,207,207,208,209,210,210,211,212,212,213,214,215,215,216,217,217,218,219,219,220,221,
221,222,223,223,224,224,225,226,226,227,227,228,229,229,230,230,231,232,232,233,233,234,234,235,235,236,236,237,237,238,238,239,
239,240,240,241,241,241,242,242,243,243,244,244,244,245,245,245,246,246,247,247,247,248,248,248,248,249,249,249,250,250,250,250,
251,251,251,251,252,252,252,252,252,253,253,253,253,253,253,253,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,255,
255,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,253,253,253,253,253,253,253,252,252,252,252,252,251,251,251,251,
250,250,250,250,249,249,249,248,248,248,248,247,247,247,246,246,245,245,245,244,244,244,243,243,242,242,241,241,241,240,240,239,
239,238,238,237,237,236,236,235,235,234,234,233,233,232,232,231,230,230,229,229,228,227,227,226,226,225,224,224,223,223,222,221,
221,220,219,219,218,217,217,216,215,215,214,213,212,212,211,210,210,209,208,207,207,206,205,204,204,203,202,201,201,200,199,198,
198,197,196,195,194,194,193,192,191,190,190,189,188,187,186,186,185,184,183,182,181,181,180,179,178,177,176,176,175,174,173,172,
171,171,170,169,168,167,166,165,165,164,163,162,161,160,159,159,158,157,156,155,154,153,153,152,151,150,149,148,147,147,146,145,
144,143,142,141,141,140,139,138,137,136,136,135,134,133,132,131,131,130,129,128,127,126,126,125,124,123,122,121,121,120,119,118,
117,117,116,115,114,113,113,112,111,110,109,109,108,107,106,105,105,104,103,102,102,101,100,99,99,98,97,96,96,95,94,93,
};

 
ft_void_t BitMapTransform(int dir, int w, int h)
{
  if (dir == 0) {
	  Ft_Gpu_CoCmd_BitmapTransform(Ft_Esd_Host, 0, 0, w, 0, 0, h, 0, 0, 511, 0, 0, 511, 0);
  } else {
	  Ft_Gpu_CoCmd_BitmapTransform(Ft_Esd_Host, 0, 0, w, 0, 0, h, 0, 0, 0, 511, 511, 0, 0);
  }
}

ft_void_t writeBitmapIntoGPUMemory(Esd_CircularGradientType gradientType)
{
	if (gradientType == ESD_PYTHAGOREAN){
		pythagGpuHandle = Ft_Esd_GpuAlloc_Alloc(Ft_Esd_GAlloc, BITMAP_TOTAL_SIZE, GA_GC_FLAG);
		pythag_bitmapAddr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, pythagGpuHandle);  

		Ft_Gpu_Hal_WrCmd32_Direct(Ft_Esd_Host, CMD_MEMWRITE);
		Ft_Gpu_Hal_WrCmd32_Direct(Ft_Esd_Host, pythag_bitmapAddr);
		Ft_Gpu_Hal_WrCmd32_Direct(Ft_Esd_Host, sizeof(pythag_raw));
	
		Ft_Gpu_Hal_WrCmdBuf(Ft_Esd_Host,pythag_raw, sizeof(pythag_raw));
	} else {
	    gaussGpuHandle = Ft_Esd_GpuAlloc_Alloc(Ft_Esd_GAlloc, BITMAP_TOTAL_SIZE, GA_GC_FLAG);
        gauss_bitmapAddr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, gaussGpuHandle);  

        Ft_Gpu_Hal_WrCmd32_Direct(Ft_Esd_Host, CMD_MEMWRITE);
        Ft_Gpu_Hal_WrCmd32_Direct(Ft_Esd_Host, gauss_bitmapAddr);
        Ft_Gpu_Hal_WrCmd32_Direct(Ft_Esd_Host, sizeof(gauss_raw));
		
        Ft_Gpu_Hal_WrCmdBuf(Ft_Esd_Host,gauss_raw, sizeof(gauss_raw));	
	}
}

ESD_METHOD(Circular_Gradient_Widget_Render_Circular, Context = Ft_Esd_CircularGradient)
ESD_PARAMETER(x0, Type = ft_int32_t, Default = 0)
ESD_PARAMETER(y0, Type = ft_int32_t, Default = 0)
ESD_PARAMETER(x1, Type = ft_int32_t, Default = 60)
ESD_PARAMETER(y1, Type = ft_int32_t, Default = 20)
ESD_PARAMETER(color1, Type = ft_argb32_t, DisplayName = "outer color", Default = #FF3F3F3F)
ESD_PARAMETER(color2, Type = ft_argb32_t, DisplayName = "inner color", Default = #FFFFFFFF)
ESD_PARAMETER(gradientType, Type = Esd_CircularGradientType, DisplayName = "gradient type", Default = ESD_PYTHAGOREAN)
ft_void_t Circular_Gradient_Widget_Render_Circular(Ft_Esd_CircularGradient *context,
				ft_int32_t x0, ft_int32_t y0, 
				ft_int32_t x1, ft_int32_t y1,
				ft_argb32_t color1, ft_argb32_t color2,
				Esd_CircularGradientType gradientType)
{   
	int handle 	= FT_ESD_SCRATCHHANDLE;
	int w 		= x1 - x0;
	int h 		= y1 - y0;
	ft_int32_t X0 	= x0 * 16; 
	ft_int32_t X1 	= x1 * 16;
	ft_int32_t Y0 	= y0 * 16;
	ft_int32_t Y1 	= y1 * 16;

	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_HANDLE(handle));
		
	if (gradientType == ESD_PYTHAGOREAN){
		pythag_bitmapAddr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, pythagGpuHandle);  
		if (pythag_bitmapAddr == 0xFFFFFFFF) {
			writeBitmapIntoGPUMemory(gradientType);
		}	
		Ft_Gpu_CoCmd_SetBitmap(Ft_Esd_Host, pythag_bitmapAddr, L8, BITMAP_WIDTH, BITMAP_HEIGHT );
	} else {
		gauss_bitmapAddr = Ft_Esd_GpuAlloc_Get(Ft_Esd_GAlloc, gaussGpuHandle);   
		if (gauss_bitmapAddr == 0xFFFFFFFF) {
			writeBitmapIntoGPUMemory(gradientType);
		}
    	Ft_Gpu_CoCmd_SetBitmap(Ft_Esd_Host, gauss_bitmapAddr, L8, BITMAP_WIDTH, BITMAP_HEIGHT );
	}
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SIZE(BILINEAR, REPEAT, REPEAT, w & 0x1FF, h & 0x1FF));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_SIZE_H( w >> 9, h >> 9));
		
	// The code below will do the circular gradient
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SAVE_CONTEXT());
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BEGIN(BITMAPS));

	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SCISSOR_XY(x0, y0));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SCISSOR_SIZE(w, h));

	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, COLOR_MASK(0, 0, 0, 1));   	    	// Only touch the alpha channel
	
	Ft_Esd_Dl_BITMAP_HANDLE(handle);									// At any instant only one bitmap is loaded in memory. 
																		// Hence we use only one Bitmap Handle. By default it is starting with zero (0)

	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BLEND_FUNC(ONE, ZERO));         	// Draw the X bitmap into alpha
	BitMapTransform(0, w, h);
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2F(X0, Y0));

	if (gradientType == ESD_PYTHAGOREAN)									
		Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BLEND_FUNC(ONE, ONE));       	// For pythagorean, want alpha addition
	else
		Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BLEND_FUNC(DST_ALPHA, ZERO)); 	// But for Gaussian, multiplication
	BitMapTransform(1, w, h);                   						// Blend the Y bitmap into alpha
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2F(X0, Y0));

	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, COLOR_MASK(1, 1, 1, 0));          	// Now use the alpha buffer
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BEGIN(RECTS));

	Ft_Esd_Dl_COLOR_RGB(color1);
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BLEND_FUNC(ONE, ZERO));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2F(X0, Y0));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2F(X1, Y1));

	Ft_Esd_Dl_COLOR_RGB(color2);
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BLEND_FUNC(DST_ALPHA, ONE_MINUS_DST_ALPHA));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2F(X0, Y0));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX2F(X1, Y1));
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, RESTORE_CONTEXT());
}


