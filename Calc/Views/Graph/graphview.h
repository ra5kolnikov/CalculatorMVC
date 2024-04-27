#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QDialog>
#include <QVector>

namespace Ui {
class GraphView;
}

namespace S21 {

class GraphView : public QDialog {
  Q_OBJECT

 public:
  explicit GraphView(QWidget *parent = nullptr);
  ~GraphView();

  void updateGraph(const QVector<double> &xValues,
                   const QVector<double> &yValues);

 signals:
  void graphUpdated();
  void valMinXChanged(double xMin);
  void valMaxXChanged(double xMax);
  void onGrapghWasClicked();

 private slots:
  void on_xMin_valueChanged(int arg1);
  void on_xMax_valueChanged(int arg1);
  void onGraphClicked();

 private:
  Ui::GraphView *ui;
};
}  // namespace S21

#endif  // GRAPHVIEW_H
