#include <iostream>

int main(){
int a=3;
int b= 5;

a= b-a;
b= b-a;
a= b+a;

std::cout<<"a ertek: "<<a<<"\n"<<"b ertek: "<<b<<"\n";
return 0;};


