// GraphController.h

#ifndef GRAPHCONTROLLER_H
#define GRAPHCONTROLLER_H

#include <QObject>

#include "Models/graphmodel.h"
#include "Views/Graph/graphview.h"

namespace S21 {

class GraphController : public QObject {
  Q_OBJECT

 public:
  GraphController(GraphModel *model, GraphView *view,
                  QObject *parent = nullptr);

 private:
  GraphModel *model;
  GraphView *view;

  void setupConnections();

 private slots:
  void onDrawGraphColicked();
  void xMinWasChanged(int value);
  void xMaxWasChanged(int value);
};
}  // namespace S21

#endif  // GRAPHCONTROLLER_H
