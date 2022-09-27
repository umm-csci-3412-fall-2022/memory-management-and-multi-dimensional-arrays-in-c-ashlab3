# Array Merge

## Implementing Array Merge

There are a number of ways this could be implemented. I will attempt to use as little memory as possible in my solution. To do this, I want to do as much with the memory I have been given as possible. Now, it is possible to sort all of the input arrays in place. However, this is potentially not the best solution as it would mutate the arrays passed to the function. Therefore, I will forego optimal memory usage in favor of not needing to mutate the input.

In thinking this through, there is a helper function I would like to make. That being `unsigned int make_unique(int* array, unsigned int length);` This function would take in an array and its length, and would mutate that incoming array such that it fills the begining of the array with the unique elements sorted in ascending order. It would then return the number of unique elements.

### `make_unique`

First, I create the forward declaration and a documentation comment.

```c
...
/// Takes in an array and its length. Sorts the array, placing its unique elements in ascending order at the front of the array and returning the number of unique elements in the array. Note that this function mutates the incoming array.
unsigned int make_unique(int* array, unsigned int length);
...
```

Now, onto the implementation. First, we will sort the incoming array. Instead of using the builtin `qsort` method, I will use the implementation of `mergesort` done for this lab. Note that because of the use of `int` in the signature for `mergesort`, I also assert that `length` can fit within an `int`.

```c
...
  // Make sure length is able to fit within an integer without overflowing
  assert(length <= INT_MAX);

  // Sort the elements of the incoming array
  mergesort((int)length, array);
...
```

Next, we implement a loop which walks through the array, only copying a value back to the beginning if it hasn't been seen before.

```c
...
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
...
```

Finally, because of where `dest_index` ends up, `dest_index + 1` is the number of unique elements.

```c
...
  // The current `dest_index` is the index of the end of the resulting array, so `dest_index + 1`is its length.
  return dest_index + 1;
...
```

### `array_merge`

Now to actually implement `array_merge`. The solution I am gunning for here is to be as elegant as possible, it will not necessarily be the fastest as I am sorting a large array. To get to the point where we can make use of `make_unique`, we first need to get all of the input values into a new array. This array will need to be allocated on the heap (we could do it on the stack, but I am assuming the point of the lab is for us to do this on the heap).

To allocate this space, we need to find the total size needed.

```c
...
  // Compute the total number of items in all of the input arrays
  unsigned int total = 0;
  for (int i = 0; i < num_arrays; i++) {
    // Make sure the input sizes are all atleast zero
    assert(sizes[i] >= 0);
    
    total += (unsigned int)sizes[i];
  }
...
```

Now, the size of the buffer we need to allocate is one greater than this as in the worst case scenario where everything is unique, we still need space to store the length.

```c
...
  // Allocate the buffer to do our sorting in
  int* buffer = calloc(total + 1, sizeof(int));
...
```

Now, we need to copy each array into this buffer.

```c
...
  // Iterate over all of the input arrays, copying them to the buffer
  // We start at index one since we need the space to put the size
  unsigned int index = 1;
  for (unsigned int i = 0; i < num_arrays; i++)
  {
    memcpy(buffer + index, values[i], sizes[i] * sizeof(int));
    index += sizes[i];
  }
...
```

Now, we can finally call `make_unique`.

```c
...
  // Get the unique elements of this array
  unsigned int unique_count = make_unique(buffer + 1, total);

  // We need to ensure this can fit within an int
  assert(unique_count <= INT_MAX);

  // Place the unqiue count at the beginning
  buffer[0] = (int)unique_count;
...
```