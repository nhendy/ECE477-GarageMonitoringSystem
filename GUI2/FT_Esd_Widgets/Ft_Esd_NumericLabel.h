/*
This file is automatically generated
Ft_Esd_NumericLabel
Header
*/

#ifndef Ft_Esd_NumericLabel__H
#define Ft_Esd_NumericLabel__H

#include "FT_DataTypes.h"
#include "Ft_Esd.h"
#include "Ft_Esd_DefaultTheme.h"
#include "Ft_Esd_Theme.h"

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

/* Number based label widget */
ESD_WIDGET(Ft_Esd_NumericLabel, Include = "Ft_Esd_NumericLabel.h", Callback, DisplayName = "ESD Numeric Label", Category = EsdWidgets, Icon = ":/icons/ui-label.png")
typedef struct
{
	void *Parent;
	ESD_INPUT(Theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
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
	ESD_INPUT(Value, Type = ft_int32_t, Default = 0)
	ft_int32_t(* Value)(void *context);
} Ft_Esd_NumericLabel;

void Ft_Esd_NumericLabel__Initializer(Ft_Esd_NumericLabel *context);

ESD_SLOT(Render)
void Ft_Esd_NumericLabel_Render(Ft_Esd_NumericLabel *context);

#endif /* Ft_Esd_NumericLabel__H */

/* end of file */
