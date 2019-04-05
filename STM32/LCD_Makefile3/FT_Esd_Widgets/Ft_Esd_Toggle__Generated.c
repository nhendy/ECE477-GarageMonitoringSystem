/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_Toggle
C Source
*/

#include "Ft_Esd_Toggle.h"

#include "FT_Esd_Dl.h"
#include "FT_Gpu.h"
#include "Ft_Esd_CoCmd.h"

extern void Ft_Esd_Noop(void *context);
Ft_Esd_Theme * Ft_Esd_Toggle_Theme__Default(void *context) { return Ft_Esd_Theme_GetCurrent(); }
ft_int16_t Ft_Esd_Toggle_Font__Default(void *context) { return 27; }
const char * Ft_Esd_Toggle_Text__Default(void *context) { return "Toggle"; }
void Ft_Esd_Toggle_Changed__Noop(void *context, ft_bool_t value) { }


static Ft_Esd_WidgetSlots s_Ft_Esd_Toggle__Slots = {
	(void(*)(void *))Ft_Esd_Widget_Initialize,
	(void(*)(void *))Ft_Esd_Toggle_Start,
	(void(*)(void *))Ft_Esd_Widget_Enable,
	(void(*)(void *))Ft_Esd_Toggle_Update,
	(void(*)(void *))Ft_Esd_Toggle_Render,
	(void(*)(void *))Ft_Esd_Widget_Idle,
	(void(*)(void *))Ft_Esd_Widget_Disable,
	(void(*)(void *))Ft_Esd_Toggle_End,
};

static void Ft_Esd_Toggle_Touch_Tag_Tap__Signal(void *context);

void Ft_Esd_Toggle__Touch_Tag__Initializer(Ft_Esd_Toggle *context)
{
	Ft_Esd_TouchTag *object = &context->Touch_Tag;
	Ft_Esd_TouchTag__Initializer(object);
	object->Owner = context;
	object->Tap = Ft_Esd_Toggle_Touch_Tag_Tap__Signal;
}

void Ft_Esd_Toggle__Initializer(Ft_Esd_Toggle *context)
{
	Ft_Esd_Widget__Initializer((Ft_Esd_Widget *)context);
	context->Widget.ClassId = Ft_Esd_Toggle_CLASSID;
	context->Widget.Slots = &s_Ft_Esd_Toggle__Slots;
	context->Widget.LocalX = 0;
	context->Widget.LocalY = 0;
	context->Widget.LocalWidth = 80;
	context->Widget.LocalHeight = 36;
	context->Theme = Ft_Esd_Toggle_Theme__Default;
	context->Font = Ft_Esd_Toggle_Font__Default;
	context->Text = Ft_Esd_Toggle_Text__Default;
	context->Toggled = Ft_Esd_Noop;
	context->State = 0;
	context->Changed = Ft_Esd_Toggle_Changed__Noop;
	context->AutoResize = ESD_AUTORESIZE_HEIGHT;
	Ft_Esd_Toggle__Touch_Tag__Initializer(context);
}

static ft_rgb32_t Ft_Esd_Toggle_Get_Default_Color__return(Ft_Esd_Toggle *context);
static ft_uint8_t Ft_Esd_Toggle_Ft_Esd_Dl_RomFont_Setup__return(Ft_Esd_Toggle *context);

ft_void_t Ft_Gpu_CoCmd_FgColor(Ft_Gpu_Hal_Context_t *, ft_rgb32_t);
ft_void_t Ft_Gpu_CoCmd_BgColor(Ft_Gpu_Hal_Context_t *, ft_rgb32_t);
ft_void_t Ft_Gpu_CoCmd_Toggle(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t, const ft_char8_t *);
ft_uint8_t Ft_Esd_Dl_RomFont_Setup(ft_uint8_t);
void Ft_Esd_Toggle_Render_CoCmd(Ft_Esd_Toggle *context, ft_uint8_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t, const ft_char8_t *);

void Ft_Esd_Toggle_Start(Ft_Esd_Toggle *context)
{
	void *owner = context->Owner;
	Ft_Esd_Widget_Start((Ft_Esd_Widget *)context);
	Ft_Esd_TouchTag_Start(&context->Touch_Tag);
}

void Ft_Esd_Toggle_Update__Builtin(Ft_Esd_Toggle *context)
{
	void *owner = context->Owner;
	Ft_Esd_TouchTag_Update(&context->Touch_Tag);
	Ft_Esd_Widget_Update((Ft_Esd_Widget *)context);
}

