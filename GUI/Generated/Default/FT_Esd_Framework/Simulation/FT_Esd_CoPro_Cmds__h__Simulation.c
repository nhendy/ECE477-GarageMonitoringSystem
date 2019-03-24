/*
This file is automatically generated
FT_Esd_CoPro_Cmds__h
Simulation wrapper
*/

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Button' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Button(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, const ft_char8_t *);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t height;
	ft_int16_t font;
	ft_uint16_t options;
	const ft_char8_t * s;
} Ft_Gpu_CoCmd_Button__ESD;

void Ft_Gpu_CoCmd_Button__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Button__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Button__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Button__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Button__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Button__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Button__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Button__ESD *)context)->width = value; }
void Ft_Gpu_CoCmd_Button__Set_height__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Button__ESD *)context)->height = value; }
void Ft_Gpu_CoCmd_Button__Set_font__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Button__ESD *)context)->font = value; }
void Ft_Gpu_CoCmd_Button__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Button__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Button__Set_s__ESD(void *context, const ft_char8_t * value) { ((Ft_Gpu_CoCmd_Button__ESD *)context)->s = value; }

void *Ft_Gpu_CoCmd_Button__Create__ESD()
{
	Ft_Gpu_CoCmd_Button__ESD *context = (Ft_Gpu_CoCmd_Button__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Button__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->width = 60;
	context->height = 40;
	context->font = 21;
	context->options = 0;
	context->s = "Button";
	return context;
}

void Ft_Gpu_CoCmd_Button__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Button_Render(Ft_Gpu_CoCmd_Button__ESD *context)
{
	Ft_Gpu_CoCmd_Button(context->phost, context->x, context->y, context->width, context->height, context->font, context->options, context->s);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Clock' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Clock(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t r;
	ft_uint16_t options;
	ft_uint16_t height;
	ft_uint16_t m;
	ft_uint16_t s;
	ft_uint16_t ms;
} Ft_Gpu_CoCmd_Clock__ESD;

void Ft_Gpu_CoCmd_Clock__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Clock__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Clock__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Clock__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Clock__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Clock__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Clock__Set_r__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Clock__ESD *)context)->r = value; }
void Ft_Gpu_CoCmd_Clock__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Clock__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Clock__Set_height__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Clock__ESD *)context)->height = value; }
void Ft_Gpu_CoCmd_Clock__Set_m__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Clock__ESD *)context)->m = value; }
void Ft_Gpu_CoCmd_Clock__Set_s__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Clock__ESD *)context)->s = value; }
void Ft_Gpu_CoCmd_Clock__Set_ms__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Clock__ESD *)context)->ms = value; }

void *Ft_Gpu_CoCmd_Clock__Create__ESD()
{
	Ft_Gpu_CoCmd_Clock__ESD *context = (Ft_Gpu_CoCmd_Clock__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Clock__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->r = 40;
	context->options = 0;
	context->height = 0U;
	context->m = 0U;
	context->s = 0U;
	context->ms = 0U;
	return context;
}

void Ft_Gpu_CoCmd_Clock__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Clock_Render(Ft_Gpu_CoCmd_Clock__ESD *context)
{
	Ft_Gpu_CoCmd_Clock(context->phost, context->x, context->y, context->r, context->options, context->height, context->m, context->s, context->ms);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Dial' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Dial(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t r;
	ft_uint16_t options;
	ft_uint16_t val;
} Ft_Gpu_CoCmd_Dial__ESD;

void Ft_Gpu_CoCmd_Dial__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Dial__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Dial__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Dial__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Dial__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Dial__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Dial__Set_r__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Dial__ESD *)context)->r = value; }
void Ft_Gpu_CoCmd_Dial__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Dial__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Dial__Set_val__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Dial__ESD *)context)->val = value; }

void *Ft_Gpu_CoCmd_Dial__Create__ESD()
{
	Ft_Gpu_CoCmd_Dial__ESD *context = (Ft_Gpu_CoCmd_Dial__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Dial__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->r = 40;
	context->options = 0;
	context->val = 0U;
	return context;
}

void Ft_Gpu_CoCmd_Dial__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Dial_Render(Ft_Gpu_CoCmd_Dial__ESD *context)
{
	Ft_Gpu_CoCmd_Dial(context->phost, context->x, context->y, context->r, context->options, context->val);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Gauge' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Gauge(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t r;
	ft_uint16_t options;
	ft_uint16_t major;
	ft_uint16_t minor;
	ft_uint16_t val;
	ft_uint16_t range;
} Ft_Gpu_CoCmd_Gauge__ESD;

void Ft_Gpu_CoCmd_Gauge__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Gauge__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Gauge__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Gauge__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Gauge__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Gauge__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Gauge__Set_r__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Gauge__ESD *)context)->r = value; }
void Ft_Gpu_CoCmd_Gauge__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Gauge__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Gauge__Set_major__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Gauge__ESD *)context)->major = value; }
void Ft_Gpu_CoCmd_Gauge__Set_minor__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Gauge__ESD *)context)->minor = value; }
void Ft_Gpu_CoCmd_Gauge__Set_val__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Gauge__ESD *)context)->val = value; }
void Ft_Gpu_CoCmd_Gauge__Set_range__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Gauge__ESD *)context)->range = value; }

