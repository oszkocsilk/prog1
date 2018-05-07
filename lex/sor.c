#include <stdio.h>

int main()
{
  int sor = 1;
  char szoveg;

  printf("Add meg a szoveget majd nyomj Ctrl-d (2x) ha kesz.\n\n");

  while((szoveg=getchar()) != EOF)
  {
     if(szoveg == ('\n'))
    {
      sor++;
    }
  }

  printf("\nA szoveged %d sorbol all.\n", sor);

  return 0;
}
