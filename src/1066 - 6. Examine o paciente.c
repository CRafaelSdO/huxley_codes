#include <stdio.h>

int main(int argc, char *argv[])
{
	float temp;
	char ans;

	scanf("%f", &temp);
	getchar();
	scanf("%c", &ans);

	switch (ans) {
		case 'S':
			printf("%s\n", (temp >= 37)? "Exames Especiais" : "Exames Basicos");
			break;
		case 'N':
			printf("%s\n", (temp >= 37)? "Exames Basicos" : "Liberado");
			break;
		default:
			printf("Erro\n");
			break;
	}
	
	return 0;
}