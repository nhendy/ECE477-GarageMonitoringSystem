/*
This file is automatically generated
App
C Source
*/

#include "App.h"

#include "stdlib.h"

extern void Ft_Esd_Noop(void *context);
extern void Ft_Esd_Spinner_Popup();


static void App_MainPage_keyPad__Signal(void *context);
static void App_YesPage_KeyPadBack__Signal(void *context);
static void App_YesPage_Confirmation__Signal(void *context);

#define MainPage__ID 1
#define Confirmation__ID 2
#define YesPage__ID 3

void App__Initializer(App *context)
{
	context->Parent = 0;
	context->_ActivePage = 0;
	context->MainPage = 0;
	context->MainPage__Active = 0;
	context->Confirmation = 0;
	context->Confirmation__Active = 0;
	context->YesPage = 0;
	context->YesPage__Active = 0;
}

static void App__MainPage__Validate(App *context)
{
	void *parent = context->Parent;
	if (!context->MainPage)
	{
		context->MainPage = (MainPage *)malloc(sizeof(MainPage));
		MainPage__Initializer(context->MainPage);
		context->MainPage->Parent = context;
		context->MainPage->keyPad = App_MainPage_keyPad__Signal;
		MainPage_Start(context->MainPage);
	}
}

static void App__MainPage__Create(App *context)
{
	App__MainPage__Validate(context);
	context->MainPage__Active = 1;
}

static void App__MainPage__Destroy(App *context, int final)
{
	if (context->MainPage__Active)
	{
		context->MainPage__Active = 0;
	}
	if (context->MainPage)
	{
		MainPage_End(context->MainPage);
		free(context->MainPage);
		context->MainPage = 0;
	}
}

static void App__Confirmation__Validate(App *context)
{
	void *parent = context->Parent;
	if (!context->Confirmation)
	{
		context->Confirmation = (Confirmation *)malloc(sizeof(Confirmation));
		Confirmation__Initializer(context->Confirmation);
		context->Confirmation->Parent = context;
		Confirmation_Start(context->Confirmation);
	}
}

static void App__Confirmation__Create(App *context)
{
	App__Confirmation__Validate(context);
	context->Confirmation__Active = 1;
}

static void App__Confirmation__Destroy(App *context, int final)
{
	if (context->Confirmation__Active)
	{
		context->Confirmation__Active = 0;
	}
	if (context->Confirmation)
	{
		Confirmation_End(context->Confirmation);
		free(context->Confirmation);
		context->Confirmation = 0;
	}
}

static void App__YesPage__Validate(App *context)
{
	void *parent = context->Parent;
	if (!context->YesPage)
	{
		context->YesPage = (YesPage *)malloc(sizeof(YesPage));
		YesPage__Initializer(context->YesPage);
		context->YesPage->Parent = context;
		context->YesPage->KeyPadBack = App_YesPage_KeyPadBack__Signal;
		context->YesPage->Confirmation = App_YesPage_Confirmation__Signal;
		YesPage_Start(context->YesPage);
	}
}

static void App__YesPage__Create(App *context)
{
	App__YesPage__Validate(context);
	context->YesPage__Active = 1;
}

static void App__YesPage__Destroy(App *context, int final)
{
	if (context->YesPage__Active)
	{
		context->YesPage__Active = 0;
	}
	if (context->YesPage)
	{
		YesPage_End(context->YesPage);
		free(context->YesPage);
		context->YesPage = 0;
	}
}

void App_Start__Builtin(App *context)
{
	void *parent = context->Parent;
	if ((context->_ActivePage == MainPage__ID))
		App__MainPage__Create(context);
	if ((context->_ActivePage == Confirmation__ID))
		App__Confirmation__Create(context);
	if ((context->_ActivePage == YesPage__ID))
		App__YesPage__Create(context);
}

