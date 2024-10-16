#include <vector>
#include <iostream>
#include <initializer_list>
#include <new>

#include "MyException.h"

template <class T>
class Queue;

template <class T>
class Iterator;

//Класс узел очереди

template  <class T>
class Node{
    friend class Queue<T>;
    friend class Iterator<T>;
    Node<T> *next;
    Node<T> *prev;
    T value;
public:
    Node() : next(nullptr), prev(nullptr), value{}{} ;
    Node(const Node&node);
};

template <class T>
Node<T>::Node(const Node<T> &node)
{
    next=node->next;
    prev=node->next;
    value=node->value;
}

//Реализация итератора для очереди
template <class T>
class Iterator{

public:
    Iterator(): node(nullptr){};
    explicit Iterator(Node<T> *);
    Iterator(const Iterator<T> &);

    bool operator ==(const Iterator<T> &);
    bool operator !=(const Iterator<T> &);
    T& operator*() const;
    Iterator& operator++();
    Iterator& operator--();
    Iterator operator++(int);
    Iterator operator--(int);
private:
    Node<T> *node;
};

namespace std
{
    template<typename T>
    struct iterator_traits<Iterator < T>>
            {
    using difference_type = std::ptrdiff_t;
    using value_type = std::remove_cv_t<T>;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::bidirectional_iterator_tag;
    using iterator_concept = std::bidirectional_iterator_tag;
    };
}

template <class T>
Iterator<T>::Iterator(Node<T> *ptr)
{
    node=ptr;
}

template <class T>
Iterator<T>::Iterator(const Iterator<T> &iterator)
{
    node=iterator.node;
}

template <class T>
bool Iterator<T>::operator==(const Iterator<T>&a)
{
    return (node==a.node);
}

template <class T>
bool Iterator<T>::operator!=(const Iterator<T>&a){
    return (node!=a.node);
}

template <class T>
T& Iterator<T>::operator*() const
{
    return node->value;
}


template <class T>
Iterator<T>& Iterator<T>::operator++()
{
        node=node->next;
    return *this;
}

template <class T>
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator<T> temp=*this;
    ++(*this);
    return temp;
}

template <class T>
Iterator<T>& Iterator<T>::operator--()
{
        node=node->prev;
    return *this;
}

template <class T>
Iterator<T> Iterator<T>::operator--(int)
{
    Iterator<T> temp=*this;
    --(*this);
    return temp;
}


//Класс очереди
template <class T>
class Queue{
    Node<T>*head;
    Node<T>*tail;
    unsigned Size;
public:
        using iterator=Iterator<T>;
       // using const_iterator = Iterator<const T>;
        using reverse_iterator=std::reverse_iterator<iterator>;
       // using const_reverse_iterator=std::reverse_iterator<const_iterator>;

    Queue();
    Queue(const std::initializer_list<T>&);
    ~Queue()
    {
        clear();
        delete head;
    }


    iterator begin() { return iterator (head->next);}
    iterator end() { return iterator (head);}

  /*  iterator begin() const{ return iterator (head->next);}
    iterator end() const{ return iterator (head);}*/

   // const_iterator cbegin() const{ return iterator (head->next);}
   // const_iterator cend() const { return  end();}

    reverse_iterator rbegin() { return std::make_reverse_iterator(end());}
    reverse_iterator rend() { return std::make_reverse_iterator(begin());}


   /* reverse_iterator rbegin() const { return std::make_reverse_iterator(rbegin());}
    reverse_iterator rend() const { return std::make_reverse_iterator(rend());}

    const_reverse_iterator crbegin() const { return std::make_reverse_iterator(rbegin());}
    const_reverse_iterator crend() const{ return std::make_reverse_iterator(rend());}*/


    template<typename T1> friend std::ostream&  operator<< (std::ostream &os, Queue<T1>& qu);
    template<typename T1> friend Queue<T1>& operator>>(std::istream &is,Queue<T1>& qu);