void *Ft_Gpu_CoCmd_Gauge__Create__ESD()
{
	Ft_Gpu_CoCmd_Gauge__ESD *context = (Ft_Gpu_CoCmd_Gauge__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Gauge__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->r = 40;
	context->options = 0;
	context->major = 0U;
	context->minor = 0U;
	context->val = 0U;
	context->range = 0U;
	return context;
}

void Ft_Gpu_CoCmd_Gauge__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Gauge_Render(Ft_Gpu_CoCmd_Gauge__ESD *context)
{
	Ft_Gpu_CoCmd_Gauge(context->phost, context->x, context->y, context->r, context->options, context->major, context->minor, context->val, context->range);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Keys' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Keys(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, const ft_char8_t *);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t height;
	ft_int16_t font;
	ft_uint16_t options;
	const ft_char8_t * s;
} Ft_Gpu_CoCmd_Keys__ESD;

void Ft_Gpu_CoCmd_Keys__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Keys__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Keys__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Keys__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Keys__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Keys__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Keys__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Keys__ESD *)context)->width = value; }
void Ft_Gpu_CoCmd_Keys__Set_height__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Keys__ESD *)context)->height = value; }
void Ft_Gpu_CoCmd_Keys__Set_font__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Keys__ESD *)context)->font = value; }
void Ft_Gpu_CoCmd_Keys__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Keys__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Keys__Set_s__ESD(void *context, const ft_char8_t * value) { ((Ft_Gpu_CoCmd_Keys__ESD *)context)->s = value; }

void *Ft_Gpu_CoCmd_Keys__Create__ESD()
{
	Ft_Gpu_CoCmd_Keys__ESD *context = (Ft_Gpu_CoCmd_Keys__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Keys__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->width = 60;
	context->height = 40;
	context->font = 21;
	context->options = 0;
	context->s = "Button";
	return context;
}

void Ft_Gpu_CoCmd_Keys__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Keys_Render(Ft_Gpu_CoCmd_Keys__ESD *context)
{
	Ft_Gpu_CoCmd_Keys(context->phost, context->x, context->y, context->width, context->height, context->font, context->options, context->s);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Number' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Number(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_int32_t);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t font;
	ft_uint16_t options;
	ft_int32_t n;
} Ft_Gpu_CoCmd_Number__ESD;

void Ft_Gpu_CoCmd_Number__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Number__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Number__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Number__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Number__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Number__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Number__Set_font__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Number__ESD *)context)->font = value; }
void Ft_Gpu_CoCmd_Number__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Number__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Number__Set_n__ESD(void *context, ft_int32_t value) { ((Ft_Gpu_CoCmd_Number__ESD *)context)->n = value; }

void *Ft_Gpu_CoCmd_Number__Create__ESD()
{
	Ft_Gpu_CoCmd_Number__ESD *context = (Ft_Gpu_CoCmd_Number__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Number__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->font = 21;
	context->options = 0;
	context->n = 0L;
	return context;
}

void Ft_Gpu_CoCmd_Number__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Number_Render(Ft_Gpu_CoCmd_Number__ESD *context)
{
	Ft_Gpu_CoCmd_Number(context->phost, context->x, context->y, context->font, context->options, context->n);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Progress' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Progress(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t height;
	ft_uint16_t options;
	ft_uint16_t val;
	ft_uint16_t range;
} Ft_Gpu_CoCmd_Progress__ESD;

void Ft_Gpu_CoCmd_Progress__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Progress__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Progress__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Progress__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Progress__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Progress__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Progress__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Progress__ESD *)context)->width = value; }
void Ft_Gpu_CoCmd_Progress__Set_height__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Progress__ESD *)context)->height = value; }
void Ft_Gpu_CoCmd_Progress__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Progress__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Progress__Set_val__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Progress__ESD *)context)->val = value; }
void Ft_Gpu_CoCmd_Progress__Set_range__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Progress__ESD *)context)->range = value; }

