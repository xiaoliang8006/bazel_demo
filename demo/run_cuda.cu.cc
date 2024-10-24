#include <iostream>
#include "my_cuda_lib.h"

int main() {
    std::cout << "Calling CUDA function from main..." << std::endl;
    my_cuda_function();
    return 0;
}