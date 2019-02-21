#ifndef _PTL_AVL_TREE_HPP_
#define _PTL_AVL_TREE_HPP_

#include <stack>
#include <list>
#include <ostream>

namespace ptl {

    template <typename Key, typename Object,typename Comparator=std::less<Key> >
    class AvlTree
    {
      private:
        
        struct BinaryNode // node definition
        {
          Key key; // keys are kept constant
          Object data;
          BinaryNode * left;
          BinaryNode * right;
          size_t height;

          BinaryNode(const Key &, const Object &,BinaryNode *, BinaryNode *, size_t = 0);
        };

        BinaryNode * root;
        size_t nodes; // number of nodes
        Comparator isLessThan; // function object to compare keys

      public:

        class Iterator // Iterator class encapsulates the location within the AVL tree
        {
            private:
                BinaryNode * current;
                const BinaryNode * root;
                std::stack<BinaryNode *> s; // will be used to conduct in order traversal if
                bool useStack; // this variable is set to true, ignored in == and !=

                Iterator(BinaryNode *, const AvlTree &, bool =true);

            public:
                Iterator(); // dummy constructor for type declaration purposes
                Iterator & operator++(); // inorder increment

                Object & operator*();  // updates data
                const Object & operator*() const; // views data

                bool operator==(const Iterator & rhs) const; // compares iterators
                bool operator!=(const Iterator & rhs) const; // compares iterators


            friend class AvlTree<Key, Object, Comparator>;
        };
        
        AvlTree();
        ~AvlTree();

        void insert(const Key &, const Object &); // inserts new key,item
        void remove(const Key &); // removes the node with the key value (and also data)

        Iterator find(const Key &) const; // finds single item
        std::list<Iterator> find(const Key &, const Key &) const;// finds in range queries

        Iterator begin() const; // starts inorder traversal 
        Iterator end() const; // dummy NULL iterator
        
        int height() const; // returns the height of the tree
        size_t size() const; // returns the number of items in the tree
        bool empty() const; // returns whether the tree is empty or not
        void print(std::ostream &) const;


      private:
        /* private utility functions */
        void makeEmpty(BinaryNode * &);

        BinaryNode * find(const Key &, BinaryNode *) const;
        int height(BinaryNode *) const;
        void print(BinaryNode *, std::ostream &) const;

        template <typename T> //static utility function
        static const T & max(const T &, const T &);

        //balancing functions
        void rotateWithLeftChild(BinaryNode * &);
        void rotateWithRightChild(BinaryNode * &);
        void doubleWithLeftChild(BinaryNode * &);
        void doubleWithRightChild(BinaryNode * &);

        void insert(const Key &, const Object &, BinaryNode * &);
        void remove(const Key &, BinaryNode * &);
        BinaryNode * findmin(BinaryNode * &);
        int getbalance(BinaryNode * &);
        std::list<Iterator> find(const Key &, const Key &, BinaryNode * const) const;
        BinaryNode * findparent(BinaryNode *  ,BinaryNode * &);
    };

    // node constructor
    template <typename K, typename O, typename C>
    AvlTree<K,O,C>::BinaryNode::
    BinaryNode(const K & _k, const O & _d,
               BinaryNode * _l, BinaryNode * _r, size_t _h)
      : key(_k), data(_d), left(_l), right(_r), height(_h)
    {
        
    }

    // default constructor of the AVL tree
    template <typename K, typename O, typename C>
    AvlTree<K,O,C>::AvlTree( )
      : root(NULL), nodes(0)
    {
        
    }

    // destructor of the AVL tree
    template <typename K, typename O, typename C>
    AvlTree<K,O,C>::~AvlTree( )
    {
      makeEmpty(root);
    }

    // private utility function for destructor
    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::makeEmpty(BinaryNode * & t)
    {
      if (t != NULL)
      {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        --nodes;
      }

      t = NULL;
    }

    // public function to insert into AVL tree
    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::insert(const K & k, const O & x)
    {
        insert(k,x,root);
    }

