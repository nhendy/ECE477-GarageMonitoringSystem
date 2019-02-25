/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_Panel
Header
*/

#ifndef Ft_Esd_Panel__H
#define Ft_Esd_Panel__H

#include "Ft_Esd.h"
#include "Ft_Esd_Layout_Fixed.h"
#include "Ft_Esd_Math.h"
#include "Ft_Esd_Theme.h"
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

#define Ft_Esd_Panel_CLASSID 0xCE7186ED
ESD_SYMBOL(Ft_Esd_Panel_CLASSID, Type = esd_classid_t)

ESD_WIDGET(Ft_Esd_Panel, Include = "Ft_Esd_Panel.h", Callback, DisplayName = "ESD Panel", Category = EsdBasicWidegts, X = 82, Y = 44, Width = 276, Height = 198)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	ESD_INPUT(Theme, Type = Ft_Esd_Theme *, Default = Ft_Esd_Theme_GetCurrent)
	Ft_Esd_Theme *(* Theme)(void *context);
	/* Corner's radius */
	ESD_INPUT(Radius, Type = int, Default = 4)
	int(* Radius)(void *context);
	ESD_INPUT(Raised, Type = ft_bool_t, Default = false)
	ft_bool_t(* Raised)(void *context);
	Ft_Esd_Layout_Fixed Fixed_Positioning;
} Ft_Esd_Panel;

void Ft_Esd_Panel__Initializer(Ft_Esd_Panel *context);

ESD_SLOT(Render)
void Ft_Esd_Panel_Render(Ft_Esd_Panel *context);

ESD_SLOT(End)
void Ft_Esd_Panel_End(Ft_Esd_Panel *context);

#endif /* Ft_Esd_Panel__H */

/* end of file */
