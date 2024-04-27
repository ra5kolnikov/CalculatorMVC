// CalculatorModel.h
#ifndef CALCULATORMODEL_H
#define CALCULATORMODEL_H

#include <QObject>

extern "C" {
#include "ThirdParty/parser/parser.h"
}

namespace S21 {

class CalculatorModel : public QObject {
  Q_OBJECT

 public:
  explicit CalculatorModel(QObject *parent = nullptr);
  void appendToExpression(const QString &value);
  void appendToDeigitX(const QString &x);
  void backspaceInExpression();
  void clearExpression();
  void backspaceInDigitX();
  void clearDigitX();
  bool validateExpression();
  QString calculate();
  QString getExpression() const;
  QString getDigitX() const;

 private:
  QString expression;
  QString DigitX;
  bool calculated = false;
};
}  // namespace S21

#endif  // CALCULATORMODEL_H
