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

#include "FT_Platform.h"
#if defined(FT900_PLATFORM)

#include "FT_MCU_Hal.h"

ft_void_t Eve_BootupConfig(Ft_Gpu_Hal_Context_t *s_Host)
{
	Ft_Gpu_Hal_Powercycle(s_Host, FT_TRUE);

	/* FT81x will be in SPI Single channel after POR
	If we are here with FT4222 in multi channel, then
	an explicit switch to single channel is essential
	*/
	Ft_Gpu_Hal_SetSPI(s_Host, FT_GPU_SPI_SINGLE_CHANNEL, FT_GPU_SPI_ONEDUMMY);


	/* Set the clk to external clock. Must disable it when no external clock source on the board*/
#if (!defined(ME810A_HV35R) && !defined(ME812A_WH50R) && !defined(ME813AU_WH50C))
	Ft_Gpu_HostCommand(s_Host, FT_GPU_EXTERNAL_OSC);
	Ft_Gpu_Hal_Sleep(10);
#endif

	/* Access address 0 to wake up the FT800 */
	Ft_Gpu_HostCommand(s_Host, FT_GPU_ACTIVE_M);
	Ft_Gpu_Hal_Sleep(300);
#if defined(FT_811_ENABLE) || defined(FT_813_ENABLE)
#if defined(PANL70) || defined(PANL70PLUS)
	Ft_Gpu_Hal_Wr8(s_Host, REG_CPURESET, 2);
	Ft_Gpu_Hal_Wr16(s_Host, REG_CYA_TOUCH, 0x05d0);
#endif
	/* Download new firmware to fix pen up issue */
	/* It may cause resistive touch not working any more*/
	Ft_Gpu_DownloadJ1Firmware(s_Host);
#if defined(PANL70) || defined(PANL70PLUS)
	Ft_Gpu_Panl70_GOODIXGPIO(s_Host);
#endif
	Ft_Gpu_Hal_Sleep(100);
#endif

	; {
		ft_uint8_t chipid;
		//Read Register ID to check if EVE is ready.
		chipid = Ft_Gpu_Hal_Rd8(s_Host, REG_ID);
		while (chipid != 0x7C)
		{
			chipid = Ft_Gpu_Hal_Rd8(s_Host, REG_ID);
			ESD_print("EVE register ID after wake up %x\n", chipid);
			ft_delay(100);
		}
		ESD_print("EVE register ID after wake up %x\n", chipid);
	}

#ifdef DISPLAY_RESOLUTION_QVGA
	init_DISPLAY_RESOLUTION_QVGA();
#endif
#ifdef DISPLAY_RESOLUTION_WVGA
	init_DISPLAY_RESOLUTION_WVGA();
#endif

#ifdef DISPLAY_RESOLUTION_HVGA_PORTRAIT
	init_DISPLAY_RESOLUTION_HVGA_PORTRAIT();
#endif

	Ft_Gpu_Hal_Wr16(s_Host, REG_HCYCLE, FT_DispHCycle);
	Ft_Gpu_Hal_Wr16(s_Host, REG_HOFFSET, FT_DispHOffset);
	Ft_Gpu_Hal_Wr16(s_Host, REG_HSYNC0, FT_DispHSync0);
	Ft_Gpu_Hal_Wr16(s_Host, REG_HSYNC1, FT_DispHSync1);
	Ft_Gpu_Hal_Wr16(s_Host, REG_VCYCLE, FT_DispVCycle);
	Ft_Gpu_Hal_Wr16(s_Host, REG_VOFFSET, FT_DispVOffset);
	Ft_Gpu_Hal_Wr16(s_Host, REG_VSYNC0, FT_DispVSync0);
	Ft_Gpu_Hal_Wr16(s_Host, REG_VSYNC1, FT_DispVSync1);
	Ft_Gpu_Hal_Wr8(s_Host, REG_SWIZZLE, FT_DispSwizzle);
	Ft_Gpu_Hal_Wr8(s_Host, REG_PCLK_POL, FT_DispPCLKPol);
	Ft_Gpu_Hal_Wr16(s_Host, REG_HSIZE, FT_DispWidth);
	Ft_Gpu_Hal_Wr16(s_Host, REG_VSIZE, FT_DispHeight);
	Ft_Gpu_Hal_Wr16(s_Host, REG_CSPREAD, FT_DispCSpread);
	Ft_Gpu_Hal_Wr16(s_Host, REG_DITHER, FT_DispDither);

#ifdef BT_EVE_SCREEN_RESISTIVE
	/* Touch configuration - configure the resistance value to 1200 - this value is specific to customer requirement and derived by experiment */
	Ft_Gpu_Hal_Wr16(s_Host, REG_TOUCH_RZTHRESH, RESISTANCE_THRESHOLD);
#endif

#if defined(FT_81X_ENABLE) || defined (BT_81X_ENABLE)
	Ft_Gpu_Hal_Wr16(s_Host, REG_GPIOX_DIR, 0xffff);
	Ft_Gpu_Hal_Wr16(s_Host, REG_GPIOX, 0xffff);
#else
	Ft_Gpu_Hal_Wr8(s_Host, REG_GPIO_DIR, 0xff);
	Ft_Gpu_Hal_Wr8(s_Host, REG_GPIO, 0xff);
#endif

	Ft_Gpu_Hal_WrMem(s_Host, RAM_DL, (ft_uint8_t *)FT_DLCODE_BOOTUP, sizeof(FT_DLCODE_BOOTUP));
	Ft_Gpu_Hal_Wr8(s_Host, REG_DLSWAP, DLSWAP_FRAME);

	Ft_Gpu_Hal_Wr8(s_Host, REG_PCLK, FT_DispPCLK);//after this display is visible on the LCD

#if (defined(ENABLE_ILI9488_HVGA_PORTRAIT) || defined(ENABLE_KD2401_HVGA_PORTRAIT))
	/* to cross check reset pin */
	Ft_Gpu_Hal_Wr8(s_Host, REG_GPIO, 0xff);
	ft_delay(120);
	Ft_Gpu_Hal_Wr8(s_Host, REG_GPIO, 0x7f);
	ft_delay(120);
	Ft_Gpu_Hal_Wr8(s_Host, REG_GPIO, 0xff);
	ft_delay(120);
#endif
	Ft_DisplayPanel_Init();


	/* make the spi to quad mode - addition 2 bytes for silicon */
#ifndef FT_80X_ENABLE
	/* api to set quad and numbe of dummy bytes */
#ifdef ENABLE_SPI_QUAD
	Ft_Gpu_Hal_SetSPI(s_Host, FT_GPU_SPI_QUAD_CHANNEL, FT_GPU_SPI_TWODUMMY);
#elif ENABLE_SPI_DUAL
	Ft_Gpu_Hal_SetSPI(s_Host, FT_GPU_SPI_DUAL_CHANNEL, FT_GPU_SPI_TWODUMMY);
#else
	Ft_Gpu_Hal_SetSPI(s_Host, FT_GPU_SPI_SINGLE_CHANNEL, FT_GPU_SPI_ONEDUMMY);
#endif

#endif

	/* Change clock frequency to 25mhz */
	spi_init(SPIM, spi_dir_master, spi_mode_0, 4);

#if (defined(ENABLE_SPI_QUAD))
	/* Initialize IO2 and IO3 pad/pin for dual and quad settings */
	gpio_function(31, pad_spim_io2);
	gpio_function(32, pad_spim_io3);
	gpio_write(31, 1);
	gpio_write(32, 1);
#endif
	/* Enable FIFO of QSPI */
	spi_option(SPIM, spi_option_fifo_size, 64);
	spi_option(SPIM, spi_option_fifo, 1);
	spi_option(SPIM, spi_option_fifo_receive_trigger, 1);


#ifdef ENABLE_SPI_QUAD
	spi_option(SPIM, spi_option_bus_width, 4);
#elif ENABLE_SPI_DUAL
	spi_option(SPIM, spi_option_bus_width, 2);
#else
	spi_option(SPIM, spi_option_bus_width, 1);
#endif
}


