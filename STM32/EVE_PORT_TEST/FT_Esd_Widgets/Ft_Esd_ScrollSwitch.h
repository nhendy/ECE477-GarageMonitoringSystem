/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_ScrollSwitch
Header
*/

#ifndef Ft_Esd_ScrollSwitch__H
#define Ft_Esd_ScrollSwitch__H

#include "Ft_Esd.h"
#include "Ft_Esd_Layout_Fixed.h"
#include "Ft_Esd_Math.h"
#include "Ft_Esd_ScrollPanel.h"
#include "Ft_Esd_Theme.h"
#include "Ft_Esd_Theme_LightBlue.h"
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

#define Ft_Esd_ScrollSwitch_CLASSID 0x5CBAD9CD
ESD_SYMBOL(Ft_Esd_ScrollSwitch_CLASSID, Type = esd_classid_t)

/* Scroll Switch Page layout, requires initialising on start and switch nodes for allocating new widget */
ESD_WIDGET(Ft_Esd_ScrollSwitch, Include = "Ft_Esd_ScrollSwitch.h", Callback, DisplayName = "Scroll Switch Page", Category = EsdLayouts, Icon = ":/icons/ui-scroll-pane.png", X = 0, Y = 0, Width = 318, Height = 478, Layout, BackToFront)
typedef struct
{
	union
	{
		void *Owner;
		Ft_Esd_Widget Widget;
	};
	/* Initial Previous Page Object Pointer */
	ESD_INPUT(InitialPrevious, DisplayName = "Initial Previous ", Type = Ft_Esd_Widget *)
	Ft_Esd_Widget *(* InitialPrevious)(void *context);
	/* Initial Current Page Object Pointer */
	ESD_INPUT(InitialCurrent, DisplayName = "Initial Current", Type = Ft_Esd_Widget *)
	Ft_Esd_Widget *(* InitialCurrent)(void *context);
	/* Initial Next Page Object Pointer */
	ESD_INPUT(InitialNext, DisplayName = "Initial Next", Type = Ft_Esd_Widget *)
	Ft_Esd_Widget *(* InitialNext)(void *context);
	/* Initial Current Index */
	ESD_INPUT(InitialIndex, DisplayName = "Initial Index", Type = int, Min = 0, Default = 1)
	int(* InitialIndex)(void *context);
	/* Active Scroll overrides on child widget tag is 255 */
	ESD_INPUT(Active_Scroll, DisplayName = "Active Scroll", Type = ft_bool_t, Default = false)
	ft_bool_t(* Active_Scroll)(void *context);
	/* Enable switch looping */
	ESD_VARIABLE(Looping, DisplayName = "Loop Pages", Type = ft_bool_t, Default = true, Public)
	ft_bool_t Looping;
	/* Page Count */
	ESD_VARIABLE(Count, DisplayName = "Count", Type = int, Min = 3, Max = 20, Default = 4, Public)
	int Count;
	/* Spacing between pages */
	ESD_VARIABLE(Spacing, DisplayName = "Spacing", Type = int, Min = 0, Max = 800, Default = 5, Public)
	int Spacing;
	ESD_VARIABLE(Touching, Type = ft_bool_t, Private)
	ft_bool_t Touching;
	/* Switch Sensitivity scale from 0.25 to 4.0 */
	ESD_VARIABLE(Sensitivity, DisplayName = "Sensitivity", Type = float, Min = 0.05, Max = 20, SingleStep = 0.1, Default = 1.5, Public)
	float Sensitivity;
	/* Switch Speed in scale of 1 to 16. */
	ESD_VARIABLE(SwitchSpeed, DisplayName = "Switch Speed", Type = int, Min = 1, Max = 16, Default = 4, Public)
	int SwitchSpeed;
	ESD_VARIABLE(ScrollXStart, Type = int, Private)
	int ScrollXStart;
	ESD_VARIABLE(ScrollX, Type = int, Private)
	int ScrollX;
	ESD_SIGNAL(NewPage)
	void(* NewPage)(void *context);
	ESD_VARIABLE(ScrollXTarget, Type = int, Private)
	int ScrollXTarget;
	ESD_VARIABLE(NewScrollX, Type = int, Private)
	int NewScrollX;
	ESD_VARIABLE(Overflow, Type = ft_int16_t, Default = false, Private)
	ft_int16_t Overflow;
	/* Set true to show spinner */
	ESD_INPUT(Spinner, DisplayName = "Spinner", Type = ft_bool_t, Default = false)
	ft_bool_t(* Spinner)(void *context);
	ESD_VARIABLE(State, Type = int, Private)
	int State;
	ESD_VARIABLE(RemovingWidget, Type = Ft_Esd_Widget *, Private)
	Ft_Esd_Widget * RemovingWidget;
	/* Previous Page Object Pointer */
	ESD_VARIABLE(Previous, DisplayName = "Previous Page", Type = Ft_Esd_Widget *, ReadOnly)
	Ft_Esd_Widget * Previous;
	/* Current Page Object Pointer */
	ESD_VARIABLE(Current, DisplayName = "Current Page", Type = Ft_Esd_Widget *, ReadOnly)
	Ft_Esd_Widget * Current;
	/* Next Page Object Pointer */
	ESD_VARIABLE(Next, DisplayName = "Next Page", Type = Ft_Esd_Widget *, ReadOnly)
	Ft_Esd_Widget * Next;
	/* Input New Page Object Pointer */
	ESD_INPUT(New, DisplayName = "New Page", Type = Ft_Esd_Widget *)
	Ft_Esd_Widget *(* New)(void *context);
	/* Current Page Index */
	ESD_VARIABLE(Index, DisplayName = "Current Index", Type = int, Default = 1, ReadOnly)
	int Index;
	/* New Page Index */
	ESD_VARIABLE(NewIndex, DisplayName = "New Index", Type = int, Default = 1, ReadOnly)
	int NewIndex;
	Ft_Esd_ScrollPanel ScrollPanel;
	Ft_Esd_Layout_Fixed FixedPositioning;
} Ft_Esd_ScrollSwitch;

void Ft_Esd_ScrollSwitch__Initializer(Ft_Esd_ScrollSwitch *context);

ESD_SLOT(End)
void Ft_Esd_ScrollSwitch_End(Ft_Esd_ScrollSwitch *context);

ESD_SLOT(Initialise)
void Ft_Esd_ScrollSwitch_Initialise(Ft_Esd_ScrollSwitch *context);

ESD_SLOT(Update)
void Ft_Esd_ScrollSwitch_Update(Ft_Esd_ScrollSwitch *context);

ESD_SLOT(Render)
void Ft_Esd_ScrollSwitch_Render(Ft_Esd_ScrollSwitch *context);

#endif /* Ft_Esd_ScrollSwitch__H */

/* end of file */
