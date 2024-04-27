#include <QApplication>

#include "Controllers/calculatorcontroller.h"
#include "Models/calculatormodel.h"
#include "Views/CalculatorView/calculatorview.h"

using namespace S21;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  CalculatorModel model;
  CalculatorView view;
  CalculatorController controller(&model, &view);

  view.show();
  return a.exec();
}
