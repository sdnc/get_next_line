# get_next_line

## Table of Contents

- [About](#about)
- [Concepts](#concepts)
- [Pseudo Code](#pseudo)

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
- (NULL): nothing else to read or an error occurred

## Concepts <a name = "concepts"></a>

To get the most of out of this projects, students should deepen their understanding of two important concepts: static variables and file descriptors.

### Static Variables

Static variables have a property of preserving their value even after they are out of scope. In some ways, they work as global variables. Hence, static variables preserve the previous value assigned in the previous scope and are not reinitalized in the new scope.
```c
static int answer = 42;
```
 If a program runs a block of code, exists it and goes on to another part of the program, and then finally calls that same block of code, the static variable will have preserved the previous value of that variable.
 

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
This file includes three subfunctions: *get_next_line()*, *read_and_append()*, *update_next_line()*

```c
char *get_next_line(int fd);
```

This function takes a file descriptor(fd) as input as this will be the file where the function will retrieve the next line from.

There are three variable declarations:

```c
    char *line // the line/string to return
    char *buffer
    static char *remainder // What is left after returning the next line
```
If the **fd** < 0 or macro BUFFER_SIZE <= 0, the return is (NULL).

Memory must be allocated on the heap for **buffer** in regards to BUFFER_SIZE. Protect malloc to avoid leaks.

**line** is assigned value by calling *read_and_append()*.

**buffer** is then freed from the heap and assigned (NULL) value to clean junk from memory.

if **line** is undefined, the return in (NULL).

**remainder** is assigned new value by calling *update_next_line()*.

Finally, the function returns **line**.
<br><br>


```c
static char *read_and_append(int fd, char *buffer, char *remainder);
```

Two additional variables are declared:

```c
    int bytes_read; //The amount of bytes read
    char    *temp; //A variable that holds a value temporarily
```
**bytes_read** is set to 1 to enter the following while loop: while **bytes_read** is not equal to 0.

**bytes_read** is assigned value by calling the "unistd.h" read function with the **fd**, **buffer** and macro-set BUFFER_SIZE.

If it returns an error (-1), the function returns (NULL). If it is the end of the file (0 return), it exits the loop.

**buffer** at the index of the **bytes_read** value is assigned a (null)-termination.

If **remainder** is undefined, **remainder** is assigned the value of an empty string using *ft_strdup()*.

**temp** takes on the value stored in **remainder**.

**remainder** is then assigned a new value by attaching **buffer** to the end of **temp** using *ft_strjoin()*.

**temp** is freed.

if a new-line character is found in **buffer** using *ft_strchr()*, the loop breaks.

The function returns the static char **remainder**.
<br><br>

```c
	static char *update_next_line(char *line);
```

Two additional variables are declared:

```c
	size_t idx; // to track the index
	char *remainder;
```
**idx** is initialized to 0.

**idx** is incremented in a loop while the **line** on the current **idx** does not equal a new-line and a null-terminator.

If the **line** at the current **idx** or at index 1 equals a null-terminator, the function returns 0.

The **remainder** is assigned its value by calling *ft_substr()*, thus creating a sub-string using **line**, the **idx** and the length of **line** minus the **idx**.

If the value stored in remainder equals (NULL), **remainder** is freed and assigned a (NULL) value.

**line** at the current **idx** plus 1 is null-terminated.

The function returns the **remainder**.

### 2️⃣  **get_next_line_utils.c**

This file consists of five subfunctions: *ft_strlen()*, *ft_substr()*, *ft_strdup()*, *ft_strjoin()*, *ft_strchr()*

Quick note: *Using constant variables is telling the compiler that you will not be making any changes to the data the variable points to which is a good practice if you won't be directly modifying your input data. In addition to telling the compiler, it is also a helpful hint to the user of the API.*
<br><br>

```c
size_t ft_strlen(const char *str);
```

*ft_strlen()* simply counts the bytes in a string and returns the counter. Size_t is used since it represents a size in bytes and also represents an index within the function (Even though size_t was not used for bytes_read in *read_and_append()* as size_t returns an unsigned value and the said function needs to return a negative number in case of error).
<br>


```c
char *ft_substr(const char *str, size_t start, size_t end);
```

*ft_substr()* creates a new string by receiving a source string as input, a size_t index starting point (start), and a size_t index ending point (end). The new string is equal to everything that is in between start and end of the original str. It returns the new str.

This function is called in *update_next_line()* with the input of line, idx (which is retrieved by iterating through line until a new line is found) + 1 (for the null-terminator), and the length of line - idx.
<br>

```c
char *ft_strdup(const char *str);
```

*ft_strdup()* takes a string as input and duplicates it into a new variable/pointer/address. It returns that new pointer which holds the same value as the input string.

It is used in the *read_and_append()* function to duplicate an empty string in case remainder does not contain any value.
<br>

```c
char *ft_strjoin(const char *s1, const char *s2)
```
*ft_strjoin()* takes two strings as input and attaches them to create a new string. s2 gets attached to the end of s1 and put into a new variable. The return value is the new string containing both input strings. 

This function is used in *read_and_append()* to attach the buffer to the end of the temp variable (that holds the original value of the remainder) and assign it to the remainder.
<br>

```c
char *ft_strchr(const char *str, int c);
```

*ft_strchr()* receives a string and iterates through it looking for c. If c is empty, the original address to str is returned. If c can't be found in str, NULL is returned. But if c is found, a pointer to the first instance of c is returned.

This function is used in *read_and_append()* to look for a new-line character in buffer.
<br><br>

### 3️⃣ **get_next_line.h**

This is the header file to be included at the top of each of the other files so they can access all other subfunctions.

External libraries must be included to assure that *malloc(), free() & read()* can be used.

It could be beneficial to define the macro BUFFER_SIZE in case it does not get defined when the program gets compiled. 
<br> <br>

<img width=140px height=70px src="https://static.wixstatic.com/media/745a58_841e3c76fb5941598a97d2fd9f23ea5c~mv2.png/v1/fill/w_918,h_508,al_c/745a58_841e3c76fb5941598a97d2fd9f23ea5c~mv2.png" alt="42 Adelaide logo"></a>