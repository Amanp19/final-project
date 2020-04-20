/*
 *final_code.cpp
 *
 *  Created on: Apr. 17, 2020
 *      Author: amanpreet
 */


#include <iostream> //iostream is the header file which contains all the functions of program inputs/outputs
#include <stdio.h> //Standard C input Output Library
#include <unistd.h> //defines miscellaneous symbolic constants and types, and declares miscellaneous functions
#include <string.h> //C Library for various String Operations
#include <termios.h> // Contains the definitions used by the terminal I/O interfaces

#include <stdlib.h> //General standard Library for various Functions

#include <sys/types.h> //definitions for types like size_t , ssize_t
#include <sys/stat.h> //header defines the structure of the data returned by the functions fstat(), lstat(), and stat(), give file size
#include <fcntl.h> // FIle control, Open, close
#include "iobb.h"  // A header library to control GPIOs of Beaglebone
#include <stdio.h>   //Standard C input Output Library
#include <time.h>  //Time Library

int servo_angle(int angle, int Servopin);  //Defining a function

int thres[] = {400,600,400,600,250,450};
// x_low, x_high, y_low, x_high, c_low, c_high

const int IN1 = 8; // Pins where Moto driver inputs are connected, Use for controlling motors
const int IN2 = 10;
const int IN3 = 12;
const int IN4 = 14;

const int ServoPin = 16; // Pin where servo is connected

int serAngle =90; // Initial Servo Angle

