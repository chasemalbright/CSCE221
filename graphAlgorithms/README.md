# Graph Algorithms
In this assignment, the Graph data structure is provided. We also provide many helper functions. The only four functions you have to write are:

- Topological Sort
  - `computeIndegree`
  - `topologicalSort`
- Dijkstra's Algorithm
  - `relax`
  - `dijkstrasAlgorithm`

Pseudocode for these functions is provided below. (Search for `PSEUDOCODE` using your browser!)

This is intended to be a fairly easy Programming Assignment to end the semester, but there are a few new concepts which we will describe below.

### `std::unordered_set`
This is similar to a `std::unordered_map`, but where a map maintains key-value pairs, the set maintains only keys. Its role is to add and remove element quickly and to quickly determine whether an element is present in the set.

It is used in Dijkstra's algorithm to manage the set of visited nodes `s`.

### `std::optional`
This type is a container that can either have an object or will not have anything. We fill the optionals with nothing (`std::nullopt`) and then can replace that data with `value_type<T>` as part of the `relax` function.

Useful functions for optionals are:
```cpp
std::optional o; // optional
// ... do domething with o
if (o.has_value()) // returns true if o has a value
o.value() // fetch the value from o, fails if no value
```

## Getting started

Download this code by running the following command in the directory of your choice:
```sh
git clone https://github.tamu.edu/csce221/assignment-graph-algorithms.git && cd assignment-graph-algorithms
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
The assignment provides you with a working `WeightedGraph` data structure, which you can use to complete the two tasks:
- [Implement Topological Sort](#implement-topological-sort) &ndash; Medium Difficulty
- [Implement Dijkstra's Algorithm](#implement-dijkstras-algorithm) &ndash; Hard Difficulty

### Understand Weighted Graph
#### Types

| Type | Alias | Description |
| ---- | ----- | ----------- |
| `value_type` | `T` | The values stored in the vertices. Commonly used in the functions you'll write. |
| `weight_type` | `int` | The type for edge weights. This is `int` for all graphs by default. The only requirement is that it is numeric. |
| `vertex_type` | `const value_type` | The type for vertices. It's a `const` form of `value_type`. Because of it being `const`, you can't use it for most of the functions you write. Use `value_type` instead. |
| `edge_type` | `std::pair<vertex_type, weight_type>` | A type for edges. The edges are really key value pairs within the adjacency list map, and I never used this type alias but it's here if you want it. |
| `adjacency_list` | `std::unordered_map<value_type, weight_type>` | The type of the adjacency list for a given source vertex. We use a `map` to associate destination vertices (`value_type`) to the weight (`weight_type`) of the edge connecting from the source. |
| `container_type` | `std::unordered_map<value_type, adjacency_list>` | The type of the container that manages the vertices (`value_type`) and their associated ajacency lists (`adjacency_list`). We use a `map` to handle the association. |
| `size_type` | `typename container_type::size_type` | We steal `size_type` from the `container`. It is likely `std::size_t` in most cases. |
| `iterator` | `typename container_type::iterator` | Our main iterator which allows us to check the vertices and/or adjacency lists is the iterator for the `container`. |
| `const_iterator` | `typename container_type::const_iterator` | We also get the `const_iterator` from the container. |
| `edge_iterator` | `typename adjacency_list::iterator` | We define an `edge_iterator` which allows us to iterate over all of the edges from a given source node. In other words, we iterate over every entry in the adjacency list for a given vertex. |
| `const_edge_iterator` | `typename adjacency_list::const_iterator` | We also get the `const_edge_iterator` which behaves similarly. |

These types were redefined in the [`graph-types.h`](src/graph-types.h) header. To use them from the header, write the type's name and supply a template argument. For example, `value_type<int>` or `weight_type<T>`.

#### Methods

```cpp
bool empty() const
```

**Description**: Determine whether the vertex set is empty.

**Parameters**: *None*

**Returns**:
- `true` if there are no vertices (and thus, no edges)
- `false` otherwise

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
bool empty(const vertex_type& vertex) const
```

**Description**: Determine whether the adjacency list associated with `vertex` is empty.

**Parameters**:
- `vertex` a vertex in the graph to test

**Returns**:
- `true` if there are no edges sourced from that vertex
- `false` otherwise

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
size_type size() const
```

**Description**: Get the size of the vertex set.

**Parameters**: *None*

**Returns**: the number of vertices in the graph

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
size_type size(const vertex_type& vertex) const
```

**Description**: Get the size of the adjacency list associated with `vertex`.

**Parameters**:
- `vertex` a vertex in the graph to test

**Returns**: the number of edges in the graph that start at `vertex`

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const adjacency_list& at(const vertex_type& vertex) const
```

**Description**: Get constant access to the adjacency list of `vertex`.

**Parameters**:
- `vertex` a vertex in the graph to access

**Returns**: a constant reference to the adjacency list for vertex `vertex`

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
std::pair<iterator, bool> push_vertex(const vertex_type& vertex)
```

