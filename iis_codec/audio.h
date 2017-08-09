/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIO_H
#define __AUDIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */
    
/** @addtogroup AUDIO
  * @{
  */

/** @defgroup AUDIO_Exported_Constants
  * @{
  */

/* Codec audio Standards */
#define CODEC_STANDARD                0x04
#define I2S_STANDARD                  I2S_STANDARD_PHILIPS

#define AUDIO_I2C_WRITE_ADDRESS                ((uint16_t)0x34)
#define AUDIO_I2C_READ_ADDRESS                ((uint16_t)0x35)
#define AUDIO_I2C_ADDRESS                       ((uint16_t)0x35)

/* Audio status definition */     
#define AUDIO_OK                            ((uint8_t)0)
#define AUDIO_ERROR                         ((uint8_t)1)
#define AUDIO_TIMEOUT                       ((uint8_t)2)

/**
  * @}
  */

/** @defgroup AUDIO_Exported_Types
  * @{
  */

/** @defgroup AUDIO_Driver_structure  Audio Driver structure
  * @{
  */
typedef struct
{
  uint32_t  (*Init)(uint16_t);
  void      (*DeInit)(void);
  uint32_t  (*ReadID)(uint16_t);
  uint32_t  (*ReadRegister)(uint16_t,uint8_t*);
  uint32_t  (*WriteRegister)(uint16_t,uint8_t*);
  uint32_t  (*Play)(uint16_t, uint16_t*, uint16_t);
  uint32_t  (*Reset)(uint16_t);
}AUDIO_DrvTypeDef;
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __AUDIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
