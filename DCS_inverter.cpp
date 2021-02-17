#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <chrono>


#include "SunSpecModbus.h"
#include "der_control.hpp"
#include "event.hpp"
#include "event_status.hpp"
#include "randomize_event.hpp"
#include "der_control_base.hpp"
#include "decive_category_type.hpp"
#include "date_time_interval.hpp"
#include "time_type.hpp"
#include "include/sep/date_time_interval.hpp"

using namespace std;

    SunSpecModbus ssmb(1, 1850954613, "192.168.0.64", 502);

int main()
{

   void (der_control,ssmb)
   {
   sep::DERControlBase *der_control_base();
   sep::DeviceCategoryType *device_category();
   sep::DERControl *der_import_control();
   sep::DERControl *der_output_control();
   sep::RandomizeEvent *randomize_charge();
   sep::RandomizeEvent *randomize_discharge();
   sep::DateTimeInterval *date_time_interval();
   sep::TimeType *time_type();
//---------------------------------------------------------------------Time window for inveter to charge------------------------------------------

   randomize_charge->randomize_start_ = 30;     // Set 30 seconds delay to begin charging
                                                //The value set as positive 30 SECONDS, so the client to delay commencement of the event.
                                                // An event can be applied after the scheduled Start time of an event.
                                                // The client can randomely choose any start-time within 30 seconds
                                                // The randomize event value can be set as negaative as well depend on if client needs the event start before the specified start time.

   randomize_charge->randomize_duration_ = 60;  // Set 60 seconds delay to end charging
                                                // randomization duration dertermines the duration that before or after an event that scheduled to conclude
                                                //The value is set as positive 60 SECONDS, so an event will end after the scheduled end time.

  date_time_interval->duration_ = 300     // set the inverter charge station for 5 minutes  (using unit32 to set in seconds)
  using clock = std::chrono::system_clock;
  clock::time_point nowp = clock ::now();
  int time_min {5};
  clock::time_point end = nowp + std::chrono::minutes (time_min);
  time_t nowt = clock::to_time_t (nowp);
  time_t endt = clock::to_time_t (end);
  //string a = ctime (&endt);
  time_type -> start_ = endt;  //scheduled time for inverter to turn on
  long long int a {};
  a=nowp;
//Determine if current time is at the beginning of time window or during the time duration

   if (der_import_control -> randomize_event_ -> event_ -> interval_ -> start_ == a )  // decide if the scheduled time equal to current time

        if (der_import_control->device_category_  == 25 ) //The number represents  OTHER_SATORAGE_SYSTEM in enum class DeviceCateGory type is 25

                if (der_import_control->randomize_event_->event_->current_status_ == 1) //ACTIVE should be 1

                     der_import_control -> der_control_base_ -> der_control_base_op_mod_energize_ = true;       //turn inverter on
                     der_control -> der_control_base_ -> der_control_base_op_mod_fixed_w_= -50  ;               //in%setMaxChargeRateW if neative value specifies a charge mode setpoint that is 0
                                                                                                                // 95 means 95% of maximum rate of energy transfer received by the storage device
                                                                                                                // default to rtgMaxChargeRateW
                                                                                                                // Currently I don't know the value of rtgMaxChargeRateW since the storage is in low voltage level
                                                                                                                // so the inverter is not being turned on

                    // der_control -> der_control_base_ -> der_control_base_op_mod_max_lim_w_ = 95              // sets the maximum active power generation level as a percentage of set capacity (%setMaxW)
                                                                                                                // setMAxW attribute:
                                                                                                                // set limit for maximum active power capability of the DER (in watts). Defaults to rtgMaxW
                                                                                                                // set 95 percent of maximum active power
//-------------------------------------------------------------------------------------------------------------------------------------------------------






//---------------------------------------------------------------------Time window for inverter to discharge-------------------------------------------


   randomize_discharge->randomize_start_ = 30;          //set 30 seconds delay to begin discharging
   randomize_discharge->randomize_duration_ = 60;       // set 60 seconds delay to end discharging

  int time_min1 {10};                                   //set discharge time 10 mins larter of current system time
  clock::time_point end_1 = nowp + std::chrono::minutes (time_min1);  // set scheduled time for inverter to discharge
  time_t endt_1 = clock::to_time_t (end_1);


   if (der_import_control -> randomize_event_ -> event_ -> interval_ -> start_ == a )  // decide if the scheduled time equal to current time

        if (der_output_control->device_category_  == 25 ) //The number represents  OTHER_SATORAGE_SYSTEM in enum class DeviceCateGory type is 25

                if (der_output_control->randomize_event_->event_->current_status_ == 1) //ACTIVE should be 1

                     der_output_control -> der_control_base_ -> der_control_base_op_mod_energize = true;        //turn inverter on

                     der_control -> der_control_base_ -> der_control_base_op_mod_fixed_w_= 50  ;                //opModFixedW function specifies a requested discharge mode setpoint 1 in %setMaxDischargeW or &setMaxW if positive value


                    // der_control -> der_control_base_ -> der_control_base_op_mod_max_lim_w_ = 95              // sets the maximum active power generation level as a percentage of set capacity (%setMaxW)
//----------------------------------------------------------------------------------------------------------------------------------------------------------


// creat a discord card the notice the Tylor to check the code

/*
    map <string, string> point;
    point["GSconfig_ReFloat_Volts"] = "50";
    ssmb.WritePoint(64116, point);
    point = ssmb.ReadBlock(64116);
*/


    point["Conn"] = "true";
    ssmb.WritePoint(123, point);
    point = ssmb.ReadBlock(123); // can we read single register using 'Readpoint' function
    ssmb.PrintBlock(point);


    point["WMaxLimPct"] = "50"; //set maximum input and output power as 50% of the capacity
    ssmb.WritePoint(123, point);
    point = ssmb.ReadBlock(123); // can we read single register using 'Readpoint' function
    ssmb.PrintBlock(point);

    // The opmodfixedW and opmodmaxlimW are the same in SunSpec.


   }//end void(der_control,ssmb)
}//end main ()