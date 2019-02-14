
#ifndef FT_ESD_DL_H
#define FT_ESD_DL_H

#include "FT_DataTypes.h"
#include "FT_Platform.h"
#include "Ft_Esd.h"
#include "FT_Gpu.h"
#include "Ft_Esd_BitmapInfo.h"

ESD_CATEGORY(EsdUtilities, DisplayName = "ESD Utilities")
ESD_CATEGORY(EveRenderFunctions, DisplayName = "EVE Render Functions")

ESD_TYPE(Ft_Gpu_Hal_Context_t *, Native = Pointer, Edit = Library)

// Keep cache of displaylist values that don't often change but are generally set by every widget to reduce display list size
#define FT_ESD_OPTIMIZE_DISPLAYLIST 1
#define FT_ESD_STATE_STACK_SIZE 5

#define FT_ESD_BITMAPHANDLE_INVALID 255

//
// Structs
//
#ifdef FT_ESD_OPTIMIZE_DISPLAYLIST
#define FT_ESD_STATE Ft_Esd_GpuState[Ft_Esd_GpuState_I]
typedef struct
{
	// Keep to a minimum
#ifdef FT_81X_ENABLE
	ft_uint32_t PaletteSource;
#endif
	ft_uint32_t ColorRGB;
	ft_uint8_t ColorA;
	ft_uint8_t Handle;         // Current handle
	ft_uint8_t Cell;           // Current cell
	ft_bool_t BitmapTransform; // BitmapTransform other than default is set
#ifdef FT_81X_ENABLE
	ft_uint8_t VertexFormat;   // Current vertex format
#endif
} Ft_Esd_GpuState_T;
#endif

//
// Globals
//
extern Ft_Gpu_Hal_Context_t *Ft_Esd_Host;
extern ft_uint16_t Ft_Esd_FontHeight[32];
#ifdef FT_ESD_OPTIMIZE_DISPLAYLIST
extern Ft_Esd_GpuState_T Ft_Esd_GpuState[FT_ESD_STATE_STACK_SIZE];
extern ft_uint8_t Ft_Esd_GpuState_I;
extern ft_uint32_t Ft_Esd_CoFgColor;
extern ft_uint32_t Ft_Esd_CoBgColor;
#endif

//Get the height of builtin font
ESD_FUNCTION(Ft_Esd_GetFontHeight, Type = ft_uint16_t ,DisplayName = "Get Font Height", Category = EsdUtilities, Macro)
ESD_PARAMETER(i, Type = int, DisplayName = "Bitmap Handle", Default = 0, Min = 0, Max = 31)
// inline static ft_uint16_t Ft_Esd_GetFontHeight(int i) { return Ft_Esd_FontHeight[i]; }
#define Ft_Esd_GetFontHeight(i) (Ft_Esd_FontHeight[i]);

// Reset any cached state
void Ft_Esd_ResetGpuState();
void Ft_Esd_ResetCoState();

ft_uint32_t Ft_Esd_BitmapHandle_GetTotalUsed();
ft_uint32_t Ft_Esd_BitmapHandle_GetTotal();

/// Set current tag. Must be returned to 255 after usage, to ensure next widgets don't draw with invalid tag
ESD_FUNCTION(Ft_Esd_Dl_TAG, Type = ft_void_t, Category = EveRenderFunctions, Inline)
ESD_PARAMETER(s, Type = ft_uint8_t, DisplayName = "Tag", Default = 255, Min = 0, Max = 255)
inline static ft_void_t Ft_Esd_Dl_TAG(ft_uint8_t s)
{
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, TAG(s));
}
//Specify color RGB
ESD_FUNCTION(Ft_Esd_Dl_COLOR_RGB, Type = ft_void_t, Category = EveRenderFunctions, Inline)
ESD_PARAMETER(c, Type = ft_rgb32_t, DisplayName = "Color")
inline static ft_void_t Ft_Esd_Dl_COLOR_RGB(ft_rgb32_t c)
{
#if FT_ESD_OPTIMIZE_DISPLAYLIST
	ft_rgb32_t rgb = c & 0xFFFFFF;
	if (rgb != FT_ESD_STATE.ColorRGB)
	{
#endif
		Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, (4UL << 24) | (rgb));
#if FT_ESD_OPTIMIZE_DISPLAYLIST
		FT_ESD_STATE.ColorRGB = rgb;
	}
