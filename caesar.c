/* 
 * caesar.c
 * Encrypts or decrypts text using a Caesar cipher with a command-line key.
 * Usage (encrypt): ./caesar -e KEY
 * Usage (decrypt): ./caesar -d KEY
 * Author: Bryan C.
 * Date: December 2025
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINARGS 3
#define ALPHABET 26
#define BUFFER 1000

void read_input(char *buf, size_t size);
char rotate(char c, int n);
int check_digits(char *s);

int main(int argc, char *argv[])
{
    int key, shift, n;
    char input[BUFFER];

    if (argc != MINARGS)
    {
        printf("Usage: %s [-e|-d] KEY\n", argv[0]);
        printf("Modes:\n-e:  encrypt\n-d:  decrypt\n");
        exit(1);
    }
    if (strcmp(argv[1], "-e") != 0 && (strcmp(argv[1], "-d") != 0))
    {
        printf("Invalid mode: %s\n", argv[1]);
        printf("Modes:\n-e:  encrypt\n-d:  decrypt\n");
        exit(2);
    }
    if (!check_digits(argv[2]))
    {
        printf("Invalid key: %s\n", argv[2]);
        printf("Key must be positive and contain only digits\n");
        exit(3);
    }

    key = atoi(argv[2]) % ALPHABET;
    shift = (strcmp(argv[1], "-e") == 0) ? key : -key;

    if (strcmp(argv[1], "-e") == 0)
    {
        printf("Encrypting...\n");
    }
    else
    {
        printf("Decrypting...\n");
    }

    printf("Input:  ");
    read_input(input, BUFFER);

    n = strlen(input);

    printf("Output: ");
    for (int i = 0; i < n; i++)
    {
        printf("%c", rotate(input[i], shift));
    }
    printf("\n");
    
    return 0;
}

void read_input(char *buf, size_t size)
{
    if (fgets(buf, size, stdin) == NULL)
    {
        exit(4);
    }
    else
    {
        buf[strcspn(buf, "\n")] = 0;
    }
}

char rotate(char c, int n)
{
    if (!isalpha(c))
    {
        return c;
    }
    if (islower(c))
    {
        return (char)('a' + ((c - 'a' + n + ALPHABET) % ALPHABET));
    }
    else if (isupper(c))
    {
        return (char)('A' + ((c - 'A' + n + ALPHABET) % ALPHABET));
    }
    return c;
}

int check_digits(char *s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)s[i]))
        {
            return 0;
        }
    }
    return 1;
}
