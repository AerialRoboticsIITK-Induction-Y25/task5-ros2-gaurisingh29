#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <chrono>
#include <iomanip>
#include "drone_exceptions.h"

static std::string get_timestamp(){
    std::time_t now=std::time(nullptr);
    std::tm t=*std::localtime(&now);
    char buf[20];
    std::strftime(buf, 20, "%d/%m/%Y %H:%M:%S", &t);
    return buf; 
}

//Vehicle-Abstract Base Class
class Vehicle{


    //Subclasses can read name directly and call add_log_entry.
    // But battery_level and status are private

    protected:
        std::string name;
        void add_log_entry(const std::string&entry){
        flight_log.push_back("["+ get_timestamp()+"]"+entry);
        }
    private:
        float battery_level;
        std::string status;
        std::vector<std::string> flight_log;
        
        

    public:
    //constructor-
    Vehicle(const std::string &n, float b) : name(n), battery_level(b), status("idle");
    //destructor-
    virtual ~Vehicle()=default;
    virtual std::string get_info() const=0;

    void drain_battery(float amount);
    //charge battery
    void charge_battery(float amount, int duration_seconds);
    bool is_critical() const;
    //to get flight log as string-

    std::string get_flight_log() const;
    void set_status(const std::string &new_status);
   
    const std::string &get_name() const ;
    float get_battery() const;
    const std::string&get_status() const ;
    void add_log_entry(const std::string& entry);

};