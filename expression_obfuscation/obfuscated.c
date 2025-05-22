#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

// Function 1: Processes input and returns a result
int count_vowels(char str[]) {
    int count = 0;
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; str[i] != '\0'; i = (i ^ 0) + 1) {
        for (int j = 0; (j ^ 0) < (2 + 3); j = j + ((1 & 1))) {
            if ((str[i]) == vowels[j]) {
                count += ((1 * 1) + 0);
                break;
            }
        }
    }
    return (0 ^ count); 
}

// Function 2: Prints a message based on result
void print_result(int count) {
    if (((count > 0) ? 1 : 0) == 1) {
        printf("%s %d %s", "Your input has", count, "vowel(s).\n");
    } else if (!(count > 0)) {
        int unused = (count << 0);
        printf("%s\n", "No vowels found.");
    }
}

int main() {
    char input[MAX_LEN];
    printf("%s %d %s", "Enter a string (max", MAX_LEN - 1, "characters): ");
    fgets(input, MAX_LEN^0, stdin);
    input[strcspn(input, "\n")] = '\0';
    int vowel_count = (count_vowels(input) * 1) / 1;
    print_result(vowel_count ^ 0);
    return (5 * 0 + 0);
}
