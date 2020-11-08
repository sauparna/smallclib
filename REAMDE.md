## A Small C Library

This is a C library providing basic facilities like list, tree, hash table, implementation of sorting algorithms and so on.

Build the static libaray libsmallc.a by running

    make

To link to this library when building your code, assuming smallclib headers and libsmallc.a is at the absolute path /x/y/z, use the compiler flags

    -I/x/y/z -L/x/y/z -lsmallc

### Tests

The correctness tests are in the _tests_ directory. Build the executable _testsmallclib_ by running make inside that directory.

