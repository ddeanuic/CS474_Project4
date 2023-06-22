# SPL Interpreter written in C++

C++ Program that interprets certain .spl commands and linked list operations:

arg: (String)
NEWID - Creates an empty new variable.

arg: (Integer) 
ASSIGN - Assigns a value to a variable.

arg: (Integer, Linked List (vice versa)), (Integer, Integer), (Linked List, Linked List)
COMBINE - Combines linked lists on integers into a linked list.

arg: (Variable1, Variable2)
COPY - Copies the value of one variable to another.

arg: (Linked List) or (Node)
HEAD - Returns the head of a list. Head of list can be another Linked List.

arg: (Linked List) or (Node)
TAIL - Returns the tail of a list. Tail of list can be another Linked List.

arg: (Integer)
CHS - Inverts the sign of an integer value.

arg: (Integer 1, Integer 2)
ADD: Adds integer value of Integer 2 to integer value of Integer 1.

