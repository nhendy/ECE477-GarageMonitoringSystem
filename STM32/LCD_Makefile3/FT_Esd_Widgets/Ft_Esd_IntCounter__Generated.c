/*
This file is automatically generated
DO NOT MODIFY BY HAND
Ft_Esd_IntCounter
C Source
*/

#include "Ft_Esd_IntCounter.h"

extern void Ft_Esd_Noop(void *context);



void Ft_Esd_IntCounter__Initializer(Ft_Esd_IntCounter *context)
{
	context->Owner = 0;
	context->Value = 0L;
	context->Step = 1L;
}

void Ft_Esd_IntCounter_Inc(Ft_Esd_IntCounter *context)
{
	void *owner = context->Owner;
	int left = context->Value;
	int right = context->Step;
	int set_variable = left + right;
	context->Value = set_variable;
}

void Ft_Esd_IntCounter_Dec(Ft_Esd_IntCounter *context)
{
	void *owner = context->Owner;
	int left_1 = context->Value;
	int right_1 = context->Step;
	int set_variable_1 = left_1 - right_1;
	context->Value = set_variable_1;
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	Ft_Esd_IntCounter Instance;
} Ft_Esd_IntCounter__ESD;


void *Ft_Esd_IntCounter__Create__ESD()
{
	Ft_Esd_IntCounter__ESD *context = (Ft_Esd_IntCounter__ESD *)malloc(sizeof(Ft_Esd_IntCounter__ESD));
	Ft_Esd_IntCounter__Initializer(&context->Instance);
	context->Instance.Owner = context;
	return context;
}

void Ft_Esd_IntCounter__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Esd_IntCounter__Set_Value__ESD(void *context, int value) { ((Ft_Esd_IntCounter__ESD *)context)->Instance.Value = value; }
void Ft_Esd_IntCounter__Set_Step__ESD(void *context, int value) { ((Ft_Esd_IntCounter__ESD *)context)->Instance.Step = value; }

#endif /* ESD_SIMULATION */

/* end of file */
