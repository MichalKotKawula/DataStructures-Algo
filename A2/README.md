The Table class is a templated abstract base class. That is, it describes the functionalities of a Table but does not implement any part of it. It is up to classes derived from the Table to implement the Table itself. This section describes the interfaces (ie the operations) of a Table. The specifics of the implementation (ie is it a hash table or a sorted array? what collision resolution method is used etc.) is all done in the derived classes.

The records for this table consists of key-value pairs. The key is a c++ string. The value can be any data type (T) that supports the following:

assignment (=)
instantiation without arguments (you can declare variables of type T, the value of which is undefined)
In the description below the word Record refer to a key-value pair. The way you store it (whether you make a template struct called Record with a data member for key and value, or you store them separately in parallel structures is entirely up to you).


A hash table organizes the records as an array, where records are placed according to a hash value that you get from a hash function. Please use the hash function from the C++ STL. You can find more info about how to do it here:

You will implement two hash tables for this assignment. One will use linear probing for collision resolution, the other will use chaining.
