/*
 * app_comms_util.h
 *
 * Created: 12/06/2018 13:55:13
 *  Author: David Fitzgerald
 */ 


#ifndef APP_COMMS_UTIL_H_
#define APP_COMMS_UTIL_H_

//! Appends an Openworks CRC16 to a buffer
void app_add_msg_crc16(uint8_t msg_buffer[], uint8_t* msg_len);
uint16_t calc_msg_crc16(const uint8_t msg_buffer[], const uint8_t msg_len);

//! Adds a uint8 variable to a binary data buffer
static inline uint8_t app_add_uint8_to_buffer(uint8_t msg_buffer[], uint8_t* index, uint8_t val)
{
	msg_buffer[*index] = (uint8_t) (val);

	// Increment index by size of variable
	*index += sizeof(val);
	
	return *index;
}

//! Adds a int8 variable to a binary data buffer
static inline uint8_t app_add_int8_to_buffer(uint8_t msg_buffer[], uint8_t* index, int8_t val)
{
	msg_buffer[*index] = (uint8_t) (val);

	// Increment index by size of variable
	*index += sizeof(val);

	return *index;
}

//! Adds a uint16 variable to a binary data buffer in little endian format
static inline uint8_t app_add_uint16_to_buffer_LE(uint8_t msg_buffer[], uint8_t* index, uint16_t val)
{	
	//! SAME family is little endian
	union
	{
		uint16_t as_uint16;
		unsigned char bytes[2];
	} converter;

	converter.as_uint16 = val;

	for (int i = 0; i < 2; i++)
	{
		msg_buffer[*index + i] = converter.bytes[i];
	}
	
	// Increment index by size of variable
	*index += sizeof(val);

	return *index;
}

//! Adds a uint16 variable to a binary data buffer in big endian format
static inline uint8_t app_add_uint16_to_buffer_BE(uint8_t msg_buffer[], uint8_t* index, uint16_t val)
{	
	//! SAME family is little endian
	union
	{
		uint16_t as_uint16;
		unsigned char bytes[2];
	} converter;

	converter.as_uint16 = val;

	for (int i = 0; i < 2; i++)
	{
		msg_buffer[*index + i] = converter.bytes[1-i];
	}
	
	// Increment index by size of variable
	*index += sizeof(val);

	return *index;
}

//! Adds a int16 variable to a binary data buffer
static inline uint8_t app_add_int16_to_buffer(uint8_t msg_buffer[], uint8_t* index, int16_t val)
{
	// AT32UC3C is big endian
	// Comms out are little endian
	msg_buffer[*index + 1] = (uint8_t) (val >> 8);
	msg_buffer[*index] = (uint8_t) (val);

	// Increment index by size of variable
	*index += sizeof(val);

	return *index;
}

//! Retrieves a uint16 from a byte array
static inline uint16_t app_get_uint16_from_buffer(uint8_t msg_buffer[], uint8_t index)
{
	uint16_t val = ((msg_buffer[index + 1] << 8) | msg_buffer[index]);
	return val;
}

//Retrieves a uint16 from a byte array
static inline uint16_t app_sw100_get_uint16_from_buffer(uint8_t msg_buffer[], uint8_t index)
{
	uint16_t val = ((msg_buffer[index] << 8) | msg_buffer[index + 1]);
	return val;
}

//Retrieves an int16 from a byte array
static inline int16_t app_sw100_get_int16_from_buffer(uint8_t msg_buffer[], uint8_t index)
{
	int16_t val = ((msg_buffer[index] << 8) | msg_buffer[index + 1]);
	return val;
}

//! Retrieves a int16 from a byte array
static inline int16_t app_get_int16_from_buffer(uint8_t msg_buffer[], uint8_t index)
{
	int16_t val = ((msg_buffer[index + 1] << 8) | msg_buffer[index]);
	return val;
}

//! Adds a float variable to a binary data buffers (requires 4 bytes) in little endian format
static inline uint8_t app_add_float_to_buffer_LE(uint8_t msg_buffer[], uint8_t* index, float val)
{
	//! SAME family is little endian
	union
	{
		float as_float;
		unsigned char bytes[4];
	} converter;

	converter.as_float = val;

	for (int i = 0; i < 4; i++)
	{
		msg_buffer[*index + i] = converter.bytes[i];
	}
	
	// Increment index by size of variable
	*index += sizeof(val);

	return *index;
}

//! Adds a float variable to a binary data buffers (requires 4 bytes) in big endian format
static inline uint8_t app_add_float_to_buffer_BE(uint8_t msg_buffer[], uint8_t* index, float val)
{
	//! SAME family is little endian
	union
	{
		float as_float;
		unsigned char bytes[4];
	} converter;

	converter.as_float = val;

	for (int i = 0; i < 4; i++)
	{
		msg_buffer[*index + i] = converter.bytes[3-i];
	}
	
	// Increment index by size of variable
	*index += sizeof(val);

	return *index;
}

