#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main()
{

	char szo[50];
	int szavak=0;
	printf("Add meg a mondatot:");
	fgets(szo,50,stdin);
	for(int i=0; i<strlen(szo);i++)
		if(szo[i]==(' '))
		{
			szavak++;
		}
printf("szavak=%d\n",szavak+1);
	

return 0;
}
