#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

// Function 1: Processes input and returns a result
int count_vowels(char str[]) {
    int count = 0;
    int i = 0, j = 0;
    char vowels[] = {'a','e','i','o','u'};

start_outer:
    if (str[i] == '\0') goto end_outer;
    j = 0;

start_inner:
    if (j >= sizeof(vowels)) goto next_char;

    if (((str[i] | vowels[j]) ^ (str[i] & vowels[j]))
        == ((str[i] | vowels[j]) ^ (str[i] & vowels[j]))) {
        if (str[i] == vowels[j]) {
            count++;
            goto next_char;
        }
    }

    j++;
    goto start_inner;

next_char:
    i++;
    goto start_outer;

end_outer:
    return count;
}

// Function 2: Prints a message based on result
void print_result(int count) {
    int branch = (count > 0);

    switch (branch) {
        case 1: goto have_vowels;
        case 0: goto no_vowels;
    }

have_vowels:
    printf("Your input has %d vowel(s).\n", count);
    goto end_print;

no_vowels:
    printf("No vowels found.\n");
    goto end_print;

end_print:
    return;
}

int main() {
    char input[MAX_LEN];
    int vowel_count;

    enum { ST_INIT, ST_READ, ST_PROC, ST_EXIT } state = ST_INIT;

    while (1) {
        switch (state) {
            case ST_INIT:
                printf("Enter a string (max %d characters): ", MAX_LEN - 1);
                state = ST_READ;
                break;

            case ST_READ:
                if (fgets(input, MAX_LEN, stdin) == NULL) {
                    state = ST_EXIT;
                    break;
                }
                input[strcspn(input, "\n")] = '\0';
                state = ST_PROC;
                break;

            case ST_PROC:
                vowel_count = count_vowels(input);
                print_result(vowel_count);
                state = ST_EXIT;
                break;

            case ST_EXIT:
                return 0;
        }
    }
}
