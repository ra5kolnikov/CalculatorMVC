#include "calculatormodel.h"

#include <QRegularExpression>
#include <QtMath>

using namespace S21;

CalculatorModel::CalculatorModel(QObject *parent) : QObject(parent) {}

void CalculatorModel::appendToDeigitX(const QString &x) {
  if (x.toDouble()) DigitX += x;
}

void CalculatorModel::backspaceInExpression() {
  if (!expression.isEmpty()) {
    expression.chop(1);
  }
}

void CalculatorModel::clearExpression() { expression.clear(); }

void CalculatorModel::backspaceInDigitX() {
  if (!DigitX.isEmpty()) {
    DigitX.chop(1);
  }
}

QString CalculatorModel::getExpression() const { return expression; }

QString CalculatorModel::getDigitX() const { return DigitX; }

void CalculatorModel::clearDigitX() { DigitX.clear(); }

void CalculatorModel::appendToExpression(const QString &value) {
  if (calculated) {
    expression.clear();
    calculated = false;
  }
  expression += value;
  if (value[0] == 'c' || value[0] == 's' || value[0] == 't' ||
      value[0] == 'a' || value[0] == 'l') {
    expression += '(';
  }
}

QString CalculatorModel::calculate() {
  if (validateExpression()) {
    float res;
    char *c = new char[expression.length() + 1];
    for (int i = 0; i < expression.length() + 1; i++) {
      c[i] = expression.toStdString().c_str()[i];
    }
    res = calculator(c, DigitX.toDouble());
    calculated = true;
    return QString::number(res, 'f', 7);
  } else {
    expression.clear();
    return "Enter a valid expression";
  }
}

bool CalculatorModel::validateExpression() {
  if (expression.isEmpty() || expression == "Enter a valid expression") {
    return false;
  }

  // Проверка на допустимые символы
  static QRegularExpression validCharsRegex(
      "^[0-9sinco\\+\\-\\*\\/\\^\\.\\(\\)xtanlqmod\\s]+$",
      QRegularExpression::CaseInsensitiveOption);
  if (!validCharsRegex.match(expression).hasMatch()) {
    return false;
  }

  // Проверка на множественные нули в начале числа и множественные точки в числе
  static QRegularExpression invalidZeroDotRegex(
      "(^|[^\\d])0+\\d|\\.\\d*\\.|(^|[^\\d.])0+(\\.0+)*$");
  if (invalidZeroDotRegex.match(expression).hasMatch()) {
    return false;
  }

  // Проверка на баланс скобок
  int openBrackets = expression.count('(');
  int closeBrackets = expression.count(')');
  if (openBrackets != closeBrackets) {
    return false;
  }

  // Проверка на недопустимые паттерны, такие как два оператора подряд, пустые
  // скобки, или отсутствие числа между скобками
  static QRegularExpression badPatternRegex(
      "\\)\\(|[\\+\\-\\*\\/]{2,}|\\(\\s*\\)|\\(\\s*[\\+\\-\\*\\/]|\\d\\s+\\d");
  if (badPatternRegex.match(expression).hasMatch()) {
    return false;
  }

  // Проверка на корректное использование оператора возведения в степень
  static QRegularExpression powerOperatorRegex("(^|[^\\d)])\\^|\\^($|[^\\d(])");
  if (powerOperatorRegex.match(expression).hasMatch()) {
    return false;  // Возвращаем false, если оператор ^ находится в начале/конце
                   // или не между числами/выражениями
  }

  // Проверка на корректное использование функций и переменных
  static QRegularExpression functionVariableRegex(
      "\\b(sin|cos|tan|asin|acos|atan|sqrt|ln|log|mod)\\b\\s*\\(|\\bx\\b");
  if (!functionVariableRegex.globalMatch(expression).isValid()) {
    return false;  // Возвращаем false, если найдены некорректные использования
                   // функций или переменной x
  }

  return true;  // Выражение прошло все проверки
}
