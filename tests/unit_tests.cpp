#include "include/math_ops.hpp"
#include "include/metrics.hpp"
#include "include/logger.hpp"
#include <cassert>

void test_math() {
    // Тестируем y = kx + b
    float result = MathOps<float>::calculateLinear(2.0f, 3.0f, 1.0f); // 3*2 + 1 = 7
    Logger::testStatus("Linear calculation (y=kx+b)", result == 7.0f);

    // Тестируем матрицу 2x2 (единичную)
    MatrixF identity(2, 2);
    identity(0,0) = 1; identity(0,1) = 0;
    identity(1,0) = 0; identity(1,1) = 1;
    
    auto [nx, ny] = MathOps<float>::transformVector(identity, 5.0f, 10.0f);
    Logger::testStatus("Matrix Transformation", (nx == 5.0f && ny == 10.0f));
}

int main() {
    Logger::info("Starting Unit Tests for Lab 1...");
    try {
        test_math();
        Logger::info("All tests completed.");
    } catch (...) {
        Logger::error("Something went wrong during testing.");
    }
    return 0;
}