//Circular Buffer implementation

template<typename T> CircularBuffer<T>::CircularBuffer(int size)
{
    this-> head=0;
    this->tail=0;
    this->size=size;
    this->nrOfData=0;
    this->data= new T[size];

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
        ++nrOfData;
        //qDebug()<<"PUT "<<QString::number(data[tail-1])<<" NR OF DATA "<<QString::number(nrOfData)<<"TAIL= "<<QString::number( tail%size) ;
        tail%=size;
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

template<typename T>bool CircularBuffer<T>::get(QVector<T>&out, const int sizeOfVec )
{
    int mSize;
    if(sizeOfVec==-1)
        mSize=nrOfData;
    else
        mSize=(sizeOfVec);
    out.resize(mSize);
    for(int i=0;i<mSize; i++){
        if(!get(out[i]))
            return false;
    }
    return true;
}


template<typename T>bool CircularBuffer<T>::get(QByteArray &out, const int sizeOfArr )
{
    int mSize;
    if(sizeOfArr==-1)
        mSize=nrOfData;
    else
        mSize=(sizeOfArr);
    T byte;
    for(int i=0;i<mSize; i++)
    {
        if(!get(byte))
        {
            return false;
        }
        out.append(byte);
    }
    return true;
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


template<typename T> bool CircularBuffer<T>:: makeDataInvalid(int nrOfData){
    if(nrOfData>this->nrOfData)
        return false;
    this->head+=nrOfData;
    this->head%=this->size;
    return true;
}

template<typename T> int CircularBuffer<T>:: searchForGivenValue(const T& val){

    for(int i =0; i<nrOfData; i++ ){
        if(data[(head+i)%(this->size)]==val)
            return i;
    }
    return -1;
}


