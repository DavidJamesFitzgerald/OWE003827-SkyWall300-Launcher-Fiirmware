/*    _____ __        _       __      _________ ____  ____     __                           __
 *   / ___// /____  _| |     / /___ _/ / /__  // __ \/ __ \   / /   ____ ___  ______  _____/ /_  ___  _____
 *   \__ \/ //_/ / / / | /| / / __ `/ / / /_ </ / / / / / /  / /   / __ `/ / / / __ \/ ___/ __ \/ _ \/ ___/
 *  ___/ / ,< / /_/ /| |/ |/ / /_/ / / /___/ / /_/ / /_/ /  / /___/ /_/ / /_/ / / / / /__/ / / /  __/ /
 * /____/_/|_|\__, / |__/|__/\__,_/_/_//____/\____/\____/  /_____/\__,_/\__,_/_/ /_/\___/_/ /_/\___/_/
 *			/____/
 */
  
/**
 *	@file		app_breech_functions.c
 *
 *	@copyright	OpenWorks Engineering Ltd. 2018
 *
 *  @author		Created by David Fitzgerald (david.fitzgerald@openworksengineering.com)
 *  @date		Last modified on 20 July 2018
 *
 *  @brief		Contains breech functions. This file is editable.
 *
 */
#include <atmel_start.h>

#include "app/inc/app_globals.h"
#include "app/inc/app_breech_functions.h"

static bool is_breech_open(void)
{
	bool is_open = true;
	is_open = gpio_get_pin_level(BREECH_OPEN_SWITCH_FB);
	return is_open;
}

static bool is_breech_closed(void)
{
	bool is_closed = false;
	is_closed = gpio_get_pin_level(BREECH_CLOSED_SWITCH_FB);
	return is_closed;
}

static bool is_breech_locked(void)
{
	bool is_locked = false;
	is_locked = gpio_get_pin_level(BREECH_LOCKED_SWITCH_FB);
	return is_locked;
}

static bool is_breach_unlocked(void)
{
	bool is_unlocked = true;
	is_unlocked = gpio_get_pin_level(BREECH_UNLOCKED_SWITCH_FB);
	return is_unlocked;
}

breech_state_e app_get_breech_position(void)
{
	//! TODO move this into a state machine
	breech_state_e state = BREECH_STATE_ERROR;
	
	if(is_breech_open())
	{
		if(is_breech_closed())
		{
			//! Cannot be be open and closed
			state = BREECH_STATE_ERROR;
		}
		else
		{
			if(is_breech_locked())
			{
				//! Should not be open and locked
				state = BREECH_STATE_ERROR;
			}
			else if(!is_breach_unlocked())
			{
				//! Could be open but not quite fully unlocked
				state = BREECH_STATE_OPEN_INDERTERMINATE;
			}
			else
			{
				state = BREECH_STATE_OPEN;
			}
		}
	}
	else if(is_breech_closed())
	{
		if(is_breech_open())
		{
			//! This would have been caught above but included for completeness

			//! Cannot be closed and open
			state = BREECH_STATE_ERROR;
		}
		else
		{
			if(is_breach_unlocked() && !is_breech_locked())
			{
				state = BREECH_STATE_CLOSED_UNLOCKED;
			}
			else if(!is_breach_unlocked() && is_breech_locked())
			{
				state = BREECH_STATE_CLOSED_LOCKED;
			}
			else if(is_breech_locked() && is_breach_unlocked())
			{
				//! Cannot be locked and unlocked
				state = BREECH_STATE_ERROR;
			}
			else
			{
				//! The breech is closed but is neither locked nor unlocked
				state = BREECH_STATE_CLOSED_INDERTERMINATE;
			}
		}
	}
	else
	{
		if(is_breech_locked() && is_breach_unlocked())
		{
			state = BREECH_STATE_ERROR;
		}
		else
		{
			//! Grand Old Duke
			state = BREECH_STATE_INDERTERMINATE;
		}
	}

	return state;
}