void App_Update(App *context)
{
	void *parent = context->Parent;
	if ((!!context->MainPage__Active) != ((context->_ActivePage == MainPage__ID)))
	{
		if (!context->MainPage__Active)
			App__MainPage__Create(context);
		else
			App__MainPage__Destroy(context, 0);
	}
	if ((!!context->Confirmation__Active) != ((context->_ActivePage == Confirmation__ID)))
	{
		if (!context->Confirmation__Active)
			App__Confirmation__Create(context);
		else
			App__Confirmation__Destroy(context, 0);
	}
	if ((!!context->YesPage__Active) != ((context->_ActivePage == YesPage__ID)))
	{
		if (!context->YesPage__Active)
			App__YesPage__Create(context);
		else
			App__YesPage__Destroy(context, 0);
	}
	if (context->MainPage__Active)
		MainPage_Update(context->MainPage);
	if (context->Confirmation__Active)
		Confirmation_Update(context->Confirmation);
	if (context->YesPage__Active)
		YesPage_Update(context->YesPage);
	if (!context->MainPage__Active && (((context->_ActivePage == MainPage__ID))))
	{
		Ft_Esd_Spinner_Popup();
	}
	if (!context->Confirmation__Active && (((context->_ActivePage == Confirmation__ID))))
	{
		Ft_Esd_Spinner_Popup();
	}
	if (!context->YesPage__Active && (((context->_ActivePage == YesPage__ID))))
	{
		Ft_Esd_Spinner_Popup();
	}
}

void App_Render(App *context)
{
	void *parent = context->Parent;
	if (context->MainPage__Active)
		MainPage_Render(context->MainPage);
	if (context->Confirmation__Active)
		Confirmation_Render(context->Confirmation);
	if (context->YesPage__Active)
		YesPage_Render(context->YesPage);
}

void App_Idle(App *context)
{
	void *parent = context->Parent;
	if (context->MainPage__Active)
		MainPage_Idle(context->MainPage);
	if (context->Confirmation__Active)
		Confirmation_Idle(context->Confirmation);
	if (context->YesPage__Active)
		YesPage_Idle(context->YesPage);
}

void App_End(App *context)
{
	void *parent = context->Parent;
	if (context->MainPage__Active)
		App__MainPage__Destroy(context, 1);
	if (context->Confirmation__Active)
		App__Confirmation__Destroy(context, 1);
	if (context->YesPage__Active)
		App__YesPage__Destroy(context, 1);
}

void App_Start(App *context)
{
	void *parent = context->Parent;
	App_Start__Builtin(context);
	context->_ActivePage = MainPage__ID;
}

void App_MainPage_keyPad__Signal(void *c)
{
	App *context = (App *)c;
	void *parent = context->Parent;
	context->_ActivePage = YesPage__ID;
}

void App_YesPage_KeyPadBack__Signal(void *c)
{
	App *context = (App *)c;
	void *parent = context->Parent;
	context->_ActivePage = MainPage__ID;
}

void App_YesPage_Confirmation__Signal(void *c)
{
	App *context = (App *)c;
	void *parent = context->Parent;
	context->_ActivePage = Confirmation__ID;
	App__Confirmation__Validate(context);
	Confirmation_getParkingSpotID(context->Confirmation);
}

static App application;

void Ft_Main__Start()
{
	App__Initializer(&application);
	App_Start(&application);
}

void Ft_Main__Update()
{
	App_Update(&application);
}

void Ft_Main__Render()
{
	App_Render(&application);
}

void Ft_Main__Idle()
{
	App_Idle(&application);
}

void Ft_Main__End()
{
	App_End(&application);
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	App Instance;
} App__ESD;


void *App__Create__ESD()
{
	App__ESD *context = (App__ESD *)malloc(sizeof(App__ESD));
	App__Initializer(&context->Instance);
	context->Instance.Parent = context;
	return context;
}

void App__Destroy__ESD(void *context)
{
	free(context);
}


#endif /* ESD_SIMULATION */

/* end of file */