static ft_void_t init_sdhost()
{
	sys_enable(sys_device_sd_card);
	sdhost_init();

#define GPIO_SD_CLK  (19)
#define GPIO_SD_CMD  (20)
#define GPIO_SD_DAT3 (21)
#define GPIO_SD_DAT2 (22)
#define GPIO_SD_DAT1 (23)
#define GPIO_SD_DAT0 (24)
#define GPIO_SD_CD   (25)
#define GPIO_SD_WP   (26)

	gpio_function(GPIO_SD_CLK, pad_sd_clk); gpio_pull(GPIO_SD_CLK, pad_pull_none); // pad_pull_none
	gpio_function(GPIO_SD_CMD, pad_sd_cmd); gpio_pull(GPIO_SD_CMD, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT3, pad_sd_data3); gpio_pull(GPIO_SD_DAT3, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT2, pad_sd_data2); gpio_pull(GPIO_SD_DAT2, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT1, pad_sd_data1); gpio_pull(GPIO_SD_DAT1, pad_pull_pullup);
	gpio_function(GPIO_SD_DAT0, pad_sd_data0); gpio_pull(GPIO_SD_DAT0, pad_pull_pullup);
	gpio_function(GPIO_SD_CD, pad_sd_cd); gpio_pull(GPIO_SD_CD, pad_pull_pullup);
	gpio_function(GPIO_SD_WP, pad_sd_wp); gpio_pull(GPIO_SD_WP, pad_pull_pullup);
}

