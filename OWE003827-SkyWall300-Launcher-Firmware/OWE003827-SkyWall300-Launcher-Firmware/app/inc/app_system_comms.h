/*    _____ __        _       __      _________ ____  ____     __                           __
 *   / ___// /____  _| |     / /___ _/ / /__  // __ \/ __ \   / /   ____ ___  ______  _____/ /_  ___  _____
 *   \__ \/ //_/ / / / | /| / / __ `/ / / /_ </ / / / / / /  / /   / __ `/ / / / __ \/ ___/ __ \/ _ \/ ___/
 *  ___/ / ,< / /_/ /| |/ |/ / /_/ / / /___/ / /_/ / /_/ /  / /___/ /_/ / /_/ / / / / /__/ / / /  __/ /
 * /____/_/|_|\__, / |__/|__/\__,_/_/_//____/\____/\____/  /_____/\__,_/\__,_/_/ /_/\___/_/ /_/\___/_/
 *			/____/
 */
  
/**
 *	@file		app_system_comms.h
 *
 *	@copyright	OpenWorks Engineering Ltd. 2018
 *
 *  @author		Created by David Fitzgerald (david.fitzgerald@openworksengineering.com)
 *  @date		Last modified on 20 July 2018
 *
 *  @brief		Contains system comms definitions. This file is editable.
 *
 */

#ifndef APP_SYSTEM_COMMS_H_
#define APP_SYSTEM_COMMS_H_

#define COMMS_PROTOCOL_REV		1

#define SYSTEM_COMMS_STRINGS_TO_BUFFER	5
#define SYSTEM_COMMS_DATA_BUF_SIZE		128
#define SYSTEM_COMMS_MIN_RX_MSG_LENGTH	5
#define SYSTEM_COMMS_MAX_RX_MSG_LENGTH	50

// System comms Special Characters
#define SYSTEM_COMMS_ESCAPE_CHAR	0x0A
#define SYSTEM_COMMS_START_CHAR		0x02
#define SYSTEM_COMMS_END_CHAR		0x03

//! System comms message identifiers
#define SYSTEM_COMMS_HDR_CAL_SERIAL_NUM_COMMAND				0x16
#define SYSTEM_COMMS_HDR_CAL_ADC_CHANNEL_COMMAND			0x17
#define SYSTEM_COMMS_HDR_CAL_DAC_CHANNEL_COMMAND			0x18
#define SYSTEM_COMMS_HDR_CONFIG_COMMAND_ACK					0x4B
#define SYSTEM_COMMS_HDR_STATUS_COMMAND						0x4C
#define SYSTEM_COMMS_HDR_SPI_COMMAND						0x4D
#define SYSTEM_COMMS_HDR_PWM_COMMAND						0x4E
#define SYSTEM_COMMS_HDR_COMMAND_RESET						0x4F
#define SYSTEM_COMMS_HDR_CONFIG_RESPONSE					0x5B
#define SYSTEM_COMMS_HDR_STATUS_RESPONSE					0x5C
#define SYSTEM_COMMS_HDR_SPI_RESPONSE						0x5D
#define SYSTEM_COMMS_HDR_PWM_RESPONSE						0x5E

//! System comms message lengths
#define SYSTEM_COMMS_CAL_SERIAL_NUMBER_COMMAND_LENGTH		7
#define SYSTEM_COMMS_CAL_ANALOGUE_CHANNEL_COMMAND_LENGTH	14
#define SYSTEM_COMMS_CONFIG_COMMAND_ACK_MSG_LENGTH			5
#define SYSTEM_COMMS_CONFIG_RESPONSE_MSG_LENGTH				15
#define SYSTEM_COMMS_STATUS_COMMAND_MSG_LENGTH				13
#define SYSTEM_COMMS_STATUS_RESPONSE_MSG_LENGTH				19
#define SYSTEM_COMMS_PWM_RESPONSE_MSG_LENGTH				19
#define SYSTEM_COMMS_SPI_RESPONSE_MSG_FIXED_LENGTH			5
#define SYSTEM_COMMS_SPI_RESPONSE_MSG_MAX_COMMAND_LENGTH	50
#define SYSTEM_COMMS_SPI_RESPONSE_MSG_MAX_VARIABLE_LENGTH	50
#define SYSTEM_COMMS_PWM_COMMAND_MSG_LENGTH					6
#define SYSTEM_COMMS_RESET_COMMAND_MSG_LENGTH				5

//! Calibration command defines
#define CAL_CMD_SAVE_OFFSET						2
#define CAL_COMMAND_SAVE_FLAG					0x01
#define CAL_CMD_SERIAL_NUMBER_OFFSET			3
#define CAL_CMD_ANALOGUE_CHANNEL_OFFSET			3
#define CAL_ANALOGUE_CHANNEL_GAIN_OFFSET		4 //< "M" values
#define CAL_ANALOGUE_CHANNEL_ZERO_OFFSET		8 //< "C" values

//! Status command defines
#define STATUS_COMMAND_PACKET_COUNT_OFFSET		1
#define STATUS_COMMAND_VOLTAGE_REQ_OFFSET		2
#define STATUS_COMMAND_CURRENT_REQ_OFFSET		6
#define STATUS_COMMAND_ENABLE_CHARGE_OFFSET		10
#define STATUS_COMMAND_ENABLE_CHARGE_FLAG		0x03

//! SPI command defines
#define SPI_COMMAND_PACKET_COUNT_OFFSET			1
#define SPI_COMMAND_COMMAND_LENGTH_OFFSET		2
#define SPI_COMMAND_PAYLOAD_START_OFFSET		3
#define SPI_COMMAND_RESPONSE_LENGTH_OFFSET		5 //< Note that this offset also requires the payload length!

//! PWM command defines
#define PWM_COMMAND_PACKET_COUNT_OFFSET			1
#define PWM_COMMAND_TIME_OF_FLIGHT_OFFSET		2

//! Structure for holding current packet ID for each message type that uses a packet ID
typedef struct system_comms_packet_count_struct {
	uint8_t status;
	uint8_t spi;
	uint8_t pwm;
} system_comms_packet_count_struct;

typedef struct system_comms_string_s
{
	uint8_t string[SYSTEM_COMMS_DATA_BUF_SIZE];
	uint8_t string_length_u8;
	bool	new_data_bool;
}system_comms_string_s;

enum system_comms_error_enum
{
	SYSTEM_COMMS_ERROR_NO_ERROR					= 0,
	SYSTEM_COMMS_ERROR_ENCODING					= 1,
	SYSTEM_COMMS_ERROR_MSG_TOO_LONG				= 2,
	SYSTEM_COMMS_ERROR_CRC_ERROR				= 3,
	SYSTEM_COMMS_ERROR_MSG_NOT_RECOGNISED		= 4,
	SYSTEM_COMMS_ERROR_UNEXPECTED_PACKET_LENGTH	= 5,
	SYSTEM_COMMS_ERROR_MAX_ENUM
};

void app_system_comms_tx_status_response(void);

#endif /* APP_SYSTEM_COMMS_H_ */