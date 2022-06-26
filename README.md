# The C Programming Language - Solutions for the 2nd Edition

This repo contains solutions for the exercises of each chapter in the K&R book. The aim is to open source my solutions as a helpful reference for future readers.

### About the book

**The C Programming Language** written by _Brian Kernighan_ and _Dennis Ritchie_ is an invaluable resource for learning the core concepts of programming in C. It is often referred to as the **K&R** book.

Each chapter of the book contains exercises related to the discussed content.

### Chapters of the Book

- [Chapter 1: A Tutorial Introduction](src/chapter_1)
- [Chapter 2: Types, Operators and Expressions](src/chapter_2)
- [Chapter 3: Control Flow](src/chapter_3)
- [Chapter 4: Functions and Program Structure](src/chapter_4)
- [Chapter 5: Pointers and Arrays](src/chapter_5)
- [Chapter 6: Structures](src/chapter_6)
- [Chapter 7: Input and Output](src/chapter_7)
- [Chapter 8: The UNIX System Interface](src/chapter_8)

### Running the Solutions

The provided solutions are independent of any IDE. You can run the solutions individually using a C compiler of your choice.

###### Running and Debugging in VS Code

If you are using VS Code, you can use the [tasks.json](.vscode/tasks.json) and [launch.json](.vscode/launch.json) to easily compile and execute each file. I also recommend using the [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) extension by Microsoft for IntelliSense, debugging and code browsing. To show the debug button in VS Code for each C file, you can enable the _C_Cpp: Debug Shortcut_ under _Settings_ > _Extensions_ > _C/C++_.

### Running Tests

For some of the exercises, you will be able to run tests with [Ceedling](http://www.throwtheswitch.org/ceedling). The tests are provided in the `tests` directory.
Once you have Ceedling installed, you can run them using the `ceedling` command.

```bash
ceedling test:all  # run all the tests
ceedling test:name # test specific test suite with `name`
```

### Feedback

If you find any mistake or can think of a more optimized or cleaner solution, please let me know! I'd be happy to hear from you.
