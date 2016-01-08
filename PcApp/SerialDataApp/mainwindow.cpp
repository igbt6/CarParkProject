#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    serialConfig= new ConfigDialog();
    us015Sensor = new US015Model();
    chartView= new DataChartView();

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);



    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));

    initActionsConnections();
    initDataTableWidget();
    ui->chartViewLayout->addWidget(chartView->getGraphPlot());
}

MainWindow::~MainWindow()
{
    delete serialConfig;
    delete ui;
    delete us015Sensor;
}

void MainWindow::openSerialPort()
{
    ConfigDialog::SerialParameters p = serialConfig->serialParams();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Open error"));
    }
}
void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    //console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About PcTestApp"),
                       tr("The <b>PcTestApp</b> Some stuff need to be always visualized "));
}

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}


void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    QList<QString> val= us015Sensor->parseFrame(data);
    //console->putData(data); //TODO
    ui->dataTableWidget->setItem(0, 0, new QTableWidgetItem(val.at(0)));
    ui->dataTableWidget->setItem(0, 1, new QTableWidgetItem(val.at(1)));
    ui->dataTableWidget->setItem(0, 2, new QTableWidgetItem(val.at(2)));
    chartView->updateRealTimeData(val.at(1).toInt());
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Something bad happened to your serial connection"), serial->errorString());
        closeSerialPort();
    }
}


void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfigure, SIGNAL(triggered()), serialConfig, SLOT(show()));
   // connect(ui->actionClear, SIGNAL(triggered()), console, SLOT(clear()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
}


void MainWindow::initDataTableWidget(){

    ui->dataTableWidget->setRowCount(10);
    ui->dataTableWidget->setColumnCount(3);  //hardcoded so far only for US015 TODO
    QStringList tableHeaders;
    tableHeaders<<"Time"<<"Data"<<"Unit";
    ui->dataTableWidget->setHorizontalHeaderLabels(tableHeaders);
    ui->dataTableWidget->setStyleSheet("QTableView {selection-background-color: green;}");
    ui->dataTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

}


