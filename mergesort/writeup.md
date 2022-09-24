# Merge Sort

## Implementing Merge Sort

The first task at hand is to implement merge sort. First, I will add some argument names and a documentation comment to `mergesort.c`:

```c
...
/// Sort the array `values` with `size` elements in place using merge sort
void mergesort(int size, int* values) {
  return;
}
...
```

Next, given this signature, there are some issues which can arrise, specifically, `size` should never be negative, as such I will add an assertation of this fact. I would prefer to change the signature to take an unsigned integer to reflect this condition in the type system as well. However, because this is the function signature desired, I will instead do a conversion after the assertation.

```c
...
  // Make sure we don't attempt to sort on arrays of a negative number of elements
  assert(size >= 0);
	unsigned int size = (unsigned int)raw_size;
...
```

To make sure I maintain this, I add a separate function which will not be made visible in `mergesort.h`.

```c
/// Internal implementation of mergesort with slightly different function signature to reflect the internal working
void internal_mergesort(unsigned int size, int* values);
```

Next, the first step in this implementation is to ensure the base case will be handled properly. That is, arrays of size zero or one are already sorted, and we can immediately return.

```c
...
	// An array of size zero or one is already sorted.
  if (size <= 1) {
    return;
  }
...
```

Now, to divide the array in two, we must compute the lengths of each segment, allocate the memory for these sub arrays, and copy the values from the array over.

```c
...
	// Compute the lengths of the left and right halfs of the array
  unsigned int left_length = size / 2;
  unsigned int right_length = size - left_length;

  // Allocate the space for these subarrays
  int* left_side = calloc(left_length, sizeof(int));
  int* right_side = calloc(right_length, sizeof(int));

  // Split the parent array into the subarrays
  memcpy(left_side, values, left_length * sizeof(int));
  memcpy(right_side, values + left_length, right_length * sizeof(int));
...
```

The recursive step is fairly easy, we just run merge sort on the left and right subarrays.

```c
...
  // Next, we need to sort the left and right hand sides
  internal_mergesort(left_length, left_side);
  internal_mergesort(right_length, right_side);
...
```

Next, we must merge together the two arrays. For now, I will add the signature of a helper function to be filled in later.

```c
...
/// Merge two sub arrays of the given lengths
void merge_subarrays(int* dest, unsigned int left_size, int* left, unsigned int right_size, int*right);
...
```

Using this function, merging the subarrays and then freeing the subarrays is fairly easy.

```c
...
	// Merge the subarrays
  merge_subarrays(values, left_length, left_side, right_length, right_side);

  // Free the buffers previously allocated
  free(left_side);
  free(right_side);
...
```

Finally, `merge_subarrays` needs to be implemented. It starts by setting three indexes which are used to walk through the destination array and the two subarrays.

```c
...
	// Initialize indexes to zero
  unsigned int left_index = 0;
  unsigned int right_index = 0;
  unsigned int dest_index = 0;
...
```

Next, if we have fully consumed either the left or right subarray, we can copy the remainder of the other one into the destination and return.

```c
...
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
...
```

Otherwise, we need to compare the front values of the left and right subarrays, and move whichever is smaller into the destination.

```c
...
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
...
```

Finally, doing these last two steps repeatedly in an array ensures we walk through both subarrays.

## Memory Leak Checking

Running valgrind shows that there are no memory leaks.