**Description**: Adds `vertex` to the vertex set if it is not already there.

**Parameters**:
- `vertex` a vertex to add to the graph

**Returns**:
- an `iterator` to the inserted vertex, or existing vertex if the vertex already existed
- `true` if the `vertex` was just inserted for the first time
- `false` if the `vertex` already existed in the graph

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
size_type pop_vertex(vertex_type& vertex)
```

**Description**: Removes `vertex` from the vertex set if it exists and from the adjacency lists of all other vertices in the set if it exists in their lists.

**Parameters**:
- `vertex` a vertex to remove from the graph

**Returns**: the sum of the number of edges to `vertex` and the number of vertices with label `vertex` that existed in graph prior to removing `vertex`

**Throws**: *None*

**Time Complexity**: *O(n)* &ndash; Linear Time (Average Case); *O(nm)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
std::pair<edge_iterator, bool> push_edge(const vertex_type& source, const vertex_type& destination, const weight_type& weight)
```

**Description**: Adds a given edge to the graph if no such edge already exists between `source` and `destination`.

**Parameters**:
- `source` a vertex in the graph at which the edge will begin
- `destination` a vertex at which the edge will end (need not yet exist in the graph)
- `weight` the weight of the newly created edge

**Returns**:
- an `iterator` to the inserted edge within the adjacency list of source, or existing edge if the edge already existed
- `true` if the edge was just inserted for the first time
- `false` if the vertex already existed in the graph

**Throws**:
- `std::out_of_range` if `source` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average Case); *O(n+m)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
size_type pop_edge(const vertex_type& source, const vertex_type& destination)
```

**Description**: Removes the given edge from the graph it exists.

**Parameters**:
- `source` a vertex in the graph at which the edge will begin
- `destination` a vertex at which the edge will end (need not exist in the graph)

**Returns**:
- `0` if the edge did not exist in the graph
- `1` if the edge existed in the graph

**Throws**:
- `std::out_of_range` if `source` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average Case); *O(n+m)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
iterator begin()
```

**Description**: Gets a `iterator` to the beginning of the vertex set.

**Parameters**: *None*

**Returns**: `iterator` to the beginning vertex in the graph. This could be any given vertex within the graph, because `unordered_map` can order the vertices however it likes.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator begin() const
```

**Description**: Gets a `const_iterator` to the beginning of the vertex set.

**Parameters**: *None*

**Returns**: `const_iterator` to the beginning vertex in the graph. This could be any given vertex within the graph, because `unordered_map` can order the vertices however it likes.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator cbegin() const
```

**Description**: Gets a `const_iterator` to the beginning of the vertex set.

**Parameters**: *None*

**Returns**: `const_iterator` to the beginning vertex in the graph. This could be any given vertex within the graph, because `unordered_map` can order the vertices however it likes.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
iterator end()
```

**Description**: Gets an `iterator` to the end of the vertex set.

**Parameters**: *None*

**Returns**: `iterator` past the last vertex in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator end() const
```

**Description**: Gets a `const_iterator` to the end of the vertex set.

**Parameters**: *None*

**Returns**: `const_iterator` past the last vertex in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
const_iterator cend() const
```

**Description**: Gets a `const_iterator` to the end of the vertex set.

**Parameters**: *None*

**Returns**: `const_iterator` past the last vertex in the graph. This is the same `cend` iterator we've seen for `unordered_map`.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
edge_iterator begin(const vertex_type& vertex)
```

**Description**: Gets an `edge_iterator` to the beginning of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `edge_iterator` to the beginning of the adjacency list for `vertex` in the graph. This could be any given edge within the list, because `unordered_map` can order the edges however it likes.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator begin(const vertex_type& vertex) const
```

**Description**: Gets a `const_edge_iterator` to the beginning of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` to the beginning of the adjacency list for `vertex` in the graph. This could be any given edge within the list, because `unordered_map` can order the edges however it likes.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator cbegin(const vertex_type& vertex) const
```

**Description**: Gets a `const_edge_iterator` to the beginning of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` to the beginning of the adjacency list for `vertex` in the graph. This could be any given edge within the list, because `unordered_map` can order the edges however it likes.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
edge_iterator end(const vertex_type& vertex)
```

**Description**: Gets an `edge_iterator` to the end of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `edge_iterator` past the last edge in the adjacency list of `vertex` in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator end(const vertex_type& vertex) const
```

**Description**: Gets a `const_edge_iterator` to the end of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` past the last edge in the adjacency list of `vertex` in the graph. This is the same `end` iterator we've seen for `unordered_map`.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
const_edge_iterator cend(const vertex_type& vertex) const
```

