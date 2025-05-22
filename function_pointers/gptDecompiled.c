#include <stdio.h> // NOTE: REQUIRED MINOR FIX TO ADD THE #INCLUDES
#include <string.h>
// ----------------------------------------------------------------------------
// int count_vowels(const char *str)
//   — str in RDI, return value in RAX (System V AMD64)
// ----------------------------------------------------------------------------
int count_vowels(const char *str) {
    // [rbp-0x28] ← str
    // Stack protector (__stack_chk_guard) is omitted here.

    // Compiler laid out this small array on the stack:
    //    mov DWORD PTR [rbp-0xd], 0x6f696561    // 'a','e','i','o'
    //    mov BYTE  PTR [rbp-0x9], 0x75          // 'u'
    // so:
    char vowels[5] = { 'a', 'e', 'i', 'o', 'u' };  // no null terminator in asm

    int count = 0;   // [rbp-0x1c]
    int idx   = 0;   // [rbp-0x18]

    // Outer loop (jmp to check at top of loop):
    //   123e: load str[idx]; test != 0; jne body (1203)
    while (str[idx] != '\0') {                    // ← test/jne at 124e/1250
        // Inner loop index
        int j = 0;                                // [rbp-0x14] = 0

        // for (j = 0; j <= 4; j++)
        //    compare str[idx] vs. vowels[j]
        for ( ; j <= 4; j++) {                    // cmp [rbp-0x14], 4; jle 1234
            if (str[idx] == vowels[j]) {          // movzx edx,[str+idx]; movzx eax,[vowels+j]; cmp
                count++;                          // add DWORD PTR [rbp-0x1c],1
                break;                            // short-circuits inner loop (jmp 123a)
            }
        }

        idx++;                                    // add DWORD PTR [rbp-0x18],1
    }

    return count;  // moves [rbp-0x1c] into EAX and returns
}


// ----------------------------------------------------------------------------
// void print_result(int count)
//   — count in EDI
// ----------------------------------------------------------------------------
void print_result(int count) {
    // if (count > 0)
    if (count > 0) {                             // cmp [rbp-0x4],0; jle -> else
        // printf("Your input has %d vowel(s).\n", count);
        //   lea rdi, [rip+0x2008] → format string in .rodata
        //   mov esi, count
        printf("Your input has %d vowel(s).\n", count);
    } else {
        // puts("No vowels found.");
        //   lea rdi, [rip+0x2020] → literal "No vowels found."
        puts("No vowels found.");
    }
}


// ----------------------------------------------------------------------------
// int main(void)
//   — no args used, return in EAX
// ----------------------------------------------------------------------------
int main(void) {
    // Compiler allocates 0xa0 bytes; we only need 100 for input
    char buffer[100];                            // [rbp-0x70 ... rbp-0x10]

    // Prompt user: printf("Enter a string (max %d characters): ", 99);
    //   mov esi,0x63 (99), lea rdi,[rip+0x2038]
    printf("Enter a string (max %d characters): ", 99);

    // Read up to 99 chars + '\0'
    fgets(buffer, 100, stdin);                   // call fgets@plt

    // Strip off trailing newline:
    //   call strcspn(buffer, "\n") → rax = index of '\n' or len
    //   mov BYTE PTR [rbp+rax*1-0x70], 0
    size_t len = strcspn(buffer, "\n");
    buffer[len] = '\0';

    // Call count_vowels(buffer) via the pointer loaded from [rbp-0x90]:
    //   lea rax, [rbp-0x70]
    //   mov rdx, [rbp-0x90]
    //   mov rdi, rax
    //   call rdx
    int count = count_vowels(buffer);

    // Call print_result(count) via [rbp-0x88]:
    //   mov edi, eax; mov rdx, [rbp-0x88]; call rdx
    print_result(count);

    return 0;                                    // mov eax,0; leave; ret
}
