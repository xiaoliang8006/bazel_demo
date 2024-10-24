// #include "curl_test.h"
#include "hello_world.h"
#include<iostream>
#include <memory>

int main() {
    auto add = [](auto a, auto b) {
        return a + b;
    };

    auto ptr = std::make_unique<int>(42);

    std::cout << add(1, 2) << std::endl;          // 输出 3
    std::cout << add(1.5, 2.5) << std::endl;      // 输出 4

    return 0;
}
