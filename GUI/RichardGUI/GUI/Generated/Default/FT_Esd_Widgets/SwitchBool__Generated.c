/*
This file is automatically generated
SwitchBool
C Source
*/

#include "SwitchBool.h"

extern void Ft_Esd_Noop(void *context);



void SwitchBool__Initializer(SwitchBool *context)
{
	context->Parent = 0;
	context->Boolean = 0;
}

void SwitchBool_SetTrue(SwitchBool *context)
{
	void *parent = context->Parent;
	ft_bool_t set_variable = 1;
	context->Boolean = set_variable;
}

ft_bool_t SwitchBool_Value(SwitchBool *context)
{
	void *parent = context->Parent;
	return context->Boolean;
}

void SwitchBool_SetFalse(SwitchBool *context)
{
	void *parent = context->Parent;
	ft_bool_t set_variable_1 = 0;
	context->Boolean = set_variable_1;
}

void SwitchBool_Switch(SwitchBool *context)
{
	void *parent = context->Parent;
	ft_bool_t value = context->Boolean;
	int set_variable_2 = !value;
	context->Boolean = set_variable_2;
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	SwitchBool Instance;
} SwitchBool__ESD;


void *SwitchBool__Create__ESD()
{
	SwitchBool__ESD *context = (SwitchBool__ESD *)malloc(sizeof(SwitchBool__ESD));
	SwitchBool__Initializer(&context->Instance);
	context->Instance.Parent = context;
	return context;
}

void SwitchBool__Destroy__ESD(void *context)
{
	free(context);
}

void SwitchBool__Set_Boolean__ESD(void *context, ft_bool_t value) { ((SwitchBool__ESD *)context)->Instance.Boolean = value; }

#endif /* ESD_SIMULATION */

/* end of file */
