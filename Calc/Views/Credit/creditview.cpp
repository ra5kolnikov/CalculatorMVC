#include "creditview.h"

#include <cstring>
#include <ctime>

#include "ui_creditview.h"

using namespace S21;

CreditView::CreditView(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditView) {
  ui->setupUi(this);
  this->setFixedSize(this->geometry().width(), this->geometry().height());
  ui->TextAboutMon->setReadOnly(true);
}

CreditView::~CreditView() { delete ui; }

void CreditView::on_calculCredit_clicked() {
  if (ui->Annuity->isChecked()) {
    emit isAnnuity();
  } else if (ui->Differentiated->isChecked()) {
    emit isDiff();
  }
}

double CreditView::getAmount() { return ui->Amount->text().toDouble(); }

int CreditView::getTerm() { return ui->CreditTerm->text().toInt(); }

double CreditView::getRate() { return ui->Rate->text().toDouble(); }

void CreditView::setDiffResult(const QString &result) {
  ui->TextAboutMon->setText(result);
}
