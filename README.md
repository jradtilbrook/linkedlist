# Linked List [![Build Status](https://travis-ci.org/jradtilbrook/linkedlist.svg?branch=master)](https://travis-ci.org/jradtilbrook/linkedlist)
A linked list library written in `C` adhering to C89. This library prioritises readability over efficiency and aims to be easy to use and as unrestrictive as possible.

This library does everything the glibc implementation can do, with some extra functionality (such as logging) and aims to be easier to use.

## Functionality
This linked list library aims to provide the following functionality:
- [x] Singly linked,
- [x] Single ended,
- [ ] Doubly linked,
- [ ] Double ended,
- [ ] ~~XOR linked (possibly?),~~
- [x] Allow the use of any data type for storage,
- [ ] Search/add/delete by index,
- [ ] Search/add/delete by element comparison,
- [ ] Delete duplicates,
- [ ] Using `const` wherever possible to ensure pointer security,
- [ ] Adding an array of elements to a list,
- [ ] Converting a list to an array,
- [ ] User enabled logging to `stderr` (with colour),
- [ ] Use multiple returns if it lessens nested `if`'s and makes more readable,
- [ ] Negative indexing,
- [ ] Unlink a node = remove from list without freeing (return the node),
- [ ] Call a function for each node in the list,
- [ ] Shallow and deep copying,
- [ ] List reversal,
- [ ] List sorting (on insertion and afterwards),
- [ ] Joining two lists

**Note:** More functionality will be added as the library is developed.

## Dependencies
Uses `cmocka` for unit testing. This can be installed from the official Ubuntu
repositories or from source. Check out the [documentation](https://cmocka.org/)
for more details.

## To-Do List
- [ ] Continuously update README to document functionality.
- [ ] Build documentation (with doxygen?) and host on github (gh-pages branch)
- [ ] Code internal (static) convenience functions for creation/traversing, etc.
- [ ] Consolidate the code style, naming and conventions.
- [ ] Phase 1:
    - [ ] Singly linked.
    - [ ] Single ended.
    - [ ] Internal storage.
    - [ ] Search/add/delete by index.
- [ ] Phase 2:
    - [ ] Add `const` to pointers to ensure security.
    - [ ] Add doubly linked.
    - [ ] Add double ended.
    - [ ] Function to add array of elements to list.
- [ ] Phase 3:
    - [ ] Search/add/delete by data.
    - [ ] Allow any datatype.
    - [ ] Allow for internal and external storage.
- [ ] Phase 4:
    - [ ] XOR linked.
