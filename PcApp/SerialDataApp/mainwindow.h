#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include "configdialog.h"
#include "us015model.h"
#include "datachartview.h"

QT_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);


private :
    void initActionsConnections(void);
    void initDataTableWidget(void);
private:
    Ui::MainWindow *ui;

    QSerialPort *serial;
    DataChartView *chartView;
    ConfigDialog * serialConfig;
    US015Model *us015Sensor;
};

#endif // MAINWINDOW_H
