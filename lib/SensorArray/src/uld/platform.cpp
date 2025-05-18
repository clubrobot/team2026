/**
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */



#include "include/platform.h"

#include "include/VL53L5CX.h"

uint8_t VL53L5CX::RdByte(
  VL53L5CX_Platform *p_platform,
  uint16_t RegisterAddress,
  uint8_t *p_value)
{
  uint8_t status = RdMulti(p_platform, RegisterAddress, p_value, 1);
  return status;
}

uint8_t VL53L5CX::WrByte(
  VL53L5CX_Platform *p_platform,
  uint16_t RegisterAddress,
  uint8_t value)
{
  // Just use WrMulti but 1 byte
  uint8_t status = WrMulti(p_platform, RegisterAddress, &value, 1);
  return status;
}

uint8_t VL53L5CX::WrMulti(
  VL53L5CX_Platform *p_platform,
  uint16_t RegisterAddress,
  uint8_t *p_values,
  uint32_t size)
{
  uint32_t i = 0;
  uint8_t buffer[2];

  while (i < size) {
    // If still more than DEFAULT_I2C_BUFFER_LEN bytes to go, DEFAULT_I2C_BUFFER_LEN,
    // else the remaining number of bytes
    size_t current_write_size = (size - i > BUFFER_LENGTH ? BUFFER_LENGTH : size - i);

    p_platform->dev_i2c->beginTransmission((uint8_t)((p_platform->address >> 1) & 0x7F));

    // Target register address for transfer
    buffer[0] = (uint8_t)((RegisterAddress + i) >> 8);
    buffer[1] = (uint8_t)((RegisterAddress + i) & 0xFF);
    p_platform->dev_i2c->write(buffer, 2);
    if (p_platform->dev_i2c->write(p_values + i, current_write_size) == 0) {
      return 1;
    } else {
      i += current_write_size;
      if (size - i) {
        // Flush buffer and send stop bit so we have compatibility also with ESP32 platforms
        p_platform->dev_i2c->endTransmission(true);
      }
    }
  }

  return p_platform->dev_i2c->endTransmission(true);
}

uint8_t VL53L5CX::RdMulti(
  VL53L5CX_Platform *p_platform,
  uint16_t RegisterAddress,
  uint8_t *p_values,
  uint32_t size)
{
  int status = 0;
  uint8_t buffer[2];

  // Loop until the port is transmitted correctly

    p_platform->dev_i2c->beginTransmission((uint8_t)((p_platform->address >> 1) & 0x7F));

    // Target register address for transfer
    buffer[0] = (uint8_t)(RegisterAddress >> 8);
    buffer[1] = (uint8_t)(RegisterAddress & 0xFF);
    p_platform->dev_i2c->write(buffer, 2);

    status = p_platform->dev_i2c->endTransmission(false);

    // Fix for some STM32 boards
    // Reinitialize the i2c bus with the default parameters
#ifdef ARDUINO_ARCH_STM32
    if (status) {
      p_platform->dev_i2c->end();
      p_platform->dev_i2c->begin();
    }
#endif
    // End of fix

    if (status != 0)
    {
      return status;
    }


  uint32_t i = 0;
  if (size > BUFFER_LENGTH) {
    while (i < size) {
      // If still more than DEFAULT_I2C_BUFFER_LEN bytes to go, DEFAULT_I2C_BUFFER_LEN,
      // else the remaining number of bytes
      uint8_t current_read_size = (size - i > BUFFER_LENGTH ? BUFFER_LENGTH : size - i);
      p_platform->dev_i2c->requestFrom(((uint8_t)((p_platform->address >> 1) & 0x7F)),
                                       current_read_size);
      while (p_platform->dev_i2c->available()) {
        p_values[i] = p_platform->dev_i2c->read();
        i++;
      }
    }
  } else {
    p_platform->dev_i2c->requestFrom(((uint8_t)((p_platform->address >> 1) & 0x7F)), size);
    while (p_platform->dev_i2c->available()) {
      p_values[i] = p_platform->dev_i2c->read();
      i++;
    }
  }

  return i != size;
}

void VL53L5CX::SwapBuffer(
  uint8_t     *buffer,
  uint16_t     size)
{
  uint32_t i, tmp;

  /* Example of possible implementation using <string.h> */
  for (i = 0; i < size; i = i + 4) {
    tmp = (
            buffer[i] << 24)
          | (buffer[i + 1] << 16)
          | (buffer[i + 2] << 8)
          | (buffer[i + 3]);

    memcpy(&(buffer[i]), &tmp, 4);
  }
}

uint8_t VL53L5CX::WaitMs(
  VL53L5CX_Platform *p_platform,
  uint32_t TimeMs)
{
  (void)p_platform;
  delay(TimeMs);

  return 0;
}