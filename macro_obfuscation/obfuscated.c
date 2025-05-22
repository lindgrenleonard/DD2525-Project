#include <stdio.h>
#include <string.h>

#define A int
#define B char
#define C return
#define D main
#define E printf
#define F fgets
#define G stdin
#define H '\0'
#define I MAX_LEN
#define J '#'
#define K define
#define L if
#define M else
#define N for
#define O break
#define X count_vowels
#define Y print_result
#define Z input
#define V vowel_count
#define U vowels
#define W count
#define Q str
#define P j
#define T i

#define MAX_LEN 100

// Function 1: Processes input and returns a result
A X(B Q[]) { \
    A W = 0; \
    B U[] = {'a', 'e', 'i', 'o', 'u'}; \
    N (A T = 0; Q[T] != H; T++) { \
        N (A P = 0; P < 5; P++) { \
            L (Q[T] == U[P]) { \
                W++; \
                O; \
            } \
        } \
    } \
    C W; \
}

// Function 2: Prints a message based on result
void Y(A W) { \
    L (W > 0) { \
        E("Your input has %d vowel(s).\n", W); \
    } M { \
        E("No vowels found.\n"); \
    } \
}

A D() { \
    B Z[I]; \
    E("Enter a string (max %d characters): ", I - 1); \
    F(Z, I, G); \
    Z[strcspn(Z, "\n")] = H; \
    A V = X(Z); \
    Y(V); \
    C 0; \
}
