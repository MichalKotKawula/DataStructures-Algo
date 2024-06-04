A Trie (pronounced "Try") is a Tree based data structure that helps implement functionalities such as autocomplete. It is used to provide a lookups for words in a dictionary. However instead of storing the words as words, a Trie will store each of the characters of the words into nodes with a terminal marker to indicate the completion of a word. Any word with the same prefix will share the nodes of the prefix.

Aside from a skeleton class declaration, you will find a function that will return a number that maps a character to a number from 0 to 25. Thus the function will return:

'a' or 'A' returns 0
'b' or 'B' returns 1
'c' or 'C' returns 2 ...
