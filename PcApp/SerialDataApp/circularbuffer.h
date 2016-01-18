#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <QVector>

template <typename T>
class CircularBuffer
{
public:

    CircularBuffer(int size);

    CircularBuffer(const CircularBuffer<T>& circBuffer);

    virtual ~CircularBuffer();


    bool put(const T& in);
    bool put (const QVector<T>& in);

    bool get(T& out);
    T get();
    bool get(QVector<T>&out, const int sizeOfVec= -1 );
    bool get(QByteArray &out, const int sizeOfArr= -1 );

    bool peek(T& out) const;
    T peek() const;
    void peek(QVector<T>&out, const int sizeOfVec=-1 ) const;
    void peek(const int idx, QVector<T>&out ) const;

    void clear();

    void operator=(const CircularBuffer<T> & circBuffer);

    int searchForGivenValue(const T& val);

    bool makeDataInvalid(int nrOfData);

    inline int getSize() const {
        return size;
    }


    inline int getNrOfData() const {
        return nrOfData;
    }

    inline bool isFull() const {
        return size==nrOfData;
    }

    inline bool isEmpty() const {
        return nrOfData==0;
    }

private:
    int head;
    int tail;
    int size;
    int nrOfData;
    T*data;

public:
    static void testMethod(){
        CircularBuffer<uchar> *cb= new CircularBuffer<uchar>(10);
        for(uchar i=0; i<10; i++){
            cb->put(i);
        }

        if(cb->isFull()){
            qDebug()<<"IS FULL_>> GOOD";
        }
        else
            qDebug()<<"IS EMPTY_> STH IS WRONG";

        uchar head;
        cb->get(head);
        qDebug()<<"NR OF DATA = "<<QString::number(cb->getNrOfData());
        qDebug()<<"HEAD Equals= "<<QString::number(head);
        delete cb;
    }

};


#include "circularbuffer.inl"

#endif // CIRCULARBUFFER_H
