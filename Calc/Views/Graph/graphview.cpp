#include "graphview.h"

#include "ui_graphview.h"

using namespace S21;

GraphView::GraphView(QWidget *parent) : QDialog(parent), ui(new Ui::GraphView) {
  ui->setupUi(this);
  connect(ui->drawGraph, &QPushButton::clicked, this,
          &GraphView::onGraphClicked);
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
}

GraphView::~GraphView() { delete ui; }

void GraphView::updateGraph(const QVector<double> &xValues,
                            const QVector<double> &yValues) {
  ui->widget->graph(0)->setData(xValues, yValues);
  ui->widget->replot();
}

void GraphView::on_xMin_valueChanged(int arg1) { emit valMinXChanged(arg1); }

void GraphView::on_xMax_valueChanged(int arg1) { emit valMaxXChanged(arg1); }

void GraphView::onGraphClicked() { emit onGrapghWasClicked(); }
