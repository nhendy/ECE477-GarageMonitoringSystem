/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2019 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FT812.h"
#include "main.h"

#include "stm32f7xx.h"
#include "hal_stm_lvgl/tft/tft.h"
#include "hal_stm_lvgl/touchpad/touchpad.h"
#include "lvgl/lvgl.h"
#include "lv_examples/lv_tests/lv_test_theme/lv_test_theme_2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

/* USER CODE BEGIN PV */
// AN_312 FT812 pin definitions
#define FT812_PD_N	GPIO_PIN_0
#define FT812_CS_N	GPIO_PIN_1

// AN312 FT812 screen size - uncomment the appropriate size
//#define LCD_QVGA																			// VM800B/C 3.5" QVGA - 320x240
//#define LCD_WQVGA																				// VM800B/C 4.3" & 5.0" WQVGA - 480x272
#define LCD_800480
// AN_312 Colors - fully saturated colors defined here
#define RED					0xFF0000UL													// Red
#define GREEN				0x00FF00UL													// Green
#define BLUE				0x0000FFUL													// Blue
#define WHITE				0xFFFFFFUL													// White
#define BLACK				0x000000UL													// Black

// Global Variables

// AN_312 FT812 pins
unsigned int ft812irqPin;																// Interrupt from FT812 to Arduino - not used here
unsigned int ft812pwrPin;																// PD_N from Arduino to FT812 - effectively FT812 reset
unsigned int ft812csPin;																// SPI chip select - defined separately since it's manipulated with GPIO calls

// AN_312 LCD display parameters
unsigned int lcdWidth;																	// Active width of LCD display
unsigned int lcdHeight;																	// Active height of LCD display
unsigned int lcdHcycle;																	// Total number of clocks per line
unsigned int lcdHoffset;																// Start of active line
unsigned int lcdHsync0;																	// Start of horizontal sync pulse
unsigned int lcdHsync1;																	// End of horizontal sync pulse
unsigned int lcdVcycle;																	// Total number of lines per screen
unsigned int lcdVoffset;																// Start of active screen
unsigned int lcdVsync0;																	// Start of vertical sync pulse
unsigned int lcdVsync1;																	// End of vertical sync pulse
unsigned char lcdPclk;																	// Pixel Clock
unsigned char lcdSwizzle;																// Define RGB output pins
unsigned char lcdPclkpol;																// Define active edge of PCLK

unsigned long ramDisplayList = RAM_DL;									// Set beginning of display list memory
unsigned long ramCommandBuffer = RAM_CMD;								// Set beginning of graphics command memory

unsigned int cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
unsigned int cmdBufferWr = 0x0000;											// Used to navigate command ring buffer
unsigned int cmdOffset = 0x0000;												// Used to navigate command rung buffer
unsigned int point_size = 0x0100;												// Define a default dot size
unsigned long point_x = (96 * 16);											// Define a default point x-location (1/16 anti-aliased)
unsigned long point_y = (136 * 16);											// Define a default point y-location (1/16 anti-aliased)
unsigned long color;																		// Variable for chanign colors
unsigned char ft812Gpio;																// Used for FT812 GPIO register

// AN_312 Specific function prototypes - See full descriptions below
static void ft812cmdWrite(unsigned char);
static void ft812memWrite8(unsigned long, unsigned char);
static void ft812memWrite16(unsigned long, unsigned int);
static void ft812memWrite32(unsigned long, unsigned long);
unsigned char ft812memRead8(unsigned long);
unsigned int ft812memRead16(unsigned long);
unsigned long ft812memRead32(unsigned long);
unsigned int incCMDOffset(unsigned int, unsigned char);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
#ifdef LCD_QVGA																					// QVGA display parameters
	lcdWidth   = 320;																			// Active width of LCD display
	lcdHeight  = 240;																			// Active height of LCD display
	lcdHcycle  = 408;																			// Total number of clocks per line
	lcdHoffset = 70;																			// Start of active line
	lcdHsync0  = 0;																				// Start of horizontal sync pulse
	lcdHsync1  = 10;																			// End of horizontal sync pulse
	lcdVcycle  = 263;																			// Total number of lines per screen
	lcdVoffset = 13;																			// Start of active screen
	lcdVsync0  = 0;																				// Start of vertical sync pulse
	lcdVsync1  = 2;																				// End of vertical sync pulse
	lcdPclk    = 8;																				// Pixel Clock
	lcdSwizzle = 2;																				// Define RGB output pins
	lcdPclkpol = 0;																				// Define active edge of PCLK