    // private utility function for insert
    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::insert(const K & k, const O & x, BinaryNode * & nodee)
    {
        if(nodee == NULL) {
            nodee = new BinaryNode(k, x, NULL, NULL);
            this->nodes++;
        }
        else if (isLessThan(k, nodee->key))
        {
            insert(k,x,nodee->left);
            if(height(nodee->left) - height(nodee->right) == 2)
            {
                if(isLessThan(k , nodee->left->key))
                    rotateWithLeftChild(nodee); //case1 for avl
                else
                    doubleWithLeftChild(nodee); //case2
            }
        }
        else if (isLessThan(nodee->key, k))
        {
            insert(k,x,nodee->right);
            if(height(nodee->right) - height(nodee->left) == 2)
            {
                if(isLessThan(nodee->right->key , k))
                    rotateWithRightChild(nodee); //case4
                else
                    doubleWithRightChild(nodee); //case3
            }
        }
        else
        {
            nodee->data = x;
        }
        nodee->height = max(height(nodee->left), height(nodee->right)) + 1;
    }

    // public function to remove key from AvlTree
    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::remove(const K & k)
    {
        remove(k,root);
    }

    // private utility function for remove
    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::remove(const K & k, BinaryNode * & nodee)
    {
        if(nodee == NULL) {    //item not found do nothing
            return;
        }
        if (isLessThan(k, nodee->key)) //trying to find
        {
            remove(k,nodee->left);
        }
        else if (isLessThan(nodee->key, k)) //trying to find
        {
            remove(k,nodee->right);
        }
        else if (nodee->left  && nodee->right ) //found, it has 2 children
        {

            BinaryNode * replacement = findmin(nodee->right); // CASE-1: replace with node->right
            if(nodee->right == replacement)
            {
                BinaryNode * parent = findparent(root,nodee);
                bool rightchild = false;
                if(parent)
                {
                    if(parent->right == nodee)
                        rightchild = true;
                }
                replacement->left = nodee->left;
                nodee->right = replacement->right;
                replacement-> right = nodee;
                nodee->left = NULL;
                if(parent){
                    if (rightchild)
                        parent->right = replacement;
                    else
                        parent->left = replacement;
                }
                else
                    root = replacement;
                remove(k,replacement->right);
            }
            else
            {
                BinaryNode * parent = findparent(root,nodee); // CASE-2: replace with min (in right subtree) that is not node->right
                BinaryNode * temp = replacement->right;
                BinaryNode * parentofrep = findparent(root,replacement);
                bool rightchild = false;
                if(parent)
                {
                    if(parent->right == nodee)
                        rightchild = true;
                }
                replacement->right = nodee->right;
                replacement->left = nodee->left;
                nodee->right = temp;
                nodee->left = NULL;
                if(parent) {
                    if (rightchild)
                        parent->right = replacement;
                    else
                        parent->left = replacement;
                }
                parentofrep->left = nodee;
                if(!parent)
                    root = replacement;
                remove(k,replacement->right);
            }


        }
        else // it has zero or one child: move that or right child here
        {
            BinaryNode * oldnode = nodee;
            nodee = (nodee->left != NULL) ? nodee->left : nodee->right;
            delete oldnode;
            this->nodes--;
        }

        // If the tree had only one node then return
        if (nodee == NULL)
            return;

        // update height each time as you go back through the recursion
        nodee->height = 1 + max(height(nodee->left),height(nodee->right));

        // get the balance factor of the node
        int balance = getbalance(nodee);

        if (1 < balance ) {
            // check for unbalance
            if (0 < getbalance(nodee->left)) {
                rotateWithLeftChild(nodee); //if left is longer, (left of left)-case 1
            }
            else
                doubleWithLeftChild(nodee); //case 3 (right of left)
        }
        else if (balance < -1) {  //symmetrically the other side,

            if (getbalance(nodee->right) < 0) {  //check for unbalance
                rotateWithRightChild(nodee); // case 2 (right of right)
            }
            else
                doubleWithRightChild(nodee); // case 4 (left of right)
        }
    }

    // private utility function findmin for remove
    template <typename K, typename O, typename C>
    typename AvlTree<K,O,C>::BinaryNode *
    AvlTree<K,O,C>::findmin(BinaryNode * & nodee)
    {
        if (nodee == NULL)
            return NULL;
        if (nodee->left == NULL)
            return nodee;
        return findmin(nodee->left);
    }


