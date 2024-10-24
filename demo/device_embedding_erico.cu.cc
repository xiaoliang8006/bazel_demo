#include "device_embedding_erico.h"
#include <cuda_runtime.h>
#include <iostream>
#include <type_traits>

__global__ void helloFromGPU() {
    printf("Hello from GPU!\n");
}

void launchHelloKernel() {
    bool is_int_arithmetic = std::is_arithmetic_v<int>;  // C++17 写法
    helloFromGPU<<<1, 1>>>();
    cudaDeviceSynchronize();
}