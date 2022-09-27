#include "array_merge.h"

#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../mergesort/mergesort.h"

/// Takes in an array and its length. Sorts the array, placing its unique elements in ascending order at the front of the array and returning the number of unique elements in the array. Note that this function mutates the incoming array.
unsigned int make_unique(int* array, unsigned int length);

int* array_merge(int num_arrays, int* sizes, int** values) {
  // We need to make sure `num_arrays` is actually nonnegative
  assert(num_arrays >= 0);

  // Compute the total number of items in all of the input arrays
  unsigned int total = 0;
  for (unsigned int i = 0; i < (unsigned int)num_arrays; i++) {
    // Make sure the input sizes are all atleast zero
    assert(sizes[i] >= 0);

    total += (unsigned int)sizes[i];
  }

  // Allocate the buffer to do our sorting in
  int* buffer = (int*)calloc(total + 1, sizeof(int));

  // If there are not items given, we don't have to do anything else
  if (total == 0) {
    buffer[0] = 0;
    return buffer;
  }

  // Iterate over all of the input arrays, copying them to the buffer
  // We start at index one since we need the space to put the size
  unsigned int index = 1;
  for (unsigned int i = 0; i < (unsigned int)num_arrays; i++)
  {
    memcpy(buffer + index, values[i], sizes[i] * sizeof(int));
    index += sizes[i];
  }

  // Get the unique elements of this array
  unsigned int unique_count = make_unique(buffer + 1, total);

  // We need to ensure this can fit within an int
  assert(unique_count <= INT_MAX);

  // Place the unqiue count at the beginning
  buffer[0] = (int)unique_count;

  return buffer;
}

/// Takes in an array and its length. Sorts the array, placing its unique elements in ascending order at the front of the array and returning the number of unique elements in the array. Note that this function mutates the incoming array.
unsigned int make_unique(int* array, unsigned int length) {
  // Make sure length is able to fit within an integer without overflowing
  assert(length <= INT_MAX);

  // Sort the elements of the incoming array
  mergesort((int)length, array);

  // Initialize the indexes to walk the array
  unsigned int dest_index = 0;
  unsigned int src_index = 0;

  // Loop over the entire array
  while (src_index < length) {
    // If the value pointed to by `src_index` is the same as the element pointed to by `dest_index`
    if (array[dest_index] == array[src_index]) {
      // Just increment the source index
      src_index++;
    }
    // Otherwise
    else {
      // Increment the destination index and copy the value over to this new value
      array[++dest_index] = array[src_index++];
    }
  }

  // The current `dest_index` is the index of the end of the resulting array, so `dest_index + 1`is its length.
  return dest_index + 1;
}