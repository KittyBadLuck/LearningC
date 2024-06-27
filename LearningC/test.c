
#include<stdio.h>

int foobar(int* n) {
	*n = *n + 1;
	return *n;
}
int main(void)
{
	int k = 6;
	printf("foobar(k) = %d,", foobar(&k));
	printf("HELLO\t\tWORLD\n");
}