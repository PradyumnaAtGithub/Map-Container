CS540 - Advanced Topics in Object Oriented Programming
Assignment - 2
Problem: MAP CONTAINER

Name: Pradyumna Kaushik
-------------------------------------------------------

g++ Version
-----------
This code is compatible with g++ version 5.2.0

Compilation and Execution
-------------------------
Compile the program using the following command
g++ test.cpp -o test.o -std=c++11 -ldl -Wall -Wextra -pedantic

Run the program using the following command
./test.o

Implementation Details
----------------------
I have used a Skip List to store the ValueTypes

Template and Member type
------------------------
Template: template <typename Key_T, typename Mapped_T> class Map;
Type Member: std::pair <const Key_T, Mapped_T>

Constructors, Operators and Functions for Map
----------------------------------------------
Map()  :  Creates empty map.

Map(const Map &)  :  Copy constructor.

Map& operator=(const Map &)  :  Copy assignment operator.

Map(std::initializer_list<std::pair<const Key_T, Mapped_T>>)  :  Initializer list constructor.

~Map()  :  Destructor.

size_t size() const  :  Returns number of elements in map.

bool empty() const  :  Returns true if map is empty, false otherwise.

Iterator begin()  :  Returns an Iterator pointing to the first element, in order.

Iterator end()  :  Returns an Iterator pointing to one past the last element, in order.

ConstIterator begin() const  :  Returns a ConstIterator pointing to the first element, in order.

ConstIterator end() const  :  Returns a ConstIterator pointing to one past the last element, in order.

ReverseIterator rbegin()  :  Returns a ReverseIterator to the first element in reverse order, which is the last element in normal order.

ReverseIterator rend()  :  Returns a ReverseIterator pointing to one past the last element in reverse order which is one before the first element in normal order.

Iterator find(const Key_T&)  :  Returns an iterator to the given key. If key not found then it returns the end() iterator.

ConstIterator find(const Key_T&) const  :  Returns a const iterator to the given key. If key not found then it returns the end() iterator.

Mapped_T &at(const Key_T &)  :  Returns a reference to the mapped object at the specified key. If key not found, throws std::out_of_range.

const Mapped_T& at(const Key_T&) const  :  Returns a const reference to the mapped object at the specified key. If key not found, throws std::out_of_range.

Mapped_T& operator[](const Key_T&)  :  If key is in the map, return a reference to the corresponding mapped object. If not, value initializes a mapped object for that key and returns a reference to it.

std::pair<Iterator, bool> insert(const ValueType &)  :  Inserts given pair into the map. If key not already present, it returns an iterator pointing to the new element and true. If key already exists, no insertion is performed nor is the mapped object changed, and it returns an iterator pointing to the element with the same key and false.

template <typename IT_T>
	void insert(IT_T range_beg, IT_T range_end)  :  Inserts given object or range of objects into the map.

void erase(Iterator pos)  :  Removes the given object from the map.

void erase(const Key_T&)  :  Removes the given object from the map. Throws std::out_of_range if key not found.

bool operator==(const Map &, const Map &)  :  Checks whether 2 map objects are equal by comparing all the elements.

bool operator!=(const Map &, const Map &)  :  Checks whether 2 map objects are not equal. works contradictory to the equality check.

bool operator<(const Map &, const Map &)  :  Checks whether map, given by first argument, is less than the map, given by the second argument, using lexicographical sorting.

Constructors, Operators and Functions for Iterator
---------------------------------------------------
Iterator(const Iterator &)  :  copy constructor

~Iterator()  :  Destructor

Iterator& operator=(const Iterator &)  :  Assignment operator

Iterator &operator++()  :  Pre-increment operator. Iterator moves to the next element, in order and a reference to the iterator is returned. If pointing to the last element then undefined behavior.

Iterator operator++(int)  :  Post-increment operator. Iterator moves to the next element, in order and a reference to the previous state of the iterator is returned. If pointing to the last element then undefined behavior.

Iterator &operator--()  :  Pre-decrement operator. Iterator moves to the previous element, in order and a reference to the iterator is returned. if pointing to the first element then undefined behavior.

Iterator &operator--(int)  :  Post-decrement operator.Iterator moves to the previous element, in order and a reference to the previous state of the iterator is returned. if pointing to the first element then undefined behavior.

ValueType &operator*() const  :  Returns reference to the std::pair<Key_T, Mapped_T> object container in this element. If the iterator is pointing to the end, the behavior is undefined.

