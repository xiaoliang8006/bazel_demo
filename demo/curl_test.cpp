// #include "hello_world.h"
#include "curl_test.h"
#include <iostream>
#include <type_traits>

// 提供虚函数的实现
inline void printHello() {
  bool is_int_arithmetic = std::is_arithmetic_v<int>;  // C++17 写法
  std::cout << "is_int_arithmetic:" << is_int_arithmetic << std::endl;
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}
  
int GetJsonResponse(const std::string& url, std::string& ret_json) {
    auto start_time = std::chrono::high_resolution_clock::now(); // 记录开始时间
    int status = 0;
    std::string response;
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ret_json);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            status = -1;
        }
        curl_easy_cleanup(curl);
    } else {
        status = -2;
    }
    auto end_time = std::chrono::high_resolution_clock::now(); // 记录结束时间
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count(); // 计算耗时
    std::cout << "GetJsonResponse status:" << status << ", took " << duration << " ms" << std::endl; // 输出耗时
    return status;
}

  bool break_write_tdbank(std::string& url) {
    std::string ret_json;
    GetJsonResponse(url, ret_json);
    Json::CharReaderBuilder builder;
    std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    Json::Value root;
    std::string err_msg;
    if (!reader->parse(ret_json.c_str(),
                        ret_json.c_str() + ret_json.size(), &root, &err_msg) ||
        !root.isObject()) {
      std::cerr << "Failed to parse embedding_sender config params: " << ret_json
              << ", err: " << std::endl;
      return false;
    }
    if (root.size() > 0) {
      // std::cout << "[send_embedding_op] message:" << root["message"].asString() << std::endl;
      std::cout << "[send_embedding_op] message:" << root["message"].asBool() << std::endl;
      // return true;
    }
    return false;
  }

int main() {
    bool is_int_arithmetic = std::is_arithmetic_v<int>;  // C++17 写法
    std::cout << "is_int_arithmetic:" << is_int_arithmetic << std::endl;
    std::string curl_url = "http://localhost:10000/status/sys/get_pretrain_tdbank_flag";
    break_write_tdbank(curl_url);
    return 0;
}