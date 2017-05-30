#include <stdio.h>

int mdc(int, int);

int main(int argc, char *argv[])
{
	int t, n, m, i;

	scanf("%d", &t);

	for (i = 0; i < t; i++) {
		scanf("%d%d", &n, &m);
		printf("MDC(%d,%d) = %d\n", n, m, (n > m)? mdc(n, m) : mdc(m, n));
	}
	
	return 0;
}

int mdc(int a, int d)
{
	int r = a % d;

	if (r == 0) {
		return d;
	} else {
		return mdc(d, r);
	}
}