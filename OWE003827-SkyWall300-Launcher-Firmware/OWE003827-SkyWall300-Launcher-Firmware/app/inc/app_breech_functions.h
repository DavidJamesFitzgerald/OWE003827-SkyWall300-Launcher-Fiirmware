/*    _____ __        _       __      _________ ____  ____     __                           __
 *   / ___// /____  _| |     / /___ _/ / /__  // __ \/ __ \   / /   ____ ___  ______  _____/ /_  ___  _____
 *   \__ \/ //_/ / / / | /| / / __ `/ / / /_ </ / / / / / /  / /   / __ `/ / / / __ \/ ___/ __ \/ _ \/ ___/
 *  ___/ / ,< / /_/ /| |/ |/ / /_/ / / /___/ / /_/ / /_/ /  / /___/ /_/ / /_/ / / / / /__/ / / /  __/ /
 * /____/_/|_|\__, / |__/|__/\__,_/_/_//____/\____/\____/  /_____/\__,_/\__,_/_/ /_/\___/_/ /_/\___/_/
 *			/____/
 */
  
/**
 *	@file		app_breech_functions.h
 *
 *	@copyright	OpenWorks Engineering Ltd. 2018
 *
 *  @author		Created by David Fitzgerald (david.fitzgerald@openworksengineering.com)
 *  @date		Last modified on 20 July 2018
 *
 *  @brief		Contains breech definitions. This file is editable.
 *
 */

#ifndef APP_BREECH_FUNCTIONS_H_
#define APP_BREECH_FUNCTIONS_H_

typedef enum
{
	BREECH_STATE_OPEN,
	BREECH_STATE_CLOSED_UNLOCKED,
	BREECH_STATE_CLOSED_LOCKED,
	BREECH_STATE_OPEN_INDERTERMINATE,
	BREECH_STATE_CLOSED_INDERTERMINATE,
	BREECH_STATE_INDERTERMINATE,
	BREECH_STATE_ERROR,
	BREECH_STATE_MAX_ENUM	
} breech_state_e;

breech_state_e app_get_breech_position(void);

#endif /* APP_BREECH_FUNCTIONS_H_ */