#ifndef _PTL_STACK_HPP_
#define _PTL_STACK_HPP_

#include "Node.hpp"

namespace ptl {

    template<class T>
    class Stack {

    private:

        Node<T> *top;

    public:

        Stack();
        Stack(const Stack<T> &rhs);
        ~Stack();
        Stack<T> &operator=(const Stack<T> &rhs);

        /* Returns true if stack is empty */
        bool isEmpty() const;
        /* Pushes newItem to stack */
        void push(const T &newItem);
        /* Popes item from stack */
        void pop();
        /* Returns top item of the stack */
        Node<T> *Top() const;
        /* Prints the stack content */
        void print() const;
    };

    template<class T>
    Stack<T>::Stack(): top(NULL) {

    }

    template<class T>
    Stack<T>::Stack(const Stack<T> &rhs) {
        top = NULL;
        *this = rhs;
    }

    template<class T>
    Stack<T>::~Stack() {
        while (!isEmpty())
            pop();
    }

    template<class T>
    Stack<T> &Stack<T>::operator=(const Stack<T> &rhs) {
        if (this != &rhs) {
            while (!isEmpty()) pop();
            if (!rhs.top)
                top = NULL;
            else {
                top = new Node<T>(rhs.top->getData());
                Node<T> *nextnode = rhs.top->getNext();
                Node<T> *topnode = top;
                while (nextnode) {
                    topnode->setNext(new Node<T>(nextnode->getData()));
                    nextnode = nextnode->getNext();
                    topnode = topnode->getNext();
                }
                topnode->setNext(NULL);
            }
        }
        return *this;   // return ll for cascading assignment
    }

    template<class T>
    bool Stack<T>::isEmpty() const {
        return top == NULL;
    }

    template<class T>
    void Stack<T>::push(const T &newItem) {
        Node<T> *newstacknode = new Node<T>(newItem);
        newstacknode->setNext(top);
        top = newstacknode;
    }

    template<class T>
    void Stack<T>::pop() {
        Node<T> *temp = top;
        top = top->getNext();
        delete temp;
    }

    template<class T>
    Node<T> *Stack<T>::Top() const {
        return top;
    }

    template<class T>
    void Stack<T>::print() const {
        const Node<T> *node = top;
        while (node) {
            std::cout << node->getData();
            node = node->getNext();
        }
        cout << std::endl;
    }
}

#endif /* _PTL_STACK_HPP_ */

