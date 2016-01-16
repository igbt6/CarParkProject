//Circular Buffer implementation

template<typename T> CircularBuffer<T>::CircularBuffer(int size)
{
    this-> head=0;
    this->tail=0;
    this->size=size;
    this->nrOfData=0;
    data= new T[size];

}


template<typename T> CircularBuffer<T>::CircularBuffer(const CircularBuffer<T>& circBuffer)
{
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

template <typename T> CircularBuffer<T>::~CircularBuffer()
{
    clear();
}

template<typename T> void CircularBuffer<T>::clear()
{
    delete[] data;
    this->head=0;
    this->tail=0;
    this->size=0;
    this->nrOfData=0;
}


template<typename T> bool CircularBuffer<T>::put(const T& in)
{

    if(!isFull()){
        data[tail++]=in;
        tail%=size;
        ++nrOfData;
        return true;
    }
    else
        return false;
}

template<typename T> bool CircularBuffer<T>:: put (const QVector<T>& in)
{

    if(in== NULL||isFull())
        return false;

    foreach (const T& var, in) {
        if(!put(var))
            break;
    }
    return true;
}


template<typename T>bool CircularBuffer<T>::get(T& out)
{
    if(isEmpty())
        return false;
    out= data[head++];
    head%=size;
    nrOfData--;
    return true;

}

template<typename T>T CircularBuffer<T>::get()
{
    T out ;
    get(out);
    return out;
}

template<typename T>void CircularBuffer<T>::get(QVector<T>&out, const int sizeOfVec )
{
    int mSize;
    if(sizeOfVec==-1)
        mSize=nrOfData;
    else
        mSize=(sizeOfVec+1)%nrOfData;
    out.resize(mSize);
    for(int i=0;i<mSize; i++){
        get(out[i]);
    }
}

template<typename T> bool CircularBuffer<T>::peek(T& out) const
{
    if(isEmpty())
        return false;
    out= data[head];

}

template<typename T> T CircularBuffer<T>::peek() const
{
    T out;
    peek(out);
    return out;
}

template<typename T> void CircularBuffer<T>::peek(QVector<T>&out, const int sizeOfVec ) const
{
    int mSize;
    if(sizeOfVec==-1)
        mSize=nrOfData;
    else
        mSize=(sizeOfVec)%(nrOfData+1);
    out.resize(mSize);
    for(int i=0;i<mSize; i++){
        out[i]= data[((head+i)%size)];
    }

}
template<typename T> void CircularBuffer<T>::peek(const int idx, QVector<T>&out ) const
{
   int mSize = nrOfData-idx;
   out.resize(mSize);
   for(int i=0;i<mSize; i++){
       out[i]= data[((head+i+idx)%size)];
   }

}

