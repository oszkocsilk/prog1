#include <iostream>
#include <cmath>

using namespace std;

double kiir (double tomb[], int db)
{int i;
for(i=0; i<db; ++i)
	{cout<<tomb[i]<<" ,";
};
};


double tavolsag(double PR[], double PRv[], int n)
{
int i;
double osszeg=0.0;
 for (i=0;i<n;++i)
	osszeg+= (PRv[i]-PR[i]) * (PRv[i]-PR[i]);

return sqrt (osszeg);
};



int main()
{
double L[4][4]={
	{0.0,0.0,1.0/3.0,0.0},
	{1.0,1.0/2.0,1.0/3.0,1.0},
	{0.0,1.0/2.0,0.0,0.0},
	{0.0,0.0,1.0/3.0,0.0}};

double PR[4]={0.0,0.0,0.0,0.0};
double PRv[4]={1.0/4.0,1.0/4.0,1.0/4.0,1.0/4.0};
int i,j;

for(;;)
    {
	for (i=0; i < 4; ++i)
	{ PR[i]=0.0;
	for (j=0; j<4; ++j)
		PR[i] += (L[i][j]* PRv[j]);
	};
	if (tavolsag (PR,PRv,4)<0.000000001)
	  break; 
	for (i=0; i< 4; ++i)
	  PRv[i] = PR[i];
    };
kiir(PR,4);

return 0;
}


