// compile: $ g++ fenykard_new.cpp -o fenykard -lboost_system -lboost_filesystem -lboost_program_options -lboost_date_time -std=c++14

#include <iostream>
#include <stdlib.h>
//#include<conio.h>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <math.h>
#include <time.h>
#define GetCurrentDir getcwd
#include <stdio.h>  /* defines FILENAME_MAX */

#include <unistd.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;


struct labor
{
    int count=0;
    int egy=0;
    int ketto=0;
    int harom=0;
    double atlag=0;
};

using act_occurrence = map <string, map<int, map<string, double>>>;


string GetCurrentWorkingDir( void ) {
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );

    string current_working_dir(buff);
    return current_working_dir;
}


map <string, int> map_points (vector<string>  folders);
void read_points ( string path, map <string, int> &acts );
int sum_points(map<string, int> points);
map <string, int> map_student ( string db_name, map <string, int> &points );
vector<pair<string, int>> sort_student ( map <string, int> &rank );
void make_gource ( string db_name );
map <string, labor> mark_map(string db_name);
act_occurrence count_occurrence (string db_name);
void print_occurrence ( act_occurrence & occurrence );
void make_simul (act_occurrence occurrence, string dump, string date);
vector<pair<string, double>> sort_mark ( map <string, labor> &rank );
map <string, int> make_my_acts(string db_name, string my_name, map <string, int> &points);
void print_missing(map <string, int> my_acts, map <string, int> points);



int main(int argc, char* argv[])
{



    vector<string> roots = {
        GetCurrentWorkingDir()+"/"+"City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Példák/Előadás",
        GetCurrentWorkingDir()+"/"+"City/Debrecen/Szórakozás/Könyv/Ismeretterjesztő/Informatika",
        GetCurrentWorkingDir()+"/"+"City/Debrecen/Oktatás/Informatika/Programozás/Tankönyv\ olvasás"
    };



    boost::program_options::options_description desc ( "Options" );
    desc.add_options()
            ( "roots,r", boost::program_options::value< vector<string> >(),
              "Root directories" )
            ("tasks", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
             "Prints the task with their value")
            ( "db", boost::program_options::value< string > (),
              "the name of a  database dump CSV file." )
            ( "gource", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
              "prints out users and activities in Gource input format." )
            ( "rank", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
              "generates and prints out the traditional grading scale." )
            ( "simul", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
              "indicates that the program will simulate users' acts." )
            ("trad-lab-mark", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
             "Calculates traditional lab mark")
            ( "simout", boost::program_options::value< std::string > ()->default_value ( "dump" ),
              "name of simulation dump")
            ( "break-day", boost::program_options::value< std::string > ()->default_value ( "2019-04-17" ),
              "end of simulation" )
            ("print-simul-prob", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
             "Prints probabilities for simulation")
            ( "print-simul-rank", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
              "Prints simulated rank")
            ("print-my-acts", boost::program_options::value< string > (),
             "Your name and the program prints your activities that are valid, concerning the given roots" )
            ("print-missing", boost::program_options::value< bool > ()->default_value ( false )->implicit_value ( true ),
             "if print-my-acts option is used prints the activities that haven't been done by the given person")
            ;

    boost::program_options::positional_options_description pdesc;
    pdesc.add ( "roots", -1 );

    boost::program_options::variables_map vm;
    boost::program_options::store ( boost::program_options::command_line_parser ( argc, argv ).options ( desc ).positional ( pdesc ).run(), vm );
    boost::program_options::notify ( vm );

    if ( vm.count ( "roots" ) )
    {
        roots = vm["roots"].as<vector<string>>();
        for(int i = 0; i < roots.size(); i++){
            roots[i] = GetCurrentWorkingDir()+"/"+ roots[i];
        }


    }
    map <string, int> points = map_points ( roots );

    if(vm.count("tasks"))
    {
        if (vm["tasks"].as<bool>() )
        {
            cout<<endl<<"-----------------Printing tasks------------------------"<<endl;
            for(auto &i : points)
            {
                cout << setw ( 3 ) << i.second << "\t" << i.first << endl;
            }
            cout<<"Sum of maximal points: "<<sum_points(points)<<endl;
        }
    }



    if ( vm.count ( "db" ) )
    {
        if(vm.count ("rank"))
        {
            if (vm["rank"].as<bool>())
            {
                map <string, int> rank = map_student ( vm["db"].as < string > (), points );
                vector<pair<string, int>> res = sort_student ( rank );
                cout<<endl<<"-----------------Printing traditional ranking------------------------"<<endl;
                for ( auto & i : res )
                    cout << i.first << " "  << i.second << endl;
            }
        }

        if (vm.count("gource"))
        {
            if (vm["gource"].as<bool>() )
            {
                make_gource(vm["db"].as < string > ());
            }
        }

        if(vm.count("trad-lab-mark"))
        {
            if(vm["trad-lab-mark"].as<bool> ())
            {
                map <string, labor> mark =mark_map(vm["db"].as <string> ());
                vector<pair<string, double>> res = sort_mark(  mark );
                cout<<endl<<"-----------------Printing calculated marks for lab------------------------"<<endl;
                for (auto & i : res)
                {

                    string fin_mark;
                    double fract =fmod(i.second, 1.0);
                    int rounded;
                    if(fract<=0.5)
                        rounded=(int)floor(i.second);
                    else
                        rounded=(int)ceil(i.second);

                    switch (static_cast<int>(rounded)) {
                    case 1: fin_mark="elégtelen"; break;
                    case 2: fin_mark="elégséges"; break;
                    case 3: fin_mark="közepes"; break;
                    case 4: fin_mark="jó"; break;
                    case 5: fin_mark="jeles"; break;
                    }

                    cout << i.first << " #"  <<mark[i.first].count<<"  mark:"<< i.second <<" "<<fin_mark <<endl;
                }
            }
        }

        if (vm.count("simul"))
        {
            if (vm["simul"].as<bool> ())
            {
                act_occurrence per_day = count_occurrence (vm["db"].as <string> ());
                if(vm.count("print-simul-entry"))
                {
                    if(vm["print-simul-entry"].as<bool> ())
                    {
                        cout<<endl<<"-----------------Printing probabilities------------------------"<<endl;
                        print_occurrence(per_day);
                    }
                }

                make_simul(per_day, vm["simout"].as<string> (), vm["break-day"].as < std::string > ());

                if(vm.count("print-simul-rank"))
                {
                    if(vm["print-simul-rank"].as<bool> ())
                    {
                        cout<<endl<<"-----------------Printing simulated ranking------------------------"<<endl;
                        map <string, int> simul_rank = map_student (vm["simout"].as<string> () , points );
                        vector<pair<string, int>> simul_res = sort_student ( simul_rank );

                        for ( auto & i : simul_res )
                            cout << i.first << " "  << i.second << endl;
                    }
                }
            }
        }

        if(vm.count("print-my-acts"))
        {
            map<string, int> my_acts =make_my_acts(vm["db"].as<string> (), vm["print-my-acts"].as<string> (), points);
            cout<<endl<<"-----------------Printing my acts------------------------"<<endl;
            for ( auto & i : my_acts )
                cout << i.first << " "  << i.second << endl;
             if(vm["print-missing"].as<bool> ())
             {
                 print_missing(my_acts, points);
             }

        }
    }
}

