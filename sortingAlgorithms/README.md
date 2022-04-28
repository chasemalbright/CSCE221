# Sorting Vectors
The goal of this assignment is to implement various sorting algorithms for the [`vector`](https://en.cppreference.com/w/cpp/container/vector) data structure.
## Assignment
### Implement Sorting Algorithms
You are to implement `bubble_sort()`, `insertion_sort()`, and `selection_sort()` using iterators. 

**HINT:** Implement `swap()` first. This is going to be used in all the sorting algorithms. Move operations are your friend.

You must implement the following functions:
| Function Name     | Function Description                                                                                                                                                         | Time Complexity            | &#35; Points            |
| -------------     | ------------------------------------------------------------------------------                                                                                               | ------------------------   | ----------------------- |
| `swap`            | swaps the position of two elements                                                                                                                                           | O(1)                       | 5     |
| `bubble_sort`     | Sorts elements in the range \[start, end) using the bubble sort algorithm. This sort should be optimized so the runtime function is about 1/2 n<sup>2</sup> in the worst case| O(n<sup>2</sup>)           | 30                      |
| `insertion_sort`  | Sorts elements in the range \[start, end) using the insertion sort algorithm.                                                                                                | O(n<sup>2</sup>)           | 30                      |
| `selection_sort`  | Sorts elements in the range \[start, end) using the selection sort algorithm.                                                                                                | O(n<sup>2</sup>)           | 30                      |

An additional 5 points is earned if you do not allocate memory during any of the sorting algorithms. You should not need to do this, so you can almost consider these points as "*free*".

It may be helpful for you to consult:
- Reference for Iterators: https://en.cppreference.com/w/cpp/iterator/iterator
- Reference for Sorts: https://en.cppreference.com/w/cpp/algorithm/sort
- Visualization of Sorting Algorithms: https://pulchroxloom.github.io/visualizing_sorts/
- Videos of Sorting Algorithms Visualized: https://youtu.be/kPRA0W1kECg

### Run The Tests
To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `sorting-vectors` folder to accomplish what you need:

**Build all of the tests**
```sh
make -C tests -j12 build-all
```

**Run the test called `<test-name>`.** Replace `<test-name>` with the name of any `.cpp` file in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run/<test-name>
```

**Run every test** in the [`./tests/tests`](./tests/tests) folder.
```sh
make -C tests -j12 run-all -k
```

**Debugging tests** &ndash; For a detailed view, see [./tests/README.md](./tests/README.md).
```sh
make -C tests -j12 build-all -k
cd tests/build
gdb <test-name>
cd ../..
```
> Alex recommends you use `cgdb` which has the same commands as `gdb` but a better user interface. You can install it with `sudo apt install cgdb` on `WSL` or `brew install cgdb` on `MacOS` (provided you have [brew](https://brew.sh))

The first command builds the tests, the next enters the folder where the tests were build. The third invokes `gdb` (**use `lldb` if on Mac OSX**) which is used to debug the program by examining Segmentation Faults and running code line-by-line. Finally, the last command takes you back to the top-level directory.

## Input File Contents
To help test your code we are providing various input files. 
- Files with the `ordered` prefix consist of numbers in sequence 1, 2, ... , n
- Files with the `rand` prefix consist of non-duplicate random numbers in the range [1, n]
- Files with the `randdup` prefix consist of random numbers in the range [1, n]. There are some duplicate values
- Files with the `reverse` prefix consist of numbers in sequence n, n-1, ... , 1
## Turn In
Submit the modified `sorting.h` to Gradescope. In general, submit everything except `main.cpp`.
