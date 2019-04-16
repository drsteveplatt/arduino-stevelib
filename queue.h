//
// header file for simple fixed-max-length Queue

template<class T, int MAX> class Queue {
    private:

    int m_bottom;   // first element in use -- next to be pulled
    int m_next;      // first free cell
    // note:  if m_next==m_bottom,  queue is empty or full, so...
    bool m_isEmpty;
    // and by definition,
    //  m_bottom!=m_next -> is not empty, is not full
    // m_bottom==m_next & m_isEmpty -> empty
    //  actually, m_empty will only be set when m_bottom==m_next
    // m_bottom==m_next & !m_isEmpty -> full

    T m_data[MAX];   // The data...
    public:
    Queue(): m_bottom(0), m_next(0), m_isEmpty(true) {}
    bool push(T val);
    bool pop(T& val);
    bool peek(T& val);
    bool isEmpty() { return m_isEmpty; }
    bool isFull() { return m_bottom==m_next && !m_isEmpty; }
};