    // private utility function findparent for remove
    template <typename K, typename O, typename C>
    typename AvlTree<K,O,C>::BinaryNode *
    AvlTree<K,O,C>::findparent(BinaryNode *  rooot, BinaryNode * & curr )
    {
        if(curr == root)
            return NULL;
        else if (rooot->left == curr || rooot->right == curr)
        {
            return rooot;
        }
        else if (isLessThan(rooot->key, curr->key))
        {
            return findparent(rooot->right, curr);
        }
        else if (isLessThan(curr->key, rooot->key))
        {
            return findparent(rooot->left, curr);
        }
    }

    // private utility function getbalance for remove
    template <typename K, typename O, typename C>
    int
    AvlTree<K,O,C>::getbalance(BinaryNode * & nodee)
    {
        if (nodee == NULL)
            return 0;
        return height(nodee->left) - height(nodee->right);
    }

    // public function to search elements in AvlTree
    template <typename K, typename O, typename C>
    typename AvlTree<K,O,C>::Iterator
    AvlTree<K,O,C>::find(const K & key) const
    {
      BinaryNode * node = find(key, root);

      if (node == NULL)
      {
        return end();
      }
      else
      {
        return Iterator(node, *this, false);
      }
    }

    // private utility function to search elements
    template <typename K, typename O, typename C>
    typename AvlTree<K,O,C>::BinaryNode *
    AvlTree<K,O,C>::find(const K & key, BinaryNode * t) const
    {
      if (t == NULL)
      {
        return NULL;
      }
      else if (isLessThan(key, t->key))
      {
        return find(key, t->left);
      }
      else if (isLessThan(t->key, key))
      {
        return find(key, t->right);
      }
      else //found
      {
        return t;
      }
    }

    // finding item between range queries in AvlTree
    template <typename K, typename O, typename C>
    std::list<typename AvlTree<K,O,C>::Iterator>
    AvlTree<K,O,C>::find(const K & lower, const K & upper) const
    {
        return find(lower,upper,root);
    }

    // private utility function for find between range queries
    template <typename K, typename O, typename C>
    std::list<typename AvlTree<K,O,C>::Iterator>
    AvlTree<K,O,C>::find(const K & lower, const K & upper, BinaryNode * const nodee) const
    {
        std::list<typename AvlTree<K,O,C>::Iterator> lst;
        BinaryNode * temp1 = nodee;
        BinaryNode * temp2 = nodee;

        while (temp1->left)
            temp1 = temp1->left;
        if(isLessThan(upper,temp1->key))
            return lst;
        while (temp2->right)
            temp2 = temp2->right;
        if(isLessThan(temp2->key,lower))
            return lst;

        typename AvlTree<K,O,C>::Iterator it = this->begin();

        while(it != this->end() && isLessThan(it.current->key , lower))
            ++it;

        while (it != this->end() && (isLessThan(it.current->key , upper) || (!(isLessThan(it.current->key,upper)) && !(isLessThan(upper,it.current->key)))))
        {
            lst.push_back(it);
            ++it;
        }
        return lst;
    }

    // Inorder iterator begins at ++root
    template <typename K, typename O, typename C>
    typename AvlTree<K,O,C>::Iterator
    AvlTree<K,O,C>::begin() const
    {
      return Iterator(root, *this);
    }

    // no more increment after end() also
    // returned in case of unsuccessful search
    // or when no more applicance of ++ is possible
    template <typename K, typename O, typename C>
    typename AvlTree<K,O,C>::Iterator
    AvlTree<K,O,C>::end() const
    {
      return Iterator(NULL, *this);
    }

    // public function to return height of the AvlTree
    template <typename K, typename O, typename C>
    int
    AvlTree<K,O,C>::height() const
    {
      return height(root);
    }

    // private utility function for computing height
    template <typename K, typename O, typename C>
    int
    AvlTree<K,O,C>::height(BinaryNode * t) const
    {
      return (t == NULL) ? -1 : t->height;
    }

    // public function to return number of nodes in the tree
    template <typename K, typename O, typename C>
    size_t
    AvlTree<K,O,C>::size() const
    {
      return nodes;
    }

    // public function to return true if empty false otherwise
    template <typename K, typename O, typename C>
    bool
    AvlTree<K,O,C>::empty( ) const
    {
      return nodes == 0;
    }

    // public function to print keys inorder to some ostream
    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::print(std::ostream & out) const
    {
      print(root, out);
      out << '\n';
    }

