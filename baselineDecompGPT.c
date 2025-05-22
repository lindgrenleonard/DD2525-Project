#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARS 100

/* Count vowels (both upper- and lowercase) in the input string */
int count_vowels(const char *s) {
    int count = 0;
    for (; *s; s++) {
        char c = *s;
        if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
            c=='A' || c=='E' || c=='I' || c=='O' || c=='U')
        {
            count++;
        }
    }
    return count;
}

/* Print the final message based on vowel count */
void print_result(int n) {
    if (n == 0) {
        puts("No vowels found.");
    } else {
        printf("Your input has %d vowel(s).\n", n);
    }
}

int main(void) {
    char input[MAX_CHARS + 1];

    /* 1) Prompt */
    printf("Enter a string (max %d characters): ", MAX_CHARS);

    /* 2) Read a line from stdin */
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }

    /* 3) Strip the trailing newline, if any */
    input[strcspn(input, "\n")] = '\0';

    /* 4) Count vowels and print the result */
    int vowels = count_vowels(input);
    print_result(vowels);

    return EXIT_SUCCESS;
}
