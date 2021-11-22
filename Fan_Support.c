#include <p18f4620.h>
#include "Main.h"
#include "Fan_Support.h"
#include "stdio.h"

extern char FAN;
extern char duty_cycle;

#define blue PORTAbits.RA4
#define green PORTAbits.RA3

int get_RPM()
{
    int RPS = TMR3L / 2;            // Read the count. Since there are 2 pulses per rev
                                    // then RPS = count/2
    TMR3L = 0;                      // Clear out the count
    return(RPS * 60);               // Return RPM = 60 * RPS
}

void Toggle_Fan()
{
    if (FAN == 0)
    {
        Turn_On_Fan();              // Turn on Fan if toggled and previously off
    }
    else if(FAN == 1){
        Turn_Off_Fan();             // Turn off Fan if toggled and previously on
    }
}

void Turn_Off_Fan()
{
    FAN = 0;                        // Set Fan variable to 0
    FAN_EN = 0;                     // Turn off fan
    FAN_LED = 0;                    // Turn off fan LED
}

void Turn_On_Fan()
{
    FAN = 1;                        // Set Fan variable to 1 
    do_update_pwm(duty_cycle);      // Set proper speed for fan
    FAN_EN = 1;                     // Turn on fan
    FAN_LED = 1;                    // Turn on fan LED
}

void Increase_Speed()
{
    if (duty_cycle == 100)          // 
    {
        Do_Beep();                  // Initiate beep twice
        Do_Beep();
        do_update_pwm(duty_cycle);  // Reprogram the pwm duty cycle
    }
    else
    {
        duty_cycle = duty_cycle + 5;    // Increase duty_cycle by 5
        do_update_pwm(duty_cycle);      // Update with new duty_cycle
    }
}

void Decrease_Speed()
{
    if (duty_cycle == 0)
    {
        Do_Beep();                      // Initiate beep twice
        Do_Beep();
        do_update_pwm(duty_cycle);      // Reprogram the pwm duty cycle
    }
    else
    {
        duty_cycle = duty_cycle - 5;    // Decrease duty_cycle by 5
        do_update_pwm(duty_cycle);      // Update with new duty_cycle
    }
}

void do_update_pwm(char duty_cycle) 
{ 
    float dc_f;
    int dc_I;
    PR2 = 0b00000100;                                   // Set the frequency for 25 kHz
    T2CON = 0b00000111;                                 // 
    dc_f = (4 * duty_cycle / 20.0);                     // Calculate factor of duty cycle versus a 25 kHz
                                                        // signal
    dc_I = (int)dc_f;                                   // Get the integer part
    if (dc_I > duty_cycle)dc_I++;                       // Round up function
    CCP1CON = ((dc_I & 0x03) << 4) | 0b00001100;
    CCPR1L = (dc_I) >> 2;
}

void Set_DC_RGB(int duty_cycle)
{
    int temp = duty_cycle;                      // Initialize a temp variable to not 
    if(duty_cycle > 70)                         // change duty cycle variable
    {
        temp = 70;                              // RGB LED will be white
    }
    else
    {
        temp = duty_cycle;
    }
    PORTD = ((temp/10) << 5) +7;                // Set RGB LED color according to temp 
                                                // Add 7 to not affect other bits in PORTD
}

void Set_RPM_RGB(int rpm)
{
    if (rpm > 0 && rpm < 1800) {                // Set RGB LED to Green
        blue = 0;
        green = 1;
    }
    else if (rpm >= 1800 && rpm < 2700) {       // Set RGB LED to Cyan
        blue = 1;
        green = 1;
    }
    else if (rpm >= 2700) {                     // Set RGB LED to Blue
        blue = 1;
        green = 0;
    }
    else                                        // Set RGB LED OFF
    {
        blue = 0;               
        green = 0;
    }
}
