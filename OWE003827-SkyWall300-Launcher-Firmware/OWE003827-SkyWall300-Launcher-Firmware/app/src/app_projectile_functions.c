/*
 * app_projectile_functions.c
 *
 * Created: 23/07/2018 10:53:54
 *  Author: David Fitzgerald
 */ 
#include "app/inc/app_globals.h"
#include "app/inc/app_projectile_functions.h"

void app_projectile_enable_charging(void)
{
//TODO
// 	gpio_configure_pin(PROJECTILE_SPI_MISO_PIN, GPIO_DIR_INPUT);
// 
// 	gpio_set_gpio_pin(ENABLE_PROJ_RELAY_OP_PIN);
// 	gpio_set_gpio_pin(ENABLE_PROJ_CHARGE_OP_PIN);
	
	globals_s.charger.enabled = true;
}

void app_projectile_disable_charging(void)
{
//TODO
// 	gpio_clr_gpio_pin(ENABLE_PROJ_RELAY_OP_PIN);
// 	gpio_clr_gpio_pin(ENABLE_PROJ_CHARGE_OP_PIN);
// 
// 	gpio_enable_gpio_pin(PROJECTILE_SPI_MISO_PIN);
// 	gpio_configure_pin(PROJECTILE_SPI_MISO_PIN, GPIO_DIR_OUTPUT);
// 	gpio_set_pin_low(PROJECTILE_SPI_MISO_PIN);
	
	globals_s.charger.enabled = false;
}

//Turn off SPI / PWM and force output low to avoid sending power to projectile over comms lines
void app_reset_io_pins(void)
{
	// Set projectile comms mode
	globals_s.projectile.comms_mode = NONE;
//TODO	
// 	// Stop sending a time delay to ensure the projectile stops being ready
// 	tc_stop(PROJECTILE_PWM_OP_TC, PROJECTILE_PWM_OP_TC_CHANNEL);
// 	tc_stop(PROJECTILE_PWM_FB_TC, PROJECTILE_PWM_FB_TC_CHANNEL);
// 	
// 	// Disable PWM interrupts
// 	PROJECTILE_PWM_OP_TC->channel[PROJECTILE_PWM_OP_TC_CHANNEL].idr |= AVR32_TC_CPCS_MASK;
// 	PROJECTILE_PWM_FB_TC->channel[PROJECTILE_PWM_FB_TC_CHANNEL].idr |= AVR32_TC_LDRAS_MASK;
// 	
// 	// Disable SPI
// 	spi_disable(PROJECTILE_SPI);
// 	
// 	// Turn PWM output into a GPIO input pin
// 	gpio_configure_pin(PROJECTILE_PWM_OP_TC_PIN, GPIO_DIR_INPUT);
// 	gpio_enable_gpio_pin(PROJECTILE_PWM_OP_TC_PIN);
// 	
// 	// Turn PWM input into a GPIO input pin
// 	gpio_configure_pin(PROJECTILE_PWM_FB_TC_PIN, GPIO_DIR_INPUT);
// 	gpio_enable_gpio_pin(PROJECTILE_PWM_FB_TC_PIN);
// 
// 	// Turn SPI SCK into Input pin
// 	gpio_configure_pin(PROJECTILE_SPI_SCK_PIN, GPIO_DIR_INPUT);
// 	gpio_enable_gpio_pin(PROJECTILE_SPI_SCK_PIN);
// 	
// 	// Turn SPI MOSI into Input pin
// 	gpio_configure_pin(PROJECTILE_SPI_MOSI_PIN, GPIO_DIR_INPUT);
// 	gpio_enable_gpio_pin(PROJECTILE_SPI_MOSI_PIN);
// 	
// 	// Turn SPI MISO into Input pin
// 	gpio_configure_pin(PROJECTILE_SPI_MISO_PIN, GPIO_DIR_INPUT);
// 	gpio_enable_gpio_pin(PROJECTILE_SPI_MISO_PIN);
}