void Ft_Esd_Toggle_End(Ft_Esd_Toggle *context)
{
	void *owner = context->Owner;
	Ft_Esd_TouchTag_End(&context->Touch_Tag);
	Ft_Esd_Widget_End((Ft_Esd_Widget *)context);
}

void Ft_Esd_Toggle_Render(Ft_Esd_Toggle *context)
{
	void *owner = context->Owner;
	ft_uint8_t alpha = 255;
	Ft_Esd_Dl_COLOR_A(alpha);
	Ft_Gpu_Hal_Context_t * phost = Ft_Esd_GetHost();
	ft_bool_t if_1 = context->State;
	ft_rgb32_t c_1;
	if (if_1)
	{
		Ft_Esd_Theme * theme = context->Theme(owner);
		c_1 = Ft_Esd_Theme_GetPrimaryColor(theme);
	}
	else
	{
		c_1 = Ft_Esd_Toggle_Get_Default_Color__return(context);
	}
	Ft_Gpu_CoCmd_FgColor(phost, c_1);
	Ft_Gpu_Hal_Context_t * phost_1 = Ft_Esd_GetHost();
	ft_bool_t if_2 = Ft_Esd_TouchTag_Inside(&context->Touch_Tag);
	ft_rgb32_t c_2;
	if (if_2)
	{
		c_2 = Ft_Esd_Toggle_Get_Default_Color__return(context);
	}
	else
	{
		Ft_Esd_Theme * theme_1 = context->Theme(owner);
		c_2 = Ft_Esd_Theme_GetBackColor(theme_1);
	}
	Ft_Gpu_CoCmd_BgColor(phost_1, c_2);
	Ft_Esd_Theme * theme_2 = context->Theme(owner);
	ft_rgb32_t c_3 = Ft_Esd_Theme_GetTextColor(theme_2);
	Ft_Esd_Dl_COLOR_RGB(c_3);
	ft_uint8_t tag = Ft_Esd_TouchTag_Tag(&context->Touch_Tag);
	ft_int16_t left = context->Widget.GlobalX;
	ft_int16_t i = context->Font(owner);
	ft_uint16_t left_3 = Ft_Esd_GetFontHeight(i);
	ft_int16_t right_1 = 5;
	ft_int16_t left_2 = left_3 * right_1;
	ft_int16_t right_2 = 4;
	ft_int16_t left_1 = left_2 / right_2;
	ft_int16_t right_3 = 2;
	ft_int16_t right = left_1 / right_3;
	ft_int16_t x = left + right;
	ft_int16_t left_5 = context->Widget.GlobalY;
	ft_int16_t i_1 = context->Font(owner);
	ft_uint16_t left_8 = Ft_Esd_GetFontHeight(i_1);
	ft_int16_t right_5 = 5;
	ft_int16_t left_7 = left_8 * right_5;
	ft_int16_t right_6 = 4;
	ft_int16_t left_6 = left_7 / right_6;
	ft_int16_t right_7 = 4;
	ft_int16_t right_4 = left_6 / right_7;
	ft_int16_t left_4 = left_5 + right_4;
	ft_int16_t left_10 = context->Widget.GlobalHeight;
	ft_int16_t i_2 = context->Font(owner);
	ft_uint16_t left_12 = Ft_Esd_GetFontHeight(i_2);
	ft_int16_t right_10 = 5;
	ft_int16_t left_11 = left_12 * right_10;
	ft_int16_t right_11 = 4;
	ft_int16_t right_9 = left_11 / right_11;
	ft_int16_t left_9 = left_10 - right_9;
	ft_int16_t right_12 = 2;
	ft_int16_t right_8 = left_9 / right_12;
	ft_int16_t y = left_4 + right_8;
	ft_int16_t left_13 = context->Widget.GlobalWidth;
	ft_int16_t i_3 = context->Font(owner);
	ft_uint16_t left_15 = Ft_Esd_GetFontHeight(i_3);
	ft_int16_t right_14 = 5;
	ft_int16_t left_14 = left_15 * right_14;
	ft_int16_t right_15 = 4;
	ft_int16_t right_13 = left_14 / right_15;
	ft_int16_t width = left_13 - right_13;
	ft_uint8_t font = Ft_Esd_Toggle_Ft_Esd_Dl_RomFont_Setup__return(context);
	ft_uint16_t options = 0;
	ft_bool_t if_3 = context->State;
	ft_uint16_t state;
	if (if_3)
	{
		state = 65535U;
	}
	else
	{
		state = 0U;
	}
	const char * s = context->Text(owner);
	Ft_Esd_Toggle_Render_CoCmd(context, tag, x, y, width, font, options, state, s);
	Ft_Esd_Widget_Render((Ft_Esd_Widget *)context); 
}

