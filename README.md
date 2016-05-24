# Linked List [![Build Status](https://travis-ci.org/jradtilbrook/linkedlist.svg?branch=master)](https://travis-ci.org/jradtilbrook/linkedlist)
A linked list library written in `C` adhering to C89. This library prioritises readability over efficiency and aims to be as easy to use and as transparent as possible.

## Functionality
This linked list library aims to provide the following functionality:
- [ ] Singly linked,
- [ ] Single ended,
- [ ] Doubly linked,
- [ ] Double ended,
- [ ] ~~XOR linked (possibly?),~~
- [x] Allow the use of any data type for storage,
- [x] Search/add/delete by index,
- [x] Search/add/delete by element comparison,
- [ ] Using `const` wherever possible to ensure pointer security,
- [ ] Adding an array of elements to a list,
- [ ] Converting a list to an array,
- [ ] User enabled logging to `stderr` (with colour),
- [ ] Use multiple returns if it lessens nested `if`'s and makes more readable
- [ ] Negative indexing

**Note:** More functionality will be added as the library is developed.

## Dependencies
Uses `check` for unit testing. This can be installed from the official Ubuntu
repositories. Check out the [documentation](http://libcheck.github.io/check/)
for more details.

## To-Do List
- [ ] Continuously update README to document functionality.
- [ ] Build documentation (with doxygen?) and host on github (gh-pages branch)
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
