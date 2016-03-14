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
