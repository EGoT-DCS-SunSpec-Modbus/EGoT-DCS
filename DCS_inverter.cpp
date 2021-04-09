#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <chrono>


#include "SunSpecModbus.h"
#include <sep/der_control.hpp>
#include <sep/event.hpp>
#include <sep/event_status.hpp>
#include <sep/randomizable_event.hpp>
#include <sep/der_control_base.hpp>
#include <sep/device_category_type.hpp>
#include <sep/date_time_interval.hpp>
#include <sep/time_type.hpp>


SunSpecModbus ssmb(1, 1850954613, "192.168.0.64", 502);

int main()

{
   

    auto now_p = std::chrono::system_clock::now();
    int time_min {5}; 
    auto end = now_p + std::chrono::minutes(time_min);
    time_t nowt =  std::chrono::system_clock::to_time_t ( now_p );
    time_t endt =  std::chrono::system_clock::to_time_t ( end);


// DateTimeInterval
sep::DateTimeInterval interval;
interval.duration = 300;
interval.start = endt;

sep::DateTimeInterval interval_1;
interval_1.duration = 300;
interval_1.start = endt;

//event status

sep::EventStatus even_sta;
sep::CurrentStatus cur_status;
even_sta.current_status = cur_status;
cur_status = sep::CurrentStatus::kActive;

//event + interval
sep::Event event;
event.creation_time = nowt;
event.event_status = even_sta;     
event.interval = interval;

sep::Event event_1;
event_1.creation_time = nowt;
event_1.event_status = even_sta;   
event_1.interval = interval_1;

//randomize_event + event
sep::RandomizableEvent rand_event;
rand_event.event = event;
rand_event.randomize_duration = 30;
rand_event.randomize_start = 30;

sep::RandomizableEvent rand_event_1;
rand_event_1.event = event_1;
rand_event_1.randomize_duration = 30;
rand_event_1.randomize_start = 30;


//DERControl Base
sep::DERControlBase derc_base;
derc_base.op_mod_connect = true;
derc_base.op_mod_energize = true;
derc_base.op_mod_fixed_w = 10000;

sep::DERControlBase derc_base1;
derc_base1.op_mod_connect = true;
derc_base1.op_mod_energize = true;
derc_base1.op_mod_fixed_w = -5000;

//DERControl + DERControl Base
sep::DERControl derc;
derc.randomize_event = rand_event;
derc.der_control_base = derc_base;
derc.device_category = sep::DeviceCategoryType::kOtherStorageSystem;

sep::DERControl derc_1;
derc_1.randomize_event = rand_event_1;
derc_1.der_control_base = derc_base1;
derc_1.device_category = sep::DeviceCategoryType::kOtherStorageSystem;



//Charging mode
   if (event.creation_time == interval.start)
      if (event.event_status.current_status == sep::CurrentStatus::kActive)
            derc_base.op_mod_fixed_w == -5000;   //(charge)
            derc_base.op_mod_energize = true;

//Discharging mode
   if (event_1.creation_time == interval_1.start)
      if (event_1.event_status.current_status == sep::CurrentStatus::kActive)
            derc_base1.op_mod_fixed_w == 5000;   //(discharge)
            derc_base1.op_mod_energize == true;

/*
    map <string, string> point;
    point["GSconfig_ReFloat_Volts"] = "50";
    ssmb.WritePoint(64116, point);
    point = ssmb.ReadBlock(64116);
*/

    std::map <std::string, std::string> point;
    point["Conn"] = std::to_string (derc_base.op_mod_energize);
    ssmb.WritePoint(123, point);
    point = ssmb.ReadBlock(123); // can we read single register using 'Readpoint' function
    ssmb.PrintBlock(point);


    point["WMaxLimPct"] = std::to_string (derc_base.op_mod_fixed_w); //set maximum input and output power as 50% of the capacity
    ssmb.WritePoint(123, point);
    point = ssmb.ReadBlock(123); // can we read single register using 'Readpoint' function
    ssmb.PrintBlock(point);

    // The opmodfixedW and opmodmaxlimW are the same in SunSpec.


   //}//end void(der_control,ssmb)
   

}//end main ()