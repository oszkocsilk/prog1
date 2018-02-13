#include <iostream>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

int i;
static void gotoxy(int x, int y)
{
  for(i=0; i<y; i++) cout << "\n";
  for(i=0; i<x; i++) cout << " ";
  cout << "o\n";
}


int main(void)
{
  int egyx=1;
  int egyy=-1;
  int i;
  int x=10;
  int y=20;
  int ty[23];
  int tx[80];

  for(i=0; i<23; i++)
       ty[i]=1;

  ty[1]=-1; 
  ty[22]=-1;

  for(i=0; i<79; i++)
       tx[i]=1;

  tx[1]=-1;
  tx[79]=-1;


  for(;;)
  {
    for(i=0; i<36; i++)
       cout << "_";

    ("x=%2d", x);
    ("y=%2d", y);

    for(i=0; i<=36; i++)
         cout << "_";


    (void)gotoxy(x,y);

    x+=egyx;
    y+=egyy;

    egyx*=tx[x];
    egyy*=ty[y];

    usleep (100000);
    system("clear");
  }

}
