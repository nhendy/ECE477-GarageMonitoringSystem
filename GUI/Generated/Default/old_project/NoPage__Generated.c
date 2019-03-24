/*
This file is automatically generated
NoPage
C Source
*/

#include "NoPage.h"

extern void Ft_Esd_Noop(void *context);

Ft_Esd_Theme * Ft_Esd_Theme_GetCurrent();
static ft_int16_t NoPage_ESD_Push_Button_X__Property(void *context) { return 335; }
static ft_int16_t NoPage_ESD_Push_Button_Y__Property(void *context) { return 202; }
static const char * NoPage_ESD_Push_Button_Text__Property(void *context) { return "No!"; }


void NoPage__Initializer(NoPage *context)
{
	context->Parent = 0;
	Ft_Esd_PushButton__Initializer(&context->ESD_Push_Button);
	context->ESD_Push_Button.Parent = context;
	context->ESD_Push_Button.X = NoPage_ESD_Push_Button_X__Property;
	context->ESD_Push_Button.Y = NoPage_ESD_Push_Button_Y__Property;
	context->ESD_Push_Button.Text = NoPage_ESD_Push_Button_Text__Property;
}

void NoPage_Start(NoPage *context)
{
	void *parent = context->Parent;
	Ft_Esd_PushButton_Start(&context->ESD_Push_Button);
}

void NoPage_Update(NoPage *context)
{
	void *parent = context->Parent;
	Ft_Esd_PushButton_Update(&context->ESD_Push_Button);
}

void NoPage_Render(NoPage *context)
{
	void *parent = context->Parent;
	Ft_Esd_PushButton_Render(&context->ESD_Push_Button);
}

void NoPage_Idle(NoPage *context)
{
	void *parent = context->Parent;
}

void NoPage_End(NoPage *context)
{
	void *parent = context->Parent;
	Ft_Esd_PushButton_End(&context->ESD_Push_Button);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	NoPage Instance;
} NoPage__ESD;


void *NoPage__Create__ESD()
{
	NoPage__ESD *context = (NoPage__ESD *)malloc(sizeof(NoPage__ESD));
	NoPage__Initializer(&context->Instance);
	context->Instance.Parent = context;
	return context;
}

void NoPage__Destroy__ESD(void *context)
{
	free(context);
}


#endif /* ESD_SIMULATION */

/* end of file */