**Description**: Gets a `const_edge_iterator` to the end of `vertex`'s adjacency list.

**Parameters**:
- `vertex` a vertex in the graph to examine

**Returns**: `const_edge_iterator` past the last edge in the adjacency list of `vertex` in the graph. This is the same `cend` iterator we've seen for `unordered_map`.

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(1)* &ndash; Constant Time (Average); *O(n)* &ndash; Linear Time (Worst Case)
- *n* is the number of vertices

----

```cpp
void clear()
```

**Description**: Clears every vertex and its corresponding adjacency list from the graph. Resets the graph to an empty state.

**Parameters**: *None*

**Returns**: *None*

**Throws**: *None*

**Time Complexity**: *O(nm)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
void clear(const vertex_type& vertex)
```

**Description**: Clears every edge from the adjacency list of `vertex`. Resets the adjacency list of `vertex` to an empty state.

**Parameters**:
- `vertex` a vertex in the graph to test

**Returns**: *None*

**Throws**:
- `std::out_of_range` if `vertex` is not in the graph

**Time Complexity**: *O(n+m)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
template <typename T>
std::ostream &operator<<(std::ostream &o, const WeightedGraph<T> &graph)
```

**Description**: Prints `graph` to `o`.

**Parameters**:
- `o` stream to receive the graph
- `graph` the graph to print

**Returns**: `o` to be used for stream chaining: `std::cout << graph << std::endl;`

**Throws**: *None*

**Time Complexity**: *O(nm)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
template <typename T>
std::istream &readEdge(std::istream &i, value_type<T> &vertex, weight_type<T> &weight)
```

**Description**: Reads `vertex` and `weight` from `i`.

**Parameters**:
- `i` stream to read the edge from
- `vertex` the vertex to save
- `weight` the weight to save

**Returns**: `i` to be used for stream chaining.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
template <typename T>
std::istream &operator>>(std::istream &i, WeightedGraph<T> &graph)
```

**Description**: Reads `graph` from `i`.

**Parameters**:
- `i` stream to read the graph from
- `graph` the graph to save

**Returns**: `i` to be used for stream chaining.

**Throws**: *None*

**Time Complexity**: *O(nm)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

### Implement Topological Sort

#### Helpers

```cpp
template <typename T>
void computeIndegrees(const WeightedGraph<T>& graph, std::unordered_map<value_type<T>, int>& indegrees)
```

**Description**: Associates the `indegrees` for each vertex in the `graph` with the values for the indegrees.

**Parameters**:
- `graph` graph to compute from
- `indegrees` the mapping of a vertex to its indegree 

**Returns**: *None*

**Throws**:
- Possibly `std::out_of_range` if the `graph` is malformed

**Time Complexity**: *O(nm)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

**Pseudocode**:
```py
for vertex in graph:
    indegree[vertex] = 0

for adj_list in graph:
    for vertex in adj_list:
        indegree[vertex] += 1
```

#### Topological Sort

```cpp
template <typename T>
std::list<value_type<T>> topologicalSort(const WeightedGraph<T>& graph)
```

**Description**: Creates a list of vertices in a valid, topological order if one exists. If not such ordering exists (perhaps because of a cycle), then it returns an empty list.

**Parameters**:
- `graph` graph to compute a topological ordering

**Returns**: List of vertices in a valid topological ordering

**Throws**:
- Possibly `std::out_of_range` if the `graph` is malformed

**Time Complexity**: *O(nm)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

**Pseudocode**:
```py
q = [] # Queue
l = [] # List

q.extend([v for v in graph if indegree[v] == 0])

while len(q) > 0:
    v = q.pop(0) # remove first
    l.append(v)

    for adj_v in v.adj_list:
        indegree[adj_v] -= 1
        if indegree[adj_v] == 0:
            q.push(adj_v)

if len(l) != len(graph):
    l.clear()

return l
```

### Implement Dijkstra's Algorithm

#### Helpers

```cpp
template <typename T>
weight_type<T> infinity()
```

**Description**: Gets the largest possible (infinite) weight. `weight_type<T>` must always be numeric or this fails to compile.

**Parameters**: *None*

**Returns**: Infinite Weight Value.

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

----

```cpp
template <typename T>
void initializeSingleSource(const WeightedGraph<T>& graph, vertex_type<T> initial_node,
std::unordered_map<value_type<T>, weight_type<T>>& distances,
std::unordered_map<value_type<T>, std::optional<value_type<T>>>& predecessors)
```

**Description**: Sets all distances to infinity except the initial node which is set to 0. Also sets all predecessors to `nullopt`. This indicates that there are no predecessors initially.

**Parameters**:
- `graph` the graph to initialize the distances
- `initial_node` the first node in the graph to source the search from
- `distances` the mapping of vertices to their distances from the source
- `predecessors` a lookup table telling the predecessor to the current node along the shortest path from the source

