#include <iostream>
#include <windows.h>
#include <string>

int main()
{
    HINSTANCE dllHandle = LoadLibrary(TEXT("C:\\Users\\artem\\source\\repos\\PP3\\PP3\\encdecrypt.dll"));
    if (dllHandle == nullptr)
    {
        std::cerr << "error loading" << std::endl;
        return 1;
    }

    char* (*encfunc)(char*, int) = (char* (*)(char*, int))GetProcAddress(dllHandle, "encrypt");
    char* (*decrfunc)(char*, int) = (char* (*)(char*, int))GetProcAddress(dllHandle, "decrypt");

    if (encfunc == nullptr || decrfunc == nullptr)
    {
        std::cerr << "error func pointers" << std::endl;
        FreeLibrary(dllHandle);
        return 1;
    }

    while (true)
    {
        int choice;
        std::cout << "1 encrypt\n2 decrypt\n3 exit\nchoice: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string text;
            int key;
            std::cout << "Enter text to encrypt: ";
            std::cin.ignore();
            std::getline(std::cin, text);
            std::cout << "Enter key: ";
            std::cin >> key;

            char* encText = encfunc(const_cast<char*>(text.c_str()), key);
            std::cout << "Encrypted text: " << encText << std::endl;
            free(encText);
        }
        else if (choice == 2)
        {
            std::string text;
            int key;
            std::cout << "Enter text to decrypt: ";
            std::cin.ignore();
            std::getline(std::cin, text);
            std::cout << "Enter key: ";
            std::cin >> key;

            char* decrText = decrfunc(const_cast<char*>(text.c_str()), key);
            std::cout << "Decrypted text: " << decrText << std::endl;
            free(decrText);
        }
        else if (choice == 3)
        {
            break;
        }
    }

    FreeLibrary(dllHandle);
    return 0;
}