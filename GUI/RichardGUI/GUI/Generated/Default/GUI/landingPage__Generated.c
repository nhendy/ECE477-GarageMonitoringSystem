/*
This file is automatically generated
landingPage
C Source
*/

#include "landingPage.h"

extern void Ft_Esd_Noop(void *context);



void landingPage__Initializer(landingPage *context)
{
	context->Parent = 0;
}

void landingPage_Start(landingPage *context)
{
	void *parent = context->Parent;
}

void landingPage_Update(landingPage *context)
{
	void *parent = context->Parent;
}

void landingPage_Render(landingPage *context)
{
	void *parent = context->Parent;
}

void landingPage_Idle(landingPage *context)
{
	void *parent = context->Parent;
}

void landingPage_End(landingPage *context)
{
	void *parent = context->Parent;
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	landingPage Instance;
} landingPage__ESD;


void *landingPage__Create__ESD()
{
	landingPage__ESD *context = (landingPage__ESD *)malloc(sizeof(landingPage__ESD));
	landingPage__Initializer(&context->Instance);
	context->Instance.Parent = context;
	return context;
}

void landingPage__Destroy__ESD(void *context)
{
	free(context);
}


#endif /* ESD_SIMULATION */

/* end of file */