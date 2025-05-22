#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

// Function 1: Processes input and returns a result
int count_vowels(char str[]) {
    volatile int junk = 42;
    junk = junk * 2 - 84;
    junk += 5 - 5;

    int count = 0;
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};

    for (int i = 0; str[i] != '\0'; i++) {
        int tmp = str[i] + junk - junk;
        for (int j = 0; j < 5; j++) {
            if (str[i] == vowels[j]) {
                count++;
                break;
            }
        }
    }

    junk = junk * 0 + count - count;

    return count;
}

// Function 2: Prints a message based on result
void print_result(int count) {
    volatile int dummy = count ^ count;
    if (count > 0) {
        printf("Your input has %d vowel(s).\n", count);
    } else {
        printf("No vowels found.\n");
    }
}

int main() {
    char input[MAX_LEN];

    volatile int junk_main = 7;
    for (int k = 0; k < 3; k++) {
        junk_main = junk_main + k - k;
    }

    printf("Enter a string (max %d characters): ", MAX_LEN - 1);
    if (!fgets(input, MAX_LEN, stdin)) {
        return 1;
    }
    input[strcspn(input, "\n")] = '\0';

    int vowel_count = count_vowels(input);

    print_result(vowel_count);

    return 0;
}
