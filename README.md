# Generic-Singly-Linked-List
Project is a C++ implementation of a robust, templated, singly linked list.

C++ singly linked list data structure where nodes are created to store generic
(templated) data and a pointer to the next node in the list.
        1         2         3         5          5
ex. [NULL|2]->[elem|3]->[elem|4]->[elem|4]->[elem|NULL]

Header file fully implements rule of 5 for managing heap memory including:
defined Copy Constructor, Copy Move Constructor, Assignment Operator overload,
Assignment Move Operator overload, and destructor. 

Also implements many functions and operator overloads for managing/using singly
linked list.
