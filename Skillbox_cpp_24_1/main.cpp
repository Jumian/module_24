#include <iostream>
#include "ctime"
#include "vector"

struct task{
    std::time_t start_time;
    std::time_t end_time;
    std::string name;
};

std::string input(std::string prompt){
    std::cout << prompt;
    std::string result;
    std::cin >> result;
    return result;
}

void print(std::vector<struct task> &tasks){
    for(int i=0;i<tasks.size();++i)
    {
        if(tasks[i].end_time!=0)
            std::cout<< tasks[i].name << " : " <<tasks[i].end_time-tasks[i].start_time<<" sec"<<std::endl;
        else std::cout<< "Current task: "<<tasks[i].name <<", elapsed time "<< std::time(nullptr)- tasks[i].start_time<<std::endl;
    }
}

void start_task (std::vector<struct task> &tasks){
    struct task new_task;
    new_task.name=input("Input name:");
    new_task.start_time=std::time(nullptr);
    new_task.end_time=0;
    tasks.push_back(new_task);
}

void end_task (std::vector<struct task> &tasks){
    std::time_t end_time=std::time(nullptr);
    for(int i=0;i<tasks.size();++i)
    {
        if(tasks[i].end_time==0)
           tasks[i].end_time= end_time;
    }
}

void work(std::vector<struct task> &tasks) {
    std::string command;
    do {
        command= input("Input command[begin,status,end,exit]:");
        if (command == "begin") {
            end_task(tasks);
            start_task(tasks);

    } else if (command == "end") {
        end_task(tasks);
    } else if (command == "status") {
        print(tasks);
    } else if (command == "exit") {
        return;
    }
}while (true);
}

int main() {
    std::vector<struct task> tasks;
    work(tasks);
    std::cout << "Exit..." << std::endl;
}
