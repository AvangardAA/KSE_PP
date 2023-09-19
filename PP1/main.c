#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#pragma warning(disable : 4996)

char textbuf[256] = "";
char fName[256] = "";

int main() 
{
	char hello_buf[15] = "Hello, world\n";
	char text_buf[50];
	printf_s(hello_buf);
	int choice;

    while (1) 
    {
        printf("\nChoose the command:\n");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            char input[256];
            scanf(" %[^\n]", input);
            strcat(textbuf, input);
            break;
        case 2:
            strcat(textbuf, "\n");
            break;
        case 3:
            printf("Enter the file name for saving: ");
            scanf(" %[^\n]", fName);
            FILE* f = fopen(fName, "w");
            fputs(textbuf, f);
            fclose(f);
            break;
        case 4:
            printf("Enter the file name for loading: ");
            scanf(" %[^\n]", fName);
            FILE* fi = fopen(fName, "r");
            fseek(fi, 0, SEEK_END);
            long len = ftell(fi);
            rewind(fi);
            fread(textbuf, 1, len, fi);
            fclose(fi);
            break;
        case 5:
            printf("%s\n", textbuf);
            break;
        case 6:
            int l, i;
            char input2[256];
            printf("Choose line and index: ");
            scanf("%d %d", &l, &i);
            printf("Enter text to insert: ");
            scanf(" %[^\n]", input2);
            memmove(textbuf + l + strlen(input2), textbuf + l, strlen(textbuf) - l + 1);
            strncpy(textbuf + l, input2, strlen(input2));
            break;
        case 7:
            char s[256];
            printf("Enter text to search: ");
            scanf(" %[^\n]", s);

            char* p = strstr(textbuf, s);
            while (p != NULL) 
            {
                int l = 0;
                int in = p - textbuf;
                for (int i = 0; i < in; i++) 
                {
                    if (textbuf[i] == '\n') 
                    {
                        l++;
                    }
                }
                printf("Text is present in this position: %d %d\n", l, in - l);
                p = strstr(p + 1, s);
            }
            break;
        case 8:
            system("cls");
            break;
        default:
            printf("kse\n");
            break;
        }
    }

    return 0;
}
