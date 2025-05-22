#include <stdio.h>
#include <string.h>

// ----------------------------------------------------------------------------
// int count_vowels(const char *str)
//   • str in RDI (System V ABI)
//   • returns in RAX
// ----------------------------------------------------------------------------
int count_vowels(const char *str) {
    // [stack‐frame cookie at fs:0x28 → __stack_chk_fail if corrupted]

    int vowel_count = 0;           // saved at [-0x1c]
    const char vowels[5] = {       // stored bytewise: 'a','e','i','o','u'
        'a','e','i','o','u'
    };
    int i = 0;                     // index into input string, saved at [-0x18]

    // Outer loop: while (str[i] != '\0')
    while (str[i] != '\0') {
        int j = 0;                 // inner index over vowels, saved at [-0x14]

        // Inner loop: for (j = 0; j <= 4; j++)
        //   if str[i] == vowels[j] → vowel_count++, break
        while (j <= 4) {
            if ((unsigned char)str[i] == (unsigned char)vowels[j]) {
                vowel_count++;
                break;
            }
            j++;
        }

        i++;
    }

    // [stack-smash check]
    return vowel_count;
}

// ----------------------------------------------------------------------------
// void print_result(int count)
//   • count in EDI
// ----------------------------------------------------------------------------
void print_result(int count) {
    // [stack-frame cookie]

    if (count > 0) {
        // printf("%s %d %s",
        //        "Your input has", count, "vowel(s).\n");
        //
        // RDI → ptr to "%s %d %s"
        // RSI → ptr to "Your input has"
        // RDX → count
        // RCX → ptr to "vowel(s).\n"
        printf("%s %d %s",
               "Your input has",
               count,
               "vowel(s).\n");
    } else {
        // puts("No vowels found.");
        puts("No vowels found.");
    }
}

// ----------------------------------------------------------------------------
// int main(void)
// ----------------------------------------------------------------------------
int main(void) {
    // [stack-frame cookie]

    // Compiler actually reserves 0x80 bytes for locals;
    // the buffer lives at rbp-0x70, but the source likely was smaller.
    char buffer[100];    // **[?]** original size (assembly uses fgets(...,100,...))

    // Prompt: printf("%s %d %s",
    //                "Enter a string (max", 99, "characters): ");
    // RDI → "%s %d %s"
    // RSI → "Enter a string (max"
    // RDX → 99
    // RCX → "characters): "
    printf("%s %d %s",
           "Enter a string (max",
           99,
           "characters): ");

    // Read up to 99 chars + NUL
    fgets(buffer, 100, stdin);

    // Strip trailing newline:
    // buffer[strcspn(buffer, "\n")] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    // Echo back:
    printf("Input: %s\n", buffer);

    // Count and report
    int n = count_vowels(buffer);
    print_result(n);

    return 0;
}
