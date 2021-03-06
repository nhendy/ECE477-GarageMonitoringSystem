/*
This file is automatically generated
Ft_Esd_Toggle
C Source
*/

#include "Ft_Esd_Toggle.h"

#include "FT_Esd_CoPro_Cmds.h"
#include "FT_Esd_Dl.h"
#include "FT_Gpu.h"

extern void Ft_Esd_Noop(void *context);
Ft_Esd_Theme * Ft_Esd_Toggle_Theme__Default(void *context) { return Ft_Esd_Theme_GetCurrent(); }
ft_int16_t Ft_Esd_Toggle_X__Default(void *context) { return 0; }
ft_int16_t Ft_Esd_Toggle_Y__Default(void *context) { return 0; }
ft_int16_t Ft_Esd_Toggle_Width__Default(void *context) { return 80; }
ft_int16_t Ft_Esd_Toggle_Height__Default(void *context) { return 36; }
ft_int16_t Ft_Esd_Toggle_Font__Default(void *context) { return 27; }
const char * Ft_Esd_Toggle_Text__Default(void *context) { return "Toggle"; }
void Ft_Esd_Toggle_Changed__Noop(void *context, ft_bool_t value) { }

Ft_Esd_Theme * Ft_Esd_Theme_GetCurrent();
Ft_Gpu_Hal_Context_t * Ft_Esd_GetHost();

static void Ft_Esd_Toggle_Touch_Tag_Tap__Signal(void *context);

void Ft_Esd_Toggle__Initializer(Ft_Esd_Toggle *context)
{
	context->Parent = 0;
	context->Theme = Ft_Esd_Toggle_Theme__Default;
	context->X = Ft_Esd_Toggle_X__Default;
	context->Y = Ft_Esd_Toggle_Y__Default;
	context->Width = Ft_Esd_Toggle_Width__Default;
	context->Height = Ft_Esd_Toggle_Height__Default;
	context->Font = Ft_Esd_Toggle_Font__Default;
	context->Text = Ft_Esd_Toggle_Text__Default;
	Ft_Esd_TouchTag__Initializer(&context->Touch_Tag);
	context->Touch_Tag.Parent = context;
	context->Touch_Tag.Tap = Ft_Esd_Toggle_Touch_Tag_Tap__Signal;
	context->Toggled = Ft_Esd_Noop;
	context->State = 0;
	context->Changed = Ft_Esd_Toggle_Changed__Noop;
}

ft_void_t Ft_Gpu_CoCmd_FgColor(Ft_Gpu_Hal_Context_t *, ft_rgb32_t);
ft_void_t Ft_Gpu_CoCmd_BgColor(Ft_Gpu_Hal_Context_t *, ft_rgb32_t);
ft_void_t Ft_Gpu_CoCmd_Toggle(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t, const ft_char8_t *);

