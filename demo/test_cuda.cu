#include <iostream>
#include <cuda_runtime.h>

// 内核函数：向量加法
__global__ void vectorAdd(float *A, float *B, float *C, int numElements) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < numElements) {
        C[i] = A[i] + B[i];
    }
}

// 内核函数：初始化向量数据
__global__ void initializeVectors(float *A, float *B, int numElements) {
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < numElements) {
        A[i] = static_cast<float>(i);
        B[i] = static_cast<float>(i * 2);
    }
}

int main(void) {
    int numElements = 50000;
    int threadsPerBlock = 256;
    int numBlocks = (numElements + threadsPerBlock - 1) / threadsPerBlock;
    size_t size = numElements * sizeof(float);

    // 分配主机内存
    float *h_A = (float *)malloc(size);
    float *h_B = (float *)malloc(size);
    float *h_C = (float *)malloc(size);

    // 初始化向量数据
    initializeVectors<<<numBlocks, threadsPerBlock>>>(h_A, h_B, numElements);
    cudaDeviceSynchronize();

    // 分配设备内存
    float *d_A, *d_B, *d_C;
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, size);
    cudaMalloc((void **)&d_C, size);

    // 将数据从主机复制到设备
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // 执行向量加法

    vectorAdd<<<numBlocks, threadsPerBlock>>>(d_A, d_B, d_C, numElements);
    cudaDeviceSynchronize();

    // 将结果从设备复制回主机
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // 打印结果
    for (int i = 0; i < numElements; ++i) {
        std::cout << h_A[i] << " + " << h_B[i] << " = " << h_C[i] << std::endl;
    }

    // 释放分配的内存
    free(h_A);
    free(h_B);
    free(h_C);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}