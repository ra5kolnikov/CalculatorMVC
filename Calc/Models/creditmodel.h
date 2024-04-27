#ifndef CREDITMODEL_H
#define CREDITMODEL_H

#include <QString>

namespace S21 {

class CreditModel {
 public:
  QString calculateAnnuity(double amount, int term, double rate);
  QString calculateDifferential(double amount, int term, double rate);
  double creditDiff(int *sum, double sd, double rate, double *res_sum,
                    double *res_pereplata, int days);
};
}  // namespace S21

#endif  // CREDITMODEL_H
