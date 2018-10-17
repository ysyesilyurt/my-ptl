#ifndef _PTL_BINARY_SEARCH_HPP_
#define _PTL_BINARY_SEARCH_HPP_

#include <cstddef>

namespace ptl{

    template <typename T>
    int binary_search(T arr[], size_t start_index, size_t end_index, T target){
        if (arr[(end_index + start_index) / 2] == target) // target found, returning index
            return (end_index + start_index) / 2;
        else if (end_index - start_index <= 1) // target is not in the array, returning -1
            return -1;
        else if (arr[(end_index + start_index) / 2] < target) // target is greater than middle
            return binary_search(arr, (end_index + start_index) / 2, end_index, target); // checking left subarray
        else if (arr[(end_index + start_index) / 2] > target) // target is smaller than middle
            return binary_search(arr, start_index, (end_index + start_index) / 2, target); // checking right subarray
    }
}

#endif /* _PTL_BINARY_SEARCH_HPP_ */
