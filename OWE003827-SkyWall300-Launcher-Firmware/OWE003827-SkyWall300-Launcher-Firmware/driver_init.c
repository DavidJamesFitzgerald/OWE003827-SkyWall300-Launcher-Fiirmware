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

#include <hpl_adc_base.h>

/* The channel amount for ADC */
#define ADC_LAUNCHER_CH_AMOUNT 1

/* The buffer size for ADC */
#define ADC_LAUNCHER_BUFFER_SIZE 128

/* The maximal channel number of enabled channels */
#define ADC_LAUNCHER_CH_MAX 0

/*! The buffer size for USART */
#define USART_SYSTEM_SERCOM1_BUFFER_SIZE 128

/*! The buffer size for USART */
#define USART_DIAG_SERCOM4_BUFFER_SIZE 128

struct adc_async_descriptor         ADC_LAUNCHER;
struct adc_async_channel_descriptor ADC_LAUNCHER_ch[ADC_LAUNCHER_CH_AMOUNT];
struct usart_async_descriptor       USART_SYSTEM_SERCOM1;
struct usart_async_descriptor       USART_DIAG_SERCOM4;

static uint8_t ADC_LAUNCHER_buffer[ADC_LAUNCHER_BUFFER_SIZE];
static uint8_t ADC_LAUNCHER_map[ADC_LAUNCHER_CH_MAX + 1];
static uint8_t USART_SYSTEM_SERCOM1_buffer[USART_SYSTEM_SERCOM1_BUFFER_SIZE];
static uint8_t USART_DIAG_SERCOM4_buffer[USART_DIAG_SERCOM4_BUFFER_SIZE];

struct dac_async_descriptor DAC_LAUNCHER;

struct qspi_sync_descriptor QSPI_FLASH;

struct spi_m_async_descriptor SPI_PROJECTILE_SERCOM5;

struct pwm_descriptor BREECH_LOCK_MOTOR_CLK_OP;

struct pwm_descriptor BREECH_CLOSE_MOTOR_CLK_OP;

/**
 * \brief ADC initialization function
 *
 * Enables ADC peripheral, clocks and initializes ADC driver
 */
