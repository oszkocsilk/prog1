#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main()
{

	char szo[50];
	int betu=0;
	printf("Add meg a mondatot:");
	fgets(szo,50,stdin);
	for(int i=0; i<strlen(szo);i++)
		if(isalpha(szo[i]))
			betu++;

printf("betuk szama=%d\n",betu);
	

return 0;
}
