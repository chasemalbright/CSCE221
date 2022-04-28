# Linked Lists
In this assignment, you will program a Doubly Linked List class called `List` which parodies the [`std::list`](https://en.cppreference.com/w/cpp/container/list) class inherent to the Standard Template Library (STL) in C++.

Topics:

- Allocation (`new`) and Deallocation (`delete`)
- Stack and Heap Memory
- Bidirectional Iterators
  - Simplification of Random Access Iterators

The difficulty of the assignment is very close to that of the `Vector` assignment. You do not need to write as many functions, but there is much more nuanced work with the inner class `List::Node`.
## Getting started
Download this code by running the following command in the directory of your choice:
```sh
git clone https://github.tamu.edu/csce221/assignment-list.git && cd assignment-list
```
[OPTIONAL] Then set up CMake (if your editor does not do this for you):
```sh
cmake -S . -B build
```
Open the code in your editor of choice. For instance, if you use VS Code:
```sh
code .
```
*Note:* On OSX you may need to enable the `code` command in VS Code with <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>P</kbd> and typing "shell command." You can select the option to install the command, and then the above command will work.
## Assignment
### Doubly Linked List Implementation
Implement the following [constructors](https://en.cppreference.com/w/cpp/container/list/list), [destructors](https://en.cppreference.com/w/cpp/container/list/%7Elist), and assignment operators [`operator=`](https://en.cppreference.com/w/cpp/container/list/operator%3D) which include the Rule of 5:
| Signature | Description | Time Complexity | Test Names |
| :--- | :--- | :--- | ---: |
| `List();` | Default constructor. Constructs an empty container.                                             | O(1) | `constructor_default` |
| `List( size_type count, const T& value );` | Constructs the container with `count` copies of elements with value `value`.                      | O(`count`) | `constructor_insert_copies` |
| `explicit List( size_type count );` | Constructs the container with `count` default-inserted instances of `T`. No copies are made.        | O(`count`) | `constructor_default_inserted` |
| `List( const List& other );` | **Copy constructor.** Constructs the container with the copy of the contents of `other`.          | O(`other.size()`) | `constructor_copy` |
| `List( List&& other );` | **Move constructor.** Constructs the container with the contents of `other` using move semantics. | O(1) | `constructor_move` |
| `~List();` | **Destructs the List.** The destructors of the elements are called and the used storage is deallocated. Note, that if the elements are pointers, the pointed-to objects are not destroyed. | O(`size()`) | Frequently Utilized |
| `List& operator=( const List& other );` | **Copy assignment operator.** Replaces the contents with a copy of the contents of `other`.  | O(max(`size()`, `other.size()`)) | `constructor_copy` |
| `List& operator=( List&& other ) noexcept;` | **Move assignment operator.** Replaces the contents with those of `other` using move semantics (i.e. the data in `other` is moved from `other` into this container). `other` is in a valid but unspecified state afterwards.  | O(`size()`) | `operator_move` |

Click the below function names to be taken to the reference page for the function.

Implement the following functions:
| Function Name | Brief Description | Time Complexity | Test Names |
| :--- | :--- | :--- | ---: |
| [`front`](https://en.cppreference.com/w/cpp/container/list/front) | access the first element | O(1) | `terminals` |
| [`back`](https://en.cppreference.com/w/cpp/container/list/back) | access the last element | O(1) | `terminals` |
| [`begin`](https://en.cppreference.com/w/cpp/container/list/begin) | returns an iterator to the beginning | O(1) | `terminals` & Frequently Utilized |
| [`end`](https://en.cppreference.com/w/cpp/container/list/end) | returns an iterator to the end | O(1) | `terminals` & Frequently Utilized |
| [`cbegin`](https://en.cppreference.com/w/cpp/container/list/begin) | returns an const iterator to the beginning | O(1) | `terminals` & Frequently Utilized |
| [`cend`](https://en.cppreference.com/w/cpp/container/list/end) | returns an const iterator to the end | O(1) | `terminals` & Frequently Utilized |
| [`empty`](https://en.cppreference.com/w/cpp/container/list/empty) | checks whether the container is empty | O(1) | `clear_and_empty` |
| [`size`](https://en.cppreference.com/w/cpp/container/list/size) | returns the number of elements | O(1) | Frequently Utilized |
| [`clear`](https://en.cppreference.com/w/cpp/container/list/clear) | clears the contents | O(`size()`) | `clear_and_empty` |
| [`insert`](https://en.cppreference.com/w/cpp/container/list/insert) | inserts elements | O(1) | `insert` |
| [`erase`](https://en.cppreference.com/w/cpp/container/list/erase) | erases elements | O(1) | `erase` |
| [`push_back`](https://en.cppreference.com/w/cpp/container/list/push_back) | adds an element to the end | O(1) | `push_back` |
| [`pop_back`](https://en.cppreference.com/w/cpp/container/list/pop_back) | removes the last element | O(1) | `pop_back` |
| [`push_front`](https://en.cppreference.com/w/cpp/container/list/push_front) | inserts an element to the beginning | O(1) | `push_front` |
| [`pop_front`](https://en.cppreference.com/w/cpp/container/list/pop_front) | removes the first element | O(1) | `pop_front` |

Implement `List::basic_iterator` which will create `iterator` and `const_iterator` for you. Write the following functions, which are **different from those of the Random Access Iterator from `Vector`.** If you reuse that code, it will not work at all because the list iterator is a **Bidirectional Iterator.**
| Signature | Description | Time Complexity | Test Names |
| :--- | :--- | :--- | :--- |
| `basic_iterator() noexcept;` | Default Constructor. We generate it automatically for you. | O(1) | `iterator` |
| `explicit basic_iterator(Node* ptr) noexcept;` | Parameterized Constructor. Set the managed pointer to the given `Node *`. | O(1) | None |
| `reference operator*() const;` | Dereference the pointer, returning a reference to the value in the managed node. **Do not return a reference to the `Node`, but instead return a reference to its managed data.** | O(1) | Frequently Utilized |
| `pointer operator->() const;` | Return a pointer to the data managed by `Node`. | O(1) | `iterator` |
| `basic_iterator& operator++();` | **Prefix Increment.** Advance the iterator so that the managed `Node` is the next node in the list. Return a reference to this iterator. | O(1) | `iterator` & Frequently Utilized |
| `basic_iterator operator++(int);` | **Postfix Increment.** Advance the iterator so that the managed `Node` is the next node in the list. Return a copy of this iterator from before it was advanced. | O(1) | `iterator` & Frequently Utilized |
| `basic_iterator& operator--();` | **Prefix Decrement.** Retreat the iterator so that the managed `Node` is the previous node in the list. Return a reference to this iterator. | O(1) | `iterator` & Frequently Utilized |
| `basic_iterator operator--(int);` | **Postfix Decrement.** Retreat the iterator so that the managed `Node` is the previous node in the list. Return a copy of this iterator from before it was retreated. | O(1) | `iterator` & Frequently Utilized |
| `bool operator==(const basic_iterator& other) const noexcept;` | Compare two iterators and determine if they are equivalent. | O(1) | `iterator` & Frequently Utilized |
| `bool operator!=(const basic_iterator& other) const noexcept;` | Compare two iterators and determine if they are not equivalent. | O(1) | `iterator` & Frequently Utilized |

A possible implementation (followed by GCC) is to make:
```cpp
auto begin_it = begin(), end_it = end();
--begin_it; ++end_it;
begin_it == end(); // this is true
end_it == begin(); // this is true
```
Thus, the end loops back to the beginning and the beginning back to the end. **You do not have to do this, but it is an approach that you can follow to prevent Segfaults from going off the end of the list.** This form of `List` is very similar to a Circular Linked List.

#### Further Reading
- [Geeks For Geeks Doubly Linked List](https://www.geeksforgeeks.org/doubly-linked-list/)
- [Tutorials Point Double Linked List](https://www.tutorialspoint.com/data_structures_algorithms/doubly_linked_list_algorithm.htm)
- [Wikipedia Doubly Linked List](https://en.wikipedia.org/wiki/Doubly_linked_list)

### Shuffling Cards (Application of Doubly Linked List)

A standard playing card has two main pieces of information:
1. It has a Suit (Spades, Diamonds, Clubs, or Hearts)
2. It has a Number (2 - 10 inclusive) or a Face (Ace, Jack, Queen, King)
   - In many games the order is: Ace, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, and King

We provide for you a `struct Card` in [`Cards.h`](./src/Cards.h) and ask that you implement the following two functions in [`Cards.cpp`](./src/Cards.cpp):
| Signature | Description | Time Complexity | Test Names |
| :--- | :--- | :--- | :--- |
| `List<Card> buildDeck(std::ifstream file);` | Read from the file the cards and add them to a `List<Card>` in the order that they are read. |  | `build_deck` |
| `List<Card> shuffle(const List<Card>& deck);` | Return a new list with the same cards in a shuffled order described below. | O(`deck.size()`) | `shuffle` |

#### Simple Shuffling Algorithm
1. Create a new empty deck to which we will add cards as we shuffle them. We henceforth refer to this as the shuffled deck.
2. Iterate over the `deck`, and for each card, flip a coin. The coin flip must be generated using the `rand221` function in `deck.cpp` which is analogous to the [standard C function `rand()`](https://www.cplusplus.com/reference/cstdlib/rand/).
3. If the result is Heads (even), add the card to the front of the shuffled deck; otherwise, add it to the back of the shuffled deck.
4. The `deck` has been shuffled into the shuffled deck when each card has been added. Return this shuffled deck from the `shuffle` function.


## Incremental Testing
 
Unlike `Vector`, elements are not organized contiguously in `List`. This means we can't directly access elements. Instead, elements
must be accessed through the `iterator`. This impacts testing since the correctness of the `iterator` can't be tested independently of
the list itself. There are many possible ways to approach the assignment. Although, there are also many implicit dependencies in the test cases. To minimize test dependencies, we recommend you follow the ordering below. These methods listed in the below steps are explicitly required by the test cases. You may wish to write additional helper methods or implement methods in an alternative order to avoid repetition.
 
### 1. Implement the following methods:
```
explicit List( size_type count );
~List();
size_t size();
cbegin();
cend();
basic_iterator operator++(int);
basic_iterator& operator--();
reference operator*() const;
bool operator!=(const basic_iterator& other) const noexcept;
```
 
This is the minimal set of methods we need for rigorous testing. With a correct implementation these of methods, you will be able to pass the `constructor_default_inserted` test. 
 
### 2. Flesh out the `iterator`:
 
```
pointer operator->() const;
bool operator==(const basic_iterator& other) const noexcept;
basic_iterator operator--(int);
basic_iterator& operator++();
begin();
end();
```
 
After implementing these methods, you will be able to pass the `iterator` test.
 
### 3. Finish the `List`:
 
At this point, the necessary foundation should exist for you to approach the remaining tests. The functions are listed with their corresponding test cases in the table above. Most will require you to implement a single method on top of this foundation. Notable exceptions include:
 
- The `push` family of methods requires that you implement the default constructor
- `clear` and `empty` are aggregated into a single test
- `front` and `back` are tested in `terminals`
- `operator_copy_consistency` requires `insert`, `erase`, and the copy operator. This serves as a stress test to assert the copy operator leaves the objects in a valid state. The copy operator is also tested independently of `insert` and `erase` in `operator_copy`.
- `operator_move_consistency` requires `insert`, `erase`, and the move operator. Same rationale.
 
### 4. Finish the `Card.cpp` functions
 
`List` is utilized in `Card.cpp` and assumed to be in working condition. The `shuffle` test relies on the `build_deck` method.

## Run Tests
**First consult this guide: [`tests/README.md`](./tests/README.md)**

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `assignment-list` folder to accomplish what you need:

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

## Turn In
Submit the following files **and no other files** to Gradescope:
- [ ] [`Cards.cpp`](src/Cards.cpp)
- [ ] [`Cards.h`](src/Cards.h) - You may not have changed this file and that's fine
- [ ] [`List.h`](src/List.h)
