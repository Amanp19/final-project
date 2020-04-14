/*
 * uart4test.cpp
 *
 *  Created on: Apr. 10, 2020
 *      Author: Aman
 */


#include <iostream> //used for input and output C++
#include <stdio.h> //standard input output for C
#include <unistd.h> // Using inbuilt functions
#include <string.h> //String library
#include <termios.h> //Terminal library

#include <sys/types.h> //Contains several predefined types like size_t
#include <sys/stat.h> //sys stat is used for getting information about file stat
#include <fcntl.h> //used for various file operations

 int main (void)
{
    int file, i; // initializing variables
    unsigned char receive[100]; // declare a buffer variable for receiving data
    char buf[20]; // A buffer to store transmitting data
    size_t nbytes; //A variable to store size of data
    size_t bytes_written; // A variable to store size of incoming data (in bytes)
    int bytes_read; // A variable to store size of data received (in bytes)

    if ((file = open("/dev/ttyO4", O_RDWR))<0) // Opening file in Read and write mode, Returns -1 if failed
    {

        printf("UART: Failed to open the file.\n"); // Ifunable to open file
        return 0;
    }

    //
    struct termios options; // make a termios structure for file communication. the termios structure is vital
    tcgetattr(file, &options); // sets the parameters associated with file

    // Set up the communications options:

    options.c_cflag = B9600 | CS8 | CREAD | CLOCAL; // 9600 baud, 8-bit, enable receiver, no modem control lines
    options.c_iflag = IGNPAR | ICRNL; // ignore partity errors, CR -> newline
    tcflush(file, TCIFLUSH); // discard file information not transmitted
    tcsetattr(file, TCSANOW, &options); // changes occur immmediately, aplly the changes

    strcpy(buf, "This is a test\n"); //copy the string to output buffer
    nbytes = strlen(buf); // Store length of buffer in bytes, needed for transmission

    while (1) // An infinite loop
    {
        bytes_written = write(file, buf, nbytes);// Write buffer value to output
        //bytes_written will hold the value, how many bytes has been written

        bytes_read = read(file,&receive,100);//Read the data coming (100 bytes max) to UART file and store in receive
        //bytes_read will hold the value to how many bytes of data was received
        for(int j=0; j<=bytes_read; j++)//Write the incoming data to output port
        {
        	printf("%c",receive[i]); // Print data byte by byte at output
        }

        sleep(10);// wait for 10 seconds
    }
    close(file);// Close the file
}

