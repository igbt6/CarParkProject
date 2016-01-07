#ifndef US015MODEL_H
#define US015MODEL_H

#include <QtCore>

class US015Model
{
public:
    US015Model();


    bool checkCorrectFrame(const QByteArray& data);
    QList<QString> parseFrame(const QByteArray& data);

private:
    int value;


};

#endif // US015MODEL_H