    // private utility function to print AvlTree
    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::print(BinaryNode * t, std::ostream & out) const
    {
      if (t != NULL && t->left != NULL)
      {
        out << '[';
        print( t->left, out );
      }
      else if (t != NULL && t->left == NULL && t->right != NULL)
      {
        out << "[";
      }

      if (t != NULL)
      {
        if (t->left == NULL && t->right == NULL)
        {
          out << '(' << (t->key) << ')';
        }
        else if (t->left != NULL || t->right != NULL)
        {
          out << '{' << (t->key) << ",H" << t->height << '}';
        }
      }

      if (t != NULL && t->right != NULL)
      {
        print( t->right, out );
        out << ']';
      }
      else if (t != NULL && t->left != NULL && t->right == NULL)
      {
        out << "]";
      }
    }

    // static function to compute maximum of two elements
    template <typename K, typename O, typename C>
    template <typename T>
    const T &
    AvlTree<K,O,C>::max(const T & el1, const T & el2)
    { 
        return el1 > el2 ? el1 : el2;
    }

    // Rotation functions
    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::rotateWithLeftChild(BinaryNode * & k2)
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = AvlTree<K,O,C>::max(height(k2->left),
                                                  height(k2->right)) + 1;
        k1->height = AvlTree<K,O,C>::max(height(k1->left),
                                                  height(k2)) + 1;
        k2 = k1;
    }

    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::rotateWithRightChild(BinaryNode * & k1)
    {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = AvlTree<K,O,C>::max(height(k1->left),
                                                  height(k1->right)) + 1;
        k2->height = AvlTree<K,O,C>::max(height(k2->right),
                                                  height(k1)) + 1;
        k1 = k2;
    }

    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::doubleWithLeftChild(BinaryNode * & k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    template <typename K, typename O, typename C>
    void
    AvlTree<K,O,C>::doubleWithRightChild(BinaryNode * & k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    /* ITERATOR functions */

    // dummy constructor
    template <typename K, typename O, typename C>
    AvlTree<K,O,C>::Iterator::Iterator()
      : current(NULL), root(NULL), useStack(false)
    {
        
    }

    // dereferencing operator non-const version
    template <typename K, typename O, typename C>
    O &
    AvlTree<K,O,C>::Iterator::operator*( )
    {
        return current->data;
    }

    // dereferencing operator const version
    template <typename K, typename O, typename C>
    const O &
    AvlTree<K,O,C>::Iterator::operator*( ) const
    {
        return current->data;
    }

    // compare Iterators ignoring useStack var
    template <typename K, typename O, typename C>
    bool
    AvlTree<K,O,C>::Iterator::
    operator==(const Iterator & rhs) const
    {
        return current == rhs.current && root == rhs.root;
    }

    // compare Iterators ignoring useStack var
    template <typename K, typename O, typename C>
    bool
    AvlTree<K,O,C>::Iterator::
    operator!=(const Iterator & rhs) const
    {
        return !(*this == rhs);
    }

    /* increment Iterator to point to the inorder next
     * node of then-current node, in case that no further
     * advances are possible return an Iterator that is
     * equal to end()
     */
    template <typename K, typename O, typename C>
    typename AvlTree<K,O,C>::Iterator &
    AvlTree<K,O,C>::Iterator::operator++( )
    {
        if(useStack && current)
        {
            if(!current->right) {
                if(s.empty())
                    current = NULL;
                else
                {
                    current = s.top();
                    s.pop();
                }
            }
            else
            {

                current = current->right;
                while (current->left)
                {
                    s.push(current);
                    current = current->left;
                }
            }
        }
        else
            current = NULL;
        return *this;
    }

    /* real Iterator constructor will be invoked by
     * AvlTree member function only. if no inorder iterator
     * is required by the computation user should
     * explicitly set useStack variable to false, o.w.
     * it will be assumed to be true.
     */
    template <typename K, typename O, typename C>
    AvlTree<K,O,C>::Iterator::
    Iterator(BinaryNode * p, const AvlTree & rhs, bool stk)
    {
        current = p;
        root = rhs.root;
        useStack = stk;
        if(stk && current)
        {
            while (current->left)
            {
                s.push(current);
                current = current->left;
            }
        }
    }
}

#endif /* _PTL_AVL_TREE_HPP_ */