void *Ft_Gpu_CoCmd_Progress__Create__ESD()
{
	Ft_Gpu_CoCmd_Progress__ESD *context = (Ft_Gpu_CoCmd_Progress__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Progress__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->width = 60;
	context->height = 40;
	context->options = 0;
	context->val = 0U;
	context->range = 0U;
	return context;
}

void Ft_Gpu_CoCmd_Progress__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Progress_Render(Ft_Gpu_CoCmd_Progress__ESD *context)
{
	Ft_Gpu_CoCmd_Progress(context->phost, context->x, context->y, context->width, context->height, context->options, context->val, context->range);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Scrollbar' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Scrollbar(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t height;
	ft_uint16_t options;
	ft_uint16_t val;
	ft_uint16_t size;
	ft_uint16_t range;
} Ft_Gpu_CoCmd_Scrollbar__ESD;

void Ft_Gpu_CoCmd_Scrollbar__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Scrollbar__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Scrollbar__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Scrollbar__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Scrollbar__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Scrollbar__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Scrollbar__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Scrollbar__ESD *)context)->width = value; }
void Ft_Gpu_CoCmd_Scrollbar__Set_height__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Scrollbar__ESD *)context)->height = value; }
void Ft_Gpu_CoCmd_Scrollbar__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Scrollbar__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Scrollbar__Set_val__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Scrollbar__ESD *)context)->val = value; }
void Ft_Gpu_CoCmd_Scrollbar__Set_size__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Scrollbar__ESD *)context)->size = value; }
void Ft_Gpu_CoCmd_Scrollbar__Set_range__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Scrollbar__ESD *)context)->range = value; }

void *Ft_Gpu_CoCmd_Scrollbar__Create__ESD()
{
	Ft_Gpu_CoCmd_Scrollbar__ESD *context = (Ft_Gpu_CoCmd_Scrollbar__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Scrollbar__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->width = 60;
	context->height = 40;
	context->options = 0;
	context->val = 0U;
	context->size = 0U;
	context->range = 0U;
	return context;
}

void Ft_Gpu_CoCmd_Scrollbar__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Scrollbar_Render(Ft_Gpu_CoCmd_Scrollbar__ESD *context)
{
	Ft_Gpu_CoCmd_Scrollbar(context->phost, context->x, context->y, context->width, context->height, context->options, context->val, context->size, context->range);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Slider' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Slider(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t, ft_uint16_t);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t height;
	ft_uint16_t options;
	ft_uint16_t val;
	ft_uint16_t range;
} Ft_Gpu_CoCmd_Slider__ESD;

void Ft_Gpu_CoCmd_Slider__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Slider__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Slider__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Slider__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Slider__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Slider__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Slider__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Slider__ESD *)context)->width = value; }
void Ft_Gpu_CoCmd_Slider__Set_height__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Slider__ESD *)context)->height = value; }
void Ft_Gpu_CoCmd_Slider__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Slider__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Slider__Set_val__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Slider__ESD *)context)->val = value; }
void Ft_Gpu_CoCmd_Slider__Set_range__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Slider__ESD *)context)->range = value; }

void *Ft_Gpu_CoCmd_Slider__Create__ESD()
{
	Ft_Gpu_CoCmd_Slider__ESD *context = (Ft_Gpu_CoCmd_Slider__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Slider__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->width = 60;
	context->height = 40;
	context->options = 0;
	context->val = 0U;
	context->range = 0U;
	return context;
}

void Ft_Gpu_CoCmd_Slider__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Slider_Render(Ft_Gpu_CoCmd_Slider__ESD *context)
{
	Ft_Gpu_CoCmd_Slider(context->phost, context->x, context->y, context->width, context->height, context->options, context->val, context->range);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Spinner' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Spinner(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_uint16_t style;
	ft_uint16_t scale;
} Ft_Gpu_CoCmd_Spinner__ESD;

void Ft_Gpu_CoCmd_Spinner__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Spinner__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Spinner__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Spinner__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Spinner__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Spinner__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Spinner__Set_style__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Spinner__ESD *)context)->style = value; }
void Ft_Gpu_CoCmd_Spinner__Set_scale__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Spinner__ESD *)context)->scale = value; }

