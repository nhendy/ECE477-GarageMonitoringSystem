/*
This file is automatically generated
Ft_Esd_Label
C Source
*/

#include "Ft_Esd_Label.h"

#include "FT_Esd_CoPro_Cmds.h"
#include "FT_Esd_Dl.h"

extern void Ft_Esd_Noop(void *context);
Ft_Esd_Theme * Ft_Esd_Label_Theme__Default(void *context) { return Ft_Esd_Theme_GetCurrent(); }
ft_int16_t Ft_Esd_Label_Font__Default(void *context) { return 27; }
const char * Ft_Esd_Label_Text__Default(void *context) { return "Label"; }
ft_int16_t Ft_Esd_Label_X__Default(void *context) { return 0; }
ft_int16_t Ft_Esd_Label_Y__Default(void *context) { return 0; }
ft_int16_t Ft_Esd_Label_Width__Default(void *context) { return 120; }
ft_int16_t Ft_Esd_Label_Height__Default(void *context) { return 36; }
ft_uint16_t Ft_Esd_Label_AlignX__Default(void *context) { return OPT_ALIGN_LEFT; }
ft_uint16_t Ft_Esd_Label_AlignY__Default(void *context) { return OPT_ALIGN_TOP; }

Ft_Esd_Theme * Ft_Esd_Theme_GetCurrent();
Ft_Gpu_Hal_Context_t * Ft_Esd_GetHost();


void Ft_Esd_Label__Initializer(Ft_Esd_Label *context)
{
	context->Parent = 0;
	context->Theme = Ft_Esd_Label_Theme__Default;
	context->Font = Ft_Esd_Label_Font__Default;
	context->Text = Ft_Esd_Label_Text__Default;
	context->X = Ft_Esd_Label_X__Default;
	context->Y = Ft_Esd_Label_Y__Default;
	context->Width = Ft_Esd_Label_Width__Default;
	context->Height = Ft_Esd_Label_Height__Default;
	context->AlignX = Ft_Esd_Label_AlignX__Default;
	context->AlignY = Ft_Esd_Label_AlignY__Default;
}

ft_void_t Ft_Gpu_CoCmd_Text(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, const ft_char8_t *);

void Ft_Esd_Label_Render(Ft_Esd_Label *context)
{
	void *parent = context->Parent;
	ft_uint8_t alpha = 255;
	Ft_Esd_Dl_COLOR_A(alpha);
	Ft_Esd_Theme * theme = context->Theme(parent);
	ft_rgb32_t c = Ft_Esd_Theme_GetTextColor(theme);
	Ft_Esd_Dl_COLOR_RGB(c);
	Ft_Gpu_Hal_Context_t * phost = Ft_Esd_GetHost();
	ft_uint16_t left = context->AlignX(parent);
	int right = 0L;
	int if_1 = left == right;
	int x;
	if (if_1)
	{
		x = context->X(parent);
	}
	else
	{
		ft_uint16_t left_1 = context->AlignX(parent);
		int right_1 = 2L;
		int if_2 = left_1 == right_1;
		if (if_2)
		{
			ft_int16_t left_2 = context->X(parent);
			ft_int16_t right_2 = context->Width(parent);
			x = left_2 + right_2;
		}
		else
		{
			ft_int16_t left_3 = context->X(parent);
			ft_int16_t left_4 = context->Width(parent);
			int right_4 = 2L;
			int right_3 = left_4 / right_4;
			x = left_3 + right_3;
		}
	}
	ft_uint16_t left_5 = context->AlignY(parent);
	int right_5 = 1L;
	int if_3 = left_5 == right_5;
	int y;
	if (if_3)
	{
		ft_int16_t left_6 = context->Y(parent);
		ft_int16_t left_7 = context->Height(parent);
		int right_7 = 2L;
		int right_6 = left_7 / right_7;
		y = left_6 + right_6;
	}
	else
	{
		ft_uint16_t left_8 = context->AlignY(parent);
		int right_8 = 0L;
		int if_4 = left_8 == right_8;
		if (if_4)
		{
			y = context->Y(parent);
		}
		else
		{
			ft_int16_t left_10 = context->Y(parent);
			ft_int16_t right_9 = context->Height(parent);
			int left_9 = left_10 + right_9;
			ft_int16_t i = context->Font(parent);
			ft_uint16_t right_10 = Ft_Esd_GetFontHeight(i);
			y = left_9 - right_10;
		}
	}
	ft_int16_t font = context->Font(parent);
	ft_uint16_t left_12 = context->AlignX(parent);
	int right_11 = 0L;
	int if_5 = left_12 == right_11;
	ft_uint16_t left_11;
	if (if_5)
	{
		left_11 = 0;
	}
	else
	{
		ft_uint16_t left_13 = context->AlignX(parent);
		int right_12 = 2L;
		int if_6 = left_13 == right_12;
		if (if_6)
		{
			left_11 = OPT_RIGHTX;
		}
		else
		{
			left_11 = OPT_CENTERX;
		}
	}
	ft_uint16_t left_14 = context->AlignY(parent);
	int right_14 = 1L;
	int if_7 = left_14 == right_14;
	ft_uint16_t right_13;
	if (if_7)
	{
		right_13 = OPT_CENTERY;
	}
	else
	{
		right_13 = 0;
	}
	ft_uint16_t options = left_11 | right_13;
	const char * s = context->Text(parent);
	Ft_Gpu_CoCmd_Text(phost, x, y, font, options, s);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_Label Instance;
	Ft_Esd_Theme * Theme;
	ft_int16_t Font;
	const char * Text;
	ft_int16_t X;
	ft_int16_t Y;
	ft_int16_t Width;
	ft_int16_t Height;
	ft_uint16_t AlignX;
	ft_uint16_t AlignY;
} Ft_Esd_Label__ESD;

