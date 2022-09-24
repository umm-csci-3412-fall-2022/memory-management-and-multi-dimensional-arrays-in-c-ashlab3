#include "mergesort.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/// Internal implementation of mergesort with slightly different function signature to reflect the internal working
void internal_mergesort(unsigned int size, int* values);

/// Merge two sub arrays of the given lengths
void merge_subarrays(int* dest, unsigned int left_size, int* left, unsigned int right_size, int*right);

/// Sort the array `values` with `size` elements in place using merge sort
void mergesort(int raw_size, int* values) {
  // Make sure we don't attempt to sort on arrays of a negative number of elements
  assert(raw_size >= 0);
  unsigned int size = (unsigned int)raw_size;

  // Switch to the internal mergesort function
  internal_mergesort(size, values);
}


/// Internal implementation of mergesort with slightly different function signature to reflect the internal working
void internal_mergesort(unsigned int size, int* values) {
  // An array of size zero or one is already sorted.
  if (size <= 1) {
    return;
  }

  // Compute the lengths of the left and right halfs of the array
  unsigned int left_length = size / 2;
  unsigned int right_length = size - left_length;

  // Allocate the space for these subarrays
  int* left_side = (int*)calloc(left_length, sizeof(int));
  int* right_side = (int*)calloc(right_length, sizeof(int));

  // Split the parent array into the subarrays
  memcpy(left_side, values, left_length * sizeof(int));
  memcpy(right_side, values + left_length, right_length * sizeof(int));

  // Next, we need to sort the left and right hand sides
  internal_mergesort(left_length, left_side);
  internal_mergesort(right_length, right_side);

  // Merge the subarrays
  merge_subarrays(values, left_length, left_side, right_length, right_side);

  // Free the buffers previously allocated
  free(left_side);
  free(right_side);
}

/// Merge two sub arrays of the given lengths
void merge_subarrays(int* dest, unsigned int left_size, int* left, unsigned int right_size, int*right) {
  // Initialize indexes to zero
  unsigned int left_index = 0;
  unsigned int right_index = 0;
  unsigned int dest_index = 0;

  while (1) {
    // If the left array has been fully consumed, we will copy the remainder of the right array to dest
    if (left_index >= left_size) {
      memcpy(dest + dest_index, right + right_index, (right_size - right_index) * sizeof(int));
      return;
    }
    // If the right array has been fully consumed, we will copy the remainder of the left array to dest
    else if (right_index >= right_size) {
      memcpy(dest + dest_index, left + left_index, (left_size - left_index) * sizeof(int));
      return;
    }

    // Otherwise, get the values at the front of each subarray
    int left_value = left[left_index];
    int right_value = right[right_index];

    // And move whichever is smaller to the destination array
    if (left_value < right_value) {
      dest[dest_index++] = left_value;
      left_index++;
    }
    else {
      dest[dest_index++] = right_value;
      right_index++;
    }
  }
}