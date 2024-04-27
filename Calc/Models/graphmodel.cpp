#include "graphmodel.h"

#include <cstring>  // Для std::memcpy

using namespace S21;

GraphModel::GraphModel(QObject *parent) : QObject(parent) {}

void GraphModel::setExpression(QString expression) {
  this->expression = expression;
}

void GraphModel::calculatePoints() {
  double a = getXMinValues();
  double b = getXMaxValues();
  double h = 0.01;
  if (a == 0 && b == 0) {
    a = -200;
    b = 200;
  }
  int N = static_cast<int>((b - a) / h) + 1;
  QVector<double> x(N), y(N);

  // Преобразуем QString в std::string, а затем в вектор char для безопасного
  // доступа
  std::string expressionStr = expression.toStdString();
  std::vector<char> c(expressionStr.begin(), expressionStr.end());
  c.push_back(
      '\0');  // Добавляем нулевой символ в конец, чтобы обозначить конец строки

  for (int i = 0; i < N; ++i) {
    double X = a + i * h;
    x[i] = X;
    y[i] = calculator(c.data(),
                      X);  // Используем data() для доступа к данным вектора
  }

  setXValues(x);

  double minY = y.front(), maxY = y.front();
  for (int i = 1; i < N; ++i) {
    if (y[i] < minY) minY = y[i];
    if (y[i] > maxY) maxY = y[i];
  }
  setYValues(y);
}
