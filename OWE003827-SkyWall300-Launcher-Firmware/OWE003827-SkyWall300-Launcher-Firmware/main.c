/*    _____ __        _       __      _________ ____  ____     __                           __
 *   / ___// /____  _| |     / /___ _/ / /__  // __ \/ __ \   / /   ____ ___  ______  _____/ /_  ___  _____
 *   \__ \/ //_/ / / / | /| / / __ `/ / / /_ </ / / / / / /  / /   / __ `/ / / / __ \/ ___/ __ \/ _ \/ ___/
 *  ___/ / ,< / /_/ /| |/ |/ / /_/ / / /___/ / /_/ / /_/ /  / /___/ /_/ / /_/ / / / / /__/ / / /  __/ /
 * /____/_/|_|\__, / |__/|__/\__,_/_/_//____/\____/\____/  /_____/\__,_/\__,_/_/ /_/\___/_/ /_/\___/_/
 *			/____/
 */
  
/**
 *	@file		main.c
 *
 *	@copyright	OpenWorks Engineering Ltd. 2018
 *
 *  @author		Created by David Fitzgerald (david.fitzgerald@openworksengineering.com)
 *  @date		Last modified on 20 July 2018
 *
 *  @brief		Contains main state machine. This file is editable.
 *
 */
  
#include <atmel_start.h>
#include "app/inc/app_globals.h"
#include "app/inc/app_system_state_handler.h"

struct globals_struct globals_s;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	//app_system_state_init();
	
	/* Replace with your application code */
	while(true)
	{
		gpio_set_pin_level(STATUS_LED_OP,!gpio_get_pin_level(STATUS_LED_OP));
		gpio_set_pin_level(ERROR_LED_OP,!gpio_get_pin_level(ERROR_LED_OP));
	}
}
