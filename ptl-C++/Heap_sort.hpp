#ifndef _PTL_HEAP_SORT_HPP_
#define _PTL_HEAP_SORT_HPP_

#include <cstddef>

namespace ptl {

    template <typename T>
    void build_heap(T arr[], size_t length, size_t parent_index);

    template <typename T>
    void heap_sort(T arr[], size_t length)
    {
        T temp;

        for (int i = length / 2 - 1; i >= 0; i--) // first build heap from array with an
            build_heap(arr, length, i);           // initial index of i = length / 2 - 1

        for (int i = length - 1; i >=0 ; i--) // One by one get the maximum element from the heap (arr[0])
        {                                     // and swap it with last index of the array (arr[i])
            temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            build_heap(arr, i, 0);  // fix max heap again with the swapped root (i = new length, 0 = index of whole tree)
        }
    }

    template <typename T>
    void build_heap(T arr[], size_t length, size_t parent_index)  // Builds heap with given subtree rooted with node i which is
    {                                                             // an index in arr[]
        size_t left_child = (2 * parent_index) + 1; // left child
        size_t right_child = (2 * parent_index) + 2; // right child
        size_t greater_index; // index of the greater child
        T temp;

        if (right_child < length) // both children exist
        {
            greater_index = (arr[left_child] > arr[right_child]) ? left_child : right_child;
            if (arr[greater_index] > arr[parent_index])
            {
                temp = arr[parent_index];
                arr[parent_index] = arr[greater_index];
                arr[greater_index] = temp;

                // Recursively fix affected sub-tree
                build_heap(arr, length, greater_index);
            }
        }
        else if (left_child < length) // right child does not exist
        {
            greater_index = left_child;
            if (arr[greater_index] > arr[parent_index])
            {
                temp = arr[parent_index];
                arr[parent_index] = arr[greater_index];
                arr[greater_index] = temp;

                // Recursively fix affected sub-tree
                build_heap(arr, length, greater_index);
            }
        }
        else // there is no child left
            return;
    }
}

#endif /* _PTL_HEAP_SORT_HPP_ */
