/*
This file is automatically generated
MainMenu
C Source
*/

#include "MainMenu.h"

extern void Ft_Esd_Noop(void *context);
void MainMenu_NoChanged__Noop(void *context, ft_bool_t value) { }
void MainMenu_YesChamged__Noop(void *context, ft_bool_t value) { }

Ft_Esd_Theme * Ft_Esd_Theme_GetCurrent();
static const char * MainMenu_ESD_Label_Text__Property(void *context) { return "Do you have a reservation code?"; }
static ft_int16_t MainMenu_ESD_Label_X__Property(void *context) { return 286; }
static ft_int16_t MainMenu_ESD_Label_Y__Property(void *context) { return 190; }
static ft_int16_t MainMenu_ESD_Label_Width__Property(void *context) { return 257; }
static ft_int16_t MainMenu_ESD3_Label_Font__Property(void *context) { return 31; }
static const char * MainMenu_ESD3_Label_Text__Property(void *context) { return "ESD3"; }
static ft_int16_t MainMenu_ESD3_Label_X__Property(void *context) { return 6; }
static ft_int16_t MainMenu_ESD_Push_Button_X__Property(void *context) { return 184; }
static ft_int16_t MainMenu_ESD_Push_Button_Y__Property(void *context) { return 250; }
static const char * MainMenu_ESD_Push_Button_Text__Property(void *context) { return "Yes"; }
static ft_int16_t MainMenu_ESD_Push_Button_2_X__Property(void *context) { return 491; }
static ft_int16_t MainMenu_ESD_Push_Button_2_Y__Property(void *context) { return 253; }
static const char * MainMenu_ESD_Push_Button_2_Text__Property(void *context) { return "No"; }

static void MainMenu_ESD_Push_Button_Pushed__Signal(void *context);
static void MainMenu_ESD_Push_Button_2_Pushed__Signal(void *context);

void MainMenu__Initializer(MainMenu *context)
{
	context->Parent = 0;
	context->Yes = Ft_Esd_Noop;
	context->No = Ft_Esd_Noop;
	context->No_1 = 0;
	context->Yes_1 = 0;
	context->NoChanged = MainMenu_NoChanged__Noop;
	context->YesChamged = MainMenu_YesChamged__Noop;
	Ft_Esd_Label__Initializer(&context->ESD_Label);
	context->ESD_Label.Parent = context;
	context->ESD_Label.Text = MainMenu_ESD_Label_Text__Property;
	context->ESD_Label.X = MainMenu_ESD_Label_X__Property;
	context->ESD_Label.Y = MainMenu_ESD_Label_Y__Property;
	context->ESD_Label.Width = MainMenu_ESD_Label_Width__Property;
	Ft_Esd_Label__Initializer(&context->ESD3_Label);
	context->ESD3_Label.Parent = context;
	context->ESD3_Label.Font = MainMenu_ESD3_Label_Font__Property;
	context->ESD3_Label.Text = MainMenu_ESD3_Label_Text__Property;
	context->ESD3_Label.X = MainMenu_ESD3_Label_X__Property;
	Ft_Esd_PushButton__Initializer(&context->ESD_Push_Button);
	context->ESD_Push_Button.Parent = context;
	context->ESD_Push_Button.X = MainMenu_ESD_Push_Button_X__Property;
	context->ESD_Push_Button.Y = MainMenu_ESD_Push_Button_Y__Property;
	context->ESD_Push_Button.Text = MainMenu_ESD_Push_Button_Text__Property;
	context->ESD_Push_Button.Pushed = MainMenu_ESD_Push_Button_Pushed__Signal;
	Ft_Esd_PushButton__Initializer(&context->ESD_Push_Button_2);
	context->ESD_Push_Button_2.Parent = context;
	context->ESD_Push_Button_2.X = MainMenu_ESD_Push_Button_2_X__Property;
	context->ESD_Push_Button_2.Y = MainMenu_ESD_Push_Button_2_Y__Property;
	context->ESD_Push_Button_2.Text = MainMenu_ESD_Push_Button_2_Text__Property;
	context->ESD_Push_Button_2.Pushed = MainMenu_ESD_Push_Button_2_Pushed__Signal;
}

void MainMenu_Start(MainMenu *context)
{
	void *parent = context->Parent;
	Ft_Esd_PushButton_Start(&context->ESD_Push_Button);
	Ft_Esd_PushButton_Start(&context->ESD_Push_Button_2);
}

void MainMenu_Update(MainMenu *context)
{
	void *parent = context->Parent;
	Ft_Esd_PushButton_Update(&context->ESD_Push_Button);
	Ft_Esd_PushButton_Update(&context->ESD_Push_Button_2);
}

void MainMenu_Render(MainMenu *context)
{
	void *parent = context->Parent;
	Ft_Esd_Label_Render(&context->ESD_Label);
	Ft_Esd_Label_Render(&context->ESD3_Label);
	Ft_Esd_PushButton_Render(&context->ESD_Push_Button);
	Ft_Esd_PushButton_Render(&context->ESD_Push_Button_2);
}

void MainMenu_Idle(MainMenu *context)
{
	void *parent = context->Parent;
}

void MainMenu_End(MainMenu *context)
{
	void *parent = context->Parent;
	Ft_Esd_PushButton_End(&context->ESD_Push_Button);
	Ft_Esd_PushButton_End(&context->ESD_Push_Button_2);
}

void MainMenu_ESD_Push_Button_Pushed__Signal(void *c)
{
	MainMenu *context = (MainMenu *)c;
	void *parent = context->Parent;
	context->Yes(parent);
	ft_bool_t hideno = 0;
	context->No_1 = hideno;
	context->NoChanged(parent, hideno);
	ft_bool_t showyes = 1;
	context->Yes_1 = showyes;
	context->YesChamged(parent, showyes);
}

void MainMenu_ESD_Push_Button_2_Pushed__Signal(void *c)
{
	MainMenu *context = (MainMenu *)c;
	void *parent = context->Parent;
	context->No(parent);
	ft_bool_t hideyes = 0;
	context->Yes_1 = hideyes;
	context->YesChamged(parent, hideyes);
	ft_bool_t showno = 1;
	context->No_1 = showno;
	context->NoChanged(parent, showno);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	MainMenu Instance;
} MainMenu__ESD;


void *MainMenu__Create__ESD()
{
	MainMenu__ESD *context = (MainMenu__ESD *)malloc(sizeof(MainMenu__ESD));
	MainMenu__Initializer(&context->Instance);
	context->Instance.Parent = context;
	return context;
}

void MainMenu__Destroy__ESD(void *context)
{
	free(context);
}

void MainMenu__Set_No_1__ESD(void *context, ft_bool_t value) { ((MainMenu__ESD *)context)->Instance.No_1 = value; }
void MainMenu__Set_Yes_1__ESD(void *context, ft_bool_t value) { ((MainMenu__ESD *)context)->Instance.Yes_1 = value; }

#endif /* ESD_SIMULATION */

/* end of file */
