#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN 1000

void cezar_decipher(char* text, int key)
{
    int length = strlen(text);

    for(int i = 0; i < length; i++)
    {
        if(islower(text[i]))
        {
            text[i] = ((text[i] - 'a' - key + 26) % 26) + 'a';
        }
        else if(isupper(text[i]))
        {
            text[i] = ((text[i] - 'A' - key + 26) % 26) + 'A';
        }
    }
}

int main()
{
    char text[MAXN];
    int key = 3;

    FILE *file = fopen("cezar.txt", "r");
    if(file == NULL)
    {
        perror("Greshka pri otvarqneto na faila!");
        return EXIT_FAILURE;
    }

    if(fgets(text, MAXN, file) == NULL)
    {
        perror("Greshka pri chetene ot faila!");
        fclose(file);
        return EXIT_FAILURE;
    }
    fclose(file);

    text[strcspn(text, "\n")] = 0;

    cezar_decipher(text,key);
    printf("Deshifriran tekst: %s\n", text);

    return EXIT_SUCCESS;

}