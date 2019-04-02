/**
* This source code ("the Software") is provided by Bridgetek Pte Ltd
* ("Bridgetek") subject to the licence terms set out
*   http://brtchip.com/BRTSourceCodeLicenseAgreement/ ("the Licence Terms").
* You must read the Licence Terms before downloading or using the Software.
* By installing or using the Software you agree to the Licence Terms. If you
* do not agree to the Licence Terms then do not download or use the Software.
*
* Without prejudice to the Licence Terms, here is a summary of some of the key
* terms of the Licence Terms (and in the event of any conflict between this
* summary and the Licence Terms then the text of the Licence Terms will
* prevail).
*
* The Software is provided "as is".
* There are no warranties (or similar) in relation to the quality of the
* Software. You use it at your own risk.
* The Software should not be used in, or for, any medical device, system or
* appliance. There are exclusions of Bridgetek liability for certain types of loss
* such as: special loss or damage; incidental loss or damage; indirect or
* consequential loss or damage; loss of income; loss of business; loss of
* profits; loss of revenue; loss of contracts; business interruption; loss of
* the use of money or anticipated savings; loss of information; loss of
* opportunity; loss of goodwill or reputation; and/or loss of, damage to or
* corruption of data.
* There is a monetary cap on Bridgetek's liability.
* The Software may have subsequently been amended by another user and then
* distributed by that other user ("Adapted Software").  If so that user may
* have additional licence terms that apply to those amendments. However, Bridgetek
* has no liability in relation to those amendments.
*/
#if defined(FT900_PLATFORM)

#ifndef _FT_PLATFORM_FT900_H_
#define _FT_PLATFORM_FT900_H_


/* Hardware or Module specific macros for gpio line numbers  */
#if defined(MM900EV1A) || defined(MM900EV2A) || defined(MM900EV3A) || defined(MM900EV_LITE)
#define FT800_SEL_PIN   						(0)
#define FT800_PD_N      						(43) //for mm900 module

#define FT900_UART0_TX							(48)
#define FT900_UART0_RX							(49)

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)
#endif


#if (defined(CLEO35))
#define FT800_SEL_PIN   						(0)
#define FT800_PD_N      						(66) //for cleo35 module

#define FT900_UART0_TX							(48)
#define FT900_UART0_RX							(49)

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)
#endif


#ifdef CLEO50
#define FT800_SEL_PIN   						(0)
#define FT800_PD_N      						(0) //for cleo50 module

#define FT900_UART0_TX							(48)
#define FT900_UART0_RX							(49)

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)
#endif


#ifdef FT900DEMOBOARD
#define FT800_SEL_PIN   						(0)
#define FT800_PD_N      						(32)

#define FT900_UART0_TX							(48)
#define FT900_UART0_RX							(49)

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)
#endif


#ifdef PANL35
#define FT800_SEL_PIN   						0
#define FT800_PD_N      						1
#define FT800_INT	      						0

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)
#endif

#ifdef PANL70
#define FT800_SEL_PIN   						0
#define FT800_PD_N      						1
#define FT800_INT	      						0
#define GOODIXGPIO	      						(33)

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)
#endif //PANL70


#ifdef PANL70PLUS
#define FT800_SEL_PIN   						0
#define FT800_PD_N      						1
#define FT800_INT	      						0
#define GOODIXGPIO								(33)

/* Timer 1 is been utilized in case of FT900 platform */
#define	FT900_FT_MILLIS_TIMER					(timer_select_b)
#define FT900_TIMER_MAX_VALUE 					(65536L)
#define FT900_TIMER_PRESCALE_VALUE 				(100)
#define FT900_TIMER_OVERFLOW_VALUE 				(1000)
#endif //PANL70PLUS


#ifndef RTC_PRESENT
#ifdef FT900_PLATFORM_RTC_I2C
#define RTC_PRESENT								(1)
#endif
#endif  /*RTC_PRESENT*/


/* Standard C libraries */
#define ESD_USING_NEW_LIB  // Using NewLib C Library for runtime

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


/* Data types */
#include "FT_DataTypes.h"


/* FT900 libraries */
#include "ft900_uart_simple.h"
#include "ft900_sdhost.h"
#include "ft900_spi.h"
#include "ft900_gpio.h"
#include "ft900_rtc.h"
#include "ft900_interrupt.h"
#include "ft900_i2cm.h"
#include "ft900.h"
#include "ft900_delay.h"

/* HAL inclusions */
#include "FT_Gpu_Hal.h"
#include "FT_Gpu.h"
#include "FT_CoPro_Cmds.h"
#include "FT_Hal_Utils.h"
#include "FT_ILI9488.h"
#include "FT_KD2401.h"
#endif

#if defined(BT_MODULE_PANL)
#include "panl.h"
#endif

#endif 

/* Nothing beyond this*/
