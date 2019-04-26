/*
This file is automatically generated
NoSpotsAvailable
Header
*/

#ifndef NoSpotsAvailable__H
#define NoSpotsAvailable__H

#include "Ft_Esd.h"
#include "Ft_Esd_Label.h"
#include "Ft_Esd_PushButton.h"
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

ESD_PAGE(NoSpotsAvailable, Include = "NoSpotsAvailable.h", Callback)
typedef struct
{
	void *Parent;
	ESD_SIGNAL(Back)
	void(* Back)(void *context);
	ESD_WRITER(BackChanged, Type = ft_bool_t)
	void(* BackChanged)(void *context, ft_bool_t value);
	ESD_VARIABLE(Back_1, Type = ft_bool_t, Default = true, Private)
	ft_bool_t Back_1;
	Ft_Esd_Label ESD_Label;
	Ft_Esd_PushButton ESD_Push_Button;
} NoSpotsAvailable;

void NoSpotsAvailable__Initializer(NoSpotsAvailable *context);

ESD_SLOT(Start)
void NoSpotsAvailable_Start(NoSpotsAvailable *context);

ESD_SLOT(Update)
void NoSpotsAvailable_Update(NoSpotsAvailable *context);

ESD_SLOT(Render)
void NoSpotsAvailable_Render(NoSpotsAvailable *context);

ESD_SLOT(Idle)
void NoSpotsAvailable_Idle(NoSpotsAvailable *context);

ESD_SLOT(End)
void NoSpotsAvailable_End(NoSpotsAvailable *context);

#endif /* NoSpotsAvailable__H */

/* end of file */