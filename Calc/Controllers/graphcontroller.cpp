#include "graphcontroller.h"

using namespace S21;

GraphController::GraphController(GraphModel *model, GraphView *view,
                                 QObject *parent)
    : QObject(parent), model(model), view(view) {
  setupConnections();
}

void GraphController::setupConnections() {
  connect(view, &GraphView::onGrapghWasClicked, this,
          &GraphController::onDrawGraphColicked);
  connect(view, &GraphView::valMaxXChanged, this,
          &GraphController::xMaxWasChanged);
  connect(view, &GraphView::valMinXChanged, this,
          &GraphController::xMinWasChanged);
}

void GraphController::onDrawGraphColicked() {
  model->calculatePoints();
  view->updateGraph(model->getXValues(), model->getYValues());
}
void GraphController::xMinWasChanged(int value) { model->setXMinValues(value); }
void GraphController::xMaxWasChanged(int value) { model->setXMaxValues(value); }
