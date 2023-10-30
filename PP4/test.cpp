#include <iostream>
#include <cstring>
#include <dlfcn.h>

char* encryptedMsg = nullptr;

void cleanup()
{
    if (encryptedMsg)
    {
        delete[] encryptedMsg;
    }
}

int main()
{
    void* handle = dlopen("./caesar.dll", RTLD_LAZY);
    if (!handle)
    {
        std::cerr << "error loading" << dlerror() << std::endl;
        return 1;
    }

    char* (*encrypt)(char*, int) = (char* (*)(char*, int))dlsym(handle, "encrypt");
    char* (*decrypt)(char*, int) = (char* (*)(char*, int))dlsym(handle, "decrypt");

    if (!encrypt || !decrypt)
    {
        std::cerr << "error func load " << dlerror() << std::endl;
        dlclose(handle);
        return 1;
    }

    int choice;
    char input[100];
    int key;

    while (true)
    {
        std::cout << "Choose an option (1 enc, 2 decr, 3 exit): " << std::endl;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
            std::cout << "Enter message to encrypt: ";
            std::cin.getline(input, sizeof(input));
            std::cout << "Enter key: ";
            std::cin >> key;
            std::cin.ignore();

            if (encryptedMsg)
            {
                delete[] encryptedMsg;
            }
            encryptedMsg = encrypt(input, key);
            break;

        case 2:
            if (encryptedMsg)
            {
                std::cout << "Enter decryption key: ";
                std::cin >> key;
                std::cin.ignore();
                char* decr = decrypt(encryptedMsg, key);
                std::cout << "Decrypted message: " << decr << std::endl;
                delete[] decr;
            }
            else
            {
                std::cout << "empty encrypted message" << std::endl;
            }
            break;

        case 3:
            cleanup();
            dlclose(handle);
            return 0;

        default:
            std::cout << "invalid option" << std::endl;
        }
    }
}