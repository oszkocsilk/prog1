#include<iostream>
#include<string>

using namespace std;
int main()
{

	char szo[50]="0";
	int szavak=1;
	cout<<"add meg a mondatot:\n";
	cin.getline(szo,50);
	for(int i=0; i<sizeof(szo);i++)
	{
		if(szo[i]==(' '))
		{
			szavak++;
		};
	};
cout<<"a mondatod: "<<szavak<<" szobol all\n";
	

return 0;
}
