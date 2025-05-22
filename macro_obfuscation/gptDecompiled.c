#include <stdio.h>
#include <string.h>

// System V ABI: first argument in RDI, return value in RAX
int count_vowels(const char *str) {
    // Prologue saved RDI at [rbp-0x28]
    // Stack-canary loaded/stored at [fs:0x28]→[rbp-0x8] to defend against overflow.

    // Inferred locals:
    //   int count = 0;            at [rbp-0x1c]
    //   int i = 0;                at [rbp-0x18]
    //   int j = 0;                at [rbp-0x14]
    //   char vowels[5] = {'a','e','i','o','u'}; stored non-sequentially but used as 5-element array

    int count = 0;
    // Initialize vowel table
    static const char vowels[5] = { 'a', 'e', 'i', 'o', 'u' };
    // Outer loop index
    for (int i = 0; ; ++i) {
        char c = str[i];               // load str[i]
        if (c == '\0')                 // test for end-of-string
            break;                     // jump to epilogue

        // Inner loop over vowels[0..4]
        for (int j = 0; j <= 4; ++j) {
            if (c == vowels[j]) {
                ++count;               // count++
                goto _next_char;       // break out of inner loop
            }
        }
    _next_char:
        ;  // continue outer loop
    }

    // Epilogue checks stack-canary and returns in EAX
    return count;
}

void print_result(int count) {
    // Prologue saved EDI (count) at [rbp-0x4]

    if (count > 0) {
        // printf format loaded from .rodata: "Your input has %d vowel(s).\n"
        printf("Your input has %d vowel(s).\n", count);
    } else {
        // puts format loaded from .rodata: "No vowels found."
        puts("No vowels found.");
    }
    // Epilogue: no return value (void), just RET
}

int main(void) {
    // Prologue: stack frame with ~128 bytes for locals
    // Locals include:
    char buffer[100]; // NOTE: REQUIRED MINOR FIX TO ADD THE BUFFER VARIABLE
    //   saved stack-canary         at [rbp-0x8]

    // Prompt the user; format in .rodata: "Enter a string (max %d characters): "
    // Compiler passed literal 0x63 (99) in ESI → prints 99
    printf("Enter a string (max %d characters): ", 99);

    // Read up to 100 bytes into buffer
    // fgets(buffer, 100, stdin)
    fgets(buffer /* [rbp-0x70] */, 100, stdin);

    // Strip trailing newline:
    //   size_t pos = strcspn(buffer, "\n");
    //   buffer[pos] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    // Call helper functions
    int num = count_vowels(buffer);
    print_result(num);

    return 0;
}