#endif
}
//Specify alpha channel
ESD_FUNCTION(Ft_Esd_Dl_COLOR_A, Type = ft_void_t, Category = EveRenderFunctions, Inline)
ESD_PARAMETER(alpha, Type = ft_uint8_t, Default = 255, Min = 0, Max = 255)
inline static ft_void_t Ft_Esd_Dl_COLOR_A(ft_uint8_t alpha)
{
#if FT_ESD_OPTIMIZE_DISPLAYLIST
	if (alpha != FT_ESD_STATE.ColorA)
	{
#endif
		Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, COLOR_A(alpha));
#if FT_ESD_OPTIMIZE_DISPLAYLIST
		FT_ESD_STATE.ColorA = alpha;
	}
#endif
}

//Specify color: Alpha(31~24 bit) + RGB(23~0 bit)
ESD_FUNCTION(Ft_Esd_Dl_COLOR_ARGB, Type = ft_void_t, Category = EveRenderFunctions, Inline)
ESD_PARAMETER(c, Type = ft_argb32_t, DisplayName = "Color")
inline static ft_void_t Ft_Esd_Dl_COLOR_ARGB(ft_uint32_t c)
{
	Ft_Esd_Dl_COLOR_RGB(c);
	Ft_Esd_Dl_COLOR_A(c >> 24);
}
//Specify bitmap handle, see BITMAP_HANDLE
ESD_FUNCTION(Ft_Esd_Dl_BITMAP_HANDLE, Type = ft_void_t, Category = EveRenderFunctions, Inline)
ESD_PARAMETER(handle, Type = ft_uint8_t, Min = 0, Max = 31)
inline static ft_void_t Ft_Esd_Dl_BITMAP_HANDLE(ft_uint8_t handle)
{
#if FT_ESD_OPTIMIZE_DISPLAYLIST
	if (handle != FT_ESD_STATE.Handle)
	{
#endif
		Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, BITMAP_HANDLE(handle));
#if FT_ESD_OPTIMIZE_DISPLAYLIST
		FT_ESD_STATE.Handle = handle;
	}
#endif
}

//Specify cell number for bitmap, see CELL 
ESD_FUNCTION(Ft_Esd_Dl_CELL, Type = ft_void_t, Category = EveRenderFunctions, Inline)
ESD_PARAMETER(cell, Type = ft_uint8_t, Min = 0, Max = 255)
inline static ft_void_t Ft_Esd_Dl_CELL(ft_uint8_t cell)
{
#if FT_ESD_OPTIMIZE_DISPLAYLIST
	if (cell != FT_ESD_STATE.Cell)
	{
#endif
		Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, CELL(cell));
#if FT_ESD_OPTIMIZE_DISPLAYLIST
		FT_ESD_STATE.Cell = cell;
	}
#endif
}
//Save EVE context, see SAVE_CONTEXT
ESD_FUNCTION(Ft_Esd_Dl_SAVE_CONTEXT, Type = ft_void_t, Category = EveRenderFunctions, Inline)
inline static ft_void_t Ft_Esd_Dl_SAVE_CONTEXT()
{
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, SAVE_CONTEXT());
#if FT_ESD_OPTIMIZE_DISPLAYLIST
	ft_uint8_t nextState = Ft_Esd_GpuState_I + 1;
	if (nextState < FT_ESD_STATE_STACK_SIZE)
	{
		Ft_Esd_GpuState[nextState] = Ft_Esd_GpuState[Ft_Esd_GpuState_I];
		Ft_Esd_GpuState_I = nextState;
	}