#endif

#ifdef LCD_WQVGA																				// WQVGA display parameters
	lcdWidth   = 480;																			// Active width of LCD display
	lcdHeight  = 272;																			// Active height of LCD display
	lcdHcycle  = 548;																			// Total number of clocks per line
	lcdHoffset = 43;																			// Start of active line
	lcdHsync0  = 0;																				// Start of horizontal sync pulse
	lcdHsync1  = 41;																			// End of horizontal sync pulse
	lcdVcycle  = 292;																			// Total number of lines per screen
	lcdVoffset = 12;																			// Start of active screen
	lcdVsync0  = 0;																				// Start of vertical sync pulse
	lcdVsync1  = 10;																			// End of vertical sync pulse
	lcdPclk    = 5;																				// Pixel Clock
	lcdSwizzle = 0;																				// Define RGB output pins
	lcdPclkpol = 1;																				// Define active edge of PCLK
#endif

#ifdef LCD_800480																				// WQVGA display parameters
	lcdWidth   = 800;																			// Active width of LCD display
	lcdHeight  = 480;																			// Active height of LCD display
	lcdHcycle  = 928;																			// Total number of clocks per line
	lcdHoffset = 88;																			// Start of active line
	lcdHsync0  = 0;																				// Start of horizontal sync pulse
	lcdHsync1  = 48;																			// End of horizontal sync pulse
	lcdVcycle  = 525;																			// Total number of lines per screen
	lcdVoffset = 32;																			// Start of active screen
	lcdVsync0  = 0;																				// Start of vertical sync pulse
	lcdVsync1  = 3;																			// End of vertical sync pulse
	lcdPclk    = 2;																				// Pixel Clock
	lcdSwizzle = 0;																				// Define RGB output pins
	lcdPclkpol = 1;																				// Define active edge of PCLK
