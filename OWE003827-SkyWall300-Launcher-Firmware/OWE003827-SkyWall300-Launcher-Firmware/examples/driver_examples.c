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
