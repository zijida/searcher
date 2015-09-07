#ifndef DEFINE_LIST_H_INCLUDED
#define DEFINE_LIST_H_INCLUDED

template<typename T>
class pool
{

public:
    typedef typename std::deque<T> List;
    typedef typename std::deque<T>::iterator Item;
    pool();

    void clean();
    bool exist(T);
    bool append(T);
    bool insert_before(Item,T);
    bool insert_after(Item,T);
    Item prev();
    Item next();
    Item first();
    Item last();

private:
    List    _l;
    Item    _i;
};

#endif // DEFINE_LIST_H_INCLUDED
