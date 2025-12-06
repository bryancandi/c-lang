# \#define macro processor (K&R exercise 6-6)

This simple #define processor program stores macros in a hash table of linked lists. It currently supports `#define` and `#undef` to insert or remove entries from the table.

- `main.c` — main function: reads and processes input
- `macro.c` — hash table operations: `hash`, `lookup`, `install`, `undef`, `print_hashtab`
- `macro.h` — header: prototypes and data structures
- `getword.c` — input utilities: `getword`, `getch`, `ungetch`
- `Makefile` — use `make` to automate compilation

## Compile the program with GCC or the Makefile:

```sh
# Using GCC directly
gcc -Wall -Wextra -Wpedantic main.c macro.c getword.c -o macro

# Using the Makefile
make        # build the program
make clean  # remove the compiled binary
```

## Program usage:

```
$ ./macro
#define MAXVAL 100     # define MAXVAL as 100
MAXVAL                 # prints: MAXVAL is defined as: 100
!print                 # prints all current macros
#undef MAXVAL          # remove MAXVAL macro
MAXVAL                 # prints: not defined: MAXVAL
```
