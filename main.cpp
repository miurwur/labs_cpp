#include "include/core.hpp"
#include "include/math_ops.hpp"
#include "include/data_processor.hpp"
#include "include/metrics.hpp"
#include "include/logger.hpp"

int main() {
    Logger::info("Laboratory Work #1: Helper Module Initialization");

    // 1. Инициализация параметров разделяющей гиперплоскости [cite: 4]
    float k = 0.8f;
    float b = 10.0f;

    // 2. Генерация данных для бинарной классификации [cite: 21]
    Logger::info("Generating dataset...");
    auto dataset = DataProcessor<float>::generateDataset(200, k, b);

    // 3. Демонстрация работы с матрицами (из страницы 2 пояснений) [cite: 20]
    MatrixF transform(2, 2);
    transform(0,0) = 1.0f; transform(0,1) = 0.1f; // Небольшой сдвиг
    transform(1,0) = 0.0f; transform(1,1) = 1.0f;

    auto [oldX, oldY] = std::make_pair(dataset[0].x, dataset[0].y);
    auto [newX, newY] = MathOps<float>::transformVector(transform, oldX, oldY);
    
    Logger::logValue("Original X", oldX);
    Logger::logValue("Transformed X", newX);

    // 4. Расчет итоговой метрики Loss [cite: 9]
    float totalLoss = Metrics<float>::totalAbsoluteError(dataset, k, b);
    Logger::logValue("Final Absolute Loss", totalLoss);

    // 5. Сохранение для визуализации
    if (DataProcessor<float>::saveToCSV(dataset, "points.csv")) {
        Logger::info("Success: 'points.csv' generated for Python visualization.");
    }

    return 0;
}