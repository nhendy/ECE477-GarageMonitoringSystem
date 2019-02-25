/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_RadioButton
Header
*/

#ifndef Ft_Esd_RadioButton__H
#define Ft_Esd_RadioButton__H

#include "FT_DataTypes.h"
#include "Ft_Esd.h"
#include "Ft_Esd_DefaultTheme.h"
#include "Ft_Esd_Label.h"
#include "Ft_Esd_Layout_Fixed.h"
#include "Ft_Esd_Math.h"
#include "Ft_Esd_RadioGroup.h"
#include "Ft_Esd_Theme.h"
#include "Ft_Esd_TouchTag.h"
#include "Ft_Esd_Widget.h"

#ifndef ESD_LOGIC
#define ESD_LOGIC(name, ...)
#define ESD_ACTOR(name, ...)
#define ESD_WIDGET(name, ...)
#define ESD_UI(name, ...)
#define ESD_PAGE(name, ...)
#define ESD_APPLICATION(name, ...)
#define ESD_INPUT(name, ...)
#define ESD_OUTPUT(name, ...)
#define ESD_SLOT(name, ...)
#define ESD_SIGNAL(name, ...)
#define ESD_VARIABLE(name, ...)
#define ESD_WRITER(name, ...)
#endif

#define Ft_Esd_RadioButton_CLASSID 0x643679B5
ESD_SYMBOL(Ft_Esd_RadioButton_CLASSID, Type = esd_classid_t)

/* Classic radio button widget with label */
ESD_WIDGET(Ft_Esd_RadioButton, Include = "Ft_Esd_RadioButton.h", Callback, DisplayName = "ESD Radio Button", Category = EsdWidgets, X = 0, Y = 0, Width = 20, Height = 20)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	ESD_INPUT(Theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
	Ft_Esd_Theme *(* Theme)(void *context);
	ESD_INPUT(RadioGroup, DisplayName = "Radio Group", Type = Ft_Esd_RadioGroup *)
	Ft_Esd_RadioGroup *(* RadioGroup)(void *context);
	ESD_SIGNAL(Checked)
	void(* Checked)(void *context);
	ESD_WRITER(Changed, Type = ft_bool_t)
	void(* Changed)(void *context, ft_bool_t value);
	ESD_INPUT(Font, Type = int, Min = 16, Max = 34, Default = 27)
	int(* Font)(void *context);
	ESD_INPUT(Text, Type = char *, Default = "Option")
	char *(* Text)(void *context);
	Ft_Esd_TouchTag Touch_Tag;
	Ft_Esd_Layout_Fixed Fixed_Position;
	Ft_Esd_Label ESD_Label;
} Ft_Esd_RadioButton;

void Ft_Esd_RadioButton__Initializer(Ft_Esd_RadioButton *context);

ESD_SLOT(Start)
void Ft_Esd_RadioButton_Start(Ft_Esd_RadioButton *context);

ESD_SLOT(Update)
void Ft_Esd_RadioButton_Update(Ft_Esd_RadioButton *context);

ESD_SLOT(End)
void Ft_Esd_RadioButton_End(Ft_Esd_RadioButton *context);

ESD_SLOT(Render)
void Ft_Esd_RadioButton_Render(Ft_Esd_RadioButton *context);

ESD_SLOT(Check)
void Ft_Esd_RadioButton_Check(Ft_Esd_RadioButton *context);

ESD_OUTPUT(Value, Type = ft_bool_t)
ft_bool_t Ft_Esd_RadioButton_Value(Ft_Esd_RadioButton *context);

#endif /* Ft_Esd_RadioButton__H */

/* end of file */
