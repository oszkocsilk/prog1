#include <iostream>

using namespace std;

int main()
{
	int a=23;
	int b=56;
	cout<<"Alap valtozok:"<<endl;
	cout<<"a: "<<a<<"\nb: "<<b<<endl;

	a=a*b;
	b=a/b;
	a=a/b;
	cout<<"Cserelve: "<<endl;
	cout<<"a: "<<a<<"\nb: "<<b<<endl;

	a=a*b;
	b=a/b;
	a=a/b;
	cout<<"Visszacsere: "<< endl;
	cout<<"a: "<<a<<"\nb: "<<b<<endl;

return 0;}
