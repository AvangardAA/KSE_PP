#include <string>
#include <cstdlib>
#include <cstring>

#pragma warning(disable : 4996)

extern "C"
{
    __declspec(dllexport) char* encrypt(char* raw, int key)
    {
        std::string res = raw;

        for (size_t i = 0; i < res.length(); i++)
        {
            if (isalpha(res[i]))
            {
                char base = islower(res[i]) ? 'a' : 'A';
                res[i] = base + (res[i] - base + key) % 26;
            }
        }

        char* encText = (char*)malloc(res.length() + 1);

        if (encText == NULL)
        {
            return NULL;
        }

        strcpy(encText, res.c_str());

        return encText;
    }
    __declspec(dllexport) char* decrypt(char* encText, int key)
    {
        return encrypt(encText, 26 - key);
    }
};