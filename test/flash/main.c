/**
 ******************************************************************************
 * @file    main.c
 * @author  Snow Yang
 * @version V1.0.0
 * @date    21-May-2015
 * @brief   main.c
 ******************************************************************************
 */

#include "mico.h"

#define TEST_COUNT 100000
#define SECTOR_SIZE 4096

static uint8_t wbuf[SECTOR_SIZE];
static uint8_t rbuf[SECTOR_SIZE];

int application_start(void)
{
  uint32_t offset;
  printf("Flash test start ...\r\n");
  for (int i = 0; i < TEST_COUNT; i++)
  {
    MicoFlashErase(MICO_PARTITION_OTA_TEMP, 0x00, SECTOR_SIZE);
    offset = 0;
    MicoFlashRead(MICO_PARTITION_OTA_TEMP, &offset, rbuf, SECTOR_SIZE);
    memset(wbuf, 0xFF, SECTOR_SIZE);
    if (memcmp(rbuf, wbuf, SECTOR_SIZE) != 0)
    {
      printf("\r\nErase error\r\n");
      return 1;
    }

    for (int j = 0; j < SECTOR_SIZE; j++)
    {
      wbuf[j] = j & 0xFF;
    }
    offset = 0;
    MicoFlashWrite(MICO_PARTITION_OTA_TEMP, &offset, wbuf, SECTOR_SIZE);
    offset = 0;
    MicoFlashRead(MICO_PARTITION_OTA_TEMP, &offset, rbuf, SECTOR_SIZE);
    if (memcmp(rbuf, wbuf, SECTOR_SIZE) != 0)
    {
      printf("\r\nWrite error\r\n");
      return 1;
    }

    printf("%d \r", i);
    fflush(stdout);
  }

  printf("\r\nTest Pass\r\n");

  return 0;
}