#endif
}
//Restore EVE context, see RESTORE_CONTEXT
ESD_FUNCTION(Ft_Esd_Dl_RESTORE_CONTEXT, Type = ft_void_t, Category = EveRenderFunctions, Inline)
inline static ft_void_t Ft_Esd_Dl_RESTORE_CONTEXT()
{
	Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, RESTORE_CONTEXT());
#if FT_ESD_OPTIMIZE_DISPLAYLIST
	if (Ft_Esd_GpuState_I > 0)
		--Ft_Esd_GpuState_I;
#endif
}

//Specify vertex format , see VERTEX_FORMAT command
ESD_FUNCTION(Ft_Esd_Dl_VERTEX_FORMAT, Type = ft_void_t, Category = EveRenderFunctions, Inline)
ESD_PARAMETER(frac, Type = ft_uint8_t, Min = 0, Max = 4)
inline static ft_void_t Ft_Esd_Dl_VERTEX_FORMAT(ft_uint8_t frac)
{
#if FT_ESD_OPTIMIZE_DISPLAYLIST
	if (frac != FT_ESD_STATE.VertexFormat)
	{
#endif
		Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, VERTEX_FORMAT(frac));
#if FT_ESD_OPTIMIZE_DISPLAYLIST
		FT_ESD_STATE.VertexFormat = frac;
	}
#endif
}

//Specify vertex format , see VERTEX_FORMAT command
ESD_FUNCTION(Ft_Esd_Dl_PALETTE_SOURCE, Type = ft_void_t, Category = EveRenderFunctions, Inline)
ESD_PARAMETER(addr, Type = ft_uint32_t, Min = 0)
inline static ft_void_t Ft_Esd_Dl_PALETTE_SOURCE(ft_uint32_t addr)
{
#if FT_ESD_OPTIMIZE_DISPLAYLIST
	if (addr != FT_ESD_STATE.PaletteSource)
	{
#endif
		Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, PALETTE_SOURCE(addr));
#if FT_ESD_OPTIMIZE_DISPLAYLIST
		FT_ESD_STATE.PaletteSource = addr;
	}
#endif
}

// Prepares a valid handle for a bitmap. Call during render to get bitmap handle. Does not necessarily call BITMAP_HANDLE
ESD_FUNCTION(Ft_Esd_Dl_Bitmap_Setup, Type = ft_uint8_t, DisplayName = "Ft_Esd_Dl_Bitmap_Setup", Category = EveRenderFunctions)
ESD_PARAMETER(bitmapInfo, Type = Ft_Esd_BitmapInfo *)
ft_uint8_t Ft_Esd_Dl_Bitmap_Setup(Ft_Esd_BitmapInfo *bitmapInfo);

void Ft_Esd_Dl_Bitmap_WidthHeight(ft_uint8_t handle, ft_uint16_t width, ft_uint16_t height);
void Ft_Esd_Dl_Bitmap_WidthHeightReset(ft_uint8_t handle);

//Specify line width in subpixel format
ESD_FUNCTION(Ft_Esd_Dl_LINE_WIDTH, Type = ft_void_t, Category = EveRenderFunctions, Inline)
ESD_PARAMETER(width, Type = ft_int32_f4_t)
inline static ft_void_t Ft_Esd_Dl_LINE_WIDTH(ft_int32_f4_t width) { Ft_Gpu_Hal_WrCmd32(Ft_Esd_Host, LINE_WIDTH(width)); }

