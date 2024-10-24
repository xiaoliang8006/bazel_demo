#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <chrono>
#include <memory>
#include <iostream>

// 函数声明
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response);
int GetJsonResponse(const std::string& url, std::string& ret_json);
bool break_write_tdbank(std::string& url);
// 提供虚函数的实现
inline void printHello();

#endif // MAIN_H