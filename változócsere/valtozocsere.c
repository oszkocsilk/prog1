#include <stdio.h>


int main(void)
{
	int a=23;
	int b=56;

	printf("Alap valtozok:\n");
	printf("a: %d\n", a);
	printf("b: %d\n", b);
	
	a=b-a;
	b=b-a;
	a=b+a;
	printf("Cserelve:\n");
	printf("a: %d \n", a);
	printf("b: %d \n", b);

	a=b-a;
	b=b-a;
	a=b+a;
	printf("Visszacserelve:\n");
	printf("a: %d\n", a);
	printf("b: %d\n", b);

return 0;}
