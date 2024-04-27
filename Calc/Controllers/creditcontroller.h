#ifndef CREDITCONTROLLER_H
#define CREDITCONTROLLER_H

#include <QObject>

#include "Models/creditmodel.h"
#include "Views/Credit/creditview.h"

namespace S21 {

class CreditController : public QObject {
  Q_OBJECT

 public:
  CreditController(CreditModel *model, CreditView *view,
                   QObject *parent = nullptr);

 private:
  CreditView *view;
  CreditModel *model;

 private slots:
  void calculateWasClicked(bool inAnnuity);
  void setAllConnections();
};
}  // namespace S21

#endif  // CREDITCONTROLLER_H
