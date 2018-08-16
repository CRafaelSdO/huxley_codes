#include <stdio.h>

int main(int argc, char *argv[]) {
	int n[3];

	scanf("%d%d%d", &n[0], &n[1], &n[2]);
	
	if(n[0] >= n[1] && n[0] >= n[2]) {
		int aux = n[0];
		n[0] = n[2];
		n[2] = aux;
	} else if(n[1] >= n[0] && n[1] >= n[2]) {
		int aux = n[1];
		n[1] = n[2];
		n[2] = aux;
	}
	if(n[0] > n[1]) {
		int aux = n[0];
		n[0] = n[1];
		n[1] = aux;
	}

	printf("%d\n%d\n%d\n", n[0], n[1], n[2]);
	return 0;
}