#endif

	HAL_GPIO_WritePin(GPIOB, FT812_PD_N, GPIO_PIN_SET); 	// Initial state of PD_N - high
	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_SET);		// Initial state of SPI CS - high
	HAL_Delay(20);																				// Wait 20ms
	HAL_GPIO_WritePin(GPIOB, FT812_PD_N, GPIO_PIN_RESET); // Reset FT812
	HAL_Delay(20);																				// Wait 20ms
	HAL_GPIO_WritePin(GPIOB, FT812_PD_N, GPIO_PIN_SET); 	// FT812 is awake
	HAL_Delay(20);																				// Wait 20ms - required
	ft812cmdWrite(FT812_CLKEXT);													// Set FT812 for external clock
		HAL_Delay(20);																					// Give some time to process
	ft812cmdWrite(FT812_ACTIVE);													// Start FT812
	HAL_Delay(20);																					// Give some time to process

	ft812cmdWrite(FT812_CLK48M);													// Set FT812 for 48MHz PLL
	HAL_Delay(20);																					// Give some time to process
	// Now FT812 can accept commands at up to 30MHz clock on SPI bus
	//   This application leaves the SPI bus at 8MHz
	///////////////////////////////
	//Getting stuck in the while loop here
	ft812memWrite8(REG_PWM_DUTY, ZERO);										// Turn off backlight
	volatile int a = ft812memRead8(REG_ID);
	volatile int b = ft812memRead8(REG_ID);
	volatile int c = ft812memRead8(REG_ID);

	//////////////////////////////////
	if (ft812memRead8(REG_ID) != 0x7C)											// Read ID register - is it 0x7C?
	{
		while(1);	// If we don't get 0x7C, the ineface isn't working - halt with infinite loop
	}

	ft812memWrite8(REG_PCLK, ZERO);												// Set PCLK to zero - don't clock the LCD until later
	ft812memWrite8(REG_PWM_DUTY, ZERO);										// Turn off backlight

	// End of Wake-up FT812

	//***************************************
	// Initialize Display
	ft812memWrite16(REG_HSIZE,   lcdWidth);								// active display width
	ft812memWrite16(REG_HCYCLE,  lcdHcycle);							// total number of clocks per line, incl front/back porch
	ft812memWrite16(REG_HOFFSET, lcdHoffset);							// start of active line
	ft812memWrite16(REG_HSYNC0,  lcdHsync0);							// start of horizontal sync pulse
	ft812memWrite16(REG_HSYNC1,  lcdHsync1);							// end of horizontal sync pulse
	ft812memWrite16(REG_VSIZE,   lcdHeight);							// active display height
	ft812memWrite16(REG_VCYCLE,  lcdVcycle);							// total number of lines per screen, incl pre/post
	ft812memWrite16(REG_VOFFSET, lcdVoffset);							// start of active screen
	ft812memWrite16(REG_VSYNC0,  lcdVsync0);							// start of vertical sync pulse
	ft812memWrite16(REG_VSYNC1,  lcdVsync1);							// end of vertical sync pulse
	ft812memWrite8(REG_SWIZZLE,  lcdSwizzle);							// FT812 output to LCD - pin order
	ft812memWrite8(REG_PCLK_POL, lcdPclkpol);							// LCD data is clocked in on this PCLK edge
	// Don't set PCLK yet - wait for just after the first display list
	// End of Initialize Display
	//***************************************

	//***************************************
	// Configure Touch and Audio - not used in this example, so disable both
	ft812memWrite8(REG_TOUCH_MODE, ZERO);									// Disable touch
	ft812memWrite16(REG_TOUCH_RZTHRESH, ZERO);						// Eliminate any false touches

	ft812memWrite8(REG_VOL_PB, ZERO);											// turn recorded audio volume down
	ft812memWrite8(REG_VOL_SOUND, ZERO);									// turn synthesizer volume down
	ft812memWrite16(REG_SOUND, 0x6000);										// set synthesizer to mute

	// End of Configure Touch and Audio
	//***************************************

	//***************************************
	// Write Initial Display List & Enable Display

	ramDisplayList = RAM_DL;															// start of Display List
	ft812memWrite32(ramDisplayList, DL_CLEAR_RGB); 				// Clear Color RGB   00000010 RRRRRRRR GGGGGGGG BBBBBBBB  (R/G/B = Colour values) default zero / black
	ramDisplayList += 4;																	// point to next location
	ft812memWrite32(ramDisplayList, (DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG));
	// Clear 00100110 -------- -------- -----CST  (C/S/T define which parameters to clear)
	ramDisplayList += 4;																	// point to next location
	ft812memWrite32(ramDisplayList, DL_DISPLAY);					// DISPLAY command 00000000 00000000 00000000 00000000 (end of display list)

	ft812memWrite32(REG_DLSWAP, DLSWAP_FRAME);						// 00000000 00000000 00000000 000000SS  (SS bits define when render occurs)
	// Nothing is being displayed yet... the pixel clock is still 0x00
	ramDisplayList = RAM_DL;															// Reset Display List pointer for next list

	ft812Gpio = ft812memRead8(REG_GPIO);									// Read the FT812 GPIO register for a read/modify/write operation
	ft812Gpio = ft812Gpio | 0x80;													// set bit 7 of FT812 GPIO register (DISP) - others are inputs
	ft812memWrite8(REG_GPIO, ft812Gpio);									// Enable the DISP signal to the LCD panel
	ft812memWrite8(REG_PCLK, lcdPclk);										// Now start clocking data to the LCD panel
	for(int duty = 0; duty <= 128; duty++)
	{
		ft812memWrite8(REG_PWM_DUTY, duty);									// Turn on backlight - ramp up slowly to full brighness
		HAL_Delay(10);
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		do
				{
					cmdBufferRd = ft812memRead16(REG_CMD_READ);					// Read the graphics processor read pointer
					cmdBufferWr = ft812memRead16(REG_CMD_WRITE); 				// Read the graphics processor write pointer
				}while (cmdBufferWr != cmdBufferRd);									// Wait until the two registers match

				cmdOffset = cmdBufferWr;															// The new starting point the first location after the last command

				if (color != WHITE)																		// If a red dot was just drawn (or first time through)...
					color = WHITE;																			// change color to white
				else																									// Otherwise...
					color = RED;																				// change the color to red

				ft812memWrite32(RAM_CMD + cmdOffset, (CMD_DLSTART));// Start the display list
				cmdOffset = incCMDOffset(cmdOffset, 4);								// Update the command pointer

				ft812memWrite32(RAM_CMD + cmdOffset, (DL_CLEAR_RGB | BLACK));
																														// Set the default clear color to black
				cmdOffset = incCMDOffset(cmdOffset, 4);								// Update the command pointer


				ft812memWrite32(RAM_CMD + cmdOffset, (DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG));
																														// Clear the screen - this and the previous prevent artifacts between lists
																														// Attributes are the color, stencil and tag buffers
				cmdOffset = incCMDOffset(cmdOffset, 4);								// Update the command pointer


				ft812memWrite32(RAM_CMD + cmdOffset, (DL_COLOR_RGB | color));
																														// Set the color of the following item(s) - toggle red/white from above
				cmdOffset = incCMDOffset(cmdOffset, 4);								// Update the command pointer


				ft812memWrite32(RAM_CMD + cmdOffset, (DL_POINT_SIZE | point_size));
																														// Select the size of the dot to draw
				cmdOffset = incCMDOffset(cmdOffset, 4);								// Update the command pointer


				ft812memWrite32(RAM_CMD + cmdOffset, (DL_BEGIN | FTPOINTS));
																														// Indicate to draw a point (dot)
				cmdOffset = incCMDOffset(cmdOffset, 4);								// Update the command pointer


				ft812memWrite32(RAM_CMD + cmdOffset, (DL_VERTEX2F | (point_x << 15) | point_y));
																														// Set the point center location
				cmdOffset = incCMDOffset(cmdOffset, 4);								// Update the command pointer


				ft812memWrite32(RAM_CMD + cmdOffset, (DL_END));				// End the point
				cmdOffset = incCMDOffset(cmdOffset, 4);								// Update the command pointer


				ft812memWrite32(RAM_CMD + cmdOffset, (DL_DISPLAY));		// Instruct the graphics processor to show the list
				cmdOffset = incCMDOffset(cmdOffset, 4);								// Update the command pointer


				ft812memWrite32(RAM_CMD + cmdOffset, (CMD_SWAP));			// Make this list active
				cmdOffset = incCMDOffset(cmdOffset, 4);								// Update the command pointer


				ft812memWrite16(REG_CMD_WRITE, (cmdOffset));					// Update the ring buffer pointer so the graphics processor starts executing

				HAL_Delay(500);																				// Wait a half-second to observe the changing color


		 // End of loop()
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void ft812cmdWrite(unsigned char ftCommand)
{
	unsigned char cZero = 0x00;														// Filler value for command
	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_RESET);	// Set chip select low
	HAL_SPI_Transmit(&hspi1, &ftCommand, 1, 0);						// Send command
	HAL_SPI_Transmit(&hspi1, &cZero, 1, 0);								// Send first filler byte
	HAL_SPI_Transmit(&hspi1, &cZero, 1, 0);								// Send second filler byte
	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_SET);		// Set chip select high
}

