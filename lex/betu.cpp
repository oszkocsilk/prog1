#include<iostream>
#include<string>

using namespace std;
int main()
{

	char szo[50]="0";
	int betu=0;
	cout<<"add meg a mondatot:\n";
	cin.getline(szo,50);
	for(int i=0; i<sizeof(szo);i++)
	{
		if(isalpha(szo[i]))
		{
			betu++;
		};
	};
cout<<"a mondatod: "<<betu<<" betubol all\n";
	

return 0;
}