/*

#define POINT_SIZE(size) ((13UL<<24)|(((size)&8191UL)<<0))
#define VERTEX2F(x,y) ((1UL<<30)|(((x)&32767UL)<<15)|(((y)&32767UL)<<0))
#define VERTEX2II(x,y,handle,cell) ((2UL<<30)|(((x)&511UL)<<21)|(((y)&511UL)<<12)|(((handle)&31UL)<<7)|(((cell)&127UL)<<0))
#define ALPHA_FUNC(func,ref) ((9UL<<24)|(((func)&7UL)<<8)|(((ref)&255UL)<<0))
#define STENCIL_FUNC(func,ref,mask) ((10UL<<24)|(((func)&7UL)<<16)|(((ref)&255UL)<<8)|(((mask)&255UL)<<0))
#define BLEND_FUNC(src,dst) ((11UL<<24)|(((src)&7UL)<<3)|(((dst)&7UL)<<0))
#define STENCIL_OP(sfail,spass) ((12UL<<24)|(((sfail)&7UL)<<3)|(((spass)&7UL)<<0))
#define CLEAR_COLOR_A(alpha) ((15UL<<24)|(((alpha)&255UL)<<0))
#define COLOR_A(alpha) ((16UL<<24)|(((alpha)&255UL)<<0))
#define CLEAR_STENCIL(s) ((17UL<<24)|(((s)&255UL)<<0))
#define CLEAR_TAG(s) ((18UL<<24)|(((s)&255UL)<<0))
#define STENCIL_MASK(mask) ((19UL<<24)|(((mask)&255UL)<<0))
#define TAG_MASK(mask) ((20UL<<24)|(((mask)&1UL)<<0))
#define BITMAP_TRANSFORM_A(a) ((21UL<<24)|(((a)&131071UL)<<0))
#define BITMAP_TRANSFORM_B(b) ((22UL<<24)|(((b)&131071UL)<<0))
#define BITMAP_TRANSFORM_C(c) ((23UL<<24)|(((c)&16777215UL)<<0))
#define BITMAP_TRANSFORM_D(d) ((24UL<<24)|(((d)&131071UL)<<0))
#define BITMAP_TRANSFORM_E(e) ((25UL<<24)|(((e)&131071UL)<<0))
#define BITMAP_TRANSFORM_F(f) ((26UL<<24)|(((f)&16777215UL)<<0))
#define SCISSOR_XY(x,y) ((27UL<<24)|(((x)&2047UL)<<11)|(((y)&2047UL)<<0))
#define SCISSOR_SIZE(width,height) ((28UL<<24)|(((width)&4095UL)<<12)|(((height)&4095UL)<<0))
#define CALL(dest) ((29UL<<24)|(((dest)&65535UL)<<0))
#define JUMP(dest) ((30UL<<24)|(((dest)&65535UL)<<0))
#define BEGIN(prim) ((31UL<<24)|(((prim)&15UL)<<0))
#define COLOR_MASK(r,g,b,a) ((32UL<<24)|(((r)&1UL)<<3)|(((g)&1UL)<<2)|(((b)&1UL)<<1)|(((a)&1UL)<<0))
#define CLEAR(c,s,t) ((38UL<<24)|(((c)&1UL)<<2)|(((s)&1UL)<<1)|(((t)&1UL)<<0))
#define VERTEX_FORMAT(frac) ((39UL<<24)|(((frac)&7UL)<<0))
#define BITMAP_LAYOUT_H(linestride,height) ((40UL<<24)|(((linestride)&3UL)<<2)|(((height)&3UL)<<0))
#define BITMAP_SIZE_H(width,height) ((41UL<<24)|(((width)&3UL)<<2)|(((height)&3UL)<<0))
#define PALETTE_SOURCE(addr) ((42UL<<24)|(((addr)&4194303UL)<<0))
#define VERTEX_TRANSLATE_X(x) ((43UL<<24)|(((x)&131071UL)<<0))
#define VERTEX_TRANSLATE_Y(y) ((44UL<<24)|(((y)&131071UL)<<0))
#define NOP() ((45UL<<24))
#define END() ((33UL<<24))
#define SAVE_CONTEXT() ((34UL<<24))
#define RESTORE_CONTEXT() ((35UL<<24))
#define RETURN() ((36UL<<24))
#define MACRO(m) ((37UL<<24)|(((m)&1UL)<<0))
#define DISPLAY() ((0UL<<24))

*/


