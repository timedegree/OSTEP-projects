# OSTEP-projects

## Description

My solutions for [OSTEP projects](https://github.com/remzi-arpacidusseau/ostep-projects).

## table of content

- [x] Inintial Utilities
  - [x] wcat
  - [x] wgrep
  - [x] wzip
  - [x] wunzip
- [x] Inintial Reverse

## Usage

use makefile to perform the following operations

### compile

compile the lab code

~~~makefile
make 
~~~

### test

run the test cases for the lab

~~~makefile
make test
# or verbose output
make test TEST_FLAGS=-v
~~~

### clean

delete all the executables and test-out files

~~~makefile
make clean
~~~

## Reference

- Operating Systems: Three Easy Pieces
- Computer Systems: A Programmer's Perspective
- The C Programming Language
- Advanced Programming in the UNIX Environment
- [xv6: a simple, Unix-like teaching operating system](http://pdos.csail.mit.edu/6.828/2012/xv6/book-rev7.pdf)
