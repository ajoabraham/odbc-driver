#pragma once

#define prod_KServerAddr ""
#define prod_KPort 443

//#define KServerAddr "http://localhost"
#define KServerAddr "http://7d606f1e.ngrok.com"

#define KPort 80
#define KUserName "ADMIN"
#define KPassword "KADMIN"
#define KDefaultProject "default"

#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string>
#include <memory>
#include <windows.h>
#include <sqlext.h>                                     // required for ODBC calls
#include <iostream>
#include <REST.h>
#include <StringUtils.h>

void report();
void report ( const char* msg );

void simpleQueryTest();
void queryFlowTest();
void restAPITest();
void crossValidate();

void veroRestApiTest();
void veroMakeUriTest();

