#pragma once

#include "core.hpp"
#include <vector>
#include <cmath>

/**
 * Модуль математических операций.
 * Реализует аппарат для вычислений, описанный в пояснениях к лабам.
 */
template <FloatingPoint T>
class MathOps {
public:
    /**
     * 1. Линейное преобразование (уравнение прямой)
     * Вычисляет значение y для заданного x: y = k*x + b
     * Используется для определения разделяющей линии[cite: 2, 4].
     */
    static T calculateLinear(T x, T k, T b) {
        return k * x + b;
    }

    /**
     * 2. Матричное умножение 2x2 на вектор (x, y)
     * Реализует формулу со страницы 2: [S] * [v] = [vs].
     * Где v = (x, y)[cite: 17].
     */
    static std::pair<T, T> transformVector(const Matrix<T>& mat, T x, T y) {
        // Проверка: матрица должна быть как минимум 2x2 (4 элемента)
        if (mat.data.size() < 4) return {x, y};

        // Формула: x_new = s11*x + s12*y; y_new = s21*x + s22*y 
        T newX = mat(0, 0) * x + mat(0, 1) * y;
        T newY = mat(1, 0) * x + mat(1, 1) * y;
        
        return {newX, newY};
    }

    /**
     * 3. Определение знака (простейшая функция активации)
     * Помогает понять, с какой стороны от линии находится точка.
     * Если y > kx + b, результат положительный.
     */
    static int predict(T x, T y, T k, T b) {
        T threshold = calculateLinear(x, k, b);
        return (y > threshold) ? 1 : 0;
    }

    /**
     * 4. Расстояние от точки до прямой (перпендикуляр)
     * На фото 1 показан перпендикуляр от точки (x3, y3) к линии P2[cite: 1, 9].
     * Это полезно для оценки "уверенности" классификатора.
     */
    static T distanceToLine(T x, T y, T k, T b) {
        // Формула: |kx - y + b| / sqrt(k^2 + 1)
        return std::abs(k * x - y + b) / std::sqrt(k * k + 1);
    }
};