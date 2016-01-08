#include "datachartview.h"

DataChartView::DataChartView()
{
    chartView = new QCustomPlot();
    initChart();


    //FOR TESTS
   // QTimer * timer = new QTimer(this);
   // connect(timer,SIGNAL(timeout()),this,SLOT(updateRealTimeDataTest()));
   // timer->start(800);
}

DataChartView::~DataChartView()
{
    delete chartView;
}
void DataChartView::initChart()
{

  chartView->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectAxes|QCP::iSelectPlottables);
  chartView->axisRect()->setupFullAxesBox();
  chartView->plotLayout()->insertRow(0);
  chartView->plotLayout()->addElement(0, 0, new QCPPlotTitle(chartView, "US-015 Sensor Data"));

  chartView->xAxis->setLabel("Time");
  chartView->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  chartView->xAxis->setDateTimeFormat("hh:mm:ss");
  chartView->xAxis->setAutoTickStep(false);
  chartView->xAxis->setTickStep(2);
  chartView->axisRect()->setupFullAxesBox();
  chartView->yAxis->setLabel("Value");

  chartView->legend->setVisible(true);
  setupGraph();
  //connect(chartView, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
  //connect(chartView, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));


}


void DataChartView::mousePress()
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (chartView->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    chartView->axisRect()->setRangeDrag(chartView->xAxis->orientation());
  else if (chartView->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    chartView->axisRect()->setRangeDrag(chartView->yAxis->orientation());
  else
    chartView->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void DataChartView::mouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (chartView->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    chartView->axisRect()->setRangeZoom(chartView->xAxis->orientation());
  else if (chartView->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    chartView->axisRect()->setRangeZoom(chartView->yAxis->orientation());
  else
    chartView->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}


void DataChartView::setupGraph()
{

  chartView->addGraph();
  chartView->graph(0)->setName(QString("US015 data:").arg(chartView->graphCount()-1));
  //chartView->graph(0)->setBrush(QBrush(QColor(Qt::green)));
  chartView->graph(0)->setLineStyle((QCPGraph::LineStyle)(rand()%10+1));
  chartView->graph(0)->setAntialiasedFill(true);
  chartView->graph(0)->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)6));
  QPen graphPen;
  graphPen.setColor(QColor(rand()%50+10, rand()%245+10, rand()%245+10));
  graphPen.setWidthF(2);
  chartView->graph(0)->setPen(graphPen);
  chartView->replot();
}


void DataChartView::updateRealTimeData(int value){

    double currentTime= QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    chartView->graph(0)->addData(currentTime,value);
   // chartView->graph(0)->removeDataBefore(currentTime-8);
    chartView->graph(0)->rescaleValueAxis();
    chartView->xAxis->setRange(currentTime, 8, Qt::AlignRight);
    chartView->replot();

}


void DataChartView::updateRealTimeDataTest(){

    double currentTime= QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    int value= rand()%30+10;
    chartView->graph(0)->addData(currentTime,value);
    chartView->graph(0)->removeDataBefore(currentTime-8);
    chartView->graph(0)->rescaleValueAxis();
    chartView->xAxis->setRange(currentTime+0.25, value+8, Qt::AlignRight);
    chartView->replot();

    qDebug()<<"HEREEE\n";

}
