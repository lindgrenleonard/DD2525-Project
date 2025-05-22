#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

// Function 1: Processes input and returns a result
int count_vowels(char str[]) {
    int count = 0;
    char vowels[] = {'a','e','i','o','u'};
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

    typedef int   (*fp_count_t)(char *);
    typedef void  (*fp_print_t)(int);

    fp_count_t counter   = count_vowels;
    fp_print_t printer   = print_result;

    void *func_table[2];
    func_table[0] = (void*)count_vowels;
    func_table[1] = (void*)print_result;

    printf("Enter a string (max %d characters): ", MAX_LEN - 1);
    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = '\0';

    int vowel_count = counter(input);

    printer(vowel_count);

    return 0;
}
