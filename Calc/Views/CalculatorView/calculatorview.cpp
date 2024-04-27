#include "calculatorview.h"

#include "ui_calculatorview.h"

using namespace S21;

CalculatorView::CalculatorView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalculatorView) {
  ui->setupUi(this);
  setupConnections();
}

CalculatorView::~CalculatorView() { delete ui; }

void CalculatorView::setupConnections() {
  connect(ui->buttonGroup, SIGNAL(buttonClicked(QAbstractButton *)), this,
          SLOT(onButtonGroupClicked(QAbstractButton *)));
  connect(ui->backspace, &QPushButton::clicked, this,
          &CalculatorView::backspaceClicked);
  connect(ui->Clear, &QPushButton::clicked, this,
          &CalculatorView::clearClicked);
  connect(ui->enter, &QPushButton::clicked, this,
          &CalculatorView::enterClicked);
  connect(ui->graph, &QPushButton::clicked, this,
          &CalculatorView::onGraphClicked);
  connect(ui->credit, &QPushButton::clicked, this,
          &CalculatorView::onCreditClicked);
}

void CalculatorView::displayResult(const QString &result) {
  ui->lineEdit->setText(result);
}

void CalculatorView::displayDigitX(const QString &result) {
  ui->DX->setText(result);
}

void CalculatorView::onButtonGroupClicked(QAbstractButton *button) {
  if (button) {
    QString buttonText = button->text();
    if (ui->lineEdit->hasFocus())
      emit numberButtonClicked(buttonText);
    else if (ui->DX->hasFocus())
      emit dXValueChanged(buttonText);
  }
}

bool CalculatorView::isLineEditFocused() const {
  return ui->lineEdit->hasFocus();
}

bool CalculatorView::isDXFocused() const { return ui->DX->hasFocus(); }

void CalculatorView::onGraphClicked() { emit graphButtonClicked(); }

void CalculatorView::onCreditClicked() { emit creditButtonClicked(); }
