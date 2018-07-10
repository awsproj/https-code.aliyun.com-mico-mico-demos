/**
 *  UNPUBLISHED PROPRIETARY SOURCE CODE
 *  Copyright (c) 2016 MXCHIP Inc.
 *
 *  The contents of this file may not be disclosed to third parties, copied or
 *  duplicated in any form, in whole or in part, without the prior written
 *  permission of MXCHIP Corporation.
 *
 */


#pragma once

#include "mico_rtos.h"
#include "mico_bt_constants.h"
#include "LinkListUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

#define PACKET_POOL_ID 0x1A2B3C4D
#define PACKET_ID      0x5F6A7B8D

/******************************************************
 *                   Enumerations
 ******************************************************/

typedef enum
{
    BT_PACKET_OWNER_POOL,
    BT_PACKET_OWNER_STACK,
    BT_PACKET_OWNER_APP,
} bt_packet_owner_t;

/******************************************************
 *                 Type Definitions
 ******************************************************/

typedef struct bt_packet      bt_packet_t;
typedef struct bt_packet_pool bt_packet_pool_t;

/******************************************************
 *                    Structures
 ******************************************************/

#pragma pack(1)
struct bt_packet
{
    uint32_t           packet_id;
    linked_list_node_t node;
    bt_packet_pool_t*  pool;
    bt_packet_owner_t  owner;
    uint8_t*           data_start;
    uint8_t*           data_end;
    uint8_t*           packet_end;
    uint8_t            packet_start[1];
};

struct bt_packet_pool
{
    uint32_t      pool_id;
    linked_list_t pool_list;
    uint8_t*      pool_buffer;
    mico_mutex_t  mutex;
    uint32_t      max_packet_count;
    uint32_t      header_size;
    uint32_t      data_size;
    uint32_t      packet_created;
    uint32_t      packet_deleted;
};
#pragma pack()

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

OSStatus bt_packet_pool_init( bt_packet_pool_t* pool, uint32_t packet_count, uint32_t header_size, uint32_t data_size );

OSStatus bt_packet_pool_deinit( bt_packet_pool_t* pool );

OSStatus bt_packet_pool_allocate_packet( bt_packet_pool_t* pool, bt_packet_t** packet );

OSStatus bt_packet_pool_dynamic_allocate_packet( bt_packet_t** packet, uint32_t header_size, uint32_t data_size );

OSStatus bt_packet_pool_free_packet( bt_packet_t* packet );

#ifdef __cplusplus
} /* extern "C" */
#endif