/******************************************************************************
 * Function:        void ft812memWritexx(ftAddress, ftDataxx, ftLength)
 * PreCondition:    None
 * Input:           ftAddress = FT812 memory space address
 *                  ftDataxx = a byte, int or long to send
 * Output:          None
 * Side Effects:    None
 * Overview:        Writes FT812 internal address space
 * Note:            "xx" is one of 8, 16 or 32
 *****************************************************************************/
void ft812memWrite8(unsigned long ftAddress, unsigned char ftData8)
{
	unsigned char cTempAddr[3];														// FT812 Memory Address

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_WRITE;	// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_RESET);	// Set chip select low

  for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, 0); 			// Send Memory Write plus high address byte
	}

	for (int j = 0; j < sizeof(ftData8); j++)
	{
		HAL_SPI_Transmit(&hspi1, &ftData8, 1, 0);						// Send data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_SET);		// Set chip select high
}

void ft812memWrite16(unsigned long ftAddress, unsigned int ftData16)
{
	unsigned char cTempAddr[3];														// FT812 Memory Address
	unsigned char cTempData[2];														// 16-bit data to write

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_WRITE;	// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	cTempData[1] = (char) (ftData16 >> 8);								// Compose data to be sent - high byte
	cTempData[0] = (char) (ftData16);											// low byte

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_RESET);	// Set chip select low

  for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, 0); 			// Send Memory Write plus high address byte
	}

	for (int j = 0; j < sizeof(cTempData); j++)						// Start with least significant byte
	{
		HAL_SPI_Transmit(&hspi1, &cTempData[j], 1, 0);			// Send data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_SET);		// Set chip select high
}

