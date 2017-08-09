
/* Includes ------------------------------------------------------------------*/
#include "nau88c10.h"
#include "mico.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup Components
 * @{
 */

/** @addtogroup nau88c10
 * @brief     This file provides a set of functions needed to drive the
 *            nau88c10 audio codec.
 * @{
 */

/** @defgroup nau88c10_Private_Types
 * @{
 */

/**
 * @}
 */

/** @defgroup nau88c10_Private_Defines
 * @{
 */
/* Uncomment this line to enable verifying data sent to codec after each write 
 operation (for debug purpose) */
#if !defined (VERIFY_WRITTENDATA)  
/*#define VERIFY_WRITTENDATA*/
#endif /* VERIFY_WRITTENDATA */
/**
 * @}
 */

/** @defgroup nau88c10_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @defgroup nau88c10_Private_Variables
 * @{
 */

/* Audio codec driver structure initialization */
AUDIO_DrvTypeDef nau88c10_drv =
    {
        nau88c10_Init,
        nau88c10_DeInit,
        nau88c10_ReadID,
        nau88c10_ReadRegister,
        nau88c10_WriteRegister,
        nau88c10_Play,
        nau88c10_Reset,
    };

/* I2C device */
mico_i2c_device_t i2c_audio_device = {
    MICO_I2C_2, NAU88C10_WRITE_ADD, I2C_ADDRESS_WIDTH_7BIT, I2C_STANDARD_SPEED_MODE
};

/************** I2C/SPI buffer length ******/
#define NAU_BUFFER_LEN 2

/** @defgroup nau88c10_Private_Functions
 * @{
 *
 */

OSStatus NAU88C10_I2C_bus_write(uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt)
{
  OSStatus err = kNoErr;
  mico_i2c_message_t nau_i2c_msg = {NULL, NULL, 0, 0, 0, false};

  uint8_t array[NAU_BUFFER_LEN];
  uint8_t stringpos;
  if(1 == (*(reg_data) && 0x01))
      array[0] = reg_addr + 1;
  else
      array[0] = reg_addr;
  i2c_audio_device.address = NAU88C10_WRITE_ADD>>1;
  for (stringpos = 0; stringpos < cnt; stringpos++) {
          array[stringpos + 1] = *(reg_data + stringpos + 1);
  }

  err = MicoI2cBuildTxMessage(&nau_i2c_msg, array, cnt + 1, 3);
  require_noerr( err, exit );
  err = MicoI2cTransfer(&i2c_audio_device, &nau_i2c_msg, 1);
  require_noerr( err, exit );

exit:
  return err;
}

OSStatus NAU88C10_I2C_bus_read(uint8_t *reg_data, uint8_t cnt)
{
  OSStatus err = kNoErr;
  mico_i2c_message_t nau_i2c_msg = {NULL, NULL, 0, 0, 0, false};
  i2c_audio_device.address = NAU88C10_READ_ADD>>1;
  err = MicoI2cBuildRxMessage(&nau_i2c_msg, reg_data, cnt, 3);
  require_noerr( err, exit );
  err = MicoI2cTransfer(&i2c_audio_device, &nau_i2c_msg, 1);
  require_noerr( err, exit );

exit:
  return err;
}

OSStatus NAU88C10_Write_RegData(uint8_t reg_addr, uint8_t* reg_data)
{
  OSStatus err = kNoErr;
  err = NAU88C10_I2C_bus_write(reg_addr<<1, reg_data, 1);
  return err;
}

OSStatus NAU88C10_Read_RegData(uint8_t reg_addr, uint8_t *reg_data)
{
  OSStatus err = kNoErr;
  err = NAU88C10_I2C_bus_write(reg_addr<<1, reg_data, 0);
  err = NAU88C10_I2C_bus_read(reg_data, 2);
  return err;
}

/**
 * @brief Initializes the audio codec and the control interface.
 * @param DeviceAddr: Device address on communication Bus.
 * @param OutputInputDevice: can be OUTPUT_DEVICE_SPEAKER, OUTPUT_DEVICE_HEADPHONE,
 *  OUTPUT_DEVICE_BOTH, OUTPUT_DEVICE_AUTO, INPUT_DEVICE_DIGITAL_MICROPHONE_1,
 *  INPUT_DEVICE_DIGITAL_MICROPHONE_2, INPUT_DEVICE_DIGITAL_MIC1_MIC2,
 *  INPUT_DEVICE_INPUT_LINE_1 or INPUT_DEVICE_INPUT_LINE_2.
 * @param Volume: Initial volume level (from 0 (Mute) to 100 (Max))
 * @param AudioFreq: Audio Frequency
 * @retval 0 if correct communication, else wrong communication
 */
uint32_t nau88c10_Init( uint16_t DeviceAddr )
{
    uint8_t reg_data[2] = {0};
    /* Initialize the Control interface of the Audio Codec */
    /*Power Management*/
    reg_data[0] = 0x01;
    reg_data[1] = 0x5d;
    NAU88C10_Write_RegData(0x1,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x15;
    NAU88C10_Write_RegData(0x2,reg_data);
    /*output in HeadPhone*/
    reg_data[0] = 0x0;
    reg_data[1] = 0xed;
    NAU88C10_Write_RegData(0x3,reg_data);
    /*Audio Control*/
    reg_data[0] = 0x0;
    reg_data[1] = 0x10;
    NAU88C10_Write_RegData(0x4,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x5,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0xc;
    NAU88C10_Write_RegData(0x6,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0xa;
    NAU88C10_Write_RegData(0x7,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x8,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x9,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x8;
    NAU88C10_Write_RegData(0xa,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0xff;
    NAU88C10_Write_RegData(0xb,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0xc,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0xd,reg_data);
    reg_data[0] = 0x1;
    reg_data[1] = 0x08;
    NAU88C10_Write_RegData(0xe,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0xff;
    NAU88C10_Write_RegData(0xf,reg_data);
    /*Equalizer*/
    reg_data[0] = 0x1;
    reg_data[1] = 0x2c;
    NAU88C10_Write_RegData(0x12,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x2c;
    NAU88C10_Write_RegData(0x13,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x2c;
    NAU88C10_Write_RegData(0x14,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x2c;
    NAU88C10_Write_RegData(0x15,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x2c;
    NAU88C10_Write_RegData(0x16,reg_data);
    /*DAC Limiter*/
    reg_data[0] = 0x0;
    reg_data[1] = 0x32;
    NAU88C10_Write_RegData(0x18,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x19,reg_data);
    /*Notch Filter*/
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x1b,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x1c,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x1d,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x1e,reg_data);
    /*ALC Control*/
    reg_data[0] = 0x0;
    reg_data[1] = 0x38;
    NAU88C10_Write_RegData(0x20,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0xb;
    NAU88C10_Write_RegData(0x21,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x32;
    NAU88C10_Write_RegData(0x22,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x23,reg_data);
    /*PLL Control*/
    reg_data[0] = 0x0;
    reg_data[1] = 0x8;
    NAU88C10_Write_RegData(0x24,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0xc;
    NAU88C10_Write_RegData(0x25,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x93;
    NAU88C10_Write_RegData(0x26,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0xe9;
    NAU88C10_Write_RegData(0x27,reg_data);
    /*BYP Control*/
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x28,reg_data);
    /*Input Output Mixer*/
    reg_data[0] = 0x0;
    reg_data[1] = 0x3;
    NAU88C10_Write_RegData(0x2c,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x10;
    NAU88C10_Write_RegData(0x2d,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x2e,reg_data);
    reg_data[0] = 0x1;
    reg_data[1] = 0x00;
    NAU88C10_Write_RegData(0x2f,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x30,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x02;
    NAU88C10_Write_RegData(0x31,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x01;
    NAU88C10_Write_RegData(0x32,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x33,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x34,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x35,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0xb9;
    NAU88C10_Write_RegData(0x36,reg_data);
    reg_data[0] = 0x0;
    reg_data[1] = 0x0;
    NAU88C10_Write_RegData(0x37,reg_data);
    /*output in HeadPhone*/
//    reg_data[0] = 0x0;
//    reg_data[1] = 0x01;
//    NAU88C10_Write_RegData(0x38,reg_data);
    /*output in speaker*/
    reg_data[0] = 0x0;
    reg_data[1] = 0x01;
    NAU88C10_Write_RegData(0x38,reg_data);
    return 0;
}

/**
 * @brief  Deinitializes the audio codec.
 * @param  None
 * @retval  None
 */
void nau88c10_DeInit( void )
{
    /* Deinitialize Audio Codec interface */
//  AUDIO_IO_DeInit();
}

/**
 * @brief  Get the nau88c10 ID.
 * @param DeviceAddr: Device address on communication Bus.
 * @retval The nau88c10 ID
 */
uint32_t nau88c10_ReadID( uint16_t DeviceAddr )
{
    /* Initialize the Control interface of the Audio Codec */
    uint8_t value[2] = {0};
    NAU88C10_Read_RegData(nau88c10_CHIPID_ADDR, value );
    return value[1];
}

uint32_t nau88c10_ReadRegister( uint16_t DeviceAddr, uint8_t* value )
{
    /* Initialize the Control interface of the Audio Codec */
    NAU88C10_Read_RegData(DeviceAddr, value );
    return 0;
}

uint32_t nau88c10_WriteRegister( uint16_t DeviceAddr,uint8_t * reg_data )
{
    NAU88C10_Write_RegData(DeviceAddr,reg_data);
    return 0;
}

/**
 * @brief Start the audio Codec play feature.
 * @note For this codec no Play options are required.
 * @param DeviceAddr: Device address on communication Bus.
 * @retval 0 if correct communication, else wrong communication
 */
uint32_t nau88c10_Play( uint16_t DeviceAddr, uint16_t* pBuffer, uint16_t Size )
{
    uint32_t counter = 0;

    return counter;
}
/**
 * @brief Resets nau88c10 registers.
 * @param DeviceAddr: Device address on communication Bus.
 * @retval 0 if correct communication, else wrong communication
 */
uint32_t nau88c10_Reset( uint16_t DeviceAddr )
{
    uint32_t counter = 0;
    uint8_t reg_data[2] = {0};
    
    /* Reset Codec by writing in 0x0000 address register */
    reg_data[0] = 0;
    reg_data[1] = 0;
    NAU88C10_Write_RegData(0x0,reg_data);
    
    return counter;
}
