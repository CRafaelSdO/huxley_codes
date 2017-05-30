#include <stdio.h>

int main(int argc, char *argv[])
{
	char f, s = '\n';

	scanf("%c%c", &f, &s);

	if (s != '\n') {
		printf("1 caractere, por favor!\n");
	} else {
		switch (f) {
			case 'A':
			case 'a':
			case 'E':
			case 'e':
			case 'I':
			case 'i':
			case 'O':
			case 'o':
			case 'U':
			case 'u':
				printf("Eh vogal\n");
				break;
			default:
				printf("Nao eh vogal");
				break;
		}
	}
	
	return 0;
}