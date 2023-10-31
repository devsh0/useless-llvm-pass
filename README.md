# useless-llvm-pass

A completely useless LLVM pass.
It's for LLVM 17.

Build (If you're working outside of CLion):

    $ cd llvm-pass-skeleton
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Build (CLion):

    $ cd cmake-build-debug
    $ ninja all

Run:

    $ source .zshrc
    $ myclang file.c

For additional info, see https://www.cs.cornell.edu/~asampson/blog/llvm.html.