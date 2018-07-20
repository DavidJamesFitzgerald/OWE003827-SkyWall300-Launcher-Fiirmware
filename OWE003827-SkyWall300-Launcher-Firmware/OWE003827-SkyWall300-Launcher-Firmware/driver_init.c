/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>

/*! The buffer size for USART */
#define USART_SYSTEM_SERCOM1_BUFFER_SIZE 16

struct usart_async_descriptor USART_SYSTEM_SERCOM1;

static uint8_t USART_SYSTEM_SERCOM1_buffer[USART_SYSTEM_SERCOM1_BUFFER_SIZE];

struct spi_m_async_descriptor SPI_PROJECTILE_SERCOM5;

struct pwm_descriptor BREECH_LOCK_MOTOR_CLK_OP;

struct pwm_descriptor BREECH_CLOSE_MOTOR_CLK_OP;

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void USART_SYSTEM_SERCOM1_CLOCK_init()
{

	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_CORE, CONF_GCLK_SERCOM1_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM1_GCLK_ID_SLOW, CONF_GCLK_SERCOM1_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBAMASK_SERCOM1_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void USART_SYSTEM_SERCOM1_PORT_init()
{

	gpio_set_pin_function(SYSTEM_COMMS_RX, PINMUX_PC27C_SERCOM1_PAD0);

	gpio_set_pin_function(SYSTEM_COMMS_TX, PINMUX_PC28C_SERCOM1_PAD1);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void USART_SYSTEM_SERCOM1_init(void)
{
	USART_SYSTEM_SERCOM1_CLOCK_init();
	usart_async_init(
	    &USART_SYSTEM_SERCOM1, SERCOM1, USART_SYSTEM_SERCOM1_buffer, USART_SYSTEM_SERCOM1_BUFFER_SIZE, (void *)NULL);
	USART_SYSTEM_SERCOM1_PORT_init();
}

void SPI_PROJECTILE_SERCOM5_PORT_init(void)
{

	// Set pin direction to output
	gpio_set_pin_direction(PROJECTILE_MOSI, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(PROJECTILE_MOSI,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(PROJECTILE_MOSI, PINMUX_PA23D_SERCOM5_PAD0);

	// Set pin direction to output
	gpio_set_pin_direction(PROJECTILE_SCK, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(PROJECTILE_SCK,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(PROJECTILE_SCK, PINMUX_PA22D_SERCOM5_PAD1);

	// Set pin direction to input
	gpio_set_pin_direction(PROJECTILE_MISO, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PROJECTILE_MISO,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(PROJECTILE_MISO, PINMUX_PA21C_SERCOM5_PAD3);
}

void SPI_PROJECTILE_SERCOM5_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM5_GCLK_ID_CORE, CONF_GCLK_SERCOM5_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM5_GCLK_ID_SLOW, CONF_GCLK_SERCOM5_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBDMASK_SERCOM5_bit(MCLK);
}

void SPI_PROJECTILE_SERCOM5_init(void)
{
	SPI_PROJECTILE_SERCOM5_CLOCK_init();
	spi_m_async_init(&SPI_PROJECTILE_SERCOM5, SERCOM5);
	SPI_PROJECTILE_SERCOM5_PORT_init();
}

void BREECH_LOCK_MOTOR_CLK_OP_PORT_init(void)
{

	gpio_set_pin_function(BREECH_LOCK_MOTOR_CLKOP, PINMUX_PB02E_TC6_WO0);
}

void BREECH_LOCK_MOTOR_CLK_OP_CLOCK_init(void)
{

	hri_mclk_set_APBDMASK_TC6_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TC6_GCLK_ID, CONF_GCLK_TC6_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
}

void BREECH_LOCK_MOTOR_CLK_OP_init(void)
{
	BREECH_LOCK_MOTOR_CLK_OP_CLOCK_init();
	BREECH_LOCK_MOTOR_CLK_OP_PORT_init();
	pwm_init(&BREECH_LOCK_MOTOR_CLK_OP, TC6, _tc_get_pwm());
}

void BREECH_CLOSE_MOTOR_CLK_OP_PORT_init(void)
{

	gpio_set_pin_function(BREECH_CLOSE_MOTORCLK_OP, PINMUX_PB01E_TC7_WO1);
}

void BREECH_CLOSE_MOTOR_CLK_OP_CLOCK_init(void)
{

	hri_mclk_set_APBDMASK_TC7_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, TC7_GCLK_ID, CONF_GCLK_TC7_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
}

void BREECH_CLOSE_MOTOR_CLK_OP_init(void)
{
	BREECH_CLOSE_MOTOR_CLK_OP_CLOCK_init();
	BREECH_CLOSE_MOTOR_CLK_OP_PORT_init();
	pwm_init(&BREECH_CLOSE_MOTOR_CLK_OP, TC7, _tc_get_pwm());
}

void USB_PORT_init(void)
{

	gpio_set_pin_direction(USB_DN,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(USB_DN,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(USB_DN,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(USB_DN,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <PINMUX_PA24H_USB_DM"> Auto
	                      // <GPIO_PIN_FUNCTION_OFF"> Off
	                      // <GPIO_PIN_FUNCTION_A"> A
	                      // <GPIO_PIN_FUNCTION_B"> B
	                      // <GPIO_PIN_FUNCTION_C"> C
	                      // <GPIO_PIN_FUNCTION_D"> D
	                      // <GPIO_PIN_FUNCTION_E"> E
	                      // <GPIO_PIN_FUNCTION_F"> F
	                      // <GPIO_PIN_FUNCTION_G"> G
	                      // <GPIO_PIN_FUNCTION_H"> H
	                      // <GPIO_PIN_FUNCTION_I"> I
	                      // <GPIO_PIN_FUNCTION_J"> J
	                      // <GPIO_PIN_FUNCTION_K"> K
	                      // <GPIO_PIN_FUNCTION_L"> L
	                      // <GPIO_PIN_FUNCTION_M"> M
	                      // <GPIO_PIN_FUNCTION_N"> N
	                      PINMUX_PA24H_USB_DM);

	gpio_set_pin_direction(USB_DP,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(USB_DP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(USB_DP,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(USB_DP,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <PINMUX_PA25H_USB_DP"> Auto
	                      // <GPIO_PIN_FUNCTION_OFF"> Off
	                      // <GPIO_PIN_FUNCTION_A"> A
	                      // <GPIO_PIN_FUNCTION_B"> B
	                      // <GPIO_PIN_FUNCTION_C"> C
	                      // <GPIO_PIN_FUNCTION_D"> D
	                      // <GPIO_PIN_FUNCTION_E"> E
	                      // <GPIO_PIN_FUNCTION_F"> F
	                      // <GPIO_PIN_FUNCTION_G"> G
	                      // <GPIO_PIN_FUNCTION_H"> H
	                      // <GPIO_PIN_FUNCTION_I"> I
	                      // <GPIO_PIN_FUNCTION_J"> J
	                      // <GPIO_PIN_FUNCTION_K"> K
	                      // <GPIO_PIN_FUNCTION_L"> L
	                      // <GPIO_PIN_FUNCTION_M"> M
	                      // <GPIO_PIN_FUNCTION_N"> N
	                      PINMUX_PA25H_USB_DP);
}

/* The USB module requires a GCLK_USB of 48 MHz ~ 0.25% clock
 * for low speed and full speed operation. */
#if (CONF_GCLK_USB_FREQUENCY > (48000000 + 48000000 / 400)) || (CONF_GCLK_USB_FREQUENCY < (48000000 - 48000000 / 400))
#warning USB clock should be 48MHz ~ 0.25% clock, check your configuration!
#endif

void USB_CLOCK_init(void)
{

	hri_gclk_write_PCHCTRL_reg(GCLK, USB_GCLK_ID, CONF_GCLK_USB_SRC | GCLK_PCHCTRL_CHEN);
	hri_mclk_set_AHBMASK_USB_bit(MCLK);
	hri_mclk_set_APBBMASK_USB_bit(MCLK);
}

void USB_init(void)
{
	USB_CLOCK_init();
	usb_d_init();
	USB_PORT_init();
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA20

	// Set pin direction to input
	gpio_set_pin_direction(PROJECTILE_FITTED_FB, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PROJECTILE_FITTED_FB,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_DOWN);

	gpio_set_pin_function(PROJECTILE_FITTED_FB, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB00

	// Set pin direction to output
	gpio_set_pin_direction(BREECH_LOCK_MOTOR_DIR_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BREECH_LOCK_MOTOR_DIR_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(BREECH_LOCK_MOTOR_DIR_OP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB21

	// Set pin direction to output
	gpio_set_pin_direction(PROJECTILE_COMMS_ENABLE_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(PROJECTILE_COMMS_ENABLE_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(PROJECTILE_COMMS_ENABLE_OP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB25

	// Set pin direction to input
	gpio_set_pin_direction(TRIGGER_SAFE_SWITCH_FB, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(TRIGGER_SAFE_SWITCH_FB,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(TRIGGER_SAFE_SWITCH_FB, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB26

	// Set pin direction to input
	gpio_set_pin_direction(BREECH_CLOSED_SWITCH_FB, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(BREECH_CLOSED_SWITCH_FB,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(BREECH_CLOSED_SWITCH_FB, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB27

	// Set pin direction to input
	gpio_set_pin_direction(BREECH_OPEN_SWITCH_FB, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(BREECH_OPEN_SWITCH_FB,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(BREECH_OPEN_SWITCH_FB, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB28

	// Set pin direction to input
	gpio_set_pin_direction(BREECH_UNLOCKED_SWITCH_FB, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(BREECH_UNLOCKED_SWITCH_FB,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(BREECH_UNLOCKED_SWITCH_FB, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB29

	// Set pin direction to input
	gpio_set_pin_direction(BREECH_LOCKED_SWITCH_FB, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(BREECH_LOCKED_SWITCH_FB,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(BREECH_LOCKED_SWITCH_FB, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB31

	// Set pin direction to output
	gpio_set_pin_direction(BREECH_MOTOR_nSLEEP_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BREECH_MOTOR_nSLEEP_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(BREECH_MOTOR_nSLEEP_OP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PC26

	// Set pin direction to output
	gpio_set_pin_direction(SERIAL_MODE_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(SERIAL_MODE_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(SERIAL_MODE_OP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PC30

	// Set pin direction to output
	gpio_set_pin_direction(BREECH_MOTOR_nENABLE_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BREECH_MOTOR_nENABLE_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(BREECH_MOTOR_nENABLE_OP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PC31

	// Set pin direction to output
	gpio_set_pin_direction(BREECH_CLOSE_MOTOR_DIR_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(BREECH_CLOSE_MOTOR_DIR_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(BREECH_CLOSE_MOTOR_DIR_OP, GPIO_PIN_FUNCTION_OFF);

	USART_SYSTEM_SERCOM1_init();

	SPI_PROJECTILE_SERCOM5_init();

	BREECH_LOCK_MOTOR_CLK_OP_init();

	BREECH_CLOSE_MOTOR_CLK_OP_init();

	USB_init();
}
