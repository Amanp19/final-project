/*
 * ledd.cpp
 *
 *  Created on: Apr. 1, 2020
 *      Author: himanshu
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(char name_file[], char s_value[]);
void removeTrigger();

int main(int argc, char* argv[])
{
   if(argc!=2){


      printf(" hiii led on and off\n");

	   printf(" hru flash LED\n");

    return 2;
   }
   printf("Starting the GPIO Test  program\n");
   printf("The current GPIO Path is: " LED3_PATH);
   printf("\n");

   // select whether command is on, off, flash or status
   if(strcmp(argv[1],"on")==0){
        printf("Making GPIO High\n");
	removeTrigger();
        writeLED("/Amplitude", "1");
   }
   else if (strcmp(argv[1],"off")==0){
        printf("Making the GPIO low\n");
	removeTrigger();
        writeLED("/Amplitude", "0");
   }
   else if (strcmp(argv[1],"flash")==0){
        printf("Flashing the GPIO\n");
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (strcmp(argv[1],"status")==0)\
   {
      FILE* fp;   // see writeLED function below for description
      char  fullFileName[100];
      char line[80];
      sprintf(fullFileName, LED3_PATH "/trigger");
      fp = fopen(fullFileName, "rt"); //reading text this time
      while (fgets(line, 80, fp) != NULL){
         printf("%s", line);
      }
      fclose(fp);
   }
   else{
	printf("Got Invalid command!\n");
   }
   printf("End of GPIO Test Program\n");
   return 0;
}

void writeLED(char name_file[], char s_value[]){
   FILE* fp;   // create a file pointer fp
   char  fullFileName[100];  // to store the path and name_file
   sprintf(fullFileName, LED3_PATH "%s", name_file); // write path and name_file
   fp = fopen(fullFileName, "w+"); // open file for writing
   fprintf(fp, "%s", s_value);  // send the s_value to the file
   fclose(fp);  // close the file using the file pointer
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

