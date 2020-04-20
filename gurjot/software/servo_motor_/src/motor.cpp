/*
 * motor.cpp
 *
 *  Created on: Apr. 15, 2020
 *      Author: gurjot
 */


#include <stdio.h>   //Standard C input Output Library
#include <time.h>  //Time Library
#include <unistd.h> //defines miscellaneous symbolic constants and types, and declares miscellaneous functions
#include "iobb.h"   // A header library to control GPIOs of Beaglebone
void servo_angle(int angle); //Defining a function

int  main(void)

{

  iolib_init();   //Initializing the iobb library

  iolib_setdir(8, 12, DigitalOut);   //Setting Pin direction of a specific pin of a specific port
  printf("Program Started\n"); // A simple print message

  while(1)  //Infinite Loop

  {



    for(int i=0;i<180;i = i+10) // A for loop to servo_angle function repeatedly with value 0 - 180
    {
	servo_angle(i);  // Calling the Function to move servo at specific angle
	 iolib_delay_ms(200);
    }

    for(int i=180;i>0;i= i-10) // A for loop to servo_angle function repeatedly with value 180 - 0
    {
	servo_angle(i); // Calling the Function to move servo at specific angle
	iolib_delay_ms(200);
    }

iolib_delay_ms(900); // A delay of 900 ms

servo_angle(0);  // Set the Servo at 0 degree

iolib_delay_ms(900); // A delay of 900 ms

servo_angle(90);  // Set the Servo at 90 degree

iolib_delay_ms(900); // A delay of 900 ms

servo_angle(180); // Set the Servo at 180 degree

iolib_delay_ms(900); // A delay of 900 ms


}


  iolib_free();  // Free the GPIos

  return(0);

}


void servo_angle(int angle) // Function for moving servo to angle
{

int delay = 0; // An integer to store delays

delay =( (5.55 * angle)+1000); // A formula to calculate delay for Servo motor
// got the delay and other details from Servo motor (SG90) datasheet

printf("Delay %d \n",delay); // Print the calculated delay

for(int i=0;i<50;i++) // A for loop running 50 times for setting angle of Servo
{
pin_high(8,12); // Making the servo connected pin high
usleep(delay); //Delay in microseconds which  calculated above
pin_low(8,12); // Making the servo connected pin low
usleep(20000-delay); //Delay in microseconds which calculated above subtracted by 20000

}

iolib_delay_ms(10); // Small delay


}
