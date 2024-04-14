#include <stdio.h>

void matrixMulBasic(float *A, float *B, float *C, int M, int N, int K) {
    #pragma acc parallel loop collapse(2) present(A[0:M*K], B[0:K*N], C[0:M*N])
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < K; ++k) {
                sum += A[i * K + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}