int sigCount = 0;

 int main (void) // Main Function
{

	iolib_init();  //Initializing the iobb library

	iolib_setdir(8, IN1, DigitalOut); //Setting Pin direction of a specific pin of a specific port
	iolib_setdir(8, IN2, DigitalOut);
	iolib_setdir(8, IN3,  DigitalOut);
	iolib_setdir(8, IN4,  DigitalOut);
	iolib_setdir(8, ServoPin, DigitalOut);

	printf("Program Started\n"); // A simple print

	servo_angle(serAngle, ServoPin); // Set the servo initially at 90 degrees

    int file, i; // Variable integers
    char receive[100]; // declare a char array for receiving data
    char buf[20]; // A buffer char array to store temporary data
    size_t nbytes; //size_t is an unsigned integer data type used for storing size
    size_t bytes_written; // //size_t is an signed integer data type used for storing size


    if ((file = open("/dev/ttyO4", O_RDWR))<0) // Try opening file in Read Write mode
    {
        printf("UART: Failed to open the file.\n"); //A message Print
        return 0;
    }

    //
    struct termios options; // the termios structure is vital
    tcgetattr(file, &options); // sets the parameters associated with file

    // Set up the communications options:
    // 9600 baud, 8-bit, enable receiver, no modem control lines
    options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR | ICRNL; // ignore partity errors, CR -> newline
    tcflush(file, TCIFLUSH); // discard file information not transmitted
    tcsetattr(file, TCSANOW, &options); // changes occur immmediately

    strcpy(buf, "This is a UART test\n"); // Copy a string in buf char array
    nbytes = strlen(buf); // Store size of buf array in nbytes


    while (1) // Infinite loop
    {
     //bytes_written = write(file, buf, nbytes); // Writing data, we don't need this
	int i = 0;
	int bytes_read = 0;

	bytes_read = read(file,&receive,100); // Read the file and store the data in receive , read 100 bytes max
	printf("\n\nBytes Received - %d",bytes_read); // Print how many bytes was received
	printf("\n");
	if(bytes_read > 10)  //If no. of bytes are read is more than 10
	{
	for(i=0;i<bytes_read;i++)
	{
	printf("%c",receive[i]);
	}
	printf("\n-----------------------------------------\n\n");



       sleep(1);



char a[25]; //A Char array for holding temporary data
char data[4]; //A char array to hold data

memcpy(a,receive,bytes_read);// Copying data from rec to a
a[bytes_read+1]='\0'; //Adding a Null caharacter at the end of array

printf("Received Data is %s ",a); // Print Statement to print received data
printf("\n");

char *xxpos; //A char array
xxpos = strchr(a,'X'); //To get the first occurance of 'X' in 'a'
int xpos = int(xxpos-a); // To get absolute index of 'X' in 'a'
printf("Position of X : %i\n",xpos); //Print position of X

char *yypos; //A char array
yypos = strchr(a,'Y'); //To get the first occurance of 'Y' in 'a'
int ypos = int(yypos-a); // To get absolute index of 'Y' in 'a'
printf("Position of Y: %i\n",ypos); //Print position of Y


char *ccpos; //A char array
ccpos = strchr(a,'C'); //To get the first occurance of 'C' in a
int cpos = int(ccpos-a); // To get absolute index of 'C' in a
printf("Position of C: %i\n",cpos); //Print position of C



char *hypppos; //A char array
hypppos = strchr(a,'H'); //To get the first occurance of 'H' in a
int hyppos = int(hypppos-a); // To get absolute index of 'H' in a
printf("Position of H: %i\n",hypppos); //Print position of H



char *unddpos; //A char array
unddpos = strchr(a,'U'); //To get the first occurance of 'U' in a
int undpos = int(unddpos-a); // To get absolute index of 'U' in a
printf("Position of U: %i\n",undpos); //Print position of U


memset(data,'\0',sizeof(data)); //Make all the characters stored in data as null
for(int i=xxpos+2;i<hypppos;i++)  // A for loop to copy X data
{
printf("%c",a[i]); //Print the character
data[i-(xxpos+2)] = a[i]; //Store the data in data variable
}
printf("- X Value \n"); //  Print
int x_data = atoi(data);//Convert Character array data to integer
if(x_data>1024) x_data = x_data/10;
printf("Integer value of X %d\n",x_data); //Print integer converted data


memset(data,'\0',sizeof(data)); //Make all the characters stored in data as null
for(int i=yypos+2;i<unddpos;i++) // A for loop to copy Y data
{
printf("%c",a[i]); //Print the character
data[i-(yypos+2)] = a[i];  //Store the data in data variable
}
printf("- Y Value \n"); //  Print

int y_data = atoi(data); //Convert Character array data to integer
if(y_data>1024) y_data = y_data/10;
printf("Integer vallue of Y %d\n",y_data); //Print integer converted data


memset(data,'\0',sizeof(data)); //Make all the characters stored in data as null
for(int i=ccpos+2;i<strlen(a)-1;i++) // A for loop to copy Y data
{
printf("%c",a[i]); //Print the character
data[i-(ccpos+2)] = a[i];  //Store the data in data variable
}
printf("- C Value \n"); // General Print

int c_data = atoi(data); //Conver Character array data to integer
if(c_data>1024) c_data = c_data/10;
printf("Integer VAlue of C %d\n",c_data);  //Print integer converted data


if (x_data > thres[0] and x_data < thres[1] and y_data > thres[2] and y_data < thres[3]) // If any value is beyond threshold
   {
     printf("STOP\n"); // Print the Current State of Robot
     pin_low(8,IN1); // Make all pins low, stops both motor
     pin_low(8,IN2);
     pin_low(8,IN3);
     pin_low(8,IN4);
   }

   else
   {
     if(x_data >= thres[1])
     {
       printf("FORWARD\n"); // Print the Current State of Robot
       pin_high(8,IN1); // Make both motors run in forward direction
       pin_low(8,IN2);
       pin_high(8,IN3);
       pin_low(8,IN4);
     }
     else if(x_data <= thres[0])
     {
    	 printf("BACKWARD\n"); // Print the Current State of Robot
    	 pin_low(8,IN1); // Run both motors run in oppossite direction to move motor backward
    	 pin_high(8,IN2);
    	 pin_low(8,IN3);
    	 pin_high(8,IN4);
     }
     else if(y_data >= thres[3])
     {
    	 printf("RIGHT\n"); // Print the Current State of Robot
    	 pin_low(8,IN1); // Make 1 motor off and 1 on to move robot in right direction
         pin_low(8,IN2);
    	 pin_high(8,IN3);
    	 pin_low(8,IN4);
     }
     else if(y_data <= thres[2])
     {
    printf("LEFT\n"); // Print the Current State of Robot
    pin_high(8,IN1);  // Make 1 motor on and 1 off to move robot in left direction
     pin_low(8,IN2);
     pin_low(8,IN3);
     pin_low(8,IN4);
     }
   }


   if(c_data > thres[4] and c_data < thres[5])
   {
	   pin_low(8,ServoPin); // Make the servo pin low
   }

   else
   {
     if(c_data <= 250)
       {
    	 printf("Camera Moving Left\n"); // Print the Current State of Servo

    	 serAngle -= 10;
    	 serAngle = servo_angle(serAngle,ServoPin);
		 tcflush(file, TCIFLUSH); // discard file information not transmitted


       }
     if(c_data >= 450)
       {
    	 printf("Camera Moving Right\n");  // Print the Current State of Servo

    	 serAngle += 10;
    	 serAngle = servo_angle(serAngle,ServoPin);
		 tcflush(file, TCIFLUSH); // discard file information not transmitted

       }
   }


	}
	else
	{
	sigCount++; // A integer to track for how many loops we didn't receive signal from Remote

	if(sigCount > 20) // If no signal received for 20 loops
	{
		printf("STOP\n");  // Print the Current State of Robot
		pin_low(8,IN1); //Making all pins low, stopping both motors
		pin_low(8,IN2);
		pin_low(8,IN3);
		pin_low(8,IN4);
		sigCount =0; //make the variable zero
	}
	iolib_delay_ms(100); //A delay of 100 ms
	}
    }
    iolib_free(); // Free the GPIOs
    close(file); // Close the file
}

 int servo_angle(int angle, int Servopin) // Function for moving servo to angle and the Pin servo connected to
 {

 int delay = 0;  // An integer to store delays

 if(angle>=180) angle = 180; //If angle is greater than 180, limit it 180
 if(angle <= 0) angle = 0; //If angle is greater than 0, limit it 0

 delay =( (5.56 * angle)+1000); // A formula to calculate delay for Servo motor
// We got the delay and other details from Servo motor (SG90) datasheet

 printf("Delay %d \n",delay);  // Print the calculated delay

 for(int i=0;i<50;i++)  // A for loop running 50 times for setting angle of Servo
 {
 pin_high(8,Servopin); // Making the servo connected pin high
 usleep(delay); //Delay in microseconds which  calculated above
 pin_low(8,Servopin); // Making the servo connected pin low
 usleep(20000-delay); //Delay in microseconds which calculated above subtracted by 20000

 }

 iolib_delay_ms(10); // Small delay

 return(angle); //Return the current angle


 }

