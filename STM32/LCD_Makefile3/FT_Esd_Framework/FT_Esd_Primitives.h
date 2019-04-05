
#ifndef FT_ESD_PRIMITIVES_H
#define FT_ESD_PRIMITIVES_H

#include "Ft_Esd.h"
#include "Ft_Esd_Dl.h"
#include "Ft_Esd_Theme.h"
#include "Ft_Esd_DefaultTheme.h"
#include "Ft_Esd_BitmapInfo.h"
#include "Ft_Esd_Math.h"

// Ft_Esd_Render_Rectangle
// Ft_Esd_Render_Line
// Ft_Esd_Render_Point
// Ft_Esd_Render_Bitmap
// Ft_Esd_Render_LineStrip
// Ft_Esd_Render_EdgeStrip

ESD_CATEGORY(EsdElements, DisplayName = "Elements", Category = EsdRenderable)
ESD_CATEGORY(EsdPrimitives, DisplayName = "Primitives", Category = EsdRenderable)

ESD_CATEGORY(EsdBasicWidegts, DisplayName = "Basics", Category = EsdWidgets)


// A function to combine RGB channel with 8 bit Alpha channel data into 32 bit integer data
ESD_FUNCTION(Ft_Esd_ColorARGB_Combine, Type = ft_argb32_t, DisplayName = "Color A+RGB Combine", Category = EsdUtilities, Inline)
ESD_PARAMETER(rgb, Type = ft_rgb32_t, Default = #FFFFFF)
ESD_PARAMETER(a, Type = ft_uint8_t, Default = 255)
static inline ft_argb32_t Ft_Esd_ColorARGB_Combine(ft_rgb32_t rgb, ft_uint8_t a)
{ return (rgb & 0xFFFFFF) | (((ft_argb32_t)a) << 24); }

// Basic bitmap rendering
ESD_RENDER(Ft_Esd_Render_Bitmap, Type = ft_void_t, DisplayName = "ESD Bitmap", Category = EsdPrimitives, Icon = ":/icons/image.png", Include = "FT_Esd_Primitives.h")
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0)
ESD_PARAMETER(bitmapCell, Type = Ft_Esd_BitmapCell, DisplayName = "Bitmap Cell")
// Color to be multiplied with bitmap color, can be used for alpha fade for example
ESD_PARAMETER(c, Type = ft_argb32_t, DisplayName = "Color", Default = #FFFFFFFF)
ft_void_t Ft_Esd_Render_Bitmap(ft_int16_t x, ft_int16_t y, Ft_Esd_BitmapCell bitmapCell, ft_argb32_t c);

// Scaled bitmap rendering
ESD_RENDER(Ft_Esd_Render_BitmapScaled, Type = ft_void_t, DisplayName = "ESD Bitmap Scaled", Category = EsdPrimitives, Icon = ":/icons/image.png", Include = "FT_Esd_Primitives.h")
ESD_PARAMETER(x, Type = ft_int16_t, Default = 0)
ESD_PARAMETER(y, Type = ft_int16_t, Default = 0)
ESD_PARAMETER(bitmapCell, Type = Ft_Esd_BitmapCell, DisplayName = "Bitmap Cell")
// Color to be multiplied with bitmap color, can be used for alpha fade for example
ESD_PARAMETER(c, Type = ft_argb32_t, DisplayName = "Color", Default = #FFFFFFFF)
// Horizontal scaling factor
ESD_PARAMETER(xscale, Type = ft_int32_f16_t, DisplayName = "Horizontal Scale", Default = 1)
// Vertical scaling factor
ESD_PARAMETER(yscale, Type = ft_int32_f16_t, DisplayName = "Vertical Scale", Default = 1)
// Horizontal offset
ESD_PARAMETER(xoffset, Type = ft_int32_f16_t, DisplayName = "X Offset", Default = 0)
// Vertical offset
ESD_PARAMETER(yoffset, Type = ft_int32_f16_t, DisplayName = "Y Offset", Default = 0)
// Width used as rendering boundary
ESD_PARAMETER(width, Type = ft_int16_t, DisplayName = "Render Width", Default = 200)
// Height used as rendering boundary
ESD_PARAMETER(height, Type = ft_int16_t, DisplayName = "Render Height", Default = 100)
ft_void_t Ft_Esd_Render_BitmapScaled(ft_int16_t x, ft_int16_t y, Ft_Esd_BitmapCell bitmapCell, ft_argb32_t c, ft_int32_f16_t xscale, ft_int32_f16_t yscale, ft_int32_f16_t xoffset, ft_int32_f16_t yoffset, ft_int16_t width, ft_int16_t height);

// Render bitmap using freeform rectangle within a specified global screen rectangle, freeform is relative to global
ft_void_t Ft_Esd_Render_BitmapFreeform(Ft_Esd_BitmapCell bitmapCell, ft_argb32_t c, Ft_Esd_Rect16 globalRect, Ft_Esd_Rect16 freeformRect, ft_uint8_t minAlpha);

//Render bitmap with rotation option
ft_void_t Ft_Esd_Render_BitmapRotate(Ft_Esd_BitmapCell bitmapCell, ft_argb32_t c, Ft_Esd_Rect16 globalRect, ft_int32_t rotateAngle);



// Basic rectangle Gradient rendering with fixed point precision
ESD_RENDER(Ft_Esd_Render_RectangleF_Gradient, Type = ft_void_t, DisplayName = "ESD Gradient Rectangle (Fixed Point)", Include = "FT_Esd_Primitives.h", Category = EsdPrimitives)
ESD_PARAMETER(x, Type = ft_int32_f4_t, Default = 0)
ESD_PARAMETER(y, Type = ft_int32_f4_t, Default = 0)
ESD_PARAMETER(width, Type = ft_int32_f4_t, Default = 60)
ESD_PARAMETER(height, Type = ft_int32_f4_t, Default = 20)
ESD_PARAMETER(color1, Type = ft_argb32_t, DisplayName = "color1", Default = #FF3F3F3F)
ESD_PARAMETER(color2, Type = ft_argb32_t, DisplayName = "color2", Default = #FFFFFFFF)
ESD_PARAMETER(direction, Type = ft_int16_t, DisplayName = "direction", Default = 90)
ft_void_t Ft_Esd_Render_RectangleF_Gradient(ft_int32_f4_t x, ft_int32_f4_t y, ft_int32_f4_t w, ft_int32_f4_t h, ft_argb32_t color1, ft_argb32_t color2, ft_int16_t direction);

// Basic rectangle Gradient rendering
ESD_RENDER(Ft_Esd_Render_Rectangle_Gradient, Type = ft_void_t, DisplayName = "ESD Gradient Rectangle (Integer)", Include = "FT_Esd_Primitives.h", Category = EsdPrimitives, Inline)
ESD_PARAMETER(x, Type = ft_int32_t, Default = 0)
ESD_PARAMETER(y, Type = ft_int32_t, Default = 0)
ESD_PARAMETER(width, Type = ft_int32_t, Default = 60)
ESD_PARAMETER(height, Type = ft_int32_t, Default = 20)
ESD_PARAMETER(color1, Type = ft_argb32_t, DisplayName = "color1", Default = #FF3F3F3F)
ESD_PARAMETER(color2, Type = ft_argb32_t, DisplayName = "color2", Default = #FFFFFFFF)
ESD_PARAMETER(direction, Type = ft_int16_t, DisplayName = "direction", Default = 90)
static inline ft_void_t Ft_Esd_Render_Rectangle_Gradient(ft_int32_t x, ft_int32_t y, ft_int32_f4_t w, ft_int32_f4_t h, ft_argb32_t color1, ft_argb32_t color2, ft_int16_t direction)
{ Ft_Esd_Render_RectangleF_Gradient(x << 4, y << 4, w << 4, h << 4, color1, color2, direction); }




// Basic rectangle rendering with fixed point precision
ESD_RENDER(Ft_Esd_Render_RectangleF, Type = ft_void_t, DisplayName = "ESD Rectangle (Fixed Point)", Include = "FT_Esd_Primitives.h", Category = EsdPrimitives)
ESD_PARAMETER(x, Type = ft_int32_f4_t, Default = 0)
ESD_PARAMETER(y, Type = ft_int32_f4_t, Default = 0)
ESD_PARAMETER(width, Type = ft_int32_f4_t, Default = 60)
ESD_PARAMETER(height, Type = ft_int32_f4_t, Default = 20)
ESD_PARAMETER(radius, Type = ft_int32_f4_t, Default = 4)
ESD_PARAMETER(color, Type = ft_argb32_t, DisplayName = "Color", Default = #FFFFFFFF)
ft_void_t Ft_Esd_Render_RectangleF(ft_int32_f4_t x, ft_int32_f4_t y, ft_int32_f4_t w, ft_int32_f4_t h, ft_int32_f4_t radius, ft_argb32_t color);

// Basic rectangle rendering
ESD_RENDER(Ft_Esd_Render_Rectangle, Type = ft_void_t, DisplayName = "ESD Rectangle (Integer)", Include = "FT_Esd_Primitives.h", Category = EsdPrimitives, Inline)
ESD_PARAMETER(x, Type = ft_int32_t, Default = 0)
ESD_PARAMETER(y, Type = ft_int32_t, Default = 0)
ESD_PARAMETER(width, Type = ft_int32_t, Default = 60)
ESD_PARAMETER(height, Type = ft_int32_t, Default = 20)
ESD_PARAMETER(radius, Type = ft_int32_t, Default = 4)
ESD_PARAMETER(color, Type = ft_argb32_t, DisplayName = "Color", Default = #FFFFFFFF)
static inline ft_void_t Ft_Esd_Render_Rectangle(ft_int32_t x, ft_int32_t y, ft_int32_f4_t w, ft_int32_f4_t h, ft_int32_f4_t radius, ft_argb32_t color)
{ Ft_Esd_Render_RectangleF(x << 4, y << 4, w << 4, h << 4, radius << 4, color); }

// Basic line rendering with fixed point precision
ESD_RENDER(Ft_Esd_Render_LineF, Type = ft_void_t, DisplayName = "ESD Line (Fixed Point)", Include = "FT_Esd_Primitives.h", Category = EsdPrimitives)
ESD_PARAMETER(x0, Type = ft_int32_f4_t, Default = 0)
ESD_PARAMETER(y0, Type = ft_int32_f4_t, Default = 0)
ESD_PARAMETER(x1, Type = ft_int32_f4_t, Default = 60)
ESD_PARAMETER(y1, Type = ft_int32_f4_t, Default = 20)
ESD_PARAMETER(width, Type = ft_int32_f3_t, Default = 2, EditRole = None)
ESD_PARAMETER(color, Type = ft_argb32_t, DisplayName = "Color", Default = #FFFFFFFF)
ft_void_t Ft_Esd_Render_LineF(ft_int32_f4_t x0, ft_int32_f4_t y0, ft_int32_f4_t x1, ft_int32_f4_t y1, ft_int32_f3_t width, ft_argb32_t color);

// Basic line rendering
ESD_RENDER(Ft_Esd_Render_Line, Type = ft_void_t, DisplayName = "ESD Line (Integer)", Include = "FT_Esd_Primitives.h", Category = EsdPrimitives, Inline)
ESD_PARAMETER(x0, Type = ft_int32_t, Default = 0)
ESD_PARAMETER(y0, Type = ft_int32_t, Default = 0)
ESD_PARAMETER(x1, Type = ft_int32_t, Default = 60)
ESD_PARAMETER(y1, Type = ft_int32_t, Default = 20)
ESD_PARAMETER(width, Type = ft_int32_t, Default = 4, EditRole = None)
ESD_PARAMETER(color, Type = ft_argb32_t, DisplayName = "Color", Default = #FFFFFFFF)
static inline ft_void_t Ft_Esd_Render_Line(ft_int32_t x0, ft_int32_t y0, ft_int32_t x1, ft_int32_t y1, ft_int32_t width, ft_argb32_t color)
{ Ft_Esd_Render_LineF(x0 << 4, y0 << 4, x1 << 4, y1 << 4, width << 3, color); }

// Get scaled size
Ft_Esd_Size16 Ft_Esd_Primitive_GetScaledSize(Ft_Esd_Size16 boundary, Ft_Esd_Size16 original, ft_uint8_t scaling);

// Get alignment position
Ft_Esd_Rect16 Ft_Esd_Primitive_GetAlignedRect(Ft_Esd_Size16 boundary, Ft_Esd_Size16 size, ft_uint8_t align);

#endif /* #ifndef FT_ESD_PRIMITIVES_H */

/* Nothing beyond this */
