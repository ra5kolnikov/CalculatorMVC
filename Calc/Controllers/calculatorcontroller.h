#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H

#include <QObject>

#include "Models/calculatormodel.h"
#include "Models/graphmodel.h"
#include "Views/CalculatorView/calculatorview.h"

namespace S21 {

class CalculatorController : public QObject {
  Q_OBJECT

 public:
  CalculatorController(CalculatorModel *model, CalculatorView *view,
                       QObject *parent = nullptr);
  void connectSignalsAndSlots();

 private slots:
  void onNumberButtonClicked(const QString &value);
  void onDXValueChanged(const QString &digitX);
  void onBackspaceClicked();
  void onClearClicked();
  void onEnterClicked();
  void onGraphViewClicked();
  void onCreditViewClicked();

 private:
  GraphModel *graphModel;
  CalculatorModel *calculatorModel;
  CalculatorView *view;
};
}  // namespace S21

#endif  // CALCULATORCONTROLLER_H
