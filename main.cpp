#include "include/core.hpp"
#include "include/math_ops.hpp"
#include "include/data_processor.hpp"
#include "include/metrics.hpp"
#include "include/logger.hpp"

int main() {
    Logger::info("Starting Laboratory Work #1...");

    // Параметры разделяющей прямой y = kx + b
    float k = 1.2f;
    float b = 5.0f;

    // Генерируем 100 точек для обучения
    auto dataset = DataProcessor<float>::generateDataset(100, k, b);
    Logger::info("Dataset generated successfully.");

    // Считаем суммарную ошибку (Loss) по формуле со стр. 1
    float loss = Metrics<float>::totalAbsoluteError(dataset, k, b);
    Logger::logValue("Total Absolute Loss", loss);

    // Матричное преобразование первой точки (стр. 2)
    Matrix<float> transform(2, 2);
    transform(0,0) = 1.1f; transform(0,1) = 0.2f;
    transform(1,0) = 0.1f; transform(1,1) = 0.9f;

    auto [nx, ny] = MathOps<float>::transformVector(transform, dataset[0].x, dataset[0].y);
    Logger::logValue("Transformed X", nx);
    Logger::logValue("Transformed Y", ny);

    // Сохраняем результат для визуализации в Python
    if (DataProcessor<float>::saveToCSV(dataset, "points.csv")) {
        Logger::info("Data saved to points.csv");
    }

    return 0;
}