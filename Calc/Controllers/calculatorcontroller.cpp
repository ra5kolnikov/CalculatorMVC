#include "calculatorcontroller.h"

#include "Controllers/creditcontroller.h"
#include "Controllers/graphcontroller.h"
#include "Models/calculatormodel.h"
#include "Models/creditmodel.h"
#include "Views/Credit/creditview.h"
#include "Views/Graph/graphview.h"

using namespace S21;

CalculatorController::CalculatorController(CalculatorModel *calculatorModel,
                                           CalculatorView *view,
                                           QObject *parent)
    : QObject(parent), calculatorModel(calculatorModel), view(view) {
  connectSignalsAndSlots();
}

void CalculatorController::connectSignalsAndSlots() {
  connect(view, &CalculatorView::dXValueChanged, this,
          &CalculatorController::onDXValueChanged);
  connect(view, &CalculatorView::numberButtonClicked, this,
          &CalculatorController::onNumberButtonClicked);
  connect(view, &CalculatorView::backspaceClicked, this,
          &CalculatorController::onBackspaceClicked);
  connect(view, &CalculatorView::clearClicked, this,
          &CalculatorController::onClearClicked);
  connect(view, &CalculatorView::enterClicked, this,
          &CalculatorController::onEnterClicked);
  connect(view, &CalculatorView::graphButtonClicked, this,
          &CalculatorController::onGraphViewClicked);
  connect(view, &CalculatorView::creditButtonClicked, this,
          &CalculatorController::onCreditViewClicked);
}

void CalculatorController::onNumberButtonClicked(const QString &value) {
  calculatorModel->appendToExpression(value);
  view->displayResult(calculatorModel->getExpression());
}

void CalculatorController::onBackspaceClicked() {
  if (view->isLineEditFocused()) {
    calculatorModel->backspaceInExpression();
    view->displayResult(calculatorModel->getExpression());
  } else if (view->isDXFocused()) {
    calculatorModel->backspaceInDigitX();
    view->displayDigitX(calculatorModel->getDigitX());
  }
}

void CalculatorController::onClearClicked() {
  if (view->isLineEditFocused()) {
    calculatorModel->clearExpression();
    view->displayResult(calculatorModel->getExpression());
  } else if (view->isDXFocused()) {
    calculatorModel->clearDigitX();
    view->displayDigitX(calculatorModel->getDigitX());
  }
}

void CalculatorController::onEnterClicked() {
  QString result = calculatorModel->calculate();
  view->displayResult(result);
}

void CalculatorController::onDXValueChanged(const QString &digitX) {
  calculatorModel->appendToDeigitX(digitX);
  view->displayDigitX(calculatorModel->getDigitX());
}

void CalculatorController::onGraphViewClicked() {
  GraphModel *model = new GraphModel();
  model->setExpression(calculatorModel->getExpression());
  GraphView *graphView = new GraphView(view);
  GraphController *controller = new GraphController(model, graphView);

  connect(graphView, &QDialog::finished, this, [controller, model]() {
    delete controller;
    delete model;
  });

  graphView->setModal(true);
  graphView->exec();
}

void CalculatorController::onCreditViewClicked() {
  CreditModel *model = new CreditModel();
  CreditView *credit = new CreditView();
  CreditController *controller = new CreditController(model, credit);

  connect(credit, &QDialog::finished, this, [controller, model]() {
    delete controller;
    delete model;
  });

  credit->setModal(true);
  credit->exec();
}
