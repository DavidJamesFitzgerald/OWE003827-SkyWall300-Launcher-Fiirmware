/*    _____ __        _       __      _________ ____  ____     __                           __
 *   / ___// /____  _| |     / /___ _/ / /__  // __ \/ __ \   / /   ____ ___  ______  _____/ /_  ___  _____
 *   \__ \/ //_/ / / / | /| / / __ `/ / / /_ </ / / / / / /  / /   / __ `/ / / / __ \/ ___/ __ \/ _ \/ ___/
 *  ___/ / ,< / /_/ /| |/ |/ / /_/ / / /___/ / /_/ / /_/ /  / /___/ /_/ / /_/ / / / / /__/ / / /  __/ /
 * /____/_/|_|\__, / |__/|__/\__,_/_/_//____/\____/\____/  /_____/\__,_/\__,_/_/ /_/\___/_/ /_/\___/_/
 *			/____/
 */
  
/**
 *	@file		app_system_state_handler.c
 *
 *	@copyright	OpenWorks Engineering Ltd. 2018
 *
 *  @author		Created by David Fitzgerald (david.fitzgerald@openworksengineering.com)
 *  @date		Last modified on 20 July 2018
 *
 *  @brief		Contains system state functions. This file is editable.
 *
 */
#include "app/inc/app_globals.h"
#include "app/inc/app_system_state_handler.h"
#include "app/inc/app_breech_functions.h"

static bool init_motor_state(void)
{
	bool success = false;

	if(BREECH_STATE_ERROR == app_get_breech_position())
	{
		ASSERT(0);
	}
	else
	{
		success = true;
	}

	return success;
}

bool app_system_state_init(void)
{
	bool success = false;
	
	success = init_motor_state();
	
	return success;
}