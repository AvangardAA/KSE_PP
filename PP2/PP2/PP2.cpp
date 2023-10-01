#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class TextEditor 
{
public:
    TextEditor() 
    {
        textbuf = "";
    }

    void inputText() 
    {
        std::string input;
        std::cout << "Enter text to append: ";
        std::cin.ignore();
        std::getline(std::cin, input);
        textbuf += input;
    }

    void deleteText(int l, int in, int len) 
    {
        int sp = dCursor(l, in);
        textbuf.erase(sp, len);
    }

    void saveFile() 
    {
        std::cout << "Enter the file name for saving: ";
        std::cin >> fName;
        std::ofstream f(fName);
        f << textbuf;
        f.close();
    }

    void loadFile() 
    {
        std::cout << "Enter the file name for loading: ";
        std::cin >> fName;
        std::ifstream f(fName);
        if (f.is_open()) 
        {
            textbuf = "";
            std::string l = "";
            while (std::getline(f, l)) 
            {
                textbuf += l;
                textbuf += '\n';
            }
            f.close();
        }
        else 
        {
            std::cerr << "file open error" << std::endl;
        }
    }

    void printText() 
    {
        std::cout << textbuf << std::endl;
    }

    void undo() 
    {
        if (!undoV.empty()) 
        {
            redoV.push_back(textbuf);
            textbuf = undoV.back();
            undoV.pop_back();
        }
    }

    void redo() 
    {
        if (!redoV.empty()) 
        {
            undoV.push_back(textbuf);
            textbuf = redoV.back();
            redoV.pop_back();
        }
    }

    void cut(int l, int in, int len) 
    {
        int sp = dCursor(l, in);
        int tlen = textbuf.length();

        //std::cout << sp << " " << tlen << "\n"; debug

        if (sp >= 0 && sp < tlen && len > 0) 
        {
            textbuf.substr(sp, len);
            undoV.push_back(textbuf);
            textbuf.erase(sp, len);
        }
        else 
        {
            std::cerr << "cut error" << std::endl;
        }
    }


    void copy(int l, int in, int len) 
    {
        int sp = dCursor(l, in);
        textbuf.substr(sp, len);
        undoV.push_back(textbuf);
        redoV.clear();
    }

    void paste(int l, int in) 
    {
        int ppos = dCursor(l, in);
        if (!undoV.empty()) 
        {
            redoV.clear();
            textbuf.insert(ppos, undoV.back());
            undoV.push_back(textbuf);
        }
    }

    void replaceText(int l, int in, const std::string& repText) 
    {
        int rpos = dCursor(l, in);
        undoV.push_back(textbuf);
        textbuf.replace(rpos, repText.length(), repText);
    }

private:
    int dCursor(int l, int in) 
    {
        int pos = 0;
        int curl = 0;
        while (curl < l && pos < textbuf.length()) 
        {
            if (textbuf[pos] == '\n') 
            {
                curl++;
            }
            pos++;
        }
        return pos + in;
    }
    std::string textbuf;
    std::string fName;
    std::vector<std::string> undoV;
    std::vector<std::string> redoV;
};

int main() 
{
    TextEditor editor;
    int choice;
    std::string repText = "";

    while (true)
    {
        std::cout << "\nChoose the command:\n";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            editor.inputText();
            break;
        case 2:
            int l, in, len;
            std::cout << "Enter line, index, and number of symbols to delete: ";
            std::cin >> l >> in >> len;
            editor.deleteText(l, in, len);
            break;
        case 3:
            editor.saveFile();
            break;
        case 4:
            editor.loadFile();
            break;
        case 5:
            editor.printText();
            break;
        case 6:
            editor.undo();
            break;
        case 7:
            editor.redo();
            break;
        case 8:
            std::cout << "Choose line and index and number of symbols: ";
            std::cin >> l >> in >> len;
            editor.cut(l, in, len);
            break;
        case 9:
            std::cout << "Choose line and index and number of symbols: ";
            std::cin >> l >> in >> len;
            editor.copy(l, in, len);
            break;
        case 10:
            std::cout << "Choose line and index: ";
            std::cin >> l >> in;
            editor.paste(l, in);
            break;
        case 11:
            std::cout << "Choose line, index and input text: ";
            std::cin >> l >> in;
            std::cin.ignore();
            std::getline(std::cin, repText);
            editor.replaceText(l, in, repText);
            break;
        case 12:
            return 0;
        default:
            std::cout << "bad choice" << std::endl;
        }
    }

    return 0;
}