void *Ft_Gpu_CoCmd_Spinner__Create__ESD()
{
	Ft_Gpu_CoCmd_Spinner__ESD *context = (Ft_Gpu_CoCmd_Spinner__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Spinner__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->style = 0U;
	context->scale = 0U;
	return context;
}

void Ft_Gpu_CoCmd_Spinner__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Spinner_Render(Ft_Gpu_CoCmd_Spinner__ESD *context)
{
	Ft_Gpu_CoCmd_Spinner(context->phost, context->x, context->y, context->style, context->scale);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Text' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Text(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, const ft_char8_t *);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t font;
	ft_uint16_t options;
	const ft_char8_t * s;
} Ft_Gpu_CoCmd_Text__ESD;

void Ft_Gpu_CoCmd_Text__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Text__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Text__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Text__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Text__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Text__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Text__Set_font__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Text__ESD *)context)->font = value; }
void Ft_Gpu_CoCmd_Text__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Text__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Text__Set_s__ESD(void *context, const ft_char8_t * value) { ((Ft_Gpu_CoCmd_Text__ESD *)context)->s = value; }

void *Ft_Gpu_CoCmd_Text__Create__ESD()
{
	Ft_Gpu_CoCmd_Text__ESD *context = (Ft_Gpu_CoCmd_Text__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Text__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->font = 21;
	context->options = 0;
	context->s = "Text";
	return context;
}

void Ft_Gpu_CoCmd_Text__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Text_Render(Ft_Gpu_CoCmd_Text__ESD *context)
{
	Ft_Gpu_CoCmd_Text(context->phost, context->x, context->y, context->font, context->options, context->s);
}

#endif /* ESD_SIMULATION */

/* Simulation wrapper for 'Ft_Gpu_CoCmd_Toggle' */

#ifdef ESD_SIMULATION
#include <stdlib.h>
#include "FT_Esd_CoPro_Cmds.h"

ft_void_t Ft_Gpu_CoCmd_Toggle(Ft_Gpu_Hal_Context_t *, ft_int16_t, ft_int16_t, ft_int16_t, ft_int16_t, ft_uint16_t, ft_uint16_t, const ft_char8_t *);

typedef struct
{
	Ft_Gpu_Hal_Context_t * phost;
	ft_int16_t x;
	ft_int16_t y;
	ft_int16_t width;
	ft_int16_t font;
	ft_uint16_t options;
	ft_uint16_t state;
	const ft_char8_t * s;
} Ft_Gpu_CoCmd_Toggle__ESD;

void Ft_Gpu_CoCmd_Toggle__Set_phost__ESD(void *context, Ft_Gpu_Hal_Context_t * value) { ((Ft_Gpu_CoCmd_Toggle__ESD *)context)->phost = value; }
void Ft_Gpu_CoCmd_Toggle__Set_x__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Toggle__ESD *)context)->x = value; }
void Ft_Gpu_CoCmd_Toggle__Set_y__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Toggle__ESD *)context)->y = value; }
void Ft_Gpu_CoCmd_Toggle__Set_width__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Toggle__ESD *)context)->width = value; }
void Ft_Gpu_CoCmd_Toggle__Set_font__ESD(void *context, ft_int16_t value) { ((Ft_Gpu_CoCmd_Toggle__ESD *)context)->font = value; }
void Ft_Gpu_CoCmd_Toggle__Set_options__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Toggle__ESD *)context)->options = value; }
void Ft_Gpu_CoCmd_Toggle__Set_state__ESD(void *context, ft_uint16_t value) { ((Ft_Gpu_CoCmd_Toggle__ESD *)context)->state = value; }
void Ft_Gpu_CoCmd_Toggle__Set_s__ESD(void *context, const ft_char8_t * value) { ((Ft_Gpu_CoCmd_Toggle__ESD *)context)->s = value; }

void *Ft_Gpu_CoCmd_Toggle__Create__ESD()
{
	Ft_Gpu_CoCmd_Toggle__ESD *context = (Ft_Gpu_CoCmd_Toggle__ESD *)malloc(sizeof(Ft_Gpu_CoCmd_Toggle__ESD));
	context->phost = Ft_Esd_GetHost();
	context->x = 0;
	context->y = 0;
	context->width = 60;
	context->font = 21;
	context->options = 0;
	context->state = 0U;
	context->s = "on\\x00off";
	return context;
}

void Ft_Gpu_CoCmd_Toggle__Destroy__ESD(void *context)
{
	free(context);
}

void Ft_Gpu_CoCmd_Toggle_Render(Ft_Gpu_CoCmd_Toggle__ESD *context)
{
	Ft_Gpu_CoCmd_Toggle(context->phost, context->x, context->y, context->width, context->font, context->options, context->state, context->s);
}

#endif /* ESD_SIMULATION */

/* end of file */
