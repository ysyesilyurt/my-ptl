#ifndef _PTL_LINKEDLIST_HPP_
#define _PTL_LINKEDLIST_HPP_

#include "Node.hpp"

namespace ptl {

    template <class T>
    class LinkedList {

    private:
        Node<T>* head;
        Node<T>* tail;
        size_t  size;

    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        /* This method returns head of the linked-list */
        Node<T>* getHead() const;
        /* This method sets head of the linked-list */
        void setHead(Node<T>* n);
        /* This method returns tail of the linked-list */
        Node<T>* getTail() const;
        /* This method sets tail of the linked-list */
        void setTail(Node<T>* n);
        /* This method gets the previous node of the node that contains the data item.
         * If the head node contains the data item, this method returns NULL.*/
        Node<T>* findPrev(const T& data) const;
        /* This method gets the node that stores the data item.
         * If data is not found in the list, this method returns NULL.*/
        Node<T>* findNode(const T& data) const;
        /* This method inserts a new node to store the data item.
         * The new node will be placed after the “prev” node.
         * If prev is NULL then inserts new node to the head.*/
        void insertNode(Node<T>* prev, const T& data);
        /* This method is used to delete the node that is next to “prevNode”. */
        void deleteNode(Node<T>* prevNode);
        /* This method is used to clear the contents of the list. */
        void clear();
        /* This method returns true if the list empty, otherwise returns false. */
        bool isEmpty() const;
        /* This method returns the current size of the list. */
        size_t getSize() const;
        /* This method prints the list content. */
        void print() const;
    };

    template <class T>
    LinkedList<T>::LinkedList(): head(NULL), tail(NULL) , size(0)
    {

    }

    template <class T>
    LinkedList<T>::LinkedList(const LinkedList<T>& ll)
    {
        head = tail = NULL;
        size = 0;
        *this = ll;
    }

    template <class T>
    LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll)
    {
        if (this != &ll) {
            clear();
            const Node<T>* r = ll.getHead();
            Node<T>* nodee = new Node<T>(r->getData());
            head = nodee;
            r = r->getNext();
            while (r) {
                insertNode(nodee , r->getData());
                r = r -> getNext();
                nodee = nodee->getNext();
            }
            tail = nodee;
        }
        return *this;     // return ll for cascading assignment
    }

    template <class T>
    LinkedList<T>::~LinkedList()
    {
        clear();       // delete all the elements, except head
        delete head;  // delete head
    }

    template <class T>
    Node<T>* LinkedList<T>::getHead() const
    {
        return head;
    }

    template <class T>
    void LinkedList<T>::setHead(Node<T>* n)
    {
        head = n;
    }

    template <class T>
    Node<T>* LinkedList<T>::getTail() const
    {
        return tail;
    }

    template <class T>
    void LinkedList<T>::setTail(Node<T>* n)
    {
        tail = n;
    }

    template <class T>
    Node<T>* LinkedList<T>::findPrev(const T& data) const
    {
        Node<T>* nodee = getHead();
        if(nodee->getData() == data)
            return NULL;
        while (nodee->getNext())
        {
            if(nodee->getNext()->getData() == data)
                return nodee;
            nodee = nodee->getNext();
        }
        return NULL;
    }

    template <class T>
    Node<T>* LinkedList<T>::findNode(const T& data) const
    {
        Node<T>* nodee = getHead();
        while (nodee) {
            if (nodee->getData() == data)
                return nodee;
            nodee = nodee->getNext();
        }
        return NULL;
    }

    template <class T>
    void LinkedList<T>::insertNode(Node<T>* prev, const T& data)
    {
        size++;
        if (prev != NULL) {    // non-empty list
            if(prev->getNext() == NULL) // insertion to end
            {
                Node<T>* newNode = new Node<T>(data);
                newNode->setNext(prev->getNext());
                prev->setNext(newNode);
                tail=newNode;
            }
            else {      //insertion to middle
                // create a new node whose next will point to prev’s next
                Node<T> *newNode = new Node<T>(data);
                newNode->setNext(prev->getNext());
                // now prev’s next will be this new node
                prev->setNext(newNode);
            }
        }
        else {   // insertion before the head (or to an empty list)
            if(isEmpty()) // empty list
            {
                Node<T>* newNode = new Node<T>(data);
                newNode->setNext(head);
                tail = head = newNode;
            }
            else { // insertion before the head
                // create a new node whose next will point to the first node
                Node<T> *newNode = new Node<T>(data);
                newNode->setNext(head);
                // now this new node will be the first of the list
                head = newNode;
            }
        }
    }

    template <class T>
    void LinkedList<T>::deleteNode(Node<T>* prevNode)
    {
        size--;
        if(prevNode != NULL)
        {
            if(prevNode->getNext() == tail)
            {
                Node<T>* target = prevNode->getNext();
                prevNode->setNext(target->getNext());
                delete target;
                tail = prevNode;
            }
            else {
                Node<T> *target = prevNode->getNext();
                prevNode->setNext(target->getNext());
                delete target;
            }
        }
        else
        {
            if(isEmpty())
                delete head;
            else    // deletion of head
            {
                Node<T> *target = head;
                head = head->getNext();
                delete target;
            }
        }
    }

    template <class T>
    void LinkedList<T>::clear() //head stays inside list (=NULL)
    {
        Node<T>* temp;
        while(!isEmpty())
        {
            temp = head;
            head = head->getNext();
            delete temp;
        }
        size = 0;
    }

    template <class T>
    bool LinkedList<T>::isEmpty() const
    {
        return head == NULL;   // if NULL, then it is empty
    }

    template <class T>
    size_t LinkedList<T>::getSize() const
    {
        return size;
    }

    template <class T>
    void LinkedList<T>::print() const{
        const Node<T>* node = head;
        while (node) {
            std::cout << node->getData();
            node = node->getNext();
        }
        std::cout << std::endl;
    }
}

#endif /* _PTL_LINKEDLIST_HPP_ */
