/*    _____ __        _       __      _________ ____  ____     __                           __
 *   / ___// /____  _| |     / /___ _/ / /__  // __ \/ __ \   / /   ____ ___  ______  _____/ /_  ___  _____
 *   \__ \/ //_/ / / / | /| / / __ `/ / / /_ </ / / / / / /  / /   / __ `/ / / / __ \/ ___/ __ \/ _ \/ ___/
 *  ___/ / ,< / /_/ /| |/ |/ / /_/ / / /___/ / /_/ / /_/ /  / /___/ /_/ / /_/ / / / / /__/ / / /  __/ /
 * /____/_/|_|\__, / |__/|__/\__,_/_/_//____/\____/\____/  /_____/\__,_/\__,_/_/ /_/\___/_/ /_/\___/_/
 *			/____/
 */
  
/**
 *	@file		app_globals.h
 *
 *	@copyright	OpenWorks Engineering Ltd. 2018
 *
 *  @author		Created by David Fitzgerald (david.fitzgerald@openworksengineering.com)
 *  @date		Last modified on 20 July 2018
 *
 *  @brief		Contains global definitions. This file is editable.
 *
 */

#ifndef APP_GLOBALS_H_
#define APP_GLOBALS_H_

#include <utils_assert.h>
#include <stdbool.h>
#include <driver_init.h>

//! Define the state enumeration
enum launcher_state_enum
{
	ST_LAUNCHER_START_UP,
	ST_LAUNCHER_CONFIG_BROADCAST,
	ST_LAUNCHER_ACTIVE,
	ST_LAUNCHER_SHUTDOWN
};

typedef struct system_tick_struct
{
	bool leds;
	bool adc;
	bool dac;
	bool comms;
	bool flash;
} system_tick_struct;

//! Define the LED enumeration
enum led_enum
{
	LED_OFF,
	LED_ON,
	LED_SLOW_FLASH,
	LED_FAST_FLASH,
	LED_INTERMITTENT_FLASH
};

typedef struct ui_struct
{
	enum led_enum	status_led;
	enum led_enum	error_led;
	uint8_t			led_flash_step;
} ui_struct;

//! ADC value structure
typedef struct adc_struct
{
	//TODO do we care about this ?
	int16_t gndana_calibration_raw;	//< GNDANA calibration in raw ADC counts
} adc_struct;

//! Reservoir structure
typedef struct reservoir_struct
{
	float measured_pressure_act;	//< Measured resevoir presssure
	bool pressure_error;			//< Measured pressure is outside of limits [TRUE]/ within limits [FALSE]
} reservoir_struct;

//! Projectile charger structure
typedef struct charger_struct
{
	float set_voltage_act;			//< Set point voltage
	float set_current_act;			//< Set point current
	float measured_voltage_act;		//< Measured voltage
	float measured_current_act;		//< Measured current
	bool enabled;					//< Projectile charge circuit enabled [TRUE]/disabled [FALSE]
	bool safety_enabled;			//< Projectile charge safety enabled [TRUE]/disabled [FALSE]
	bool current_error;				//< Measured current is outside of limits [TRUE]/ within limits [FALSE]
	bool voltage_error;				//< Measured voltage is outside of limits [TRUE]/ within limits [FALSE]
} charger_struct;

//! Define the projectile comms enumeration
enum proj_comms_mode_enum
{
	NONE,
	SPI,
	PWM
};

typedef struct projectile_struct
{
	bool						fitted;
	uint16_t					pwm_op_val;
	uint16_t					pwm_fb_val;
	uint8_t						pwm_fb_error_count;
	uint8_t						pwm_fb_missed_count;	//< This count could be 1 and everything is OK. Only bad if >= 2.
	enum proj_comms_mode_enum	comms_mode;
} projectile_struct;

//! Configuration control structure
typedef struct config_struct
{
	int16_t hw_version_raw;			//< Hardware version in raw ADC counts
} config_struct;

//! Date and time structure
typedef struct date_time_struct
{
	uint16_t				year;
	uint8_t					month;
	uint8_t					day;
	uint8_t					hour;
	uint8_t					minute;
	uint8_t					second;
} date_time_struct;

//! Flash data structure
typedef struct __attribute__((packed)) flash_data_struct //TODO packed
{
	date_time_struct	date_time_of_calibration;
	uint16_t			serial_number;
	float				proj_charge_voltage_dac_zero;
	float				proj_charge_voltage_dac_gain;
	float				proj_charge_current_dac_zero;
	float				proj_charge_current_dac_gain;
	float				res_pressure_adc_zero;
	float				res_pressure_adc_gain;
	float				hw_version_adc_zero;
	float				hw_version_adc_gain;
	float				charger_voltage_adc_zero;
	float				charger_voltage_adc_gain;
	float				charger_current_adc_zero;
	float				charger_current_adc_gain;
	uint16_t			crc;
} flash_data_struct;

// Calibration data structure
typedef struct calibration_struct
{
	bool valid_flag;
	bool save_flag;
	flash_data_struct data;
} calibration_struct;

struct globals_struct
{
	enum launcher_state_enum	launcher_state;
	system_tick_struct			systick;
	ui_struct					leds;
	adc_struct					adc;
	reservoir_struct			reservoir;
	charger_struct				charger;
	projectile_struct			projectile;
	config_struct				config;
	calibration_struct			calibration;
	uint16_t					tc2_comms_timeout_count;
};

extern struct globals_struct globals_s;

#endif /* APP_GLOBALS_H_ */