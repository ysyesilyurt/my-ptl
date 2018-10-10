#ifndef _PTL_MERGE_SORT_HPP_
#define _PTL_MERGE_SORT_HPP_

#include <cstddef>

namespace ptl {

    template <typename T>
    void merge_sort(T[], size_t, size_t);

    template <typename T>
    void merge_for_sort(T[], size_t, size_t, size_t);

    template <typename T>
    void merge_sort(T arr[], size_t arr_size) { // function overloading for calling
        merge_sort(arr, 0, arr_size - 1);       // merge sort with right parameters
    }

    template <typename T>
    void merge_sort(T *arr, size_t start_index, size_t end_index) {

        if (start_index < end_index) {
            merge_sort(arr, start_index, (end_index + start_index) / 2); // middle = (end + start)/2
            merge_sort(arr, (end_index + start_index) / 2 + 1, end_index);
            merge_for_sort(arr, start_index, (end_index + start_index) / 2, end_index);
        }
    }

    template <typename T>
    void merge_for_sort(T *arr, size_t first, size_t middle, size_t last) {
        
        size_t len1 = middle - first + 1, len2 = last - middle, arr_index = first, arr1_index = 0, arr2_index = 0;
        size_t arr1[len1], arr2[len2];

        for (int l = 0; l < len1; ++l) { // create arr1 with first half
            arr1[l] = arr[first + l];
        }
        for (int l = 0; l < len2; ++l) { // create arr2 with second half
            arr2[l] = arr[middle + 1 + l];
        }

        while ((arr1_index < len1) && (arr2_index < len2)) // merge arr1 and arr2 to arr in a sorted manner
        {
            if (arr1[arr1_index] <= arr2[arr2_index]) {
                arr[arr_index] = arr1[arr1_index];
                arr_index++;
                arr1_index++;
            } 
            else {
                arr[arr_index] = arr2[arr2_index];
                arr_index++;
                arr2_index++;
            }
        }

        if (arr1_index < len1) {                            // if arr1 has some remaining numbers push them to arr
            for (; arr1_index < len1; ++arr1_index, ++arr_index) {
                arr[arr_index] = arr1[arr1_index];
            }
        }
        else {                                              // if arr2 has some remaining numbers push them to arr
            for (; arr2_index < len2; ++arr2_index, ++arr_index) {
                arr[arr_index] = arr2[arr2_index];
            }
        }
    }
}

#endif /* _PTL_MERGE_SORT_HPP_ */
