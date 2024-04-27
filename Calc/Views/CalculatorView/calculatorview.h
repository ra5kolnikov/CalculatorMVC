// CalculatorView.h
#ifndef CALCULATORVIEW_H
#define CALCULATORVIEW_H

#include <qabstractbutton.h>

#include <QMainWindow>
#include <QString>

namespace Ui {
class CalculatorView;
}

namespace S21 {

class CalculatorView : public QMainWindow {
  Q_OBJECT

 public:
  explicit CalculatorView(QWidget *parent = nullptr);
  ~CalculatorView();

 public:
  bool isLineEditFocused() const;
  bool isDXFocused() const;

 signals:
  void numberButtonClicked(const QString &value);
  void buttonClicked(QAbstractButton *);
  void backspaceClicked();
  void clearClicked();
  void enterClicked();
  void dXValueChanged(QString digitX);
  void dXclear();
  void lineEditClear();
  void graphButtonClicked();
  void creditButtonClicked();

 public slots:
  void onButtonGroupClicked(QAbstractButton *button);
  void displayResult(const QString &result);
  void displayDigitX(const QString &digitX);
  void onGraphClicked();
  void onCreditClicked();

 private:
  Ui::CalculatorView *ui;
  void setupConnections();
};
}  // namespace S21

#endif  // CALCULATORVIEW_H
