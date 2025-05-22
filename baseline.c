#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

// Function 1: Processes input and returns a result
int count_vowels(char str[]) {
    int count = 0;
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; str[i] != '\0'; i++) {
        for (int j = 0; j < 5; j++) {
            if (str[i] == vowels[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}

// Function 2: Prints a message based on result
void print_result(int count) {
    if (count > 0) {
        printf("Your input has %d vowel(s).\n", count);
    } else {
        printf("No vowels found.\n");
    }
}

int main() {
    char input[MAX_LEN];

    printf("Enter a string (max %d characters): ", MAX_LEN - 1);
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = '\0';

    int vowel_count = count_vowels(input);
    print_result(vowel_count);

    return 0;
}