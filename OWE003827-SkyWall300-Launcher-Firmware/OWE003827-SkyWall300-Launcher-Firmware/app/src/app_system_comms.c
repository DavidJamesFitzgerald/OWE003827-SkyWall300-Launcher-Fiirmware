/*    _____ __        _       __      _________ ____  ____     __                           __
  *   / ___// /____  _| |     / /___ _/ / /__  // __ \/ __ \   / /   ____ ___  ______  _____/ /_  ___  _____
  *   \__ \/ //_/ / / / | /| / / __ `/ / / /_ </ / / / / / /  / /   / __ `/ / / / __ \/ ___/ __ \/ _ \/ ___/
  *  ___/ / ,< / /_/ /| |/ |/ / /_/ / / /___/ / /_/ / /_/ /  / /___/ /_/ / /_/ / / / / /__/ / / /  __/ /
  * /____/_/|_|\__, / |__/|__/\__,_/_/_//____/\____/\____/  /_____/\__,_/\__,_/_/ /_/\___/_/ /_/\___/_/
  *			/____/
 */
  
/**
//  *	@file		app_system_comms.c
//  *
//  *	@copyright	OpenWorks Engineering Ltd. 2018
//  *
//  *  @author		Created by David Fitzgerald (david.fitzgerald@openworksengineering.com)
//  *  @date		Last modified on 20 July 2018
//  *
//  *  @brief		Contains system comms functions. This file is editable.
//  *
//  */
// #include "app/inc/app_globals.h"
// #include "app/inc/app_system_comms.h"
// #include "app/inc/app_comms_util.h"
// #include "app/inc/app_analog_functions.h"
// 
// static bool system_comms_initiated = false;
// static bool system_comms_established = false;
// static struct io_descriptor *io = NULL;
// static uint8_t system_comms_rx_char = 0;
// static uint8_t system_comms_rx_buffer_index = 0;
// static uint8_t system_comms_tx_buffer_index = 0;
// static bool system_comms_main_thread_semaphore = false;
// static system_comms_string_s system_comms_strings_to_parse[SYSTEM_COMMS_STRINGS_TO_BUFFER];
// 
// static volatile bool system_comms_rx_semaphore = false;
// static volatile bool system_comms_tx_semaphore = false;
// 
// //! Global variables
// uint8_t system_comms_rx_buffer[SYSTEM_COMMS_DATA_BUF_SIZE] = {0};
// uint8_t system_comms_tx_buffer[SYSTEM_COMMS_DATA_BUF_SIZE] = {0};
// int8_t system_comms_string_to_write_index = 0;
// int8_t system_comms_string_to_read_index = 0;
// 
// system_comms_packet_count_struct packet_count =
// {
// 	.status = 0,
// 	.spi = 0,
// 	.pwm = 0
// };
// 
// //! Prototypes
// static void system_comms_clear_rx_buffer(void);
// static void system_comms_clear_tx_buffer(void);
// 
// static void system_comms_usart_rx_callback(struct usart_async_descriptor * io_descr)
// {
// 	if(NULL != io)
// 	{
// 		if (1 == io_read(io, &system_comms_rx_char, 1))
// 		{
// 			static bool system_comms_in_msg = false;
// 		
// 			if((SYSTEM_COMMS_START_CHAR == system_comms_rx_char) && (false == system_comms_in_msg))
// 			{
// 				system_comms_in_msg = true;
// 				system_comms_rx_buffer_index = 0;
// 			}
// 			else if((SYSTEM_COMMS_END_CHAR == system_comms_rx_char) && (true == system_comms_in_msg) && (system_comms_rx_buffer_index > 1))
// 			{		
// 				bool discard = false;
// 			
// //! If the system_comms_main_thread_semaphore is locked, then the main thread is currently accessing the
// //! system_comms_strings_to_parse array and this callback can, potentially, overwrite data currently being read
// //! by the main thread. If we happen to be reading the index to which we are about to write then discard the message.
// //********************************************************* Critical Section *********************************************************
// 				if(true == system_comms_main_thread_semaphore)
// 				{
// 					if(system_comms_string_to_write_index == system_comms_string_to_read_index)
// 					{
// 						if(true == system_comms_strings_to_parse[system_comms_string_to_write_index].new_data_bool)
// 						{
// 							discard = true;
// 						}
// 					}
// 				}
// 			
// 				if(false == discard)
// 				{					
// 					//! Reset current string
// 					for (uint8_t i = 0; i < SYSTEM_COMMS_DATA_BUF_SIZE; i++)
// 					{
// 						system_comms_strings_to_parse[system_comms_string_to_write_index].string[i] = 0;
// 					}
// 
// 					system_comms_strings_to_parse[system_comms_string_to_write_index].string_length_u8 = system_comms_rx_buffer_index;
// 
// 					//! Copy rx buffer into string buffer for parsing
// 					memcpy(system_comms_strings_to_parse[system_comms_string_to_write_index].string, system_comms_rx_buffer, system_comms_rx_buffer_index);
// 
// 					system_comms_strings_to_parse[system_comms_string_to_write_index].new_data_bool = true;
// 
// 					system_comms_string_to_write_index++;
// 					if (system_comms_string_to_write_index >= SYSTEM_COMMS_STRINGS_TO_BUFFER)
// 					{
// 						system_comms_string_to_write_index = 0;
// 					}
// 
// 					//globals_s.launcher_message_received_bool = true; TODO
// 				}
// //************************************************************************************************************************************
// 				system_comms_in_msg = false;
// 				system_comms_rx_buffer_index = 0;
// 				system_comms_rx_semaphore = false;
// 				usart_async_flush_rx_buffer(io_descr);
// 				system_comms_clear_rx_buffer();
// 			}
// 			else if(true == system_comms_in_msg)
// 			{
// 				if(SYSTEM_COMMS_ESCAPE_CHAR == system_comms_rx_char)
// 				{
// 					if(system_comms_rx_buffer[system_comms_rx_buffer_index-1] >= (uint8_t)SYSTEM_COMMS_ESCAPE_CHAR)
// 					{
// 						system_comms_rx_buffer[system_comms_rx_buffer_index-1] -= (uint8_t)(SYSTEM_COMMS_ESCAPE_CHAR+1);
// 					}
// 					else
// 					{
// 						//! Corruption has occured
// 						system_comms_in_msg = false;
// 						system_comms_rx_buffer_index = 0;
// 						system_comms_rx_semaphore = false;
// 						usart_async_flush_rx_buffer(io_descr);
// 						system_comms_clear_rx_buffer();
// 					}
// 				}
// 				else
// 				{
// 					system_comms_rx_buffer[system_comms_rx_buffer_index++] = system_comms_rx_char;			
// 				}
// 				
// 				if (system_comms_rx_buffer_index >= SYSTEM_COMMS_DATA_BUF_SIZE)
// 				{
// 					//! Overflow has occurred, abort current message
// 					system_comms_in_msg = false;
// 					system_comms_rx_buffer_index = 0;
// 					system_comms_rx_semaphore = false;
// 					usart_async_flush_rx_buffer(io_descr);
// 					system_comms_clear_rx_buffer();
// 				}
// 			}
// 			else
// 			{
// 				//! Corruption has occured
// 				system_comms_in_msg = false;
// 				system_comms_rx_buffer_index = 0;
// 				system_comms_rx_semaphore = false;
// 				usart_async_flush_rx_buffer(io_descr);
// 				system_comms_clear_rx_buffer();
// 			}	
// 		}
// 	}//< end if(NULL != io)
// }
// 
// static void system_comms_usart_tx_callback(struct usart_async_descriptor * io_descr)
// {
// 
// }
// 
// static void system_comms_usart_err_callback(struct usart_async_descriptor * io_descr)
// {
// 
// }
// 
// static uint8_t system_comms_calc_msg_checksum(const uint8_t msg_buffer[], const uint8_t msg_len)
// {
// 	uint8_t checksum = 0;
// 	for (int i=0; i<msg_len; i++)
// 	{
// 		checksum ^= msg_buffer[i];
// 	}
// 	return checksum;
// }
// 
// static void system_comms_clear_rx_buffer(void)
// {
// 	for(uint8_t i = 0; i < sizeof(system_comms_rx_buffer); i++)
// 	{
// 		system_comms_rx_buffer[i] = 0;
// 	}
// }
// 
// static void system_comms_clear_tx_buffer(void)
// {
// 	for(uint8_t i = 0; i < sizeof(system_comms_tx_buffer); i++)
// 	{
// 		system_comms_tx_buffer[i] = 0;
// 	}
// }
// 
// static void system_comms_encode_and_send_msg(uint8_t msg_buffer[], uint8_t msg_len)
// {
// 	if(io != NULL)
// 	{
// 		system_comms_clear_tx_buffer();
// 		system_comms_tx_buffer_index = 0;
// 		
// 		app_add_uint8_to_buffer(system_comms_tx_buffer, &system_comms_tx_buffer_index, SYSTEM_COMMS_START_CHAR);
// 		
// 		for(uint8_t i = 0; i < msg_len; i++)
// 		{
// 			if(msg_buffer[i] == SYSTEM_COMMS_START_CHAR || msg_buffer[i] == SYSTEM_COMMS_ESCAPE_CHAR || msg_buffer[i] == SYSTEM_COMMS_END_CHAR)
// 			{
// 				app_add_uint8_to_buffer(system_comms_tx_buffer, &system_comms_tx_buffer_index, SYSTEM_COMMS_ESCAPE_CHAR);
// 				app_add_uint8_to_buffer(system_comms_tx_buffer, &system_comms_tx_buffer_index, (uint8_t)(msg_buffer[i]+SYSTEM_COMMS_ESCAPE_CHAR));
// 			}
// 			else
// 			{
// 				app_add_uint8_to_buffer(system_comms_tx_buffer, &system_comms_tx_buffer_index, (msg_buffer[i]));
// 			}
// 		}
// 		
// 		app_add_uint8_to_buffer(system_comms_tx_buffer, &system_comms_tx_buffer_index, SYSTEM_COMMS_END_CHAR);
// 		io_write(io, system_comms_tx_buffer, system_comms_tx_buffer_index);
// 	}
// }
// 
// void app_system_comms_init(void)
// {
// 	bool success = false;
// 	
// 	if(NULL == io)
// 	{
// 		int32_t error_code = ERR_FAILURE;
// 
// 		error_code = usart_async_register_callback(&USART_SYSTEM_SERCOM1, USART_ASYNC_RXC_CB, (usart_cb_t)system_comms_usart_rx_callback);
// 
// 		if(ERR_NONE == error_code){ error_code = usart_async_register_callback(&USART_SYSTEM_SERCOM1, USART_ASYNC_TXC_CB, system_comms_usart_tx_callback); }
// 		if(ERR_NONE == error_code){ error_code = usart_async_register_callback(&USART_SYSTEM_SERCOM1, USART_ASYNC_ERROR_CB, system_comms_usart_err_callback); }
// 		if(ERR_NONE == error_code){ error_code = usart_async_get_io_descriptor(&USART_SYSTEM_SERCOM1, &io); }
// 		if(ERR_NONE == error_code){ error_code = usart_async_enable(&USART_SYSTEM_SERCOM1); }
// 
// 		if(ERR_NONE == error_code)
// 		{
// 			success = true;
// 		}
// 	}
// }
// 
// bool app_system_comms_process_msg(void)
// {
// 	bool valid_message = false;
// 	enum system_comms_error_enum error = SYSTEM_COMMS_ERROR_NO_ERROR;
// 		
// 	uint8_t string_to_parse[SYSTEM_COMMS_DATA_BUF_SIZE] = {0};
// 	volatile uint8_t string_to_parse_length_u8 = 0;
// 	
// //! If the system_comms_main_thread_semaphore is locked, then the launcher rx callback is currently writing to the
// //! system_comms_strings_to_parse array. Wait until the callback is done writing before accessing this shared resource.
// //********************************************************* Critical Section *********************************************************
// 	while (true == system_comms_main_thread_semaphore){}
// 	
// 	system_comms_main_thread_semaphore = true; //< Take semaphore to prevent the launcher callback from overwriting the system_comms_strings_to_parse array
// 
// 	if(true == system_comms_strings_to_parse[system_comms_string_to_read_index].new_data_bool)
// 	{
// 		string_to_parse_length_u8 = system_comms_strings_to_parse[system_comms_string_to_read_index].string_length_u8;
// 		memcpy(string_to_parse, system_comms_strings_to_parse[system_comms_string_to_read_index].string, string_to_parse_length_u8);
// 		system_comms_strings_to_parse[system_comms_string_to_read_index].new_data_bool = false;
// 	
// 		system_comms_string_to_read_index++;
// 		if (system_comms_string_to_read_index >= SYSTEM_COMMS_STRINGS_TO_BUFFER)
// 		{
// 			system_comms_string_to_read_index = 0;
// 		}
// 	}
// 	system_comms_main_thread_semaphore = false; //< Release semaphore
// 	
// //************************************************************************************************************************************
// 
// 	if(0 != system_comms_calc_msg_checksum(string_to_parse, string_to_parse_length_u8))
// 	{
// 		error = SYSTEM_COMMS_ERROR_CRC_ERROR;
// 	}
// 	
// 	if((SYSTEM_COMMS_ERROR_NO_ERROR == error) && (string_to_parse_length_u8 < SYSTEM_COMMS_MIN_RX_MSG_LENGTH))
// 	{
// 		error = SYSTEM_COMMS_ERROR_UNEXPECTED_PACKET_LENGTH;
// 	}
// 	
// 	if((SYSTEM_COMMS_ERROR_NO_ERROR == error) && (string_to_parse_length_u8 > SYSTEM_COMMS_MAX_RX_MSG_LENGTH))
// 	{
// 		error = SYSTEM_COMMS_ERROR_UNEXPECTED_PACKET_LENGTH;
// 	}
// 	
// 	if(SYSTEM_COMMS_ERROR_NO_ERROR == error)
// 	{
// 		bool reset_PWM_errors = true;
// 
// //! The following use of semaphores is not (currently) needed as all reads
// //! and writes of the global structure data, with the exception of interrupt flags,
// //! occur from the main thread. Reads and writes of the interrupt flags are considered atomic.
// //! These semaphores will remain should future changes access the global structure from
// //! outside of the main thread.
// //********************************************************* Critical Section *********************************************************
// // 		while (true == app_get_globals_struct_semaphore()){}
// // 		app_set_globals_struct_semaphore(true);
// // 		
// // 		globals_s.launcher_connected_bool = true;
// // 		
// // 		app_set_globals_struct_semaphore(false);
// //************************************************************************************************************************************
// 		switch (string_to_parse[0])
// 		{
// 			case SYSTEM_COMMS_HDR_CAL_SERIAL_NUM_COMMAND :
// 			{
// 				if (SYSTEM_COMMS_CAL_SERIAL_NUMBER_COMMAND_LENGTH == string_to_parse_length_u8)
// 				{
// 					valid_message = true;
// 
// 					// Only save calibration structures to flash when commanded to do so
// 					if (true == (string_to_parse[CAL_CMD_SAVE_OFFSET] & CAL_COMMAND_SAVE_FLAG))
// 					{
// 						// Set global flag to save current calibration data to flash mem
// 						globals_s.calibration.save_flag = true;
// 					}
// 
// 					globals_s.calibration.data.serial_number = app_get_uint16_from_buffer(string_to_parse, CAL_CMD_SERIAL_NUMBER_OFFSET);
// 				}
// 				else
// 				{
// 					error = SYSTEM_COMMS_ERROR_UNEXPECTED_PACKET_LENGTH;
// 				}
// 				break;
// 			}
// 
// 			case SYSTEM_COMMS_HDR_CAL_ADC_CHANNEL_COMMAND :
// 			{
// 				if (SYSTEM_COMMS_CAL_ANALOGUE_CHANNEL_COMMAND_LENGTH == string_to_parse_length_u8)
// 				{
// 					valid_message = true;
// 					float gain = 0.0F;
// 					float zero = 0.0F;
// 
// 					// Only save calibration structures to flash when commanded to do so
// 					if (true == (string_to_parse[CAL_CMD_SAVE_OFFSET] & CAL_COMMAND_SAVE_FLAG))
// 					{
// 						// Set global flag to save current calibration data to flash mem
// 						globals_s.calibration.save_flag = true;
// 					}
// 
// 					gain = app_get_float_from_buffer(string_to_parse, (uint8_t)CAL_ANALOGUE_CHANNEL_GAIN_OFFSET);
// 					zero = app_get_float_from_buffer(string_to_parse, (uint8_t)CAL_ANALOGUE_CHANNEL_ZERO_OFFSET);
// 
// 					if ((false == isnan(gain)) && (false == isnan(zero)))
// 					{
// 						switch (string_to_parse[CAL_CMD_ANALOGUE_CHANNEL_OFFSET])
// 						{
// 							case ANA_ADC_CHANNEL_RESERVOIR:
// 								globals_s.calibration.data.res_pressure_adc_gain = gain;
// 								globals_s.calibration.data.res_pressure_adc_zero = zero;
// 								break;
// 
// 							case ANA_ADC_CHANNEL_CURRENT:
// 								globals_s.calibration.data.charger_current_adc_gain = gain;
// 								globals_s.calibration.data.charger_current_adc_zero = zero;
// 								break;
// 
// 							case ANA_ADC_CHANNEL_VOLTAGE:
// 								globals_s.calibration.data.charger_voltage_adc_gain = gain;
// 								globals_s.calibration.data.charger_voltage_adc_zero = zero;
// 								break;
// 
// 							case ANA_ADC_CHANNEL_HW_VERSION:
// 								globals_s.calibration.data.hw_version_adc_gain = gain;
// 								globals_s.calibration.data.hw_version_adc_zero = zero;
// 								break;
// 
// 							case ANA_ADC_CHANNEL_GND_CAL:
// 								//TODO ?
// 								globals_s.calibration.save_flag = false;
// 								break;
// 
// 							default:
// 								// Unknown command. Reset global flag to save current calibration data to flash mem
// 								globals_s.calibration.save_flag = false;
// 								break;
// 						}
// 					}
// 				}
// 				else
// 				{
// 					error = SYSTEM_COMMS_ERROR_UNEXPECTED_PACKET_LENGTH;
// 				}
// 				break;
// 			}
// 
// 			case SYSTEM_COMMS_HDR_CONFIG_COMMAND_ACK :
// 			{
// 				if (SYSTEM_COMMS_CONFIG_COMMAND_ACK_MSG_LENGTH == string_to_parse_length_u8)
// 				{
// 					valid_message = true;
// 
// 					// Received a config ack from Beckhoff, respond with command response
// 					if (globals_s.launcher_state == ST_LAUNCHER_CONFIG_BROADCAST)
// 					{
// 						// Set flag to indicate successful comms
// 						system_comms_established = true;
// 
// 						// Move to active state
// 						globals_s.launcher_state = ST_LAUNCHER_ACTIVE;
// 					}
// 				}
// 				else
// 				{
// 					error = SYSTEM_COMMS_ERROR_UNEXPECTED_PACKET_LENGTH;
// 				}
// 				break;
// 			}
// 
// 			case SYSTEM_COMMS_HDR_STATUS_COMMAND :
// 			{
// 				if (SYSTEM_COMMS_STATUS_COMMAND_MSG_LENGTH == string_to_parse_length_u8)
// 				{
// 					valid_message = true;
// 
// 					packet_count.status = string_to_parse[STATUS_COMMAND_PACKET_COUNT_OFFSET];
// 
// 					globals_s.charger.set_voltage_act = app_get_float_from_buffer(string_to_parse, STATUS_COMMAND_VOLTAGE_REQ_OFFSET);
// 					globals_s.charger.set_current_act = app_get_float_from_buffer(string_to_parse, STATUS_COMMAND_CURRENT_REQ_OFFSET);
// 
// 					if (STATUS_COMMAND_ENABLE_CHARGE_FLAG == string_to_parse[STATUS_COMMAND_ENABLE_CHARGE_OFFSET])
// 					{
// 						app_projectile_enable_charging();
// 					}
// 					else
// 					{
// 						app_projectile_disable_charging();
// 					}
// 
// 					app_system_comms_tx_status_response();
// 				}
// 				else
// 				{
// 					error = SYSTEM_COMMS_ERROR_UNEXPECTED_PACKET_LENGTH;
// 				}
// 				break;
// 			}
// 
// 			case SYSTEM_COMMS_HDR_SPI_COMMAND :
// 			{
// 				valid_message = true;
// 
// 				packet_count.spi = string_to_parse[SPI_COMMAND_PACKET_COUNT_OFFSET];
// 
// 				if (SPI != globals_s.projectile.comms_mode)
// 				{
// 					// Reset PWM and SPI outputs to safe states
// 					app_reset_io_pins();
// 
// 					// Set projectile comms mode
// 					globals_s.projectile.comms_mode = SPI;
// 
// //TODO
// 					// Ensure that the SPI pins are re-connected to their SPI functions
// // 					gpio_enable_module_pin(PROJECTILE_SPI_MISO_PIN, PROJECTILE_SPI_MISO_FUNCTION);
// // 					gpio_enable_module_pin(PROJECTILE_SPI_MOSI_PIN, PROJECTILE_SPI_MOSI_FUNCTION);
// // 					gpio_enable_module_pin(PROJECTILE_SPI_SCK_PIN, PROJECTILE_SPI_SCK_FUNCTION);
// // 					spi_enable(PROJECTILE_SPI);
// 				}
// 
// //TODO
// 				//system_comms_tx_launcher_spi_response(string_to_parse, msg_len);
// 
// 				break;
// 			}
// 
// 			case SYSTEM_COMMS_HDR_PWM_COMMAND :
// 			{
// 				if (SYSTEM_COMMS_PWM_COMMAND_MSG_LENGTH == string_to_parse_length_u8)
// 				{
// 					valid_message = true;
// 					reset_PWM_errors = false;
// 
// 					packet_count.pwm = string_to_parse[PWM_COMMAND_PACKET_COUNT_OFFSET];
// 
// 					globals_s.projectile.pwm_op_val = app_get_uint16_from_buffer(string_to_parse, PWM_COMMAND_TIME_OF_FLIGHT_OFFSET);
// 
// 					// If not in PWM_mode, set pins accordingly
// 					if (PWM == globals_s.projectile.comms_mode)
// 					{
// 						// Set PWM output counts received from TC
// 						tc_write_ra(PROJECTILE_PWM_OP_TC, PROJECTILE_PWM_OP_TC_CHANNEL, globals_s.projectile.pwm_op_val);
// 					}
// 					else
// 					{
// 						// Reset PWM and SPI outputs to safe states
// 						reset_io_pins();
// 
// 						// Set projectile comms mode
// 						globals_s.projectile.comms_mode = PWM;
// 
// 						// Wait to ensure no cross-over
// 						delay_us(1);
// 
// 						// Turn PWM input pin back into PWM function
// 						gpio_enable_module_pin(PROJECTILE_PWM_FB_TC_PIN, PROJECTILE_PWM_FB_TC_FUNCTION);
// 
// 						// Turn PWM output pin back into PWM function
// 						gpio_enable_module_pin(PROJECTILE_PWM_OP_TC_PIN, PROJECTILE_PWM_OP_TC_FUNCTION);
// 
// 						globals_s.projectile.pwm_fb_error_count = 0;
// 						globals_s.projectile.pwm_fb_missed_count = 0;
// 
// 						PROJECTILE_PWM_OP_TC->channel[PROJECTILE_PWM_OP_TC_CHANNEL].ier |= AVR32_TC_CPCS_MASK;		// Trigger an interrupt on RC (rising edge)
// 						PROJECTILE_PWM_FB_TC->channel[PROJECTILE_PWM_FB_TC_CHANNEL].ier |= AVR32_TC_LDRAS_MASK;		// Enable the Input Capture interrupt
// 
// 						// Set default PWM values
// 						tc_write_ra(PROJECTILE_PWM_OP_TC, PROJECTILE_PWM_OP_TC_CHANNEL, globals_s.projectile.pwm_op_val);
// 						tc_write_rc(PROJECTILE_PWM_OP_TC, PROJECTILE_PWM_OP_TC_CHANNEL, PWM_PERIOD_COUNT);
// 
// 						// Start the OP and FB timers as close to synchronously as possible
// 						tc_start(PROJECTILE_PWM_OP_TC, PROJECTILE_PWM_OP_TC_CHANNEL);
// 						tc_start(PROJECTILE_PWM_FB_TC,  PROJECTILE_PWM_FB_TC_CHANNEL);
// 					}
// 
// 					// Send response back to TC
// 					tx_launcher_pwm_response();
// 				}
// 				else
// 				{
// 					error = SYSTEM_COMMS_ERROR_UNEXPECTED_PACKET_LENGTH;
// 				}
// 				break;
// 			}
// 
// 			case SYSTEM_COMMS_HDR_COMMAND_RESET :
// 			{
// 				if (SYSTEM_COMMS_RESET_COMMAND_MSG_LENGTH == string_to_parse_length_u8)
// 				{
// 					valid_message = true;
// 
// 					globals_s.launcher_state = ST_LAUNCHER_START_UP;
// 				}
// 				else
// 				{
// 					error = SYSTEM_COMMS_ERROR_UNEXPECTED_PACKET_LENGTH;
// 				}
// 				break;
// 			}
// 
// 			default:
// 			{
// 				error = SYSTEM_COMMS_ERROR_MSG_NOT_RECOGNISED;
// 				break;
// 			}
// 		}//end switch (sw100_rx_buffer[0])
// 
// 		if(SYSTEM_COMMS_ERROR_NO_ERROR != error)
// 		{			
// 			//launcher_rx_error_count++;
// 		}
// 		else
// 		{			
// 			//! Reset comms timeout count on reception of a good message
// 			valid_message = true;
// 			
// //! The following use of semaphores is not (currently) needed as all reads
// //! and writes of the global structure data, with the exception of interrupt flags,
// //! occur from the main thread. Reads and writes of the interrupt flags are considered atomic.
// //! These semaphores will remain should future changes access the global structure from
// //! outside of the main thread.
// //********************************************************* Critical Section *********************************************************
// // 			while (true == app_get_globals_struct_semaphore()){}
// // 			app_set_globals_struct_semaphore(true);
// // 			
// // 			globals_s.launcher_time_since_last_comms_ms = 0;
// // 			
// // 			app_set_globals_struct_semaphore(false);
// //************************************************************************************************************************************
// 		
// 			if (true == reset_PWM_errors)
// 			{
// 				globals_s.projectile.pwm_fb_error_count = 0;
// 				globals_s.projectile.pwm_fb_missed_count = 0;
// 
// 				if (PWM == globals_s.projectile.comms_mode)
// 				{
// 					reset_io_pins();
// 
// 					// Ensure that the SPI pins are re-connected to their SPI functions
// 					gpio_enable_module_pin(PROJECTILE_SPI_MISO_PIN, PROJECTILE_SPI_MISO_FUNCTION);
// 					gpio_enable_module_pin(PROJECTILE_SPI_MOSI_PIN, PROJECTILE_SPI_MOSI_FUNCTION);
// 					gpio_enable_module_pin(PROJECTILE_SPI_SCK_PIN, PROJECTILE_SPI_SCK_FUNCTION);
// 					spi_enable(PROJECTILE_SPI);
// 
// 					globals_s.projectile.comms_mode = SPI;
// 				}
// 			}//end if (true == reset_PWM_errors)
// 		}
// 	}//end if(SYSTEM_COMMS_ERROR_NO_ERROR == error)
// }
// 
// void app_system_comms_tx_status_response(void)
// {
// 	uint8_t index = 0;
// 	uint8_t msg_buffer[SYSTEM_COMMS_STATUS_RESPONSE_MSG_LENGTH];
// 
// 	app_add_uint8_to_buffer(msg_buffer, &index, SYSTEM_COMMS_HDR_STATUS_RESPONSE);
// 
// 	app_add_uint8_to_buffer(msg_buffer, &index, packet_count.status);
// 	app_add_uint8_to_buffer(msg_buffer, &index, get_status_byte());
// 	app_add_float_to_buffer_LE(msg_buffer, &index, globals_s.reservoir.measured_pressure_act);
// 	app_add_float_to_buffer_LE(msg_buffer, &index, globals_s.charger.measured_current_act);
// 	app_add_float_to_buffer_LE(msg_buffer, &index, globals_s.charger.measured_voltage_act);
// 	app_add_uint8_to_buffer(msg_buffer, &index, globals_s.projectile.pwm_fb_error_count);
// 	app_add_uint8_to_buffer(msg_buffer, &index, globals_s.projectile.pwm_fb_missed_count);
// 
// 	app_add_msg_crc16(msg_buffer, &index);
// 	system_comms_encode_and_send_msg(msg_buffer, SYSTEM_COMMS_STATUS_RESPONSE_MSG_LENGTH);
// }