//! Retrieves a float variable from a binary data buffer (requires 4 bytes)
static inline float app_get_float_from_buffer(uint8_t msg_buffer[], uint8_t index)
{
	//! SAME family is little-endian.
	union
	{
		float as_float;
		unsigned char bytes[4];
	} converter;

	for (int i = 0; i < 4; i++)
	{
		converter.bytes[3-i] = msg_buffer[index + i];
	}

	return converter.as_float;
}

//! Gets a float variable from a binary data buffer (requires 4 bytes)
static inline float app_sw100_get_float_from_buffer(uint8_t msg_buffer[], uint8_t index)
{
	union {
		float as_float;
		unsigned char bytes[4];
	} converter;
	
	for (int i = 0; i < 4; i++)
	{ 
		converter.bytes[i] = msg_buffer[index + i];
	}
	
	return converter.as_float;
}

//! Adds a double variable to a binary data buffer (requires 8 bytes) in little endian format
static inline uint8_t app_add_double_to_buffer_LE(uint8_t msg_buffer[], uint8_t* index, double val)
{
	//! SAME family is little-endian.
	union
	{
		double as_double;
		unsigned char bytes[8];
	} converter;

	converter.as_double = val;

	for (int i = 0; i < 8; i++)
	{
		msg_buffer[*index + i] = converter.bytes[i];
	};
	
	// Increment index by size of variable
	*index += sizeof(val);

	return *index;
}

//! Adds a double variable to a binary data buffer (requires 8 bytes) in big endian format
static inline uint8_t app_add_double_to_buffer_BE(uint8_t msg_buffer[], uint8_t* index, double val)
{
	//! SAME family is little-endian.
	union
	{
		double as_double;
		unsigned char bytes[8];
	} converter;

	converter.as_double = val;

	for (int i = 0; i < 8; i++)
	{
		msg_buffer[*index + i] = converter.bytes[7-i];
	};
	
	// Increment index by size of variable
	*index += sizeof(val);

	return *index;
}

//! Retrieves a double variable from a binary data buffer (requires 8 bytes)
static inline double app_get_double_from_buffer(uint8_t msg_buffer[], uint8_t index)
{
	union
	{
		double as_double;
		unsigned char bytes[8];
	} converter;

	for (int i = 0; i < 8; i++)
	{
		converter.bytes[7-i] = msg_buffer[index + i];
	};

	return converter.as_double;
}

static inline double app_get_double_from_buffer_LE(uint8_t msg_buffer[], uint8_t index)
{
	union
	{
		double as_double;
		unsigned char bytes[8];
	} converter;

	for (int i = 0; i < 8; i++)
	{
		converter.bytes[i] = msg_buffer[index + i];
	};

	return converter.as_double;
}

//! Adds a uint32 variable to a binary data buffer in little endian format
static inline uint8_t app_add_uint32_to_buffer_LE(uint8_t msg_buffer[], uint8_t* index, uint32_t val)
{
	//! SAME family is little endian
	union
	{
		uint16_t as_uint32;
		unsigned char bytes[4];
	} converter;

	converter.as_uint32 = val;

	for (int i = 0; i < 4; i++)
	{
		msg_buffer[*index + i] = converter.bytes[i];
	}
	
	// Increment index by size of variable
	*index += sizeof(val);

	return *index;
}

//! Adds a uint32 variable to a binary data buffer in big endian format
static inline uint8_t app_add_uint32_to_buffer_BE(uint8_t msg_buffer[], uint8_t* index, uint32_t val)
{
	//! SAME family is little endian
	union
	{
		uint16_t as_uint32;
		unsigned char bytes[4];
	} converter;

	converter.as_uint32 = val;

	for (int i = 0; i < 4; i++)
	{
		msg_buffer[*index + i] = converter.bytes[3-i];
	}
	
	// Increment index by size of variable
	*index += sizeof(val);

	return *index;
}

//! Retrieves a UInt32 variable from a binary data buffer (requires 4 bytes)
static inline uint32_t app_get_uint32_from_buffer(uint8_t msg_buffer[], uint8_t index)
{
	union
	{
		uint32_t as_uint32;
		unsigned char bytes[4];
	} converter;

	for (int i = 0; i < 4; i++)
	{
		converter.bytes[3-i] = msg_buffer[index + i];
	};

	return converter.as_uint32;
}

static inline uint32_t app_get_uint32_from_buffer_LE(uint8_t msg_buffer[], uint8_t index)
{
	union
	{
		uint32_t as_uint32;
		unsigned char bytes[4];
	} converter;

	for (int i = 0; i < 4; i++)
	{
		converter.bytes[i] = msg_buffer[index + i];
	};

	return converter.as_uint32;
}

#endif /* APP_COMMS_UTIL_H_ */