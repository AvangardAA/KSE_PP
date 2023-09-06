#include <stdio.h>

int main()
{
	char hello_buf[15] = "Hello, world\n";
	char text_buf[50];
	printf_s(hello_buf);
	int choice;

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

		default:
			printf_s(hello_buf);
			break;
		}
	}
	return 0;
}