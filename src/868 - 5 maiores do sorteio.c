#include <stdio.h>
#include <stdlib.h>

void sort(int *v, int n){
	int i, aux;
	if (n){
		for (i = 0; i < n; i++){
			if (v[i] > v[i + 1]){
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
			}
		}
		sort(v, n - 1);
	}
}

int main(){
	int n, d, maiores[5] = {-1, -1, -1, -1, -1}, p = 4, i;
	scanf("%d%d", &n, &d);
	int numeros[n];
	for (i = 0; i < n; i++){
		scanf("%d", &numeros[i]);
	}
	sort(numeros, n);
	for (i = n; i >= 0; i--){
		if (abs(numeros[i]) % 10 == d){
			maiores[p] = numeros[i];
			p--;
		}
	}
	for (i = 0; i < 5; i++){
		printf("%d\n", maiores[i]);
	}
}