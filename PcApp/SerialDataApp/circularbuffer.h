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


    void put(const T& in);
    void put (const QVector<T>& in);

    void get(T& out);
    T get();
    void get(QVector<T>&out, const int N=-1 );

    void peek(T& out) const;
    T peek() const;
    void peek(QVector<T>&out, const int N=-1 ) const;
    void peek(const int idx, QVector<T>&out ) const;

    void clear();

    void operator=(const CircularBuffer<T> & circBuffer);

    inline int getSize() const {
        return nrOfData;
    }

private:
    int head;
    int tail;
    int size;
    int nrOfData;
    T*data;

};



//implementation

template<typename T> CircularBuffer<T>::CircularBuffer(int size){
    this-> head=0;
    this->tail=0;
    this->size=size;
    this->nrOfData=0;
    data= new T[size];

}


template<typename T> CircularBuffer<T>::CircularBuffer(const CircularBuffer<T>& circBuffer){
    if(circBuffer!= NULL){
        this->head=circBuffer.head;
        this->tail=circBuffer.tail;
        this->size=circBuffer.size;
        this->nrOfData=circBuffer.nrOfData;
        delete [] data;
        data= new T[size];

        for (int i = 0; i < circBuffer.nrOfData; i++){
            data[i] = circBuffer.data[i];
        }
    }
}

template <typename T> CircularBuffer<T>::~CircularBuffer(){
    clear();
}

template<typename T> void CircularBuffer<T>::clear(){
    delete[] data;
    this->head=0;
    this->tail=0;
    this->size=0;
    this->nrOfData=0;
}


template<typename T> void CircularBuffer<T>::put(const T& in){

    data[tail++]=in;
    ++nrOfData;
    //if(tail>)

}
template<typename T> void put (const QVector<T>& in){

}


#endif // CIRCULARBUFFER_H