void read_points ( string path, map <string, int> &acts )
{
    DIR *dir;
    dirent *pdir;
    dir = opendir(path.c_str());
    while(pdir=readdir(dir))
    {

        if(strcmp(pdir->d_name, ".")!=0 && strcmp(pdir->d_name, "..")!=0)
        {
            if(strcasestr(pdir->d_name, ".props"))
            {
                string file_path = path+"/"+pdir->d_name;
                ifstream file;
                file.open((file_path.c_str()));
                string temp;
                int actual_points = 0;

                while(getline(file, temp))
                {
                    bool found_digit = false;

                    int end = 0;
                    int start = 0;
                    size_t found = path.find("GSOC");
                    for(int i=temp.length()-1; i>=0; i--)
                    {
                        if(!found_digit&&isdigit(temp[i]))
                        {
                            found_digit = true;
                            end = i;
                        }
                        if( found_digit && !isdigit(temp[i]))
                        {
                            start = i+1;
                            string::size_type sz;
                            string num=temp.substr(start, end-start+1);
                            int pt = stoi(num, &sz);
                            actual_points += pt;
                            break;
                        }

                    }
                    temp.clear();
                }

                string pwd=GetCurrentWorkingDir()+"/";
                acts[ path.substr(pwd.length())]= actual_points;
                file.close();
            }
            else
            {
                read_points(path+"/"+pdir->d_name, acts);
            }
        }

    }
    closedir(dir);
}

map <string, int> map_points (vector<string>  folders)
{
    map <string, int> acts;
    for ( const auto & path : folders)
    {

        read_points ( path, acts );
    }

    return acts;
}

int sum_points(map<string, int> points)
{
    int temp = 0;
    for(auto &i : points)
    {
        temp += i.second;
    }

    return temp;

}