ft_rgb32_t Ft_Esd_Toggle_Get_Default_Color__return(Ft_Esd_Toggle *context)
{
	void *owner = context->Owner;
	Ft_Esd_Theme * theme_3 = context->Theme(owner);
	return Ft_Esd_Theme_GetCurrentColor(theme_3);
}

ft_uint8_t Ft_Esd_Toggle_Ft_Esd_Dl_RomFont_Setup__return(Ft_Esd_Toggle *context)
{
	void *owner = context->Owner;
	ft_int16_t font_1 = context->Font(owner);
	return Ft_Esd_Dl_RomFont_Setup(font_1);
}

void Ft_Esd_Toggle_Toggle(Ft_Esd_Toggle *context)
{
	void *owner = context->Owner;
	ft_bool_t value = context->State;
	int set_variable = !value;
	context->State = set_variable;
	context->Changed(owner, set_variable);
	context->Toggled(owner);
}

void Ft_Esd_Toggle_Update(Ft_Esd_Toggle *context)
{
	void *owner = context->Owner;
	ft_uint8_t left_16 = context->AutoResize;
	ft_uint8_t right_16 = ESD_AUTORESIZE_HEIGHT;
	ft_uint8_t if_4 = left_16 & right_16;
	if (if_4)
	{
		ft_int16_t i_4 = context->Font(owner);
		ft_uint16_t left_18 = Ft_Esd_GetFontHeight(i_4);
		ft_int16_t right_17 = 5;
		ft_int16_t left_17 = left_18 * right_17;
		ft_int16_t right_18 = 4;
		ft_int16_t set_variable_2 = left_17 / right_18;
		Ft_Esd_Widget_SetHeight((Ft_Esd_Widget *)context, set_variable_2);
	}
	else
	{
	}
	Ft_Esd_Toggle_Update__Builtin(context);
}

void Ft_Esd_Toggle_Touch_Tag_Tap__Signal(void *c)
{
	Ft_Esd_Toggle *context = (Ft_Esd_Toggle *)c;
	void *owner = context->Owner;
	ft_bool_t value_1 = context->State;
	int set_variable_1 = !value_1;
	context->State = set_variable_1;
	context->Changed(owner, set_variable_1);
	context->Toggled(owner);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_Toggle Instance;
	Ft_Esd_Theme * Theme;
	ft_int16_t Font;
	const char * Text;
} Ft_Esd_Toggle__ESD;

Ft_Esd_Theme * Ft_Esd_Toggle__Get_Theme__ESD(void *context) { return ((Ft_Esd_Toggle__ESD *)context)->Theme; }
void Ft_Esd_Toggle__Set_Theme__ESD(void *context, Ft_Esd_Theme * value) { ((Ft_Esd_Toggle__ESD *)context)->Theme = value; }
ft_int16_t Ft_Esd_Toggle__Get_Font__ESD(void *context) { return ((Ft_Esd_Toggle__ESD *)context)->Font; }
void Ft_Esd_Toggle__Set_Font__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Toggle__ESD *)context)->Font = value; }
const char * Ft_Esd_Toggle__Get_Text__ESD(void *context) { return ((Ft_Esd_Toggle__ESD *)context)->Text; }
void Ft_Esd_Toggle__Set_Text__ESD(void *context, const char * value) { ((Ft_Esd_Toggle__ESD *)context)->Text = value; }

void *Ft_Esd_Toggle__Create__ESD()
{
	Ft_Esd_Toggle__ESD *context = (Ft_Esd_Toggle__ESD *)malloc(sizeof(Ft_Esd_Toggle__ESD));
	Ft_Esd_Toggle__Initializer(&context->Instance);
	context->Instance.Owner = context;
	context->Theme = Ft_Esd_Theme_GetCurrent();
	context->Instance.Theme = Ft_Esd_Toggle__Get_Theme__ESD;
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
void Ft_Esd_Toggle__Set_AutoResize__ESD(void *context, ft_uint8_t value) { ((Ft_Esd_Toggle__ESD *)context)->Instance.AutoResize = value; }

#endif /* ESD_SIMULATION */

/* end of file */
