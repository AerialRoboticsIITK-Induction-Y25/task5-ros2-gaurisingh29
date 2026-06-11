    #include "Vehicle.h" 
    
    //constructor-

    Vehicle::Vehicle(const std::string &n, float b) : name(n), battery_level(b), status("idle") 
    {
        add_log_entry("Vehicle '"+name+"'created, battery= "+std::to_string(b)+ "%");

    }


    void Vehicle::drain_battery(float amount){
        if(battery_level<=0.0f)
        throw BatteryDepletedError("Battery depleted on '"+name+"'");
        battery_level=std::max(0.0f, battery_level-amount);
        add_log_entry("Drained "+std::to_string(amount)+ "% Remaining= "+ std::to_string(battery_level)+"%");

    }
    //charge battery
    void Vehicle::charge_battery(float amount, int duration_seconds){
        if(status!="charging")
        throw InvalidStateError("Cannot charge '"+name+"', status is not 'charging'");
        battery_level=std::min(100.0f, battery_level+amount);
        add_log_entry("Charged "+std::to_string(amount)+"% in "+std::to_string(duration_seconds)+" seconds. Level="+std::to_string(battery_level)+"%");

    }
    //is_critical returns true when battery below 20%
    bool Vehicle::is_critical() const{
        return battery_level<20.0f;
    } 
    //to get flight log as string-
    std::string get_flight_log() const{
        std::ostringstream oss;
        oss<<"Flight Log: "<<name<<"\n";
        for(size_t i=0;i<flight_log.size(); ++i)
            oss<<"["<<(i+1)<<"]"<<flight_log[i]<<"\n";
        return oss.str();
    }

    void Vehicle::set_status(const std::string &new_status){
        static const std::set<std::string> allowed={
            "idle", "flying", "charging","emergency", "mission" , "landed"
        };