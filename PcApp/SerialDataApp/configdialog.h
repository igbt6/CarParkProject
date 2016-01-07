#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>

QT_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui {
class ConfigDialog;
}
class QIntValidator;
QT_END_NAMESPACE

class ConfigDialog: public QDialog
{

    Q_OBJECT
public:
    struct SerialParameters{
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };
    explicit ConfigDialog(QWidget * parent =0);
    ~ConfigDialog();

    SerialParameters serialParams() const;

signals:

private slots:
    void showPortInfo(int idx);
    void apply();
    void checkCustomBaudRatePolicy(int idx);
    void checkCustomDevicePathPolicy(int idx);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

private :
    Ui::ConfigDialog *ui;

    SerialParameters currentSettings;
    QIntValidator *intValidator;
};

#endif // CONFIGDIALOG_H