static void ADC_LAUNCHER_init(void)
{
	hri_mclk_set_APBDMASK_ADC1_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, ADC1_GCLK_ID, CONF_GCLK_ADC1_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	adc_async_init(&ADC_LAUNCHER,
	               ADC1,
	               ADC_LAUNCHER_map,
	               ADC_LAUNCHER_CH_MAX,
	               ADC_LAUNCHER_CH_AMOUNT,
	               &ADC_LAUNCHER_ch[0],
	               (void *)NULL);
	adc_async_register_channel_buffer(&ADC_LAUNCHER, 0, ADC_LAUNCHER_buffer, ADC_LAUNCHER_BUFFER_SIZE);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PROJECTILE_CHARGE_VOLTAGE_AN, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PROJECTILE_CHARGE_VOLTAGE_AN, PINMUX_PB08B_ADC1_AIN0);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PROJECTILE_CHARGE_CURRENT_AN, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PROJECTILE_CHARGE_CURRENT_AN, PINMUX_PB09B_ADC1_AIN1);

	// Disable digital pin circuitry
	gpio_set_pin_direction(HW_VERSION_AN, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(HW_VERSION_AN, PINMUX_PB04B_ADC1_AIN6);

	// Disable digital pin circuitry
	gpio_set_pin_direction(RES_PRESSURE_A_AN, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(RES_PRESSURE_A_AN, PINMUX_PB05B_ADC1_AIN7);

	// Disable digital pin circuitry
	gpio_set_pin_direction(RES_PRESSURE_B_AN, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(RES_PRESSURE_B_AN, PINMUX_PD00B_ADC1_AIN14);
}

void DAC_LAUNCHER_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(PROJECTILE_CHARGE_VOLTAGE_AO, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PROJECTILE_CHARGE_VOLTAGE_AO, PINMUX_PA02B_DAC_VOUT0);

	// Disable digital pin circuitry
	gpio_set_pin_direction(PROJECTILE_CHARGE_CURRENT_AO, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PROJECTILE_CHARGE_CURRENT_AO, PINMUX_PA05B_DAC_VOUT1);
}

void DAC_LAUNCHER_CLOCK_init(void)
{

	hri_mclk_set_APBDMASK_DAC_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, DAC_GCLK_ID, CONF_GCLK_DAC_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
}

void DAC_LAUNCHER_init(void)
{
	DAC_LAUNCHER_CLOCK_init();
	dac_async_init(&DAC_LAUNCHER, DAC);
	DAC_LAUNCHER_PORT_init();
}

void QSPI_FLASH_PORT_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(QSPI_CS, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(QSPI_CS,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(QSPI_CS, PINMUX_PB11H_QSPI_CS);

	gpio_set_pin_direction(QSPI_IO0,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(QSPI_IO0,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(QSPI_IO0,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(QSPI_IO0,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <PINMUX_PA08H_QSPI_DATA0"> Auto
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
	                      PINMUX_PA08H_QSPI_DATA0);

	gpio_set_pin_direction(QSPI_IO1,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(QSPI_IO1,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(QSPI_IO1,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(QSPI_IO1,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <PINMUX_PA09H_QSPI_DATA1"> Auto
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
	                      PINMUX_PA09H_QSPI_DATA1);

	gpio_set_pin_direction(QSPI_IO2,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(QSPI_IO2,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(QSPI_IO2,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(QSPI_IO2,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <PINMUX_PA10H_QSPI_DATA2"> Auto
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
	                      PINMUX_PA10H_QSPI_DATA2);

	gpio_set_pin_direction(QSPI_IO3,
	                       // <y> Pin direction
	                       // <id> pad_direction
	                       // <GPIO_DIRECTION_OFF"> Off
	                       // <GPIO_DIRECTION_IN"> In
	                       // <GPIO_DIRECTION_OUT"> Out
	                       GPIO_DIRECTION_OUT);

	gpio_set_pin_level(QSPI_IO3,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_pull_mode(QSPI_IO3,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(QSPI_IO3,
	                      // <y> Pin function
	                      // <id> pad_function
	                      // <i> Auto : use driver pinmux if signal is imported by driver, else turn off function
	                      // <PINMUX_PA11H_QSPI_DATA3"> Auto
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
	                      PINMUX_PA11H_QSPI_DATA3);

	// Set pin direction to input
	gpio_set_pin_direction(QSPI_SCK, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(QSPI_SCK,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(QSPI_SCK, PINMUX_PB10H_QSPI_SCK);
}

void QSPI_FLASH_CLOCK_init(void)
{
	hri_mclk_set_AHBMASK_QSPI_bit(MCLK);
	hri_mclk_set_AHBMASK_QSPI_2X_bit(MCLK);
	hri_mclk_set_APBCMASK_QSPI_bit(MCLK);
}

void QSPI_FLASH_init(void)
{
	QSPI_FLASH_CLOCK_init();
	qspi_sync_init(&QSPI_FLASH, QSPI);
	QSPI_FLASH_PORT_init();
}

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

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void USART_DIAG_SERCOM4_CLOCK_init()
{

	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM4_GCLK_ID_CORE, CONF_GCLK_SERCOM4_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM4_GCLK_ID_SLOW, CONF_GCLK_SERCOM4_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBDMASK_SERCOM4_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void USART_DIAG_SERCOM4_PORT_init()
{

	gpio_set_pin_function(DIAG_COMMS_RX, PINMUX_PB12C_SERCOM4_PAD0);

	gpio_set_pin_function(DIAG_COMMS_TX, PINMUX_PB13C_SERCOM4_PAD1);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void USART_DIAG_SERCOM4_init(void)
{
	USART_DIAG_SERCOM4_CLOCK_init();
	usart_async_init(
	    &USART_DIAG_SERCOM4, SERCOM4, USART_DIAG_SERCOM4_buffer, USART_DIAG_SERCOM4_BUFFER_SIZE, (void *)NULL);
	USART_DIAG_SERCOM4_PORT_init();
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

void USB_LAUNCHER_PORT_init(void)
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

void USB_LAUNCHER_CLOCK_init(void)
{

	hri_gclk_write_PCHCTRL_reg(GCLK, USB_GCLK_ID, CONF_GCLK_USB_SRC | GCLK_PCHCTRL_CHEN);
	hri_mclk_set_AHBMASK_USB_bit(MCLK);
	hri_mclk_set_APBBMASK_USB_bit(MCLK);
}

void USB_LAUNCHER_init(void)
{
	USB_LAUNCHER_CLOCK_init();
	usb_d_init();
	USB_LAUNCHER_PORT_init();
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA06

	// Set pin direction to output
	gpio_set_pin_direction(ERROR_LED_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(ERROR_LED_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(ERROR_LED_OP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA07

	// Set pin direction to output
	gpio_set_pin_direction(STATUS_LED_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(STATUS_LED_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   true);

	gpio_set_pin_function(STATUS_LED_OP, GPIO_PIN_FUNCTION_OFF);

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

	// GPIO on PB16

	// Set pin direction to output
	gpio_set_pin_direction(FILL_VALVE_FINE_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(FILL_VALVE_FINE_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(FILL_VALVE_FINE_OP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB17

	// Set pin direction to output
	gpio_set_pin_direction(FILL_VALVE_COARSE_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(FILL_VALVE_COARSE_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(FILL_VALVE_COARSE_OP, GPIO_PIN_FUNCTION_OFF);

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

	// GPIO on PC05

	// Set pin direction to input
	gpio_set_pin_direction(PROJECTILE_CURRENT_FB, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PROJECTILE_CURRENT_FB,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(PROJECTILE_CURRENT_FB, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PC06

	// Set pin direction to input
	gpio_set_pin_direction(PROJECTILE_VOLTAGE_FB, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(PROJECTILE_VOLTAGE_FB,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(PROJECTILE_VOLTAGE_FB, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PC22

	// Set pin direction to input
	gpio_set_pin_direction(SYSTEM_PRESSURE_ENABLE_FB, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(SYSTEM_PRESSURE_ENABLE_FB,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(SYSTEM_PRESSURE_ENABLE_FB, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PC23

	// Set pin direction to input
	gpio_set_pin_direction(SYSTEM_CHARGE_ENABLE_FB, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(SYSTEM_CHARGE_ENABLE_FB,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_UP);

	gpio_set_pin_function(SYSTEM_CHARGE_ENABLE_FB, GPIO_PIN_FUNCTION_OFF);

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

	// GPIO on PD20

	// Set pin direction to output
	gpio_set_pin_direction(DUMP_VALVE_FINE_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(DUMP_VALVE_FINE_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(DUMP_VALVE_FINE_OP, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PD21

	// Set pin direction to output
	gpio_set_pin_direction(DUMP_VALVE_COARSE_OP, GPIO_DIRECTION_OUT);

	gpio_set_pin_level(DUMP_VALVE_COARSE_OP,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	gpio_set_pin_function(DUMP_VALVE_COARSE_OP, GPIO_PIN_FUNCTION_OFF);

	ADC_LAUNCHER_init();

	DAC_LAUNCHER_init();

	QSPI_FLASH_init();

	USART_SYSTEM_SERCOM1_init();
	USART_DIAG_SERCOM4_init();

	SPI_PROJECTILE_SERCOM5_init();

	BREECH_LOCK_MOTOR_CLK_OP_init();

	BREECH_CLOSE_MOTOR_CLK_OP_init();

	USB_LAUNCHER_init();
}
