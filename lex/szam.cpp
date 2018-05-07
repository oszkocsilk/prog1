#include<iostream>
#include<string>

using namespace std;
int main()
{

	char szo[50]="0";
	int szam=0;
	cout<<"add meg a mondatot:\n";
	cin.getline(szo,50);
	for(int i=0; i<sizeof(szo);i++)
	{
		if(isdigit(szo[i]))
		{
			szam++;
		};
	};
cout<<"a mondatod: "<<szam<<" szambol all\n";
	

return 0;
}
