#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <dlfcn.h>

class Reader 
{
public:
    virtual ~Reader() {}
    virtual std::string read(const std::string& ffile) = 0;
};

class FReader : public Reader 
{
public:
    std::string read(const std::string& ffile) 
    {
        std::ifstream file(ffile);
        if (!file.is_open()) 
        {
            throw std::runtime_error("err file not found");
        }
        std::string dt((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return dt;
    }
};

class Writer 
{
public:
    virtual ~Writer() {}
    virtual void write(const std::string& ffile, const std::string& dt) = 0;
};

class FWriter : public Writer 
{
public:
    void write(const std::string& ffile, const std::string& dt) 
    {
        std::ofstream file(ffile);
        if (file.is_open()) 
        {
            file << dt;
            file.close();
        }
        else 
        {
            throw std::runtime_error("err already exist");
        }
    }
};

typedef char* (*encr)(char*, int);
typedef char* (*decr)(char*, int);

class DllClass 
{
public:
    DllClass(const std::string& dllPath) 
    {
        slib = dlopen(dllPath.c_str(), RTLD_LAZY);
        if (!slib) 
        {
            std::cerr << "load fail " << dlerror() << std::endl;
        }
        else 
        {
            encrypt = (encr)dlsym(slib, "encrypt");
            decrypt = (decr)dlsym(slib, "decrypt");
            if (!encrypt || !decrypt) 
            {
                std::cerr << "func pointer fail" << std::endl;
                dlclose(slib);
            }
        }
    }

    ~DllClass() 
    {
        if (slib) 
        {
            dlclose(slib);
        }
    }

    char* encr_internal(char* dt, int key) 
    {
        if (encrypt) 
        {
            return encrypt(dt, key);
        }
        return nullptr;
    }

    char* decr_internal(char* dt, int key) 
    {
        if (decrypt) 
        {
            return decrypt(dt, key);
        }
        return nullptr;
    }

private:
    encr encrypt;
    decr decrypt;
    void* slib;
};

int main(int argc, char* argv[]) 
{
    if (argc < 4) 
    {
        std::cerr << "Correct usage: " << argv[0] << "\n<mode> (1 encrypt, 2 decrypt, 3 secret encrypt)\n<input> (input file name)\n<output> (output file name)\n<key> (key for encr./decryption)" << std::endl;
        return 1;
    }

    int mode = std::stoi(argv[1]);
    std::string input = argv[2];
    std::string output = argv[3];
    int key = (argc >= 5) ? std::stoi(argv[4]) : 0;

    DllClass encryption("./PP3.dll");

    Reader* reader = new FReader();
    Writer* writer = new FWriter();

    std::string dt = reader->read(input);
    char* res = nullptr;

    if (mode == 1) 
    {
        res = encryption.encr_internal(const_cast<char*>(dt.c_str()), key);
    }
    else if (mode == 2) 
    {
        res = encryption.decr_internal(const_cast<char*>(dt.c_str()), key);
    }
    else if (mode == 3) 
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        key = rand() % 26;
        res = encryption.encr_internal(const_cast<char*>(dt.c_str()), key);

        std::ofstream keyFile("secret.txt");
        if (keyFile.is_open()) 
        {
            keyFile << "key: " << key << std::endl;
            keyFile.close();
        }
        else {
            std::cerr << "secret save fail" << std::endl;
        }
    }

    if (res) 
    {
        writer->write(output, res);
        delete[] res;
    }
    else 
    {
        std::cerr << "encr/decr fail" << std::endl;
    }

    delete reader;
    delete writer;

    return 0;
}
