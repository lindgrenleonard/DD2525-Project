#include <stdio.h>
#include <string.h>    // for strcspn

/* ----------------------------------------------------------------------------
 * int count_vowels(const char *str)
 *   System V ABI: 
 *     str in RDI, return value in EAX.
 * ----------------------------------------------------------------------------
 */
int count_vowels(const char *str) {
    /* Prologue inferred from
     *   push   %rbp
     *   mov    %rsp,%rbp
     *   sub    $0x30,%rsp
     *   mov    %rdi,-0x28(%rbp)
     *   …canary save at -0x8(%rbp)… 
     */
    const char *s = str;             // stored at rbp-0x28
    int count = 0;                   // at rbp-0x1c
    int i = 0;                       // at rbp-0x18
    int j;                           // at rbp-0x14

    /* The compiler scribbles vowels[] onto the stack via
     *   movl   $0x6f696561,-0xd(%rbp)   // 'a','e','i','o'
     *   movb   $0x75,     -0x9(%rbp)   // 'u'
     * so: char vowels[5] = "aeiou";
     */
    char vowels[5];
    vowels[0] = 'a';
    vowels[1] = 'e';
    vowels[2] = 'i';
    vowels[3] = 'o';
    vowels[4] = 'u';

    /* Outer loop over str[i] */
    for (;;) {                       // loop_i @ 1208… test/jmp back
        unsigned char c = (unsigned char)s[i];   // movzbl (%rax),%eax
        if (c == '\0')                // test %al,%al; je end
            break;

        /* Inner loop to compare against vowels[] */
        for (j = 0; j <= 4; j++) {     // cmp $4,… ja skip_inner
            if (c == (unsigned char)vowels[j]) {
                count++;               // addl $1,-0x1c
                i++;                   // addl $1,-0x18
                goto next_char;        // jmp out of inner
            }
        }
        /* no match: just advance i */
        i++;
    next_char:
        ;
    }

    /* Epilogue and return */
    return count;                   // movl -0x1c(%rbp),%eax
}


/* ----------------------------------------------------------------------------
 * void print_result(int count)
 *   ABI: count in EDI, no return.
 * ----------------------------------------------------------------------------
 */
void print_result(int count) {
    /* Prologue from
     *   push   %rbp
     *   mov    %rsp,%rbp
     *   sub    $0x20,%rsp
     *   mov    %edi,-0x14(%rbp)
     */
    int positive = (count > 0);      // setg; movzbl; stored at -0x4

    if (positive == 1) {             // cmp/mov; je to else
        /* printf("Your input has %d vowel(s).\n", count); */
        printf("Your input has %d vowel(s).\n", count);
    } else {
        /* puts("No vowels found."); */
        puts("No vowels found.");
    }

    /* Epilogue: leave; ret */
}


/* ----------------------------------------------------------------------------
 * int main(void)
 * ----------------------------------------------------------------------------
 */
int main(void) {
    /* Prologue:
     *   push   %rbp
     *   mov    %rsp,%rbp
     *   sub    $0x80,%rsp
     *   canary saved at -0x8(%rbp)
     */
    char buffer[100];                // lives at rbp-0x70…-0x10 (≈100 bytes)
    int state = 0;                   // at rbp-0x78
    int vowel_count;                 // at rbp-0x74

    /* Simulates:
     *   while (1) { switch(state) { … } }
     * with a manually‐unrolled “state machine”:
     */
loop_start:                         // label at 0x12ed
    /* if (state == 3) goto exit; */
    if (state == 3)
        goto case3;
    /* if (state > 3) goto loop_start; */
    if (state > 3)
        goto loop_start;

    /* if (state == 2) goto case2; */
    if (state == 2)
        goto case2;
    /* if (state == 1) goto case1; */
    if (state == 1)
        goto case1;

    /* else (state == 0) */        // default/case0
case0:
    /* printf("Enter a string (max %d characters): ", 99); */
    printf("Enter a string (max %d characters): ", 99);
    state = 1;                     // movl $1,-0x78
    goto loop_start;

case1:
    /* if (fgets(buffer, 100, stdin) != NULL) { … } else { state=3; } */
    if (fgets(buffer, 100, stdin) != NULL) {
        /* buffer[strcspn(buffer, "\n")] = '\0'; */
        buffer[strcspn(buffer, "\n")] = '\0';
        state = 2;                 // movl $2,-0x78
    } else {
        state = 3;                 // movl $3,-0x78 (on EOF/error)
    }
    goto loop_start;

case2:
    /* vowel_count = count_vowels(buffer); */
    vowel_count = count_vowels(buffer);
    /* print_result(vowel_count); */
    print_result(vowel_count);
    state = 3;                     // movl $3,-0x78
    goto loop_start;

case3:
    /* return 0; */
    return 0;

    /* Implicit epilogue:
     *   mov    canary back and check
     *   leave; ret
     */
}