ft_void_t  Ft_Mcu_Init()
{
#if (defined(PANL35) || defined(PANL70) || defined(PANL70PLUS))
	init_printf(UART0, tfp_putc);
	panl_board_cfg bcfg;
#if defined(PANL35)
	panl_board_cfg_set_defaults(PANL35_GENERIC_V2, &bcfg);
#elif defined(PANL70) || defined(PANL70PLUS)
	panl_board_cfg_set_defaults(PANL70_PLUS_V2, &bcfg);
#endif	

	panl_result res = panl_init(&bcfg);
	panl_bacnet_cfg_s cfg = { .msg_rxed_cb = bacnet_msg_received,.notif_ack_cb = bacnet_notification_acked,.unconf_msg_rxed_cb = bacnet_unconf_msg_received,.mac = 13,.config = config_default };
	if (!panl_bacnet_init(&cfg)) {
		ESD_print("Error init bacnet!\n");
	}

	panl_led_init();

	uint8_t panlID = 0;
	res = panl_get_panl_id(&panlID);

	ESD_print("\r\nPanL ID :  %04x\r\n", panlID);
#endif

	interrupt_enable_globally();

	sys_enable(sys_device_uart0);
	gpio_function(48, pad_uart0_txd); /* UART0 TXD */
	gpio_function(49, pad_uart0_rxd); /* UART0 RXD */
	uart_open(UART0,     /* Device */
		1,               /* Prescaler = 1 */
		UART_DIVIDER_115200_BAUD,  /* Divider = 1302 */
		uart_data_bits_8,   /* No. Data Bits */
		uart_parity_none,   /* Parity */
		uart_stop_bits_1);  /* No. Stop Bits */


#if (defined(ENABLE_ILI9488_HVGA_PORTRAIT) || defined(ENABLE_KD2401_HVGA_PORTRAIT))
/* asign all the respective pins to gpio and set them to default values */
	gpio_function(34, pad_gpio34);
	gpio_dir(34, pad_dir_output);
	gpio_write(34, 1);

	gpio_function(27, pad_gpio27);
	gpio_dir(27, pad_dir_output);
	gpio_write(27, 1);

	gpio_function(29, pad_gpio29);
	gpio_dir(29, pad_dir_output);
	gpio_write(29, 1);

	gpio_function(33, pad_gpio33);
	gpio_dir(33, pad_dir_output);
	gpio_write(33, 1);


	gpio_function(30, pad_gpio30);
	gpio_dir(30, pad_dir_output);
	gpio_write(30, 1);

	gpio_function(28, pad_gpio28);
	gpio_dir(28, pad_dir_output);
	gpio_write(28, 1);


	gpio_function(43, pad_gpio43);
	gpio_dir(43, pad_dir_output);
	gpio_write(43, 1);
	gpio_write(34, 1);
	gpio_write(28, 1);
	gpio_write(43, 1);
	gpio_write(33, 1);
	gpio_write(33, 1);
#endif

	init_sdhost();
	ft_millis_init();
}

#endif

/* end of file */
