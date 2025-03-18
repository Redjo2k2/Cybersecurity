#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXN 1024

char* vigenere_encrypt(char* plaintext, char* key)
{
    int text_length = strlen(plaintext);
    int key_length = strlen(key);

    char* cipher = (char*) malloc(sizeof(char) * (text_length + 1));
    if(!cipher)
    {
        perror("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < text_length; i++)
    {
        if(isalpha(plaintext[i]))
        {
            int shift = tolower(key[i % key_length]) - 'a';
            if(islower(plaintext[i]))
            {
                cipher[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
            }
            else
            {
                cipher[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
            }
        }
        else
        {
            cipher[i] = plaintext[i];
        }
    }

    cipher[text_length] = '\0';
    return cipher;
}

void read_from_file(const char* filename, char* buffer, int max_length)
{
    FILE* file = fopen(filename, "r");
    if(!file)
    {
        perror("Error opening file!");
        exit(EXIT_FAILURE);
    }
    if(!fgets(buffer, max_length, file)){
        perror("Error reading file!");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

void write_to_file(const char* filename, const char* text)
{
    FILE* file = fopen(filename, "w");
    if(!file)
    {
        perror("Error opening output file!");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s", text);
    fclose(file);
}

int main()
{
    char text[MAXN];
    char key[MAXN];

    read_from_file("vigeneretext.txt", text, MAXN);
    read_from_file("vigenerekey.txt", key, MAXN);

    char* cipher = vigenere_encrypt(text, key);
    write_to_file("cipher.txt", cipher);

    free(cipher);
    return EXIT_SUCCESS;
}