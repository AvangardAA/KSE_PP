#include <string>
#include <cstring>
#include <iostream>

extern "C"
{
    char* encrypt(char* input, int key)
    {
        int len = strlen(input);
        char* encr = new char[len + 1];

        for (int i = 0; i < len; i++)
        {
            char c = input[i];
            if (isalpha(c))
            {
                char base = (isupper(c)) ? 'A' : 'a';
                encr[i] = static_cast<char>(base + (c - base + ((key%26) + 26)) % 26);
            }
            else
            {
                encr[i] = c;
            }
        }
        encr[len] = '\0';

        return encr;
    }

    char* decrypt(char* encr, int key)
    {
        return encrypt(encr, 26 - key);
    }

}
