/**
 ******************************************************************************
 * @file    iis_codec.c
 * @author  William Xu
 * @version V1.0.0
 * @date    21-May-2015
 * @brief   iis codec loopback demo
 ******************************************************************************
 *
 *  The MIT License
 *  Copyright (c) 2016 MXCHIP Inc.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is furnished
 *  to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 *  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 ******************************************************************************
 */

#include "mico.h"
#include "audio.h"
#include "nau88c10.h"

#define os_iis_coedc_log(format, ...)  custom_log("iis_codec", format, ##__VA_ARGS__)

extern mico_i2c_device_t i2c_audio_device;
mico_iis_device_t iis_audio_device;

void audio_task( uint32_t arg );

int application_start( void )
{
    uint8_t ret = AUDIO_ERROR;
    uint8_t reg_data[2] = { 0 };
    uint8_t reg_data_read[2] = { 0 };
    uint32_t deviceid = 0;
    OSStatus err = kNoErr;
    /* Start MiCO system functions according to mico_config.h*/
    mico_system_init( mico_system_context_init( 0 ) );

    /* init iis */
    iis_audio_device.master_enable = 1;
    iis_audio_device.port = MICO_IIS_1;
    iis_audio_device.bits = 16;
    iis_audio_device.clk_freq = 8 * 1000 * 16 * 2 * 8;   //mclk frequence 2.048MHZ
//  MicoIISFinalize(&iis_audio_device);
    err = MicoIISInitialize( &iis_audio_device );
    os_iis_coedc_log("IIS init return %d",err);
    /* init iic */
    MicoI2cFinalize( &i2c_audio_device );
    i2c_audio_device.address = AUDIO_I2C_ADDRESS;
    i2c_audio_device.address_width = I2C_ADDRESS_WIDTH_7BIT;
    i2c_audio_device.port = MICO_I2C_2;
    i2c_audio_device.speed_mode = I2C_STANDARD_SPEED_MODE;
    err = MicoI2cInitialize( &i2c_audio_device );

    /* nau88c10 codec initialization */
    deviceid = nau88c10_drv.ReadID( AUDIO_I2C_READ_ADDRESS );
//    printf( "deviceid is 0x%02x\r\n", (unsigned int)deviceid );
    if ( deviceid == NAU88C10_ID )
    {
        /* Reset the Codec Registers */
        nau88c10_drv.Reset( AUDIO_I2C_WRITE_ADDRESS );
        ret = AUDIO_OK;
    }
    else
        ret = AUDIO_ERROR;
    if ( ret == AUDIO_OK )
    {
        /* Initialize the codec internal registers */
        nau88c10_drv.Init( AUDIO_I2C_WRITE_ADDRESS );
    }
    /*for loopback test mode*/
//    reg_data[0] = 0x0;
//    reg_data[1] = 0x1;
//    nau88c10_drv.WriteRegister( 0x05, reg_data );
//    nau88c10_drv.ReadRegister( 0x05, reg_data_read );
//    printf( "register 0x05 is 0x%x 0x%x \r\n", reg_data_read[0], reg_data_read[1] );

	mico_rtos_create_thread( NULL, MICO_APPLICATION_PRIORITY, "audio_task", 
	audio_task, 0x10000, 0);

    /* write test data */
	while(1)
	{
		mico_rtos_delay_microseconds(100);
	}
}

void audio_task( uint32_t arg )
{
    uint8_t p_buf[1024*4] = { 0x0 };
	uint8_t p_buf_read[1024*4] = { 0x0 };
	platform_iis_message_segment_t iis_msg;
	iis_msg.rx_buffer = p_buf_read;
	iis_msg.tx_buffer = p_buf;
	iis_msg.length = sizeof(p_buf);
	uint8_t flag = 0;
	 while ( 1 )
    {
	    MicoIISTransfer( &iis_audio_device, &iis_msg, 1);
    	if(flag == 0)
    	{
    	    iis_msg.tx_buffer = p_buf_read;
    	    iis_msg.rx_buffer = p_buf;
    	    flag = 1;
    	}else {
            iis_msg.tx_buffer = p_buf;
            iis_msg.rx_buffer = p_buf_read;
            flag = 0;
    	}
    }
}

