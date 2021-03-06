/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef DRIVER_INIT_INCLUDED
#define DRIVER_INIT_INCLUDED

#include "atmel_start_pins.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <hal_atomic.h>
#include <hal_delay.h>
#include <hal_gpio.h>
#include <hal_init.h>
#include <hal_io.h>
#include <hal_sleep.h>

#include <hal_adc_async.h>

#include <hal_dac_async.h>

#include <hal_qspi_sync.h>

#include <hal_usart_async.h>
#include <hal_usart_async.h>

#include <hal_spi_m_async.h>
#include <hal_pwm.h>
#include <hpl_tc_base.h>
#include <hal_pwm.h>
#include <hpl_tc_base.h>

#include "hal_usb_device.h"

extern struct adc_async_descriptor ADC_LAUNCHER;

extern struct dac_async_descriptor DAC_LAUNCHER;

extern struct qspi_sync_descriptor   QSPI_FLASH;
extern struct usart_async_descriptor USART_SYSTEM_SERCOM1;
extern struct usart_async_descriptor USART_DIAG_SERCOM4;

extern struct spi_m_async_descriptor SPI_PROJECTILE_SERCOM5;

extern struct pwm_descriptor BREECH_LOCK_MOTOR_CLK_OP;

extern struct pwm_descriptor BREECH_CLOSE_MOTOR_CLK_OP;

void DAC_LAUNCHER_PORT_init(void);
void DAC_LAUNCHER_CLOCK_init(void);
void DAC_LAUNCHER_init(void);

void QSPI_FLASH_PORT_init(void);
void QSPI_FLASH_CLOCK_init(void);
void QSPI_FLASH_init(void);

void USART_SYSTEM_SERCOM1_PORT_init(void);
void USART_SYSTEM_SERCOM1_CLOCK_init(void);
void USART_SYSTEM_SERCOM1_init(void);

void USART_DIAG_SERCOM4_PORT_init(void);
void USART_DIAG_SERCOM4_CLOCK_init(void);
void USART_DIAG_SERCOM4_init(void);

void SPI_PROJECTILE_SERCOM5_PORT_init(void);
void SPI_PROJECTILE_SERCOM5_CLOCK_init(void);
void SPI_PROJECTILE_SERCOM5_init(void);

void BREECH_LOCK_MOTOR_CLK_OP_PORT_init(void);
void BREECH_LOCK_MOTOR_CLK_OP_CLOCK_init(void);
void BREECH_LOCK_MOTOR_CLK_OP_init(void);

void BREECH_CLOSE_MOTOR_CLK_OP_PORT_init(void);
void BREECH_CLOSE_MOTOR_CLK_OP_CLOCK_init(void);
void BREECH_CLOSE_MOTOR_CLK_OP_init(void);

void USB_LAUNCHER_CLOCK_init(void);
void USB_LAUNCHER_init(void);

/**
 * \brief Perform system initialization, initialize pins and clocks for
 * peripherals
 */
void system_init(void);

#ifdef __cplusplus
}
#endif
#endif // DRIVER_INIT_INCLUDED
