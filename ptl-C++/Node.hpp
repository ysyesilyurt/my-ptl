#ifndef _PTL_NODE_HPP_
#define _PTL_NODE_HPP_

#include <iostream>

namespace ptl {

    template<class T>
    class Node;

    template<class T>
    std::ostream &operator<<(std::ostream &out, const Node<T> &n);

    template<class T>
    class Node {

        private:
            Node<T> *next;
            T data;

        public:

            Node();
            Node(const T &d);

            Node<T> *getNext() const;
            T getData() const;
            void setNext(Node<T> *newNext);

            friend std::ostream &operator<< <> (std::ostream &out, const Node<T> &n);

    };

    template<class T>
    Node<T>::Node() {
        data = T();
        next = NULL;
    }

    template<class T>
    Node<T>::Node(const T &d) {
        data = d;
        next = NULL;
    }

    template<class T>
    Node<T> *Node<T>::getNext() const {
        return next;
    }

    template<class T>
    T Node<T>::getData() const {
        return data;
    }

    template<class T>
    void Node<T>::setNext(Node<T> *newNext) {
        next = newNext;
    }

    template<class T>
    std::ostream &operator<<(std::ostream &out, const Node<T> &n) {
        out << n.data;
        return out;
    };
}

#endif /* _PTL_NODE_HPP_ */