    void writeToBin(std::ostream &);
    void readFromBin(std::istream &);

    void push(const T&); //добавление элемента
    bool empty();        //проверка на пустоту
    unsigned size();     //получение размера
    std::vector<T> peek(); //получение данных
    T pop();             //удаление элемента и его получение
    void print();        //вывод элементов очереди
    void clear();        //очистка очереди
};



template <class T>
Queue<T>::Queue(const std::initializer_list<T> &list)
{
    try
    {
        head = new Node<T>;
        head->prev = head;
        head->next = head;
        tail = head;
        Size = 0;
        unsigned size = list.size();
        for (const auto &value: list)
        {
            try
            {
                push(value);
            }
            catch (std::bad_alloc &exception)
            {
                std::cout << "Bad allocation error: " << exception.what() << std::endl;
            }
        }
    }
    catch(std::bad_alloc &exception)
    {
        std::cout << "Bad allocation error: " << exception.what() << std::endl;
    }
}

template <class T>
Queue<T>::Queue()
{
    head=new Node<T>;
    head->prev=head;
    head->next=head;
    tail=head;
    Size=0;
}

template <class T>
void Queue<T>::clear()
{
    Node<T> *ptr=head->next;
    while(ptr!=head)
    {
        Node<T>*next=ptr->next;
        delete ptr;
        ptr=next;
    }
    head->next=head;
    head->prev=head;
    Size=0;
   // std::cout<<"Cleared"<<std::endl;
}



template <class T>
void Queue<T>::push(const T & val)
{
    auto *temp = new Node<T>;

    temp->value=val;

    temp->prev=tail;
    temp->next=head;
    head->prev=temp;
    tail->next=temp;

    tail=temp;
    Size++;
}


template<class T>
bool Queue<T>::empty()
{
    return (Size==0);
}

template<class T>
unsigned Queue<T>::size()
{
    return Size;
}

template<class T>
std::vector<T> Queue<T>::peek()
{
    std::vector<T> vector;
    if(Size)
    {
        for (const auto &element: *this)
        {
            vector.push_back(element);
        }
    }
    else
        std::cout<<"No elements!"<<std::endl;
    return vector;
}

template <class T>
T Queue<T>::pop()
{
    if(empty())
        throw std::out_of_range("Can't pop from empty list");
    Node<T>*ptr=head->next;
    T save=ptr->value;
        head->next = ptr->next;
        ptr->next->prev = head;
        delete ptr;
        Size--;
    return save;
}

template <class T>
void Queue<T>::print()
{
    std::cout<<"Printing Queue:"<<std::endl;
    std::cout<<std::endl;
   for(const auto&item :*this)
       std::cout<<item<<"----------"<<std::endl;
}

template <typename T1>
std::ostream & operator<<(std::ostream &os, Queue<T1>& qu)
{
    for(const auto& item:qu)
    {
        os<<item;
        os<<"----------"<<std::endl;
    }
    return os;
}

template <typename T1>
Queue<T1>& operator>>(std::istream& is, Queue<T1>&qu)
{
    char buf[255];
    T1 item;
    do{
        is>>item;
        if(is.eof())
            break;
        try
        {
            qu.push(item);
        }
        catch(std::bad_alloc& exception)
        {
            std::cout<<"Allocation error: "<<exception.what()<<std::endl;
        }
            is >> buf;
    }while(true);
    return qu;
}

template <class T>
void Queue<T>::writeToBin(std::ostream & os)
{
    for( auto&item:*this)
    {
        os.write(reinterpret_cast<char*>(&item),sizeof(*this));
    }
}

template <class T>
void Queue<T>::readFromBin(std::istream & is)
{
    T item;
    while( is.read(reinterpret_cast<char*>(&item),sizeof(*this)))
    {
        try
        {
            this->push(item);
        }
        catch(std::bad_alloc& exception)
        {
            std::cout<<"Allocation error: "<<exception.what()<<std::endl;
        }
    }
}








