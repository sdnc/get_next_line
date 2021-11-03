# Project Title

## Table of Contents

- [About](#about)
- [Concepts](#concepts)
- [Pseudo Code](#pseudo)
- [Contributing](../CONTRIBUTING.md)

## About <a name = "about"></a>

Get_next_line is a function that returns a line read from a file descriptor. 

External functions used: read, malloc, free

### 💾 *Prototype*

```c
char *get_next_line(int fd);
```

### ⚙️  *Parameters*

- fd: File descriptor to read from

### ◀ *Return value*

- Read line: correct behavior
- NULL: nothing else to read or an error occurred

## Concepts <a name = "concepts"></a>

To get the most of out of this projects, students should deepen their understanding of two important concepts: static variables and file descriptors.

### Static Variables

Static variables have a property of preserving their value even after they are out of scope. In some ways, they work as global variables. Hence, static variables preserve the previous value assigned in the previous scope and are not reinitalied in the new scope.
```c
static int answer = 42;
```


### File Descriptors

A **file descriptor** is a number that uniquely identifies an open file in a computer's operating system. It describes the data resource (file, website, database) and how to access it. 

When a program asks to open a file, or another data resource, like a network socket, the kernel: 

```c
1. grants access
```

```c
2. creates an entry in the global file table
```

```c
3. provides the software with the location (address) of that entry.
```
When a set of instructions make a successful request to open a file, the kernel returns a file descriptor that points to an entry in the kernel's global file table. The file table entry contains information such as the inode of the file (a.k.a. index node - a description of a file-system objects such as a file or a directory), byte offset, and the access restrictions for that data stream (read-only, write-only, etc.).

<img width="400" height="200" src="https://www.computerhope.com/jargon/f/file-descriptor.jpg">

## Pseudo Code <a name = "pseudo"></a>

This function consists of three files: 
- get_next_line.c, primary file
- get_next_line_utils.c, assisting functions
- get_next_line.h, header file

### 1️⃣   **get_next_line.c**
This file includes three function: *get_next_line()*, *read_and_append()*, *update_next_line()*

```c
	char *get_next_line(int fd);
```

This function takes a file descriptor(fd) as input as this will be the file where the function will retrieve the next line from. 

There are three variable declarations:

```c
	char *line // the line/string to return
	char *buffer
	static char *remainder 
// What is left after returning the next line
// This is a static char as it keeps it's value throughout program run-time 
```


<img width=140px height=70px src="https://static.wixstatic.com/media/745a58_841e3c76fb5941598a97d2fd9f23ea5c~mv2.png/v1/fill/w_918,h_508,al_c/745a58_841e3c76fb5941598a97d2fd9f23ea5c~mv2.png" alt="42 Adelaide logo"></a>