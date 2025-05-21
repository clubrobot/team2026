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

#define I2C_MASTER_WRITE 0x00
#define I2C_MASTER_READ 0X00

#define I2C_TXRX_BUFFER_SIZE 256

//A buffer used to add index for the vl53l8cx data format
uint8_t i2c_buffer[I2C_TXRX_BUFFER_SIZE + 2];

uint8_t VL53L5CX::RdByte(
  VL53L5CX_Platform *p_platform,
  uint16_t RegisterAddress,
  uint8_t *p_value)
{
  uint8_t status = RdMulti(p_platform, RegisterAddress, p_value, 1);
  return status;
}

uint8_t VL53L5CX::WrByte(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t value)
{
  // Just use WrMulti but 1 byte
  uint8_t status = WrMulti(p_platform, RegisterAddress, &value, 1);
  return status;
}



uint8_t VL53L5CX::WrMulti(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_values, uint32_t size)
{
  int i = 0;
  uint8_t status = 0;

  while (i + I2C_TXRX_BUFFER_SIZE < size)
  {
    //Add index to the data
    i2c_buffer[0] = (RegisterAddress + i) >> 8;
    i2c_buffer[1] = (RegisterAddress + i) & 0xFF;

    p_platform->dev_i2c->handle.XferOptions = I2C_OTHER_AND_LAST_FRAME;

    //Add the data
    memcpy(&i2c_buffer[2], p_values + i, I2C_TXRX_BUFFER_SIZE);

    status = i2c_master_write(p_platform->dev_i2c, (p_platform->address & 0xFE) | I2C_MASTER_WRITE, i2c_buffer,I2C_TXRX_BUFFER_SIZE + 2);

    if (status != I2C_OK)
    {
      return status;
    }

    i+= I2C_TXRX_BUFFER_SIZE;
  }

  //Add index to the data
  i2c_buffer[0] = (RegisterAddress + i) >> 8;
  i2c_buffer[1] = (RegisterAddress + i) & 0xFF;

  p_platform->dev_i2c->handle.XferOptions = I2C_OTHER_AND_LAST_FRAME;

  //Add the data
  memcpy(&i2c_buffer[2], p_values + i, size - i);

  return i2c_master_write(p_platform->dev_i2c, (p_platform->address & 0xFE) | I2C_MASTER_WRITE, i2c_buffer,size + 2 - i);
}

uint8_t VL53L5CX::RdMulti(VL53L5CX_Platform *p_platform, uint16_t RegisterAddress, uint8_t *p_values, uint32_t size)
{
  i2c_status_e status = I2C_OK;
  //Add index to the data
  i2c_buffer[0] = RegisterAddress >> 8;
  i2c_buffer[1] = RegisterAddress & 0xFF;

  p_platform->dev_i2c->handle.XferOptions = I2C_OTHER_FRAME;

  status = i2c_master_write(p_platform->dev_i2c, (p_platform->address & 0xFE) | I2C_MASTER_WRITE, i2c_buffer, 2);

  p_platform->dev_i2c->handle.XferOptions = I2C_OTHER_AND_LAST_FRAME;

  if (status != I2C_OK)
  {
    return status;
  }

  return i2c_master_read(p_platform->dev_i2c, (p_platform->address & 0xFE) | I2C_MASTER_READ, p_values, size);
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