#include <stdio.h>

#define TILE_WIDTH 32

void matrixMulTiled(float *A, float *B, float *C, int M, int N, int K) {
    #pragma acc parallel loop present(A[0:M*K], B[0:K*N], C[0:M*N])
    for (int by = 0; by < (M - 1) / TILE_WIDTH + 1; ++by) {
        #pragma acc loop
        for (int bx = 0; bx < (N - 1) / TILE_WIDTH + 1; ++bx) {
            float sum;
            for (int ty = 0; ty < TILE_WIDTH; ++ty) {
                for (int tx = 0; tx < TILE_WIDTH; ++tx) {
                    int row = by * TILE_WIDTH + ty;
                    int col = bx * TILE_WIDTH + tx;
                    sum = 0.0f;
                    for (int m = 0; m < K; ++m) {
                        if (row < M && col < N) {
                            sum += A[row * K + m] * B[m * N + col];
                        }
                    }
                    if (row < M && col < N) {
                        C[row * N + col] = sum;
                    }
                }
            }
        }
    }
}