#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QObject>

extern "C" {
#include "ThirdParty/parser/parser.h"
}

namespace S21 {

class GraphModel : public QObject {
  Q_OBJECT

 public:
  explicit GraphModel(QObject *parent = nullptr);
  void setExpression(QString expression);
  void calculatePoints();

  QVector<double> getXValues() const { return xValues; }
  QVector<double> getYValues() const { return yValues; }
  double getXMinValues() const { return xMin; }
  double getXMaxValues() const { return xMax; }
  double setXMinValues(double xMin) { return this->xMin = xMin; }
  double setXMaxValues(double xMax) { return this->xMax = xMax; }
  QVector<double> setXValues(QVector<double> xValues) {
    return this->xValues = xValues;
  }
  QVector<double> setYValues(QVector<double> yValues) {
    return this->yValues = yValues;
  }

 private:
  QString expression;
  QVector<double> xValues;
  QVector<double> yValues;
  double xMin = 0.;
  double xMax = 0.;
};
}  // namespace S21

#endif  // GRAPHMODEL_H
