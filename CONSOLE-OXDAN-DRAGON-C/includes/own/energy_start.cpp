#include <windows.h>
#include <stdio.h>  // For printf
#include "all_diclarations.h"

void energy_start()
{
    SYSTEM_POWER_STATUS spsPwr;

    // Gets the system power status
    if (GetSystemPowerStatus(&spsPwr))
    {
        // Check battery life percentage and print accordingly
        if (spsPwr.BatteryLifePercent < 50)
        {
            // Prints battery percentage
            printf("\nBattery percentage: \033[0;31m%d\033[0;37m\n", spsPwr.BatteryLifePercent);
        }
        else
        {
            // Prints battery percentage
            printf("\nBattery percentage: \033[0;32m%d\033[0;37m\n", spsPwr.BatteryLifePercent);
        }

        // Check if the system is plugged in
        if (spsPwr.ACLineStatus == 1)
        {
            // Prints power plugged in status
            printf("\033[0;37mPower plugged in: \033[0;32myes\n\033[0;37m");
        }
        else if (spsPwr.ACLineStatus == 0)
        {
            // Prints power not plugged in status
            printf("\033[0;37mPower plugged in: \033[0;31mno\n\033[0;37m");
        }
        else
        {
            // Prints unknown power status
            printf("\033[0;37mPower plugged in: \033[0;33munknown\n\033[0;37m");
        }

        // Optional: Print battery life time if available
        if (spsPwr.BatteryLifeTime != (DWORD)-1)
        {
            //printf("\033[0;37mBattery left: %d:%02d:%02d\n",
                //spsPwr.BatteryLifeTime / 3600,
                //(spsPwr.BatteryLifeTime % 3600) / 60,
                //spsPwr.BatteryLifeTime % 60);
        }
    }
    else
    {
        // Handle error if GetSystemPowerStatus fails
        //printf("\033[0;31mFailed to get power status\033[0;37m\n");
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        printf("(!Failed to get power status!)\n");
        printf("\033[0;37m");
    }

    check_start_start();
}
