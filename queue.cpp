// implementation file for queue
//

#include "queue.h"

template<class T, int MAX> bool Queue<T, MAX>::push(T val) {
    if(isFull()) return false;
    m_data[m_next] = val;
    m_next++;
    if(m_next==MAX) m_next=0;
    m_isEmpty = false;
    return true;
}

template<class T, int MAX> bool Queue<T, MAX>::pop(T& val) {
    if(isEmpty()) return false;
    val = m_data(m_bottom);
    m_bottom++;
    if(m_bottom==MAX) m_bottom=0;
    if(m_bottom==m_next) m_isEmpty = false;
    return true;
}

template<class T, int MAX> bool Queue<T, MAX>::peek(T& val) {
    if(isEmpty()) return false;
    val = m_data(m_bottom);
    return true;
}
