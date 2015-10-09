#pragma once

#include <map>
#include "vld.h"
#include "MsgTypes.h"


//REST
bool restAuthenticate(char* serverAddr, long port, char* username, char* passwd);
void restListProjects(char* serverAddr, long port, char* username, char* passwd, std::map<string, string>& projectMap);
std::unique_ptr<SQLResponse> restQuery(wchar_t* rawSql, char* serverAddr, long port, char* username, char* passwd, char* project);
std::unique_ptr<MetadataResponse> restGetMeta(char* serverAddr, long port, char* username, char* passwd, char* project);

//TEST
std::wstringstream makeMetaUri(char* project);
std::wstringstream makeQueryUri(char* project);