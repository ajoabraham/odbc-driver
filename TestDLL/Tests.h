#pragma once

#define prod_KServerAddr ""
#define prod_KPort 443

//#define KServerAddr "http://localhost"
#define KServerAddr "http://54.152.150.114/"
//#define KServerAddr "http://localhost"

#define KPort 9000
//#define KPort 8080
#define KUserName "aaa"
#define KPassword "bbb"
#define KDefaultProject "yulin_s_project"

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
void veroProbeQueryTest();
void veroMakeUriTest();
void veroJsonTest();

