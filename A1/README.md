
CacheList
The basic class declarations can be found in a1q1.h. Please use it as a starting point. You are welcome to add whatever private/protected members you see fit to it.

Write the following linked list called CacheList, along with const_iterator and iterator for the list. This type of linked lists ensures that nodes that have been most often accessed are placed at the front of the linked list so that they are quickly found.

The CacheList is a templated linked list where each node stores an instance of an unspecified data type (called T below), and an access counter. This linked list must be doubly linked and perform operations as described. Other than this the specifics of the implementation is left up to you.

You may assume the following operators are valid for the unspecified data type (T):

==
!=
=
This means you can compare two instances of T using == and !=. You can also assign using the assignment operator.

In the description below, front/back refers to the first node that contains data, and the last node that contains data respectively. Any reference to first/last node refers to the first/last node that contains data.

The algorithm for determining the candidate is as follows:

Go through each pair of values in the array (array[0] and array[1], then array[2] and array[3], etc.)
for each pair, if the numbers are the same, keep one of them for the next iteration. If the numbers are different, keep neither of them.
the majority element candidate in this new array is the same as the majority element candidate in the old array.
if there is an odd number of values in the array, the last value in the array that is not part of a pair is the candidate IF a candidate could not be determined by the first portion of the array (see example 2)