ValueType *operator->() const :  Special member access operator for the element. If the iterator is pointing to the end, the behavior is undefined.

Constructors, Operators and Functions for ConstIterator
--------------------------------------------------------
ConstIterator(const ConstIterator &)  :  Copy constructor.

~ConstIterator()  :  Destructor.

ConstIterator& operator=(const ConstIterator &)  :  Assignment operator.

ConstIterator &operator++()  :  Pre-increment operator. ConstIterator moves to the next element, in order and a reference to the const iterator is returned. If pointing to the last element then undefined behavior.

ConstIterator operator++(int)  :  Post-increment operator. ConstIterator moves to the next element, in order and a reference to the previous state of the const iterator is returned. If pointing to the last element then undefined behavior.

ConstIterator &operator--()  :  Pre-decrement operator. ConstIterator moves to the previous element, in order and a reference to the const iterator is returned. if pointing to the first element then undefined behavior.

ConstIterator &operator--(int)  :  Post-decrement operator. ConstIterator moves to the previous element, in order and a reference to the previous state of the const iterator is returned. if pointing to the first element then undefined behavior.

const ValueType &operator*() const  :  Returns const reference to the std::pair<Key_T, Mapped_T> object container in this element. If the const iterator is pointing to the end, the behavior is undefined.

const ValueType *operator->() const  :  Special member access operator for the element. If the const iterator is pointing to the end, the behavior is undefined.

Constructors, Operators and Functions for ReverseIterator
----------------------------------------------------------
ReverseIterator(const ReverseIterator &)  :  Copy constructor

~ReverseIterator()  :  Destructor

ReverseIterator& operator=(const ReverseIterator &)  :  Assignment operator

ReverseIterator &operator++()  :  Pre-increment operator. ReverseIterator moves to the next element, in reverse order and a reference to the reverse iterator is returned. If pointing to the last element then undefined behavior.

ReverseIterator operator++(int)  :  Post-increment operator. ReverseIterator moves to the next element, in reverse order and a reference to the previous state of the reverse iterator is returned. If pointing to the last element then undefined behavior.

ReverseIterator &operator--()  :  Pre-decrement operator. ReverseIterator moves to the previous element, in reverse order and a reference to the reverse iterator is returned. if pointing to the first element then undefined behavior.

ReverseIterator &operator--(int)  :  Post-decrement operator. ReverseIterator moves to the previous element, in reverse order and a reference to the previous state of the reverse iterator is returned. if pointing to the first element then undefined behavior.

ValueType &operator*() const  :  Returns reference to the std::pair<Key_T, Mapped_T> object container in this element. If the reverse iterator is pointing to the end, the behavior is undefined.

ValueType *operator->() const  :  Special member access operator for the element. If the reverse iterator is pointing to the end, the behavior is undefined.

Comparison operators for Iterators, ConstIterators and ReverseIterators
-------------------------------------------------------------------------
bool operator==(const Iterator &, const Iterator &)
bool operator==(const ConstIterator &, const ConstIterator &)
bool operator==(const Iterator &, const ConstIterator &)
bool operator==(const ConstIterator &, const Iterator &)
bool operator!=(const Iterator &, const Iterator &)
bool operator!=(const ConstIterator &, const ConstIterator &)
bool operator!=const Iterator &, const ConstIterator &)
bool operator!=const ConstIterator &, const Iterator &)
bool operator==(const ReverseIterator &, const ReverseIterator &)
bool operator!=(const ReverseIterator &, const ReverseIterator &)

Memory Leaks
------------
There are no memory leaks and here in the valgrind output (1000 iteration of test1.cpp):-

==3560==     in use at exit: 72,704 bytes in 1 blocks
==3560==   total heap usage: 9,925 allocs, 9,924 frees, 1,454,328 bytes allocated
==3560==
==3560== LEAK SUMMARY:
==3560==    definitely lost: 0 bytes in 0 blocks
==3560==    indirectly lost: 0 bytes in 0 blocks
==3560==      possibly lost: 0 bytes in 0 blocks
==3560==    still reachable: 0 bytes in 0 blocks
==3560==         suppressed: 72,704 bytes in 1 blocks
==3560==
==3560== For counts of detected and suppressed errors, rerun with: -v
==3560== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 3 from 3)

Reference:
----------
https://en.wikipedia.org/wiki/Skip_list
http://www.sanfoundry.com/cpp-program-implement-skip-list/
http://www.drdobbs.com/cpp/skip-lists-in-c/184403579
