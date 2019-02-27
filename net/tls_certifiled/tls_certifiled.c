/**
 ******************************************************************************
 * @file    hello_world.c
 * @author  William Xu
 * @version V1.0.0
 * @date    21-May-2015
 * @brief   First MiCO application to say hello world!
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

#define app_log(format, ...)  custom_log("APP", format, ##__VA_ARGS__)

const char *PEM_CERT = "-----BEGIN CERTIFICATE-----\r\n\
MIIDCTCCAq+gAwIBAgIJAOdypp4THRdcMAoGCCqGSM49BAMCMIGNMQswCQYDVQQG\r\n\
EwJVUzEPMA0GA1UECAwGT3JlZ29uMQ4wDAYDVQQHDAVTYWxlbTETMBEGA1UECgwK\r\n\
Q2xpZW50IEVDQzENMAsGA1UECwwERmFzdDEYMBYGA1UEAwwPd3d3LndvbGZzc2wu\r\n\
Y29tMR8wHQYJKoZIhvcNAQkBFhBpbmZvQHdvbGZzc2wuY29tMB4XDTE2MDgxMTIw\r\n\
MDczOFoXDTE5MDUwODIwMDczOFowgY0xCzAJBgNVBAYTAlVTMQ8wDQYDVQQIDAZP\r\n\
cmVnb24xDjAMBgNVBAcMBVNhbGVtMRMwEQYDVQQKDApDbGllbnQgRUNDMQ0wCwYD\r\n\
VQQLDARGYXN0MRgwFgYDVQQDDA93d3cud29sZnNzbC5jb20xHzAdBgkqhkiG9w0B\r\n\
CQEWEGluZm9Ad29sZnNzbC5jb20wWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAARV\r\n\
v/QPRFCaPc6bt/DFTfVwe9TsJI4ZgOxaTKIkA2Ism9rvojUSQ4R2FsZWlQbMAam9\r\n\
9nUaQve9qbI2Il/HXX+0o4H1MIHyMB0GA1UdDgQWBBTr1EtZa5VhP1FXtgRNiUGI\r\n\
RFyr8jCBwgYDVR0jBIG6MIG3gBTr1EtZa5VhP1FXtgRNiUGIRFyr8qGBk6SBkDCB\r\n\
jTELMAkGA1UEBhMCVVMxDzANBgNVBAgMBk9yZWdvbjEOMAwGA1UEBwwFU2FsZW0x\r\n\
EzARBgNVBAoMCkNsaWVudCBFQ0MxDTALBgNVBAsMBEZhc3QxGDAWBgNVBAMMD3d3\r\n\
dy53b2xmc3NsLmNvbTEfMB0GCSqGSIb3DQEJARYQaW5mb0B3b2xmc3NsLmNvbYIJ\r\n\
AOdypp4THRdcMAwGA1UdEwQFMAMBAf8wCgYIKoZIzj0EAwIDSAAwRQIgQ5q2foeO\r\n\
jNcW8Q3SUBGkrLasB+/pYOGQol/JduZUGoECIQDWi3y6UxIFBvqPxcdYw5qfoYSM\r\n\
tIiDTWq0t4V6szzz3w==\r\n\
-----END CERTIFICATE-----\r\n";

int cert_parse(void)
{
    char buf[80];

    /* ------ PARSE ORIGINAL SELF-SIGNED CERTIFICATE ------ */
    ssl_x509_get_text_by_nid(NID_COMMON_NAME, PEM_CERT, strlen(PEM_CERT), buf, sizeof(buf));
    printf("CN = %s\r\n", buf);

    ssl_x509_get_text_by_nid(NID_COUNTRY_NAME, PEM_CERT, strlen(PEM_CERT),
                             buf, sizeof(buf));
    printf("COUNTRY = %s\r\n", buf);

    ssl_x509_get_text_by_nid(NID_LOCALITY_NAME, PEM_CERT, strlen(PEM_CERT),
                             buf, sizeof(buf));
    printf("LOCALITY = %s\r\n", buf);

    ssl_x509_get_text_by_nid(NID_STATE_NAME, PEM_CERT, strlen(PEM_CERT),
                             buf, sizeof(buf));
    printf("STATE = %s\r\n", buf);

    ssl_x509_get_text_by_nid(NID_ORG_NAME, PEM_CERT, strlen(PEM_CERT),
                             buf, sizeof(buf));
    printf("ORG = %s\r\n", buf);

    ssl_x509_get_text_by_nid(NID_ORGUNIT_NAME, PEM_CERT, strlen(PEM_CERT),
                             buf, sizeof(buf));
    printf("ORG UNIT = %s\r\n", buf);

    return 0;
}

int application_start( void )
{
  cert_parse();

  return 0;
}


