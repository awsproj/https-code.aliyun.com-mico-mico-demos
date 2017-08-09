/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NAU88C10_H
#define __NAU88C10_H

/* Includes ------------------------------------------------------------------*/
#include "audio.h"

/** @defgroup NAU88C10_Exported_Constants
  * @{
  */ 

/******************************************************************************/
/****************************** REGISTER MAPPING ******************************/
/******************************************************************************/
/** 
  * @brief  NAU88C10 ID
  */  
#define  NAU88C10_ID    0xca

#define  NAU88C10_WRITE_ADD 0x34
#define  NAU88C10_READ_ADD 0x35

/**
  * @brief Device ID Register: Reading from this register will indicate device 
  *                            family ID 8994h
  */
#define nau88c10_CHIPID_ADDR                  0x40
#define nau88c10_AICC                         0x05


/**
  * @}
  */ 

/** @defgroup nau88c10_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup nau88c10_Exported_Functions
  * @{
  */
    
/*------------------------------------------------------------------------------
                           Audio Codec functions 
------------------------------------------------------------------------------*/
/* High Layer codec functions */
uint32_t nau88c10_Init(uint16_t DeviceAddr);
void     nau88c10_DeInit(void);
uint32_t nau88c10_ReadID(uint16_t DeviceAddr);
uint32_t nau88c10_ReadRegister( uint16_t DeviceAddr, uint8_t* value );
uint32_t nau88c10_WriteRegister( uint16_t DeviceAddr,uint8_t * reg_data );
uint32_t nau88c10_Play(uint16_t DeviceAddr, uint16_t* pBuffer, uint16_t Size);
uint32_t nau88c10_Reset(uint16_t DeviceAddr);

/* Audio driver structure */
extern AUDIO_DrvTypeDef   nau88c10_drv;

#endif /* __nau88c10_H */
