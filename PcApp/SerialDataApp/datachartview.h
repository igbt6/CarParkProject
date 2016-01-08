#ifndef DATACHARTVIEW_H
#define DATACHARTVIEW_H

#include <QtCore>
#include "qcustomplot.h"
#include "datachartview.h"

class DataChartView : public QObject
{
 Q_OBJECT
public:
    DataChartView();
    ~DataChartView();
    inline QCustomPlot *getGraphPlot()
    {
        return chartView;
    }



private:
    void initChart(void);
    void setupGraph();


private :
    QCustomPlot* chartView;


public slots:
    void updateRealTimeData(int value);
private slots:
   void mousePress();
   void mouseWheel();

   void updateRealTimeDataTest();
   //void graphClicked(QCPAbstractPlottable *plottable);


};

#endif // DATACHARTVIEW_H
