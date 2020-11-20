#include <iostream>
#include <string>
#include <map>

#include "SunSpecModbus.h"
#include "der_control.hpp"

using namespace std;

int main()
{
    SunSpecModbus ssmb(1, 1850954613, "192.168.0.64", 502);

    map <string, string> point;
    point["GSconfig_ReFloat_Volts"] = "50";
    ssmb.WritePoint(64116, point);
    point = ssmb.ReadBlock(64116);
    ssmb.PrintBlock(point);
    return 0;
}