**Returns**: *None*

**Throws**: *None*

**Time Complexity**: *O(nm)* &ndash; Linear Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

----

```cpp
template <typename T>
class DijkstraComparator
```

**Description**: Compares two vertices by their distance from the source vertex.

----

```cpp
template <typename T>
void updateHeap(std::priority_queue<value_type<T>, std::vector<value_type<T>>, DijkstraComparator<T>>& q,
std::unordered_map<value_type<T>, weight_type<T>>& distances)
```

**Description**: Reorders the heap based on changes to the distances after relaxation.

**Parameters**:
- `q` the priority queue to reorganize
- `distances` the mapping of vertices to their distances from the source

**Returns**: *None*

**Throws**: *None*

**Time Complexity**: *O(n)* &ndash; Linear Time
- *n* is the queue size

----

```cpp
template <typename T>
bool relax(value_type<T> u, value_type<T> v, weight_type<T> w,
std::unordered_map<value_type<T>, weight_type<T>>& distances,
std::unordered_map<value_type<T>, std::optional<value_type<T>>>& predecessors)
```

**Description**: Relaxes the edge from `u` to `v` given `w` and the distances. If the relaxation occurs, the `distances` and `predecessors` are updated.

**Parameters**:
- `u` the node at the start of the edge
- `v` the node at the end of the edge
- `w` the weight of the edge from `u` to `v`
- `distances` the mapping of vertices to their distances from the source
- `predecessors` the mapping of vertices to their predecessors along the shortest path from the source

**Returns**:
- `true` the edge was relaxed
- `false` otherwise

**Throws**: *None*

**Time Complexity**: *O(1)* &ndash; Constant Time

**Pseudocode**:
```py
if distance[v] > distance[u] + w:
    distance[v] = distance[u] + w
    predecessor[v] = u
    return True

return False
```

#### Dijkstra's Algorithm

```cpp
template <typename T>
std::list<value_type<T>> dijkstrasAlgorithm(const WeightedGraph<T>& graph, vertex_type<T> initial_node, vertex_type<T> destination_node)
```

**Description**: Performs [Dijkstra's Algorithm](https://canvas.tamu.edu/courses/136654/files/35930572/preview) (Slide 16) on `graph` starting at `initial_node` and returns a list with every node visited along the path from `initial_node` to `destination_node`.

**Parameters**:
- `graph` graph to find a path through
- `initial_node` the starting node in the graph
- `destination_node` the ending node in the graph

**Returns**: A list of all of the vertices along the shortest path from `initial_node` to `destination_node` or an empty list if no path exists.

**Throws**:
- `std::out_of_range` if either `initial_node` or `destination_node` are not in `graph`.

**Time Complexity**: *O(nm log(nm))* &ndash; Polynomial Time
- *n* is the number of vertices
- *m* is the average number of edges in each adjacency list

**Pseudocode**:
```py
initializeSingleSource(graph, initial_node)
s = [] # Set
q = [] # Priority Queue
q.extend([v for v in graph])

while len(q) > 0:
    u = min(q)
    q.remove(u)
    if u not in s:
        s.append(u)
    for pair in u.adj_list:
        v = pair.first
        if v in s:
            continue
        w = pair.second
        r = relax(u, v, w)
        if r:
            updateHeap(q)

if predecessor[destination_node] is None:
    return []

l = [] # List

node = destination_node
while predecessor[node] is not None:
    l.append(node)

l.append(initial_node)
return l
```

### Further Reading
#### Topological Sort
- [Topological sorting - Wikipedia](https://en.wikipedia.org/wiki/Topological_sorting)
- [Topological sorting - GeeksforGeeks](https://www.geeksforgeeks.org/topological-sorting/)

#### Dijkstra's Algorithm
- [Dr. Leyk's Slides](https://canvas.tamu.edu/courses/136654/files/35930572/preview)
- [Dijkstra's algorithm - Wikipedia](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
- [Dijkstra's algorithm - GeeksforGeeks](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/)


### Application of Graphs & Graph Algorithms
Graphs are not commonly used directly by programmers to solve problems but properties of graphs are often used. You will learn much more about graphs in CSCE 411 - Design and Analysis of Algorithms.

## Run Tests

**First consult this guide: [`tests/README.md`](./tests/README.md)**

To run the tests, you need to rename [`main.cpp`](./src/main.cpp) or you need to rename the `int main` function within that file.

Execute the following commands from the `assignment-unordered-map` folder to accomplish what you need:

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


## Incremental Testing:



## Turn In

Submit the following file **and no other files** to Gradescope:
- [ ] [`dijkstras-helpers.h`](src/dijkstras-helpers.h)
- [ ] [`top-sort-helpers.h`](src/top-sort-helpers.h)
- [ ] [`graph-algorithms.h`](src/graph-algorithms.h)
