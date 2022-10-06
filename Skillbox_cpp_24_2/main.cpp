#include <iostream>
#include <ctime>
#include <map>
#include <iomanip>

#define DELIM '/'
#define DELIMPOS1 4
#define DELIMPOS2 7
#define isNotNumber(NUM) ((NUM)<'0'||(NUM>'9'))
#define isNotDelimeter(NUM,DELIM) ((NUM)!=(DELIM))
#define DELIMPOS(NUM) ((NUM)==DELIMPOS1||(NUM)==DELIMPOS2)

std::string input(std::string prompt){
    std::cout << prompt;
    std::string result;
    std::getline(std::cin,result);
    return result;
}

bool isDateFormat(std::string str){
    if(str.size()!=10)return false;
    for(int i=0;i<str.size();++i){
        if(DELIMPOS(i)&&isNotDelimeter(str[i],DELIM))return false;
        else if(!DELIMPOS(i)&&isNotNumber(str[i])) return false;
    }
    return true;
}

void input_date(std::tm& date){
    bool notDone= true;
    do {
        std::string str = input("Input birth day date [YYYY/MM/DD]:");
        if (isDateFormat(str)) {
            std::stringstream stream(str);
            std::string debug;
            stream >> std::get_time(&date,"%Y/%m/%d");
            notDone= false;
        } else {
            std::cout << "Please input date in correct order and use 0  befor single digit numbers (01,02..09)"<< std::endl;
        }
    }while(notDone);
}

bool input_friend(std::map<std::string,std::tm> &friends){
    std::time_t time = std::time(nullptr);
    std::pair<std::string,std::tm> new_pair;
    if(new_pair.first=="") new_pair.first= input("Input name:");;
    if(new_pair.first=="end") return false;
    input_date(new_pair.second);
    friends.insert(new_pair);
    return true;
}

int main() {
    std::map<std::string,std::tm> friends;
    bool notFinished = true;
    while(notFinished){
        notFinished=input_friend(friends);
        if(notFinished);
    }
    std::time_t t=std::time(nullptr);
    std::tm curr= *std::localtime(&t);
    for(std::map<std::string,std::tm>::iterator it=friends.begin();
            it!=friends.end();it++){
        if(it->second.tm_mon==curr.tm_mon && it->second.tm_mday==curr.tm_mday)
            std::cout<<"Happy Birthday, "<<it->first<<"!!!"<<std::endl;
        else if ((it->second.tm_mon>curr.tm_mon)|| (it->second.tm_mon==curr.tm_mon && it->second.tm_mday>curr.tm_mday)){
            std::cout<<it->first<<" have a birthday on "<< std::put_time(&it->second,"%m/%d")<< std::endl;
        }
    }
}
