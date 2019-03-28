/**
 ******************************************************************************
 * @file    hello_world.c
 * @author  Snow Yang
 * @version V1.0.0
 * @date    2-Feb-2019
 * @brief   First MXOS application to say hello world!
 ******************************************************************************
 *
 *  The MIT License
 *  Copyright (c) 2019 MXCHIP Inc.
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
#include "mkv.h"

#define app_log(format, ...) custom_log("APP", format, ##__VA_ARGS__)

static OSStatus func_test(void)
{
	int n;
	int rc;
	OSStatus err = kGeneralErr;
	uint8_t val[KV_MAX_KEY_LEN] = {0};
	uint8_t dump[KV_MAX_VAL_LEN];

	printf("--------------------------------\r\n");
	printf("kv item set->get test\r\n");
	for (int i = 0; i < 1000; i++)
	{
		printf("times %d\r", i + 1);
		fflush(stdout);
		memset(val, i, KV_MAX_VAL_LEN - 1);
		rc = mkv_item_set("name", val, KV_MAX_VAL_LEN - 1);
		require(rc == 0, exit);
		n = KV_MAX_VAL_LEN;
		rc = mkv_item_get("name", dump, &n);
		require(n == KV_MAX_VAL_LEN - 1, exit);
		require(memcmp(val, dump, n) == 0, exit);
	}
	printf("\npass\r\n");

	printf("--------------------------------\r\n");
	printf("kv item set->get->delete test\r\n");
	for (int i = 0; i < 1000; i++)
	{
		printf("times %d\r", i + 1);
		fflush(stdout);
		memset(val, i, KV_MAX_VAL_LEN);
		rc = mkv_item_set("name", val, KV_MAX_VAL_LEN);
		require(rc == 0, exit);
		n = KV_MAX_VAL_LEN;
		rc = mkv_item_get("name", dump, &n);
		require(n == KV_MAX_VAL_LEN, exit);
		require(memcmp(val, dump, n) == 0, exit);
		rc = mkv_item_delete("name");
		require(rc == 0, exit);
	}
	printf("\npass\r\n");

	err = kNoErr;

exit:
	printf("last rc = %d\r\n", rc);
	return err;
}

static OSStatus perf_test(void)
{
	int n;
	int i;
	int rc;
	OSStatus err = kGeneralErr;
	char key[KV_MAX_KEY_LEN + 1];
	uint8_t val[KV_MAX_VAL_LEN];

	strcpy(key, "i");
	rc = mkv_item_set(key, val, 1);
	require(rc == 0, exit);
	printf("--------------------------------\r\n");
	printf("get item, key length = %d, value length = %d\r\n", 1, 1);
	printf("start\r\n");
	for (i = 0; i < 5000; i++)
	{
		n = KV_MAX_VAL_LEN;
		rc = mkv_item_get(key, val, &n);
		require(rc == 0, exit);
	}
	printf("times = %d\r\n", i);

	memset(key, 'K', KV_MAX_KEY_LEN);
	key[KV_MAX_KEY_LEN] = '\0';
	rc = mkv_item_set(key, val, KV_MAX_VAL_LEN);
	require(rc == 0, exit);
	printf("--------------------------------\r\n");
	printf("get item, key length = %d, value length = %d\r\n", KV_MAX_KEY_LEN, KV_MAX_VAL_LEN);
	printf("start\r\n");
	for (i = 0; i < 5000; i++)
	{
		n = KV_MAX_VAL_LEN;
		rc = mkv_item_get(key, val, &n);
		require(rc == 0, exit);
	}
	printf("times = %d\r\n", i);

	printf("--------------------------------\r\n");
	printf("set item, key length = %d, value length = %d\r\n", 1, 1);
	printf("start\r\n");
	for (i = 0; i < 500; i++)
	{
		memset(val, i, 1);
		rc = mkv_item_set(key, val, 1);
		require(rc == 0, exit);
	}
	printf("times = %d\r\n", i);

	memset(key, 'K', KV_MAX_KEY_LEN);
	key[KV_MAX_KEY_LEN] = '\0';
	printf("--------------------------------\r\n");
	printf("set item, key length = %d, value length = %d\r\n", KV_MAX_KEY_LEN, KV_MAX_VAL_LEN);
	printf("start\r\n");
	for (i = 0; i < 100; i++)
	{
		memset(val, i, KV_MAX_VAL_LEN);
		rc = mkv_item_set(key, val, KV_MAX_VAL_LEN);
		require(rc == 0, exit);
	}
	printf("times = %d\r\n", i);

	err = kNoErr;

exit:
	printf("last rc = %d\r\n", rc);
	return err;
}

int application_start(void)
{
	int rc;
	OSStatus err = kGeneralErr;

	rc = mkv_init();
	require(rc == 0, exit);

	err = func_test();
	require_noerr(err, exit);

	err = perf_test();
	require_noerr(err, exit);

	err = kNoErr;

exit:
	return err;
}
