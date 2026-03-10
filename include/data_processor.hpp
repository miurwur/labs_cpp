#pragma once // Защита от повторного включения файла

#include "core.hpp"
#include <vector>
#include <fstream>
#include <random>
#include <string>


template <FloatingPoint T> // Проверяем, что это тип с плавающей точкой(core.hpp concept)
class DataProcessor {
public: 
    static std::vector<Point<T>> generateDataset(size_t count, T k, T b)
    // Генерируем набор данных типа T(с плавающей точкой) 
    {
        std::vector<Point<T>> dataset;
        std::random_device rd; // Источник энтропии для генерации случайных чисел
        std::mt19937 gen(rd()); // Инициализация MT19937 этим числом
        std::uniform_real_distribution<T> dist(0.0, 100.0); // Равномерное распределение числе в диапазоне

        for (size_t i = 0; i < count; ++i) {
            T x = dist(gen);
            T y = dist(gen);
            // Случайные точки

            // Определяем класс точки относительно прямой y = kx + b
            int label = (y > (k * x + b)) ? 1 : 0;
            
            dataset.emplace_back(x, y, label);
            // Добавляем точку в бд
        }
        return dataset;
    }

    static bool saveToCSV(const std::vector<Point<T>>& data, const std::string& filename) 
    // Сохраняем данные в файл CSV
    { 
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        file << "x,y,label\n";
        for (const auto& p : data) {
            file << p.x << "," << p.y << "," << p.label << "\n";
        }
        file.close();
        return true;
    }
};