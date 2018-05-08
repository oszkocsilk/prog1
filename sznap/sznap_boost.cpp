#include<iostream>
#include <boost/date_time.hpp>
#include<string.h>

using namespace std;

int main() {

    int year, month, day;
    cout<<"Ev:"  ;
    cin>>year;
    cout<<"Honap:"  ;
    cin>>month;
    cout<<"Nap:"  ;
    cin>>day;

    boost::gregorian::date dateObj { year, month, day };
    int plus;
    plus = 3000 - year;
    boost::gregorian::years yearsObj(plus);
    dateObj = dateObj + yearsObj;

    cout<< dateObj<<endl;
    string s;
    switch (dateObj.day_of_week())
    {
        case boost::date_time::Sunday: s="Vasarnap"; break;
        case boost::date_time::Saturday: s="Szombat"; break;
        case boost::date_time::Friday: s="Pentek"; break;
        case boost::date_time::Thursday: s="Csutortok"; break;
        case boost::date_time::Wednesday: s="Szerda"; break;
        case boost::date_time::Tuesday: s="Kedd"; break;
        case boost::date_time::Monday: s="Hetfo"; break;

    }
    cout<<"Ez "<<s<<" lesz"<<endl;


}

