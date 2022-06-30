# CS300 - Data Structures Assignments


This repository contains the codes I wrote for the assignments given in the CS300 Data Structures course given at Sabanci University in the 2021-2022 Spring semester. The detailed description file of all assignments can be viewed from the relevant folders.

Concepts used in the assignments:
* Linked Lists
* Stacks, Queues
* Binary Search Trees
* AVL Trees, Tree Traversals
* Hash Tables
* Insertion Sort, Shell Sort,Heap Sort, Merge Sort, Quick Sort
* Complexity Analysis


### Maze

In the first assignment, you will implement a program which will generate a random maze of size MxN,
where M represents the number of rows, and N represents the number of columns. Then, you will also
need to implement a function which will find the path between designated entry and exit points in a given
maze. You are required to implement a Stack using a LinkedList data structure, and the stack class is a template-based class. 

### Notebook

In the second assignment, you will implement two “Notebooks” by using the AVL Search Tree and the
Binary Search Tree (BST). Additionally, you will display the speed of some of the operations on
these tree data structures that are used for the implementation. Each “Notebook” will have a
nested tree structure, which will be explained in more detail in the corresponding folder.

### Search Engine

In the third assignment, you will write a search engine. Additionally, you will compare the speed of
two different data structures for your search engine architecture. The search engines in real life
search hundreds of millions web pages to see if they have the words that you have typed, and
they can do this for thousands of users at a given time. In order to do these searches really fast,
search engines such as Google do a lot of what we call preprocessing of the pages they search;
that is, they transform the contents of a web page (which for the purposes of this homework,
we will assume it consists of only strings) into a structure that can be searched very fast.
In this homework, you are going to preprocess the documents provided to you. For each unique
word, you will insert a node into both of your data structures, i.e. Binary Search Tree (BST) and
Hash Table. Of course, you will also keep track of the details such as the document name which
the word appears in and the number of times the word appears in each document. So, you need
to implement a templated BST and Hash Table.

### PhoneBook

In the fourth assignment, you are given an unsorted PhoneBook and asked to sort it in alphabetical
order. You will compare the given 4 Sorting algorithms and conclude which one is faster. Also, since
fundamental usage of a PhoneBook is search for some names, you are expected to implement 2
search algorithms to compare.
