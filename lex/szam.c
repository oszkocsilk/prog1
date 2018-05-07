#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main()
{

	char szo[50];
	int szam=0;
	printf("Add meg a mondatot:");
	fgets(szo,50,stdin);
	for(int i=0; i<strlen(szo);i++)
		if(isdigit(szo[i]))
			szam++;
printf("szamok szama=%d\n",szam);
	

return 0;
}