void Ft_Esd_Toggle_Render(Ft_Esd_Toggle *context)
{
	void *parent = context->Parent;
	ft_uint8_t alpha = 255;
	Ft_Esd_Dl_COLOR_A(alpha);
	ft_uint8_t s = Ft_Esd_TouchTag_Tag(&context->Touch_Tag);
	Ft_Esd_Dl_TAG(s);
	Ft_Gpu_Hal_Context_t * phost = Ft_Esd_GetHost();
	ft_bool_t if_1 = context->State;
	ft_rgb32_t c;
	if (if_1)
	{
		Ft_Esd_Theme * theme = context->Theme(parent);
		c = Ft_Esd_Theme_GetPrimaryColor(theme);
	}
	else
	{
		Ft_Esd_Theme * theme_1 = context->Theme(parent);
		c = Ft_Esd_Theme_GetCurrentColor(theme_1);
	}
	Ft_Gpu_CoCmd_FgColor(phost, c);
	Ft_Gpu_Hal_Context_t * phost_1 = Ft_Esd_GetHost();
	Ft_Esd_Theme * theme_2 = context->Theme(parent);
	ft_rgb32_t c_1 = Ft_Esd_Theme_GetBackColor(theme_2);
	Ft_Gpu_CoCmd_BgColor(phost_1, c_1);
	Ft_Esd_Theme * theme_3 = context->Theme(parent);
	ft_rgb32_t c_2 = Ft_Esd_Theme_GetTextColor(theme_3);
	Ft_Esd_Dl_COLOR_RGB(c_2);
	Ft_Gpu_Hal_Context_t * phost_2 = Ft_Esd_GetHost();
	ft_int16_t left = context->X(parent);
	ft_int16_t i = context->Font(parent);
	ft_uint16_t left_3 = Ft_Esd_GetFontHeight(i);
	ft_int16_t right_1 = 5;
	ft_int16_t left_2 = left_3 * right_1;
	ft_int16_t right_2 = 4;
	ft_int16_t left_1 = left_2 / right_2;
	ft_int16_t right_3 = 2;
	ft_int16_t right = left_1 / right_3;
	ft_int16_t x = left + right;
	ft_int16_t left_5 = context->Y(parent);
	ft_int16_t i_1 = context->Font(parent);
	ft_uint16_t left_8 = Ft_Esd_GetFontHeight(i_1);
	ft_int16_t right_5 = 5;
	ft_int16_t left_7 = left_8 * right_5;
	ft_int16_t right_6 = 4;
	ft_int16_t left_6 = left_7 / right_6;
	ft_int16_t right_7 = 4;
	ft_int16_t right_4 = left_6 / right_7;
	ft_int16_t left_4 = left_5 + right_4;
	ft_int16_t left_10 = context->Height(parent);
	ft_int16_t i_2 = context->Font(parent);
	ft_uint16_t left_12 = Ft_Esd_GetFontHeight(i_2);
	ft_int16_t right_10 = 5;
	ft_int16_t left_11 = left_12 * right_10;
	ft_int16_t right_11 = 4;
	ft_int16_t right_9 = left_11 / right_11;
	ft_int16_t left_9 = left_10 - right_9;
	ft_int16_t right_12 = 2;
	ft_int16_t right_8 = left_9 / right_12;
	ft_int16_t y = left_4 + right_8;
	ft_int16_t left_13 = context->Width(parent);
	ft_int16_t i_3 = context->Font(parent);
	ft_uint16_t left_15 = Ft_Esd_GetFontHeight(i_3);
	ft_int16_t right_14 = 5;
	ft_int16_t left_14 = left_15 * right_14;
	ft_int16_t right_15 = 4;
	ft_int16_t right_13 = left_14 / right_15;
	ft_int16_t width = left_13 - right_13;
	ft_int16_t font = context->Font(parent);
	ft_uint16_t options = 0;
	ft_bool_t if_2 = context->State;
	ft_uint16_t state;
	if (if_2)
	{
		state = 65535U;
	}
	else
	{
		state = 0U;
	}
	const char * s_1 = context->Text(parent);
	Ft_Gpu_CoCmd_Toggle(phost_2, x, y, width, font, options, state, s_1);
	ft_uint8_t s_2 = 255;
	Ft_Esd_Dl_TAG(s_2);
}

void Ft_Esd_Toggle_Start(Ft_Esd_Toggle *context)
{
	void *parent = context->Parent;
	Ft_Esd_TouchTag_Start(&context->Touch_Tag);
}

void Ft_Esd_Toggle_Touch_Tag_Tap__Signal(void *c)
{
	Ft_Esd_Toggle *context = (Ft_Esd_Toggle *)c;
	void *parent = context->Parent;
	ft_bool_t value = context->State;
	int set_variable = !value;
	context->State = set_variable;
	context->Changed(parent, set_variable);
	context->Toggled(parent);
}

void Ft_Esd_Toggle_Update(Ft_Esd_Toggle *context)
{
	void *parent = context->Parent;
	Ft_Esd_TouchTag_Update(&context->Touch_Tag);
}

void Ft_Esd_Toggle_End(Ft_Esd_Toggle *context)
{
	void *parent = context->Parent;
	Ft_Esd_TouchTag_End(&context->Touch_Tag);
}

