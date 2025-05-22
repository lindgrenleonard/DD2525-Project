#include <stdio.h>
#include <string.h>

/*
 * decrypt:
 *   Signature: void decrypt(char *s)
 *   Calling convention (System V): 
 *     - s in RDI
 *     - returns in RAX (unused)
 *   Behavior: XOR-decrypts a NUL-terminated string in place with key 0x5A.
 */
void decrypt(char *s) {
    // Inferred from:
    //   mov    DWORD PTR [rbp-0x4],0            // i = 0
    // loop:
    //   BYTE tmp = s[i];
    //   tmp ^= 0x5A;
    //   s[i] = tmp;
    //   i++;
    //   if (s[i] != 0) goto loop;
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] ^= 0x5A;
    }
}

/*
 * count_vowels:
 *   Signature: int count_vowels(const char *s)
 *   Calling convention:
 *     - s in RDI
 *     - returns in EAX
 *   Behavior: Counts occurrences of 'a', 'e', 'i', 'o', 'u' in the string.
 */
int count_vowels(const char *s) {
    int count = 0;
    // Compiler allocated a local array of 5 bytes and stored {'a','e','i','o'} + 'u'
    char vowels[5] = { 'a', 'e', 'i', 'o', 'u' };
    // Outer loop over each character until NUL
    for (int i = 0; s[i] != '\0'; i++) {
        // Inner loop over the 5 vowels
        for (int j = 0; j < 5; j++) {
            if (s[i] == vowels[j]) {
                count++;
            }
        }
    }
    return count;
}

/*
 * print_result:
 *   Signature: void print_result(int count)
 *   Calling convention:
 *     - count in EDI
 *   Behavior:
 *     - Decrypts three embedded string constants:
 *         buf_yes[] = "Your input has ";
 *         buf_mid[] = " vowel(s).\n";
 *         buf_no[]  = "No vowels found.\n";
 *     - If count > 0, prints: printf("%s%d%s", buf_yes, count, buf_mid);
 *     - Else           prints: printf("%s", buf_no);
 */
void print_result(int count) {
    // The compiler built these encrypted on the stack via movabs, then called decrypt:
    char buf_yes[] = "Your input has ";
    char buf_mid[] = " vowel(s).\n";
    char buf_no[]  = "No vowels found.\n";

    decrypt(buf_yes);
    decrypt(buf_mid);
    decrypt(buf_no);

    if (count > 0) {
        // Format string "%s%d%s" was loaded from .rodata
        printf("%s%d%s", buf_yes, count, buf_mid);
    } else {
        // Format string "%s" was loaded from .rodata
        printf("%s", buf_no);
    }
}

/*
 * main:
 *   Signature: int main(void)
 *   Behavior:
 *     - Builds an encrypted prompt on the stack:
 *         "Enter a string (max 99 characters): "
 *       via movabs immediates, then calls decrypt().
 *     - Prints it with printf("%s", prompt).
 *     - Reads up to 99 chars into buffer[100] via fgets(buffer, 100, stdin).
 *     - Strips trailing newline using strcspn(buffer, "\n").
 *     - Calls count_vowels(buffer) and then print_result().
 */
int main(void) {
    char prompt[40];      // actual size inferred from stack reservation (≈39 chars + NUL)
    char input[100];
    int  vowels;

    // decrypt(prompt);
    decrypt(prompt);

    // printf("%s", prompt);
    printf("%s", prompt);

    if (fgets(input, sizeof input, stdin) != NULL) {
        // strip newline: input[strcspn(input, "\n")] = '\0';
        input[strcspn(input, "\n")] = '\0';

        vowels = count_vowels(input);
        print_result(vowels);
    }

    return 0;
}
