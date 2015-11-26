# linkedlist
A linked list library written in C and adhering to C89.

## Functionality
This linked list library aims to provide the following functionality:
- [ ] Singly linked,
- [ ] Single ended,
- [ ] Doubly linked,
- [ ] Double ended,
- [ ] XOR linked (possibly?),
- [ ] Allow the use of any data type for storage,
- [ ] ~~Allow for internal and external data storage,~~
- [ ] Search/add/delete by index,
- [ ] Search/add/delete by element comparison,
- [ ] Using `const` wherever possible to ensure pointer security,
- [ ] Adding an array of elements to a list,
- [ ] Converting a list to an array,
- [ ] User enabled logging to `stderr` (with colour),

**Note:** More functionality will be added as the library is developed.

## About
While this project seeks to develop a linked list library, it also serves as an experiment and learning exercise in the full code development lifecycle.

It comes as part of a personal revamp of GitHub use and repo organisation.

The aims of the project are:
* To learn how to use the full capabilities of `git` and GitHub. This includes:
    - using emoji in commit messages, :+1:
    - the use of development branches and tagging,
    - issue tracking, and
    - any other features that may be useful to learn.
* To build up a full code library from scratch,
* To learn about automating the build process with `make`. Moreover:
    - building an extensive `Makefile`, and
    - using all the functionality of `make`.
* To learn to write in markdown,
*  To comment the code to allow for automated documentation generation using `doxygen`, or other,
* To learn about code testing and test harnesses, with automated testing and feedback.
    - _i.e._ Using `python` to automate `valgrind`.
    - using `gdb`.
    - perhaps using something like [CUnit](http://cunit.sourceforge.net/index.html).
* To adhere to the C89 standard,
* To not use an IDE or any GUI tools.
    - `vim` (with plugins) is used for writing.
* Solely CLI based utilities.
* Allow its use in any project that may require a linked list.
* Use some of the tools/software/services available in the GitHub Student Developer Pack.

## Helpful Resources
* Markdown help:
    - [Markdown Basics](https://help.github.com/articles/markdown-basics/)
    - [Writing on GitHub](https://help.github.com/articles/writing-on-github/)
    - [Mastering Markdown](https://guides.github.com/features/mastering-markdown/)
    - [Markdown Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
    - [GitHub Flavored Markdown](https://help.github.com/articles/github-flavored-markdown/)
* `git` help:
    - [git-scm](https://git-scm.com/)
    - [Student Developer Pack](https://education.github.com/pack)
* `doxygen` help:
    - [Doxygen Homepage](http://www.stack.nl/~dimitri/doxygen/)

## To-Do List
- [ ] Continuously update README to document functionality.
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