void ft812memWrite32(unsigned long ftAddress, unsigned long ftData32)
{
	unsigned char cTempAddr[3];														// FT812 Memory Address
	unsigned char cTempData[4];														// 32-bit data to write

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_WRITE;	// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	cTempData[3] = (char) (ftData32 >> 24);								// Compose data to be sent - high byte
	cTempData[2] = (char) (ftData32 >> 16);								//
	cTempData[1] = (char) (ftData32 >> 8);								//
	cTempData[0] = (char) (ftData32);											// low byte

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_RESET);	// Set chip select low

  for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, 0); 			// Send Memory Write plus high address byte
	}

	for (int j = 0; j < sizeof(cTempData); j++)						// Start with least significant byte
	{
		HAL_SPI_Transmit(&hspi1, &cTempData[j], 1, 0);			// Send SPI byte
	}

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_SET);		// Set chip select high
}
/******************************************************************************
 * Function:        unsigned char ft812memReadxx(ftAddress, ftLength)
 * PreCondition:    None
 * Input:           ftAddress = FT812 memory space address
 * Output:          ftDataxx (byte, int or long)
 * Side Effects:    None
 * Overview:        Reads FT812 internal address space
 * Note:            "xx" is one of 8, 16 or 32
 *****************************************************************************/
unsigned char ft812memRead8(unsigned long ftAddress)
{
  unsigned char ftData8 = ZERO;													// Place-holder for 8-bits being read
	unsigned char cTempAddr[3];														// FT812 Memory Address
	unsigned char cZeroFill = ZERO;												// Dummy byte

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_READ;		// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_RESET);	// Set chip select low

  for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, 0); 			// Send Memory Write plus high address byte
	}

  HAL_SPI_Transmit(&hspi1, &cZeroFill, 1, 0);						// Send dummy byte

	for (int j = 0; j < sizeof(ftData8); j++)							// Start with least significant byte
	{
		HAL_SPI_Receive(&hspi1, &ftData8, 1, 0);						// Receive data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_SET);		// Set chip select high

  return ftData8;																				// Return 8-bits
}

unsigned int ft812memRead16(unsigned long ftAddress)
{
  unsigned int ftData16;																// 16-bits to return
	unsigned char cTempAddr[3];														// FT812 Memory Address
	unsigned char cTempData[2];														// Place-holder for 16-bits being read
	unsigned char cZeroFill;

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_READ;		// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_RESET);	// Set chip select low

  for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, 0); 			// Send Memory Write plus high address byte
	}

  HAL_SPI_Transmit(&hspi1, &cZeroFill, 1, 0);						// Send dummy byte

	for (int j = 0; j < sizeof(cTempData); j++)						// Start with least significant byte
	{
		HAL_SPI_Receive(&hspi1, &cTempData[j], 1, 0);				// Receive data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_SET);		// Set chip select high

	ftData16 = (cTempData[1]<< 8) | 											// Compose value to return - high byte
					   (cTempData[0]); 														// low byte

  return ftData16;																			// Return 16-bits
}

unsigned long ft812memRead32(unsigned long ftAddress)
{
  unsigned long ftData32;																// 32-bits to return
	unsigned char cTempAddr[3];														// FT812 Memory Address
	unsigned char cTempData[4];														// Place holder for 32-bits being read
	unsigned char cZeroFill;															// Dummy byte

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_READ;		// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_RESET);	// Set chip select low

  for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, 0); 			// Send Memory Write plus high address byte
	}

  HAL_SPI_Transmit(&hspi1, &cZeroFill, 1, 0);						// Send dummy byte

	for (int j = 0; j < sizeof(cTempData); j++)						// Start with least significatn byte
	{
		HAL_SPI_Receive(&hspi1, &cTempData[j], 1, 0);				// Receive data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT812_CS_N, GPIO_PIN_SET);		// Set chip select high

	ftData32 = (cTempData[3]<< 24) | 											// Compose value to return - high byte
						 (cTempData[2]<< 16) |
						 (cTempData[1]<< 8) |
						 (cTempData[0]); 														// Low byte

  return ftData32;																			// Return 32-bits
}

/******************************************************************************
 * Function:        void incCMDOffset(currentOffset, commandSize)
 * PreCondition:    None
 *                    starting a command list
 * Input:           currentOffset = graphics processor command list pointer
 *                  commandSize = number of bytes to increment the offset
 * Output:          newOffset = the new ring buffer pointer after adding the command
 * Side Effects:    None
 * Overview:        Adds commandSize to the currentOffset.
 *                  Checks for 4K ring-buffer offset roll-over
 * Note:            None
 *****************************************************************************/
unsigned int incCMDOffset(unsigned int currentOffset, unsigned char commandSize)
{
    unsigned int newOffset;															// Used to hold new offset
    newOffset = currentOffset + commandSize;						// Calculate new offset
    if(newOffset > 4095)																// If new offset past boundary...
    {
        newOffset = (newOffset - 4096);									// ... roll over pointer
    }
    return newOffset;																		// Return new offset
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
