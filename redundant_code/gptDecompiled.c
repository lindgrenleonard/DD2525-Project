#include <stdio.h>
#include <string.h>

// System V ABI: 
//   – first argument in RDI, second in RSI, return in RAX/EAX
// Prologue/epilogue and stack‐cookie checks elided for clarity.

/**
 * count_vowels
 * ----------------
 * Count how many characters in the NUL-terminated string `s` are in the vowel set.
 *
 * @param s   pointer to input string
 * @return    number of vowels found
 */
int count_vowels(const char *s) {
    // local stack frame laid out with space for:
    //   - stack cookie at [rbp-0x8]
    //   - saved pointer `s` at [rbp-0x38]
    //   - int count at [rbp-0x24]
    //   - int str_idx at [rbp-0x1c]
    //   - int vowel_idx at [rbp-0x18]
    //   - int inner_count (unused) at [rbp-0x20]
    //   - char vowels[5] stored at [rbp-0xd..rbp-0x9]
    
    int count = 0;                     // [rbp-0x24]
    static const char vowels[] = "aeiou";  // built in .rodata, length = 5

    // Outer loop: for each character until NUL
    for (int str_idx = 0; s[str_idx] != '\0'; str_idx++) {
        // Inner loop: check against each vowel
        for (int v = 0; v < 5; v++) {
            if (s[str_idx] == vowels[v]) {
                count++;
                break;  // out of inner loop once matched
            }
        }
    }

    return count;
}

/**
 * print_result
 * ----------------
 * If `count` > 0, prints "Your input has %d vowel(s).\n",
 * otherwise prints "No vowels found." (via puts).
 *
 * @param count  number of vowels to report
 */
void print_result(int count) {
    // Stack and cookie handling omitted
    if (count > 0) {
        // format lives in .rodata: "Your input has %d vowel(s).\n"
        printf("Your input has %d vowel(s).\n", count);
    } else {
        // format in .rodata: "No vowels found."
        puts("No vowels found.");
    }
}

/**
 * main
 * ----------------
 * Prompts the user, reads a line (max 99 chars + NUL), strips newline,
 * counts vowels, and prints the result.
 *
 * Note: there is a small redundant loop at the top that does nothing
 * (it sets a local var to itself three times).
 */
int main(void) {
    // Prologue with stack-cookie saved at [rbp-0x8] omitted
    
    // --- Redundant code region inferred from:
    //      movl $7, -0x7c; movl $0, -0x78;
    //    0x78..0x7c used for these locals.
    int redundant = 7;    // var at [rbp-0x7c]
    for (int i = 0; i <= 2; i++) {
        // assembly does: mov redundant, EAX; mov EAX, redundant;
        // a no-effect self-assignment
        redundant = redundant;
    }
    // End of redundant region

    // Prompt user
    // .rodata: "Enter a string (max %d characters): \n"
    printf("Enter a string (max %d characters): \n", 99);

    // Buffer allocated on stack at [rbp-0x70], size inferred from
    //                      lea   -0x70(%rbp),%rax
    // and later fgets(..., 100, stdin)
    char buffer[100];

    // Read line; check for EOF
    if (fgets(buffer, 100, stdin) == NULL) {
        return 1;
    }

    // Strip trailing newline:
    //   size_t len = strcspn(buffer, "\n");
    //   buffer[len] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    // Count and report
    int vcount = count_vowels(buffer);
    print_result(vcount);

    return 0;
}
