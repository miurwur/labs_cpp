#pragma once // Защита от повторного включения файла

#include <vector>
#include <concepts>
#include <type_traits>

/**
 * 1. КОНЦЕПТЫ (C++20)
 * Используем их вместо макросов для проверки типов данных.
 * Это гарантирует, что в нашу нейросеть не засунут строки или целые числа там, 
 * где нужны вычисления. [cite: 14]
 */
template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

/**
 * 2. БАЗОВЫЕ СТРУКТУРЫ
 * Структура точки для бинарного классификатора. [cite: 1, 7]
 */
template <FloatingPoint T>
struct Point {
    T x;           // Координата X
    T y;           // Координата Y
    int label;     // Класс (0 или 1) [cite: 21]

    // Удобный конструктор
    Point(T x_val, T y_val, int l = 0) : x(x_val), y(y_val), label(l) {}
};

/**
 * 3. МАТРИЦА
 * Обертка над std::vector для хранения весов или данных. [cite: 20]
 * Мы делаем её максимально простой, так как "читаемость >> сложные алгоритмы".
 */
template <FloatingPoint T>
struct Matrix {
    std::vector<T> data;
    size_t rows;
    size_t cols;

    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r * c, 0.0f) {}

    // Оператор доступа к элементам (строка, столбец)
    T& operator()(size_t r, size_t c) {
        return data[r * cols + c];
    }

    const T& operator()(size_t r, size_t c) const {
        return data[r * cols + c];
    }
};

/**
 * 4. ОБЩИЕ ТИПЫ
 * Определяем псевдонимы для удобства, чтобы не писать везде длинные шаблоны.
 */
using PointF = Point<float>;
using MatrixF = Matrix<float>;