map <string, int> map_student ( string db_name, map <string, int> &points )
{
    map <string, int> rank;

    ifstream db ( db_name );

    string line;
    while ( getline ( db, line ) ) {

        boost::tokenizer<boost::escaped_list_separator<char>> tokens {line};

        auto iter = tokens.begin();
        string name = *iter;
        string act = *++iter;
        act = act.substr ( 2 );

        rank[name] += points[act];

    }

    return rank;
}

vector<pair<string, int>> sort_student ( map <string, int> &rank )
{
    vector<pair<string, int>> sorted;

    for ( auto & i : rank ) {
        if ( i.second ) {
            pair<string, int> p {i.first, i.second};
            sorted.push_back ( p );
        }
    }

    sort (
                begin ( sorted ), end ( sorted ),
                [ = ] ( auto && p1, auto && p2 ) {
        return p1.second > p2.second;
    }
    );

    return sorted;
}


void make_gource ( string db_name )
{
    cout<<endl<<"-----------------Printing data for gource video------------------------"<<endl;
    map <string, int> count;
    ifstream db ( db_name );
    string line;
    while ( getline ( db, line ) ) {
        boost::tokenizer<boost::escaped_list_separator<char>> tokens {line};
        auto iter = tokens.begin();
        string nev = *iter;
        string feladat = *++iter;
        string datum = *++iter;
        feladat = feladat.substr ( 2 );
        struct tm tm;
        strptime(datum.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
        time_t loctime = mktime(&tm);
        ++count[feladat];
        char mode;
        if(count[feladat]==1)
            mode = 'A';
        else
            mode = 'M';
        cout<<loctime<<"|"<<nev<<"|"<<mode<<"|"<<feladat<<endl;
    }
}


map <string, labor> mark_map(string db_name)
{
    map <string, labor> mark;
    ifstream db(db_name);
    string egy="City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés/I";
    string ketto="City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés/II";
    string harom="City/Debrecen/Oktatás/Informatika/Programozás/DEIK/Prog1/Labor/Védés/III";
    string line;
    while (getline(db, line)) {

        boost::tokenizer<boost::escaped_list_separator<char>> tokens {line};

        auto iter = tokens.begin();
        string name = *iter;
        string act = *++iter;
        act = act.substr(2);
        size_t found1 = act.find(egy);
        size_t found2 = act.find(ketto);
        size_t found3 = act.find(harom);
        int temp=0;
        if(found1!=string::npos && act.compare(egy)!=0 && found2==string::npos && found3==string::npos )
        {
            //cout<<name<<" "<<act<<endl;
            act=act.substr(egy.length()+1);

            if(act.compare("jeles")==0)
                temp= 5;
            else if (act.compare("jó")==0)
                temp= 4;
            else if (act.compare("közepes")==0)
                temp= 3;
            else if (act.compare("elégséges")==0)
                temp= 2 ;
            else if (act.compare("elégtelen")==0)
                temp= 1;
            if (temp>mark[name].egy)
            {
                if(mark[name].egy==0)
                    mark[name].count++;
                mark[name].egy=temp;
            }

        }
        else if(found2!=string::npos && act.compare(ketto)!=0 && found3==string::npos)
        {
            //cout<<name<<" "<<act<<endl;
            act=act.substr(ketto.length()+1);

            if(act.compare("jeles")==0)
                temp= 5;
            else if (act.compare("jó")==0)
                temp= 4;
            else if (act.compare("közepes")==0)
                temp= 3;
            else if (act.compare("elégséges")==0)
                temp= 2 ;
            else if (act.compare("elégtelen")==0)
                temp= 1;
            if (temp>mark[name].ketto)
            {
                if(mark[name].ketto==0)
                    mark[name].count++;
                mark[name].ketto=temp;

            }

        }
        else if(found3!=string::npos && act.compare(harom)!=0)
        {
            //cout<<name<<" "<<act<<endl;
            act=act.substr(harom.length()+1);
            if(act.compare("jeles")==0)
                temp= 5;
            else if (act.compare("jó")==0)
                temp= 4;
            else if (act.compare("közepes")==0)
                temp= 3;
            else if (act.compare("elégséges")==0)
                temp= 2 ;
            else if (act.compare("elégtelen")==0)
                temp= 1;
            if (temp>mark[name].ketto)
            {
                if(mark[name].harom==0)
                    mark[name].count++;
                mark[name].harom=temp;


            }

        }
    }
    for (auto & i : mark)
    {
        if(i.second.count!=0)
            i.second.atlag=(i.second.egy+i.second.ketto+i.second.harom)/static_cast<double> (i.second.count);
    }
    return mark;

}

act_occurrence count_occurrence (string db_name)
{
    act_occurrence occurrence;

    ifstream db (db_name);
    string line;
    bool first = true;
    struct tm first_date;
    struct tm last_date;
    struct tm tm;
    while (getline(db, line))
    {
        boost::tokenizer<boost::escaped_list_separator<char>> tokens {line};

        auto iter = tokens.begin();
        string name = *iter;
        string act = *++iter;
        string date = *++iter;
        act = act.substr ( 2 );


        strptime(date.c_str(), "%Y-%m-%d %H:%M:%S", &tm);
        if(first)
        {
            first_date=tm;
            first = false;
        }
        //time_t loctime = mktime(&tm);
        occurrence[name][tm.tm_wday][act]++;



    }
    last_date = tm;

    boost::gregorian::date lastDate = boost::gregorian::date_from_tm(last_date);
    boost::gregorian::date firstDate = boost::gregorian::date_from_tm(first_date);
    boost::gregorian::date_duration duration = lastDate - firstDate;
    unsigned long d_duration = duration.days();
    double dofw[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    for(int i=0; i<d_duration; i++)
    {
        dofw[(first_date.tm_wday+i)%7]++;
    }
    for ( auto & name : occurrence ) {
        for ( auto & day : name.second ) {
            for ( auto & act : day.second ) {

                if ( act.second > d_duration )
                    act.second = d_duration;

                act.second = act.second/dofw[day.first]*100;

            }
        }
    }

    return occurrence;
}

void print_occurrence ( act_occurrence & occurrence )
{
    for ( auto & name : occurrence ) {
        for ( auto & day : name.second ) {
            for ( auto & act : day.second ) {

                cout << name.first << " " << day.first <<  " " << act.first << " " << act.second << endl;

            }
        }

    }
}

void make_simul (act_occurrence occurrence,string dump, string date )
{
    ofstream sim_out (dump);
    srand(time(NULL));
    boost::gregorian::date break_day = boost::gregorian::from_string ( date );
    struct tm today;
    struct tm *tmpdate;
    time_t now = std::time ( NULL );
    tmpdate = std::gmtime ( &now );
    today = *tmpdate;
    boost::gregorian::date now_date = boost::gregorian::date_from_tm(today);
    boost::gregorian::date_duration duration = break_day - now_date;
    unsigned d_duration = duration.days();
    for (int i=0; i<d_duration; i++)
    {
        for ( auto & name : occurrence )
        {
            for ( auto & day : name.second )
            {
                for ( auto & act :day.second )
                {
                    if (day.first==(today.tm_wday+i)%7)
                    {
                        int random = rand()%101;
                        if(random < act.second)
                        {
                            boost::gregorian::date tmp_date = now_date;
                            boost::gregorian::days daysObj(i);
                            tmp_date = tmp_date + daysObj;
                            sim_out<<"\""<<name.first<<"\",\"./"<<act.first<<"\",\""<<boost::gregorian::to_iso_extended_string ( tmp_date ) << " 21:45:41\""<<endl;;
                        }
                    }
                }
            }
        }
    }
    sim_out.close();
}

map <string, int> make_my_acts(string db_name, string my_name, map <string, int> &points)
{
    map <string, int> my_acts;

    ifstream db ( db_name );

    string line;
    while ( getline ( db, line ) ) {

        boost::tokenizer<boost::escaped_list_separator<char>> tokens {line};

        auto iter = tokens.begin();
        string name = *iter;
        string act = *++iter;
        act = act.substr ( 2 );
        if(name.compare(my_name)==0)
            if (points[act]>0)
            my_acts[act] += points[act];

    }

    return my_acts;
}

vector<pair<string, double>> sort_mark ( map <string, labor> &mark )
{
    vector<pair<string, double>> sorted;

    for ( auto & i : mark) {
        if ( i.second.atlag ) {
            pair<string, double> p {i.first, i.second.atlag};
            sorted.push_back ( p );
        }
    }

    sort (
                begin ( sorted ), end ( sorted ),
                [ = ] ( auto && p1, auto && p2 ) {
        return p1.second > p2.second;
    }
    );

    return sorted;
}

void print_missing(map <string, int> my_acts, map <string, int> points)
{
    cout<<endl<<"-----------------Printing activities not done by the user------------------------"<<endl;
    for ( auto & i : points)
    {
        bool found = false;
        for (auto & j: my_acts)
        {
            if (i.first.compare(j.first)==0)
                found = true;
        }
        if(!found && i.second>0)
            cout<<i.first<<"  "<<i.second<<endl;
    }
}

