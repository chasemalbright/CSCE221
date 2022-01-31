# Vectors
The overall goal of this assignment is to begin programming data structures by implementing your own slimmed-down [`vector`](https://en.cppreference.com/w/cpp/container/vector).
## Assignment
### Implement Vector
You are to implement `Vector`. A `Vector` is a dynamic array as it is a continuous structure that dynamically updates its capacity as needed. As a result, most operations take constant time to complete. However, the amount of wasted space is often equivalent to the amount used. Therefore, `Vector` is not a particularly spatially efficient storage structure.

You may have already used `std::vector` in previous assignments, so your `Vector` should behave similarly. The big difference is that `std::vector` decreases its capacity when enough `pop_back` operations occur, whereas your `Vector` does not ever need to reduce its capacity.

**HINT:** Do the following functions first.
- `Vector()`
- `Vector(size_t count)`
- `~Vector()`
- `size_t size() const noexcept`
- `size_t capacity() const noexcept`
- `T& operator[](size_t pos)`
- `const T& operator[](size_t pos)`
<br/>More info about the above functions can be seen below. If you complete the above functions, you should be able to complete any other function and it should pass. The above are the only functions which are "depended on." *Please note that there may be minor exceptions to this rule.*

`Vector` must implement the following constructors:
- `Vector() noexcept` &ndash; Default constructor. **Complexity: O(1)** _Points: 2_
- `Vector(size_t count, const T& value)` &ndash; Constructs the container with `count` copies of elements with value `value`.  **Complexity: O(`count`)** _Points 4_
- `explicit Vector(size_t count)` &ndash; Constructs the container with count *default-inserted* instances of T. No copies are made.  **Complexity: O(`count`)** _Points: 4_
- `Vector(const Vector& other)` &ndash; Copy constructor. Constructs the container with the copy of the contents of `other`.  **Complexity: O(`other.size()`)** _Points: 4_
- `Vector(Vector&& other) noexcept` &ndash; Move constructor. Constructs the container with the contents of `other` using move semantics. After the move, `other` is guaranteed to be `empty()`.  **Complexity: O(1)** _Points: 4_

[Constructors Reference](https://en.cppreference.com/w/cpp/container/vector/vector)

You need the following destructor:
- `~Vector()` &ndash; Destructs the vector. The destructors of the elements are called, and the used storage is deallocated. Note that if the elements are pointers, the pointed-to objects are not destroyed. **Complexity: Depends on Allocator** _Points: Frequently Utilized_

[Destructor Reference](https://en.cppreference.com/w/cpp/container/vector/~vector)

You need to implement the following assignment (`operator=`) calls:
- `Vector& operator=(const Vector& other)` &ndash; Copy assignment operator. Replaces the contents with a copy of the contents of `other`. **Complexity: O(`size() + other.size()`)** _Points: 4_
- `Vector& operator=(Vector&& other) noexcept` &ndash; Move assignment operator. Replaces the contents with those of `other` using move semantics (i.e. the data in other is moved from other into this container). After the move, `other` is guaranteed to be `empty()`.  **Complexity: O(`size()`)** _Points: 5_

[`operator=` Reference](https://en.cppreference.com/w/cpp/container/vector/operator%3D)

Your `Vector` must also implement the following functions:
| Function Name | Function Description                                                           | Time Complexity          | Reference                                                              | &#35; Points            |
| ------------- | ------------------------------------------------------------------------------ | ------------------------ | ---------------------------------------------------------------------- | ----------------------- |
| `begin`       | returns an iterator to the beginning                                           | O(1)                     | [Link](https://en.cppreference.com/w/cpp/container/vector/begin)       | 2                       |
| `end`         | returns an iterator to the end                                                 | O(1)                     | [Link](https://en.cppreference.com/w/cpp/container/vector/end)         | 2                       |
| `empty`       | checks whether the container is empty                                          | O(1)                     | [Link](https://en.cppreference.com/w/cpp/container/vector/empty)       | 2                       |
| `size`        | returns the number of elements                                                 | O(1)                     | [Link](https://en.cppreference.com/w/cpp/container/vector/size)        | Frequently Utilized     |
| `capacity`    | returns the number of elements that can be held in currently allocated storage | O(1)                     | [Link](https://en.cppreference.com/w/cpp/container/vector/capacity)    | Frequently Utilized     |
| `at`          | access specified element with bounds checking                                  | O(1)                     | [Link](https://en.cppreference.com/w/cpp/container/vector/at)          | 3                       |
| `operator[]`  | access specified element                                                       | O(1)                     | [Link](https://en.cppreference.com/w/cpp/container/vector/operator_at) | 2                       |
| `front`       | access the first element                                                       | O(1)                     | [Link](https://en.cppreference.com/w/cpp/container/vector/front)       | 3 (shared with `back`)  |
| `back`        | access the last element                                                        | O(1)                     | [Link](https://en.cppreference.com/w/cpp/container/vector/back)        | 3 (shared with `front`) |
| `push_back`   | adds an element to the end                                                     | O(1) amortized           | [Link](https://en.cppreference.com/w/cpp/container/vector/push_back)   | 5 + 4 = 9               |
| `pop_back`    | removes the last element                                                       | O(1)                     | [Link](https://en.cppreference.com/w/cpp/container/vector/pop_back)    | 3                       |
| `insert`      | inserts elements                                                               | O(`count + end() - pos`) | [Link](https://en.cppreference.com/w/cpp/container/vector/insert)      | 4 + 4 + 4 = 12          |
| `erase`       | erases elements                                                                | O(`size()`)              | [Link](https://en.cppreference.com/w/cpp/container/vector/erase)       | 2 + 3 = 5               |
| `clear`       | clears the contents                                                            | O(`size()`)              | [Link](https://en.cppreference.com/w/cpp/container/vector/clear)       | 2                       |

You must also implement an inner class `iterator` in `Vector`. Your `iterator` should implement the following operations.

| Function Name | Function Description                                                          | &#35; Points                                                                              |
| ------------- | ----------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------- |
| `operator*`   | access a reference to the data at the location of the current iterator        | 3 (shared with `operator->`)                                                              |
| `operator->`  | access a member or method of the data at the location of the current iterator | 3 (shared with `operator*`)                                                               |
| `operator++`  | increment an iterator                                                         | 3                                                                                         |
| `operator--`  | decrement an iterator                                                         | 3                                                                                         |
| `operator+=`  | advances the iterator                                                         | 3 (shared with `operator+`, `operator-=`, `operator-`, &amp; `operator[]`)                |
| `operator+`   | advances the iterator                                                         | 3 (shared with `operator+=`, `operator-=`, `operator-`, &amp; `operator[]`)               |
| `operator-=`  | regresses the iterator                                                        | 3 (shared with `operator+=`, `operator+`, `operator-`, &amp; `operator[]`)                |
| `operator-`   | computes the distance between two iterators or regresses the iterator         | 3 (shared with `operator+=`, `operator+`, `operator-=`, &amp; `operator[]`)               |
| `operator[]`  | accesses the element offset from the iterator                                 | 3 (shared with `operator+=`, `operator+`, `operator-=`, &amp; `operator-`)                |
| `operator==`  | compares the underlying iterators                                             | 3 (shared with `operator!=`, `operator<`, `operator>`, `operator<=`, &amp; `operator>=`)  |
| `operator!=`  | compares the underlying iterators                                             | 3 (shared with `operator==`, `operator<`, `operator>`, `operator<=`, &amp; `operator>=`)  |
| `operator<`   | compares the underlying iterators                                             | 3 (shared with `operator==`, `operator!=`, `operator>`, `operator<=`, &amp; `operator>=`) | 
| `operator>`   | compares the underlying iterators                                             | 3 (shared with `operator==`, `operator!=`, `operator<`, `operator<=`, &amp; `operator>=`) |
| `operator<=`  | compares the underlying iterators                                             | 3 (shared with `operator==`, `operator!=`, `operator<`, `operator>`, &amp; `operator>=`)  |
| `operator>=`  | compares the underlying iterators                                             | 3 (shared with `operator!=`, `operator!=`, `operator<`, `operator>`, &amp; `operator<=`)  |

Feel free to read about `const_iterator` and `reverse_iterator` in C++. However, you need only implement `iterator` for this assignment.

It may be helpful for you to consult:
- Reference for Iterators: https://en.cppreference.com/w/cpp/iterator/iterator
- Reference for Vector Begin: https://en.cppreference.com/w/cpp/container/vector/begin
- Reference for Vector End: https://en.cppreference.com/w/cpp/container/vector/end
- Reference for List Begin: https://en.cppreference.com/w/cpp/container/list/begin
- Reference for List End: https://en.cppreference.com/w/cpp/container/list/end

### Use Vector (`Datum`)
We have provided a few data files in Comma Separated Values (CSV) format. These files contain data representing COVID-19 at Texas A&M University. 

> The COVID data was obtained from [TAMU's historical records](https://covid.tamu.edu/dashboard/historical.html) in mid January 2020. The original data was accurate as asserted by A&M and affiliated testing providers. **We have intentionally added inaccuracies you must identify as part of this programming exercise.** We also generate random data for testing purposes. Please refer to TAMU for accurate data.

There is a struct, `Datum` in [Datum.h](./src/Datum.h) as well as a few simple function declarations. You are to write these functions in [Datum.cpp](./src/Datum.cpp).

- `unsigned int Datum::compute_total()` &ndash; Compute the total number of tests given (sum of positive and negative tests) _Points: 2 (shared with `compute_positivity`)_
- `float Datum::compute_positivity()` &ndash; Compute the positivity rate (positive tests divided by computed total) _Points: 2 (shared with `compute_positivity`)_
- `std::ostream& operator<<(std::ostream& out, const Datum& datum)` &ndash; Prints `datum` to `out`. This is only for debugging purposes and we do not test this method. _Points: 0_
- `std::istream& operator>>(std::istream& in, Datum& datum)` &ndash; Sets the fields of `datum` to represent the values stored in `in` _Points: 2_
- `Vector<Datum> readData(std::istream & file)` &ndash; Assume `file` argument corresponds to a input file which is open as an `ifstream`.  Read the data line-by-line into a `Vector<Datum>` and return the result. Do not read the header. _Points: 2_
- `Vector<Datum> badDataEntries(const Vector<Datum>& data) noexcept` &ndash; Return a `Vector` containing only the entries whose `total` does not match the computed total or whose `positivity` does not match the computed `positivity` to within `0.1`. _Points: 2_
- `bool goodData(const Vector<Datum>& data) noexcept` &ndash; Returns `true` if there is no bad data, i.e. if `badDataEntries(data).empty()` is `true`. Returns `false` otherwise. _Points: 2_

## Turn In
Submit the modified `Datum.cpp`, `Datum.h` and `Vector.h` to Gradescope. In general, submit everything except `main.cpp`.
