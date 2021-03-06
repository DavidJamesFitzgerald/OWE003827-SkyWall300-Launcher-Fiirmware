/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

static void convert_cb_ADC_LAUNCHER(const struct adc_async_descriptor *const descr, const uint8_t channel)
{
}

/**
 * Example of using ADC_LAUNCHER to generate waveform.
 */
void ADC_LAUNCHER_example(void)
{
	adc_async_enable_channel(&ADC_LAUNCHER, 0);
	adc_async_register_callback(&ADC_LAUNCHER, 0, ADC_ASYNC_CONVERT_CB, convert_cb_ADC_LAUNCHER);
	adc_async_start_conversion(&ADC_LAUNCHER);
}

static uint16_t example_DAC_LAUNCHER[10] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900};

static void tx_cb_DAC_LAUNCHER(struct dac_async_descriptor *const descr, const uint8_t ch)
{
	dac_async_write(descr, 0, example_DAC_LAUNCHER, 10);
}

/**
 * Example of using DAC_LAUNCHER to generate waveform.
 */
void DAC_LAUNCHER_example(void)
{
	dac_async_enable_channel(&DAC_LAUNCHER, 0);
	dac_async_register_callback(&DAC_LAUNCHER, DAC_ASYNC_CONVERSION_DONE_CB, tx_cb_DAC_LAUNCHER);
	dac_async_write(&DAC_LAUNCHER, 0, example_DAC_LAUNCHER, 10);
}

/**
 * Example of using QSPI_FLASH to get N25Q256A status value,
 * and check bit 0 which indicate embedded operation is busy or not.
 */
void QSPI_FLASH_example(void)
{
	uint8_t              status = 0xFF;
	struct _qspi_command cmd    = {
        .inst_frame.bits.inst_en  = 1,
        .inst_frame.bits.data_en  = 1,
        .inst_frame.bits.tfr_type = QSPI_READ_ACCESS,
        .instruction              = 0x05,
        .buf_len                  = 1,
        .rx_buf                   = &status,
    };

	qspi_sync_enable(&QSPI_FLASH);
	while (status & (1 << 0)) {
		qspi_sync_serial_run_command(&QSPI_FLASH, &cmd);
	}
	qspi_sync_deinit(&QSPI_FLASH);
}

/**
 * Example of using USART_SYSTEM_SERCOM1 to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_USART_SYSTEM_SERCOM1[12] = "Hello World!";

static void tx_cb_USART_SYSTEM_SERCOM1(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void USART_SYSTEM_SERCOM1_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&USART_SYSTEM_SERCOM1, USART_ASYNC_TXC_CB, tx_cb_USART_SYSTEM_SERCOM1);
	/*usart_async_register_callback(&USART_SYSTEM_SERCOM1, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART_SYSTEM_SERCOM1, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&USART_SYSTEM_SERCOM1, &io);
	usart_async_enable(&USART_SYSTEM_SERCOM1);

	io_write(io, example_USART_SYSTEM_SERCOM1, 12);
}

/**
 * Example of using USART_DIAG_SERCOM4 to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_USART_DIAG_SERCOM4[12] = "Hello World!";

static void tx_cb_USART_DIAG_SERCOM4(const struct usart_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void USART_DIAG_SERCOM4_example(void)
{
	struct io_descriptor *io;

	usart_async_register_callback(&USART_DIAG_SERCOM4, USART_ASYNC_TXC_CB, tx_cb_USART_DIAG_SERCOM4);
	/*usart_async_register_callback(&USART_DIAG_SERCOM4, USART_ASYNC_RXC_CB, rx_cb);
	usart_async_register_callback(&USART_DIAG_SERCOM4, USART_ASYNC_ERROR_CB, err_cb);*/
	usart_async_get_io_descriptor(&USART_DIAG_SERCOM4, &io);
	usart_async_enable(&USART_DIAG_SERCOM4);

	io_write(io, example_USART_DIAG_SERCOM4, 12);
}

/**
 * Example of using SPI_PROJECTILE_SERCOM5 to write "Hello World" using the IO abstraction.
 *
 * Since the driver is asynchronous we need to use statically allocated memory for string
 * because driver initiates transfer and then returns before the transmission is completed.
 *
 * Once transfer has been completed the tx_cb function will be called.
 */

static uint8_t example_SPI_PROJECTILE_SERCOM5[12] = "Hello World!";

static void complete_cb_SPI_PROJECTILE_SERCOM5(const struct spi_m_async_descriptor *const io_descr)
{
	/* Transfer completed */
}

void SPI_PROJECTILE_SERCOM5_example(void)
{
	struct io_descriptor *io;
	spi_m_async_get_io_descriptor(&SPI_PROJECTILE_SERCOM5, &io);

	spi_m_async_register_callback(
	    &SPI_PROJECTILE_SERCOM5, SPI_M_ASYNC_CB_XFER, (FUNC_PTR)complete_cb_SPI_PROJECTILE_SERCOM5);
	spi_m_async_enable(&SPI_PROJECTILE_SERCOM5);
	io_write(io, example_SPI_PROJECTILE_SERCOM5, 12);
}

/**
 * Example of using BREECH_LOCK_MOTOR_CLK_OP.
 */
void BREECH_LOCK_MOTOR_CLK_OP_example(void)
{
	pwm_set_parameters(&BREECH_LOCK_MOTOR_CLK_OP, 10000, 5000);
	pwm_enable(&BREECH_LOCK_MOTOR_CLK_OP);
}

/**
 * Example of using BREECH_CLOSE_MOTOR_CLK_OP.
 */
void BREECH_CLOSE_MOTOR_CLK_OP_example(void)
{
	pwm_set_parameters(&BREECH_CLOSE_MOTOR_CLK_OP, 10000, 5000);
	pwm_enable(&BREECH_CLOSE_MOTOR_CLK_OP);
}
