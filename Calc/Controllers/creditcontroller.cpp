#include "creditcontroller.h"

using namespace S21;

CreditController::CreditController(CreditModel *model, CreditView *view,
                                   QObject *parent)
    : QObject(parent), view(view), model(model) {
  setAllConnections();
}
void CreditController::setAllConnections() {
  connect(view, &CreditView::isAnnuity, this,
          [this]() { this->calculateWasClicked(true); });
  connect(view, &CreditView::isDiff, this,
          [this]() { this->calculateWasClicked(false); });
}

void CreditController::calculateWasClicked(bool isAnnuity) {
  int term = view->getTerm();
  double amount = view->getAmount();
  double rate = view->getRate();

  if (isAnnuity) {
    QString result = model->calculateAnnuity(amount, term, rate);
    view->setDiffResult(result);
  } else {
    QString result = model->calculateDifferential(amount, term, rate);
    view->setDiffResult(result);
  }
}
