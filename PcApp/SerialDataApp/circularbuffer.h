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
    void get(QVector<T>&out, const int sizeOfVec= -1 );

    bool peek(T& out) const;
    T peek() const;
    void peek(QVector<T>&out, const int sizeOfVec=-1 ) const;
    void peek(const int idx, QVector<T>&out ) const;

    void clear();

    void operator=(const CircularBuffer<T> & circBuffer);

    inline int getSize() const {
        return size;
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

};


#include "circularbuffer.inl"

#endif // CIRCULARBUFFER_H
