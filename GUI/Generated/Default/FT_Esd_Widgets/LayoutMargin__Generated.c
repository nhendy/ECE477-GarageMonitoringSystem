/*
This file is automatically generated
LayoutMargin
C Source
*/

#include "LayoutMargin.h"

extern void Ft_Esd_Noop(void *context);
int LayoutMargin_X__Default(void *context) { return 0L; }
int LayoutMargin_Y__Default(void *context) { return 0L; }
int LayoutMargin_Width__Default(void *context) { return 0L; }
int LayoutMargin_Height__Default(void *context) { return 0L; }
int LayoutMargin_Margin__Default(void *context) { return 0L; }



void LayoutMargin__Initializer(LayoutMargin *context)
{
	context->Parent = 0;
	context->X = LayoutMargin_X__Default;
	context->Y = LayoutMargin_Y__Default;
	context->Width = LayoutMargin_Width__Default;
	context->Height = LayoutMargin_Height__Default;
	context->Margin = LayoutMargin_Margin__Default;
}

int LayoutMargin_OutX(LayoutMargin *context)
{
	void *parent = context->Parent;
	int left = context->X(parent);
	int right = context->Margin(parent);
	return left + right;
}

int LayoutMargin_OutY(LayoutMargin *context)
{
	void *parent = context->Parent;
	int left_1 = context->Y(parent);
	int right_1 = context->Margin(parent);
	return left_1 + right_1;
}

int LayoutMargin_OutWidth(LayoutMargin *context)
{
	void *parent = context->Parent;
	int left_2 = context->Width(parent);
	int left_3 = context->Margin(parent);
	int right_3 = 2L;
	int right_2 = left_3 * right_3;
	return left_2 - right_2;
}

int LayoutMargin_OutHeight(LayoutMargin *context)
{
	void *parent = context->Parent;
	int left_4 = context->Height(parent);
	int left_5 = context->Margin(parent);
	int right_5 = 2L;
	int right_4 = left_5 * right_5;
	return left_4 - right_4;
}

#ifdef ESD_SIMULATION
#include <stdlib.h>

typedef struct
{
	LayoutMargin Instance;
	int X;
	int Y;
	int Width;
	int Height;
	int Margin;
} LayoutMargin__ESD;

int LayoutMargin__Get_X__ESD(void *context) { return ((LayoutMargin__ESD *)context)->X; }
void LayoutMargin__Set_X__ESD(void *context, int value) { ((LayoutMargin__ESD *)context)->X = value; }
int LayoutMargin__Get_Y__ESD(void *context) { return ((LayoutMargin__ESD *)context)->Y; }
void LayoutMargin__Set_Y__ESD(void *context, int value) { ((LayoutMargin__ESD *)context)->Y = value; }
int LayoutMargin__Get_Width__ESD(void *context) { return ((LayoutMargin__ESD *)context)->Width; }
void LayoutMargin__Set_Width__ESD(void *context, int value) { ((LayoutMargin__ESD *)context)->Width = value; }
int LayoutMargin__Get_Height__ESD(void *context) { return ((LayoutMargin__ESD *)context)->Height; }
void LayoutMargin__Set_Height__ESD(void *context, int value) { ((LayoutMargin__ESD *)context)->Height = value; }
int LayoutMargin__Get_Margin__ESD(void *context) { return ((LayoutMargin__ESD *)context)->Margin; }
void LayoutMargin__Set_Margin__ESD(void *context, int value) { ((LayoutMargin__ESD *)context)->Margin = value; }

void *LayoutMargin__Create__ESD()
{
	LayoutMargin__ESD *context = (LayoutMargin__ESD *)malloc(sizeof(LayoutMargin__ESD));
	LayoutMargin__Initializer(&context->Instance);
	context->Instance.Parent = context;
	context->X = 0L;
	context->Instance.X = LayoutMargin__Get_X__ESD;
	context->Y = 0L;
	context->Instance.Y = LayoutMargin__Get_Y__ESD;
	context->Width = 0L;
	context->Instance.Width = LayoutMargin__Get_Width__ESD;
	context->Height = 0L;
	context->Instance.Height = LayoutMargin__Get_Height__ESD;
	context->Margin = 0L;
	context->Instance.Margin = LayoutMargin__Get_Margin__ESD;
	return context;
}

void LayoutMargin__Destroy__ESD(void *context)
{
	free(context);
}


#endif /* ESD_SIMULATION */

/* end of file */