/*
ft_void_t FT_Esd_Dl_VERTEX2F(ft_int16_t x, ft_int16_t y);
ft_void_t FT_Esd_Dl_VERTEX2II(ft_uint16_t x, ft_uint16_t y, ft_uint16_t handle, ft_uint16_t cell);
ft_void_t FT_Esd_Dl_BITMAP_SOURCE(ft_uint32_t addr);

ESD_FUNCTION(FT_Esd_Dl_CLEAR_COLOR_RGB, Type = ft_void_t, Include = "FT_Esd_Dl.h")
ESD_PARAMETER(c, Type = ft_uint32_t, EditType = Color)
ft_void_t FT_Esd_Dl_CLEAR_COLOR_RGB(ft_uint32_t c);

// ft_void_t FT_Esd_Dl_BITMAP_LAYOUT(ft_uint16_t format, ft_uint16_t linestride, ft_uint16_t height);
// ft_void_t FT_Esd_Dl_BITMAP_SIZE(ft_uint16_t filter, ft_uint16_t wrapx, ft_uint16_t wrapy, ft_uint16_t width, ft_uint16_t height);

ft_void_t FT_Esd_Dl_ALPHA_FUNC(ft_uint16_t func, ft_uint16_t ref);
ft_void_t FT_Esd_Dl_STENCIL_FUNC(ft_uint16_t func, ft_uint16_t ref, ft_uint16_t mask);
ft_void_t FT_Esd_Dl_BLEND_FUNC(ft_uint16_t src, ft_uint16_t dst);
ft_void_t FT_Esd_Dl_STENCIL_OP(ft_uint16_t sfail, ft_uint16_t spass);
ft_void_t FT_Esd_Dl_POINT_SIZE(ft_uint16_t size);
ft_void_t FT_Esd_Dl_LINE_WIDTH(ft_uint16_t width);

ft_void_t FT_Esd_Dl_CLEAR_STENCIL(ft_uint8_t s);
ft_void_t FT_Esd_Dl_CLEAR_TAG(ft_uint8_t s);
ft_void_t FT_Esd_Dl_STENCIL_MASK(ft_uint32_t mask);
ft_void_t FT_Esd_Dl_TAG_MASK(ft_uint32_t mask);
ft_void_t FT_Esd_Dl_BITMAP_TRANSFORM_A(ft_uint32_t a);
ft_void_t FT_Esd_Dl_BITMAP_TRANSFORM_B(ft_uint32_t b);
ft_void_t FT_Esd_Dl_BITMAP_TRANSFORM_C(ft_uint32_t c);
ft_void_t FT_Esd_Dl_BITMAP_TRANSFORM_D(ft_uint32_t d);
ft_void_t FT_Esd_Dl_BITMAP_TRANSFORM_E(ft_uint32_t e);
ft_void_t FT_Esd_Dl_BITMAP_TRANSFORM_F(ft_uint32_t f);
ft_void_t FT_Esd_Dl_SCISSOR_XY(ft_uint16_t x, ft_uint16_t y);
ft_void_t FT_Esd_Dl_SCISSOR_SIZE(ft_uint16_t width, ft_uint16_t height);

// ft_void_t FT_Esd_Dl_CALL(ft_uint16_t dest);
// ft_void_t FT_Esd_Dl_JUMP(ft_uint16_t dest);

ft_void_t FT_Esd_Dl_BEGIN(ft_uint32_t prim);
ft_void_t FT_Esd_Dl_COLOR_MASK(ft_uint8_t r, ft_uint8_t g, ft_uint8_t b, ft_uint8_t a);
ft_void_t FT_Esd_Dl_CLEAR(ft_uint8_t c, ft_uint8_t s, ft_uint8_t t);
ft_void_t FT_Esd_Dl_END();

// ft_void_t FT_Esd_Dl_RETURN();

ESD_FUNCTION(FT_Esd_Dl_MACRO, Type = ft_void_t, Include = "FT_Esd_Dl.h")
ESD_PARAMETER(m, Type = ft_uint8_t, Min = 0, Max = 1)
ft_void_t FT_Esd_Dl_MACRO(ft_uint8_t m);

// ft_void_t FT_Esd_Dl_DISPLAY();
*/
//////////// old stuff below for testing compat


