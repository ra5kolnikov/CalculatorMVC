#ifndef CREDIT_H
#define CREDIT_H

#include <stdlib.h>

#include <QAbstractButton>
#include <QDialog>
#include <QtWidgets>

namespace Ui {
class CreditView;
}

namespace S21 {

class CreditView : public QDialog {
  Q_OBJECT

 public:
  explicit CreditView(QWidget *parent = nullptr);
  ~CreditView();

  double getAmount();
  int getTerm();
  double getRate();

  void setDiffResult(const QString &result);

 signals:
  void isAnnuity();  // Сигнал для аннуитетного расчета
  void isDiff();  // Сигнал для дифференцированного расчета

 private slots:
  void on_calculCredit_clicked();

 private:
  Ui::CreditView *ui;
};
}  // namespace S21

#endif  // CREDIT_H
