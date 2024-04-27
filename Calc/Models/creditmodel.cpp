#include "creditmodel.h"

#include <QStringList>
#include <cmath>
#include <ctime>

using namespace S21;

QString CreditModel::calculateAnnuity(double amount, int term, double rate) {
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int date = ltm->tm_mon;
  int year = 1900 + ltm->tm_year;
  std::string monthsList[12] = {
      "January", "February", "March",     "April",   "May",      "June",
      "July",    "August",   "September", "October", "November", "December"};
  double monthlyRate = rate / 1200;
  double annuityPayment =
      amount * (monthlyRate / (1 - pow(1 + monthlyRate, -term)));
  double totalPayment = annuityPayment * term;
  double overPayment = totalPayment - amount;

  QString result =
      QString("Monthly payment: %1\nTotal payment: %2\nOverpayment: %3\n\n")
          .arg(annuityPayment, 0, 'f', 2)
          .arg(totalPayment, 0, 'f', 2)
          .arg(overPayment, 0, 'f', 2);
  for (int i = 1; i <= term; i++) {
    result.append(QString::fromStdString(monthsList[date % 12]) + " " +
                  QString::number(year, 'f', 0) + ": " +
                  QString::number(annuityPayment, 'f', 2) + "\n");
    date++;
    if (date > 11) {
      year += 1;
      date %= 12;
    }
  }
  return result;
}

QString CreditModel::calculateDifferential(double amount, int term,
                                           double rate) {
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int date = ltm->tm_mon;  // Месяц начинается с 0, поэтому для вывода нам нужно
                           // будет прибавлять 1
  int year = 1900 + ltm->tm_year;
  double totalPayment = 0;
  double overPayment = 0;
  QString result = "";

  int mDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  std::string monthsList[12] = {
      "January", "February", "March",     "April",   "May",      "June",
      "July",    "August",   "September", "October", "November", "December"};
  int am = static_cast<int>(amount);
  double sd = amount / term;

  for (int i = 1; i <= term; i++) {
    // Обработка високосного года для февраля
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
      mDays[1] = 29;
    } else {
      mDays[1] = 28;
    }

    double per =
        creditDiff(&am, sd, rate, &totalPayment, &overPayment, mDays[date]);
    result +=
        QString::fromStdString(
            monthsList[date]) +  // Нет необходимости использовать % 12 тут
        " " +
        QString::number(year) + ":  " + QString::number(per, 'f', 2) + "\n";
    date++;
    if (date > 11) {
      year += 1;
      date = 0;  // Сбросить индекс месяца на январь
    }
  }

  // Добавлен вывод итоговой суммы и переплаты
  result += QString("\n\nTotal payment: %1\nOverpayment: %2")
                .arg(totalPayment, 0, 'f', 2)
                .arg(overPayment, 0, 'f', 2);

  return result;
}

double CreditModel::creditDiff(int *sum, double sd, double rate,
                               double *res_sum, double *res_pereplata,
                               int days) {
  double sp = (*sum * rate * days) / 365 / 100;
  double per = sd + sp;
  *sum -= sd;  // Исправлено: убрано лишнее присваивание
  *res_sum += per;
  *res_pereplata += sp;
  return per;
}