ESD_CATEGORY(EveRenderFunctionsProto, DisplayName = "EVE Render Functions (Prototype)", Category = _GroupHidden)
ESD_CATEGORY(EveRenderDisplayListProto, DisplayName = "Display List", Category = EveRenderFunctionsProto)
ESD_CATEGORY(EveRenderCoprocessorProto, DisplayName = "Coprocessor", Category = EveRenderFunctionsProto)

ESD_CATEGORY(EsdWidgetsProto, DisplayName = "ESD Widgets (Prototype)", Category = _GroupHidden)

ESD_FUNCTION(FT_Esd_Render_Rect, DisplayName = "Render RECT", Include = "FT_Esd_Dl.h", Category = EveRenderDisplayListProto)
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0)
ESD_PARAMETER(w, Type = ft_int16_t, Default = 60)
ESD_PARAMETER(h, Type = ft_int16_t, Default = 20)
void FT_Esd_Render_Rect(ft_int16_t x, ft_int16_t y, ft_int16_t w, ft_int16_t h);

ESD_FUNCTION(Ft_Esd_Cmd_Button, DisplayName = "cmd_button", Include = "FT_Esd_Dl.h", Category = EveRenderCoprocessorProto)
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0)
ESD_PARAMETER(w, Type = ft_int16_t, Default = 60)
ESD_PARAMETER(h, Type = ft_int16_t, Default = 20)
ESD_PARAMETER(font, Type = ft_int16_t, Default = 21)
ESD_PARAMETER(options, Type = Ft_CoPro_Opt)
ESD_PARAMETER(s, Type = const ft_char8_t *, Default = "Button")
ft_void_t Ft_Esd_Cmd_Button(ft_int16_t x, ft_int16_t y, ft_int16_t w, ft_int16_t h, ft_int16_t font, ft_uint16_t options, const ft_char8_t* s);

ESD_FUNCTION(Ft_Esd_Cmd_Number, DisplayName = "cmd_number", Include = "FT_Esd_Dl.h", Category = EveRenderCoprocessorProto)
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0)
ESD_PARAMETER(font, Type = ft_int16_t, Default = 21)
ESD_PARAMETER(options, Type = Ft_CoPro_Opt)
ESD_PARAMETER(n, Type = ft_int32_t, Default = 0)
ft_void_t Ft_Esd_Cmd_Number(ft_int16_t x, ft_int16_t y, ft_int16_t font, ft_uint16_t options, ft_int32_t n);

ESD_FUNCTION(Ft_Gpu_Hal_Rd32, Type = ft_uint32_t, Buffered, Include = "FT_Gpu_Hal.h", Category = _GroupHidden)
ESD_PARAMETER(phost, Type = Ft_Gpu_Hal_Context_t *, Default = Ft_Esd_GetHost, Hidden, Internal, Static)
ESD_PARAMETER(addr, Type = ft_uint32_t, DisplayName = "Address")

ESD_FUNCTION(Ft_Gpu_Hal_WrCmd32, Include = "FT_Gpu_Hal.h", Category = _GroupHidden)
ESD_PARAMETER(phost, Type = Ft_Gpu_Hal_Context_t *, Default = Ft_Esd_GetHost, Hidden, Internal, Static)
ESD_PARAMETER(cmd, Type = ft_uint32_t)

#endif /* #ifndef FT_ESD_DL_H */

/* end of file */