void Ft_Esd_Toggle_Toggle(Ft_Esd_Toggle *context)
{
	void *parent = context->Parent;
	ft_bool_t value_1 = context->State;
	int set_variable_1 = !value_1;
	context->State = set_variable_1;
	context->Changed(parent, set_variable_1);
	context->Toggled(parent);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_Toggle Instance;
	Ft_Esd_Theme * Theme;
	ft_int16_t X;
	ft_int16_t Y;
	ft_int16_t Width;
	ft_int16_t Height;
	ft_int16_t Font;
	const char * Text;
} Ft_Esd_Toggle__ESD;

Ft_Esd_Theme * Ft_Esd_Toggle__Get_Theme__ESD(void *context) { return ((Ft_Esd_Toggle__ESD *)context)->Theme; }
void Ft_Esd_Toggle__Set_Theme__ESD(void *context, Ft_Esd_Theme * value) { ((Ft_Esd_Toggle__ESD *)context)->Theme = value; }
ft_int16_t Ft_Esd_Toggle__Get_X__ESD(void *context) { return ((Ft_Esd_Toggle__ESD *)context)->X; }
void Ft_Esd_Toggle__Set_X__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Toggle__ESD *)context)->X = value; }
ft_int16_t Ft_Esd_Toggle__Get_Y__ESD(void *context) { return ((Ft_Esd_Toggle__ESD *)context)->Y; }
void Ft_Esd_Toggle__Set_Y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Toggle__ESD *)context)->Y = value; }
ft_int16_t Ft_Esd_Toggle__Get_Width__ESD(void *context) { return ((Ft_Esd_Toggle__ESD *)context)->Width; }
void Ft_Esd_Toggle__Set_Width__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Toggle__ESD *)context)->Width = value; }
ft_int16_t Ft_Esd_Toggle__Get_Height__ESD(void *context) { return ((Ft_Esd_Toggle__ESD *)context)->Height; }
void Ft_Esd_Toggle__Set_Height__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Toggle__ESD *)context)->Height = value; }
ft_int16_t Ft_Esd_Toggle__Get_Font__ESD(void *context) { return ((Ft_Esd_Toggle__ESD *)context)->Font; }
void Ft_Esd_Toggle__Set_Font__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Toggle__ESD *)context)->Font = value; }
const char * Ft_Esd_Toggle__Get_Text__ESD(void *context) { return ((Ft_Esd_Toggle__ESD *)context)->Text; }
void Ft_Esd_Toggle__Set_Text__ESD(void *context, const char * value) { ((Ft_Esd_Toggle__ESD *)context)->Text = value; }

void *Ft_Esd_Toggle__Create__ESD()
{
	Ft_Esd_Toggle__ESD *context = (Ft_Esd_Toggle__ESD *)malloc(sizeof(Ft_Esd_Toggle__ESD));
	Ft_Esd_Toggle__Initializer(&context->Instance);
	context->Instance.Parent = context;
	context->Theme = Ft_Esd_Theme_GetCurrent();
	context->Instance.Theme = Ft_Esd_Toggle__Get_Theme__ESD;
	context->X = 0;
	context->Instance.X = Ft_Esd_Toggle__Get_X__ESD;
	context->Y = 0;
	context->Instance.Y = Ft_Esd_Toggle__Get_Y__ESD;
	context->Width = 80;
	context->Instance.Width = Ft_Esd_Toggle__Get_Width__ESD;
	context->Height = 36;
	context->Instance.Height = Ft_Esd_Toggle__Get_Height__ESD;
	context->Font = 27;
	context->Instance.Font = Ft_Esd_Toggle__Get_Font__ESD;
	context->Text = "Toggle";
	context->Instance.Text = Ft_Esd_Toggle__Get_Text__ESD;
	return context;
}

void Ft_Esd_Toggle__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Toggle__Set_State__ESD(void *context, ft_bool_t value) { ((Ft_Esd_Toggle__ESD *)context)->Instance.State = value; }

#endif /* ESD_SIMULATION */

/* end of file */
