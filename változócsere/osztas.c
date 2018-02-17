#include <stdio.h>


int main(void)
{
	int a=23;
	int b=56;

	printf("Alap valtozok:\n");
	printf("a: %d\n", a);
	printf("b: %d\n", b);
	
	a=a*b;
	b=a/b;
	a=a/b;
	printf("Cserelve:\n");
	printf("a: %d \n", a);
	printf("b: %d \n", b);

	a=a*b;
	b=a/b;
	a=a/b;
	printf("Visszacserelve:\n");
	printf("a: %d\n", a);
	printf("b: %d\n", b);

return 0;}
