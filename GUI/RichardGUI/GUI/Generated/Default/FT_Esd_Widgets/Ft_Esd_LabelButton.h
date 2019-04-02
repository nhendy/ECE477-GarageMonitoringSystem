/*
This file is automatically generated
Ft_Esd_LabelButton
Header
*/

#ifndef Ft_Esd_LabelButton__H
#define Ft_Esd_LabelButton__H

#include "FT_DataTypes.h"
#include "Ft_Esd.h"
#include "Ft_Esd_DefaultTheme.h"
#include "Ft_Esd_Theme.h"
#include "Ft_Esd_TouchTag.h"

#ifndef ESD_LOGIC
#define ESD_LOGIC(name, ...)
#define ESD_ACTOR(name, ...)
#define ESD_WIDGET(name, ...)
#define ESD_PAGE(name, ...)
#define ESD_APPLICATION(name, ...)
#define ESD_INPUT(name, ...)
#define ESD_OUTPUT(name, ...)
#define ESD_SLOT(name, ...)
#define ESD_SIGNAL(name, ...)
#define ESD_VARIABLE(name, ...)
#define ESD_WRITER(name, ...)
#endif

/* Text based label with pushed signal */
ESD_WIDGET(Ft_Esd_LabelButton, Include = "Ft_Esd_LabelButton.h", Callback, DisplayName = "ESD Label Button", Category = EsdWidgets, Icon = ":/icons/ui-label-link.png")
typedef struct
{
	void *Parent;
	Ft_Esd_TouchTag Touch_Tag;
	ESD_SIGNAL(Pushed)
	void(* Pushed)(void *context);
	ESD_INPUT(Theme, Type = Ft_Esd_Theme *, EditRole = Library, Default = Ft_Esd_Theme_GetCurrent)
	Ft_Esd_Theme *(* Theme)(void *context);
	ESD_INPUT(X, Type = ft_int16_t, Default = 0)
	ft_int16_t(* X)(void *context);
	ESD_INPUT(Y, Type = ft_int16_t, Default = 0)
	ft_int16_t(* Y)(void *context);
	ESD_INPUT(Width, Type = ft_int16_t, Max = 4096, Default = 120)
	ft_int16_t(* Width)(void *context);
	ESD_INPUT(Height, Type = ft_int16_t, Max = 4096, Default = 36)
	ft_int16_t(* Height)(void *context);
	ESD_INPUT(Font, Type = ft_int16_t, Min = 0, Max = 31, Default = 27)
	ft_int16_t(* Font)(void *context);
	ESD_INPUT(Text, Type = const char *, Default = "Label Button")
	const char *(* Text)(void *context);
	ESD_INPUT(Primary, Type = ft_bool_t, Default = true)
	ft_bool_t(* Primary)(void *context);
} Ft_Esd_LabelButton;

void Ft_Esd_LabelButton__Initializer(Ft_Esd_LabelButton *context);

ESD_SLOT(Start)
void Ft_Esd_LabelButton_Start(Ft_Esd_LabelButton *context);

ESD_SLOT(Update)
void Ft_Esd_LabelButton_Update(Ft_Esd_LabelButton *context);

ESD_SLOT(End)
void Ft_Esd_LabelButton_End(Ft_Esd_LabelButton *context);

ESD_SLOT(Render)
void Ft_Esd_LabelButton_Render(Ft_Esd_LabelButton *context);

#endif /* Ft_Esd_LabelButton__H */

/* end of file */
