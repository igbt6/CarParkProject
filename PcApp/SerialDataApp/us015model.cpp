#include "us015model.h"

US015Model::US015Model()
{

}

QList<QString> US015Model::parseFrame(const QByteArray& data){

    QList<QString> frameVal;
    frameVal.append(QString(QDate::currentDate().toString()));
    frameVal.append(QString::fromStdString(data.toStdString()));
    frameVal.append(QString::fromStdString("[mm]"));
    return  frameVal;

}
