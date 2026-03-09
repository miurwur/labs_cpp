import pandas as pd
import matplotlib.pyplot as plt

# Загружаем данные, которые только что создал твой C++ код
data = pd.read_csv('points.csv')

plt.figure(figsize=(10, 6))
# Точки класса 0 (под прямой) — синие, класса 1 (над прямой) — красные
plt.scatter(data[data['label'] == 0]['x'], data[data['label'] == 0]['y'], color='blue', label='Class 0')
plt.scatter(data[data['label'] == 1]['x'], data[data['label'] == 1]['y'], color='red', label='Class 1')

plt.title('Laboratory Work #1: Point Classification')
plt.xlabel('X coordinate')
plt.ylabel('Y coordinate')
plt.legend()
plt.grid(True)
plt.show()