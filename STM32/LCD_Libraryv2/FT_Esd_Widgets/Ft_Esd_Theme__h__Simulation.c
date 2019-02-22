/*
This file is automatically generated
Ft_Esd_Theme__h
Simulation wrapper
*/

/* Simulation wrapper for 'Ft_Esd_Theme_SetCurrent' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "Ft_Esd_Theme.h"

void Ft_Esd_Theme_SetCurrent(Ft_Esd_Theme *);

typedef struct
{
	Ft_Esd_Theme * theme;
} Ft_Esd_Theme_SetCurrent__ESD;

void Ft_Esd_Theme_SetCurrent__Set_theme__ESD(void *context, Ft_Esd_Theme * value) { ((Ft_Esd_Theme_SetCurrent__ESD *)context)->theme = value; }

void *Ft_Esd_Theme_SetCurrent__Create__ESD()
{
	Ft_Esd_Theme_SetCurrent__ESD *context = (Ft_Esd_Theme_SetCurrent__ESD *)malloc(sizeof(Ft_Esd_Theme_SetCurrent__ESD));
	context->theme = 0;
	return context;
}

void Ft_Esd_Theme_SetCurrent__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_Theme_SetCurrent_Render(Ft_Esd_Theme_SetCurrent__ESD *context)
{
	Ft_Esd_Theme_SetCurrent(context->theme);
}

#endif /* ESD_SIMULATION */

/* end of file */