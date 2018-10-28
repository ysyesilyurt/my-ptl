#ifndef _PTL_QUICK_SORT_HPP_
#define _PTL_QUICK_SORT_HPP_

#include <cstddef>

namespace ptl {

    template <typename T>
    void quick_sort(T[], size_t, size_t);

    template <typename T>
    void partition(T[], size_t, size_t, size_t &pivot_index);

    template <typename T>
    void quick_sort(T arr[], size_t length) { // function overloading for calling
        quick_sort(arr, 0, length - 1);       // quick sort with right parameters
    }

    template <typename T>
    void quick_sort(T arr[], size_t start_index, size_t end_index) {
        size_t pivot_index;

        if (start_index < end_index) {
            // create the partition: S1, pivot, S2
            partition(arr, start_index, end_index, pivot_index);
            // sort regions S1 and S2
            quick_sort(arr, start_index, pivot_index-1);
            quick_sort(arr, pivot_index+1, end_index);
        }
    }

    template <typename T>
    void partition(T arr[], size_t start_index, size_t end_index, size_t &pivot_index)
    {
        T temp;
        size_t last_of_S1 = pivot_index = start_index; // set pivot as the first element in the array and set i as the pivot
        size_t first_unknown = last_of_S1 + 1; // 'initially', first unknown index = last index of first subarray + 1

        for ( ; first_unknown <= end_index; ++first_unknown) { // walk through array
            if(arr[first_unknown] < arr[pivot_index]) // swap items when needed
            {
                last_of_S1++;
                temp = arr[last_of_S1];
                arr[last_of_S1] = arr[first_unknown];
                arr[first_unknown] = temp;
            }
        }
        // finally swap last item of the first subarray with pivot
        // and make array in the form -> item < pivot | pivot | item > pivot
        temp = arr[pivot_index];
        arr[pivot_index] = arr[last_of_S1];
        arr[last_of_S1] = temp;
        pivot_index = last_of_S1;
    }
}

#endif /* _PTL_QUICK_SORT_HPP_ */
