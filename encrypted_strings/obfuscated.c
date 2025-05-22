#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
#define XOR_KEY 0x5A 

void decrypt(unsigned char *str) {
    for (int i = 0; str[i] != 0x00; i++) {
        str[i] ^= XOR_KEY;
    }
}

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
    // XOR-encrypted: "Your input has "
    unsigned char msg1[] = {
        0x03, 0x35, 0x2F, 0x28,
        0x7A, 0x33, 0x34, 0x2A,
        0x2F, 0x2E, 0x7A, 0x32,
        0x3B, 0x29, 0x7A, 0x00
    };

    // XOR-encrypted: " vowel(s).\n"
    unsigned char msg2[] = {
        0x7A, 0x2C, 0x35, 0x2D,
        0x3F, 0x36, 0x72, 0x29,
        0x73, 0x74, 0x50, 0x00
    };

    // XOR-encrypted: "No vowels found.\n"
    unsigned char msg3[] = {
        0x14, 0x35, 0x7A, 0x2C,
        0x35, 0x2D, 0x3F, 0x36,
        0x29, 0x7A, 0x3C, 0x35,
        0x2F, 0x34, 0x3E, 0x74,
        0x50, 0x00
    };

    decrypt(msg1);
    decrypt(msg2);
    decrypt(msg3);

    if (count > 0) {
        printf("%s%d%s", msg1, count, msg2);
    } else {
        printf("%s", msg3);
    }
}

int main() {
    char input[MAX_LEN];

    // XOR-encrypted: "Enter a string (max 99 characters): "
    unsigned char msg4[] = {
        0x1F, 0x34, 0x2E, 0x3F,
        0x28, 0x7A, 0x3B, 0x7A,
        0x29, 0x2E, 0x28, 0x33,
        0x34, 0x3D, 0x7A, 0x72,
        0x37, 0x3B, 0x22, 0x7A,
        0x63, 0x63, 0x7A, 0x39,
        0x32, 0x3B, 0x28, 0x3B,
        0x39, 0x2E, 0x3F, 0x28,
        0x29, 0x73, 0x60, 0x7A,
        0x00
    };

    decrypt(msg4);
    printf("%s", msg4);

    fgets(input, MAX_LEN, stdin);
    input[strcspn(input, "\n")] = '\0';

    int vowel_count = count_vowels(input);
    print_result(vowel_count);

    return 0;
}