Ft_Esd_Theme * Ft_Esd_Label__Get_Theme__ESD(void *context) { return ((Ft_Esd_Label__ESD *)context)->Theme; }
void Ft_Esd_Label__Set_Theme__ESD(void *context, Ft_Esd_Theme * value) { ((Ft_Esd_Label__ESD *)context)->Theme = value; }
ft_int16_t Ft_Esd_Label__Get_Font__ESD(void *context) { return ((Ft_Esd_Label__ESD *)context)->Font; }
void Ft_Esd_Label__Set_Font__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Label__ESD *)context)->Font = value; }
const char * Ft_Esd_Label__Get_Text__ESD(void *context) { return ((Ft_Esd_Label__ESD *)context)->Text; }
void Ft_Esd_Label__Set_Text__ESD(void *context, const char * value) { ((Ft_Esd_Label__ESD *)context)->Text = value; }
ft_int16_t Ft_Esd_Label__Get_X__ESD(void *context) { return ((Ft_Esd_Label__ESD *)context)->X; }
void Ft_Esd_Label__Set_X__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Label__ESD *)context)->X = value; }
ft_int16_t Ft_Esd_Label__Get_Y__ESD(void *context) { return ((Ft_Esd_Label__ESD *)context)->Y; }
void Ft_Esd_Label__Set_Y__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Label__ESD *)context)->Y = value; }
ft_int16_t Ft_Esd_Label__Get_Width__ESD(void *context) { return ((Ft_Esd_Label__ESD *)context)->Width; }
void Ft_Esd_Label__Set_Width__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Label__ESD *)context)->Width = value; }
ft_int16_t Ft_Esd_Label__Get_Height__ESD(void *context) { return ((Ft_Esd_Label__ESD *)context)->Height; }
void Ft_Esd_Label__Set_Height__ESD(void *context, ft_int16_t value) { ((Ft_Esd_Label__ESD *)context)->Height = value; }
ft_uint16_t Ft_Esd_Label__Get_AlignX__ESD(void *context) { return ((Ft_Esd_Label__ESD *)context)->AlignX; }
void Ft_Esd_Label__Set_AlignX__ESD(void *context, ft_uint16_t value) { ((Ft_Esd_Label__ESD *)context)->AlignX = value; }
ft_uint16_t Ft_Esd_Label__Get_AlignY__ESD(void *context) { return ((Ft_Esd_Label__ESD *)context)->AlignY; }
void Ft_Esd_Label__Set_AlignY__ESD(void *context, ft_uint16_t value) { ((Ft_Esd_Label__ESD *)context)->AlignY = value; }

void *Ft_Esd_Label__Create__ESD()
{
	Ft_Esd_Label__ESD *context = (Ft_Esd_Label__ESD *)malloc(sizeof(Ft_Esd_Label__ESD));
	Ft_Esd_Label__Initializer(&context->Instance);
	context->Instance.Parent = context;
	context->Theme = Ft_Esd_Theme_GetCurrent();
	context->Instance.Theme = Ft_Esd_Label__Get_Theme__ESD;
	context->Font = 27;
	context->Instance.Font = Ft_Esd_Label__Get_Font__ESD;
	context->Text = "Label";
	context->Instance.Text = Ft_Esd_Label__Get_Text__ESD;
	context->X = 0;
	context->Instance.X = Ft_Esd_Label__Get_X__ESD;
	context->Y = 0;
	context->Instance.Y = Ft_Esd_Label__Get_Y__ESD;
	context->Width = 120;
	context->Instance.Width = Ft_Esd_Label__Get_Width__ESD;
	context->Height = 36;
	context->Instance.Height = Ft_Esd_Label__Get_Height__ESD;
	context->AlignX = OPT_ALIGN_LEFT;
	context->Instance.AlignX = Ft_Esd_Label__Get_AlignX__ESD;
	context->AlignY = OPT_ALIGN_TOP;
	context->Instance.AlignY = Ft_Esd_Label__Get_AlignY__ESD;
	return context;
}

void Ft_Esd_Label__Destroy__ESD(void *context)
{
	free(context);
}


#endif /* ESD_SIMULATION */

/* end of file */