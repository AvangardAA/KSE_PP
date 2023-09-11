#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char hello_buf[15] = "Hello, world\n";
	char* text_buf = (char*)malloc(20 * sizeof(char));
	printf_s(hello_buf);
	int choice;

	strcpy(text_buf, "Hello,World");

	while (1)
	{
		printf_s("Choose the command: ");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
			printf_s("test\n");
			break;
		case 2:
			text_buf[strlen(text_buf)] = "\n";
			text_buf[strlen(text_buf) + 1] = "\0";
			break;
		case 3:
			char namebuf[15];
			scanf("%s", namebuf);
			FILE *f = fopen(namebuf, "w");
			fprintf(f, text_buf);
			fclose(f);
			break;
		case 4:
			printf_s("Jugg2");
			break;
		default:
			printf_s(text_buf);
			break;
		}
	}
	free(text_buf);
	return 0;
}