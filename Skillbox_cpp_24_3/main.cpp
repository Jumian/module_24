#include <iostream>
#include <ctime>
#include <map>
#include <iomanip>

#define DELIM ':'
#define DELIMPOS1 2
#define isNotNumber(NUM) ((NUM)<'0'||(NUM>'9'))
#define isNotDelimeter(NUM,DELIM) ((NUM)!=(DELIM))
#define DELIMPOS(NUM) ((NUM)==DELIMPOS1)

std::string input(std::string prompt){
    std::cout << prompt;
    std::string result;
    std::getline(std::cin,result);
    return result;
}

bool isTimeFormat(std::string str){
    if(str.size()!=5) return false;
    for(int i=0;i<str.size();++i){
        if(DELIMPOS(i)&&isNotDelimeter(str[i],DELIM))return false;
        else if(!DELIMPOS(i)&&isNotNumber(str[i])) return false;
    }
    return true;
}

void input_time(std::tm& time_ret){
    bool notDone= true;
    do {
        std::string str = input("Input timer [MM:SS]:");
        if (isTimeFormat(str)) {
            std::stringstream stream(str);
            stream >> std::get_time(&time_ret, "%M:%S");
            notDone= false;
        } else {
            std::cout << "Please input timer in correct order and use 0 before single digit number(01,02..09)"<< std::endl;
        }
    }while(notDone);
}

int main() {
    std::time_t time_zero=0;
    std::tm timer= *localtime(&time_zero);
    input_time(timer);
    std::time_t time;
    time=std::time(nullptr)+ mktime(&timer);
    while(true){
        std::time_t now = std::time(nullptr),prev;
        if(now-prev==0) continue;
        for(int i =0;i<10000000;i++);
        prev = now;
        std::time_t diff = std::difftime(time,now);
        if(diff<=0) {  break;}
        std::tm diff_time = *localtime(&diff);
        std::cout <<std::put_time(&diff_time,"%M:%S") <<" left" << std::endl;
    }
    std::cout << "=====( ( ( DING! DING! DING! ) ) )====="<<std::endl;
}
