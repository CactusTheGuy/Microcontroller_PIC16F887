#include <Bai1.h>
unsigned int8 byte_c = 0;  //Store the number of time LED blink
unsigned int1 start_hold = 0;  //Make LED blinking even if START is released after press

void main()
{
   set_tris_b(0xfe);  //Setup port B at B0 to output, B1 to B7 to input
   set_tris_c(0x00);  //Setup port C to all output
   set_tris_d(0xff);  //Setup port D to all input
   output_low(PIN_B0);  //Give the output pin a low signal to ensure a correct output of the pin
   output_c(byte_c);
   while(TRUE)  //Program start
   {
      if (!input(PIN_D0))  //Check if the SET button is pressed
      {
        delay_ms(10);
        if (input(PIN_D0))  //Check if SET button is released
        {
            byte_c++;
            output_c(byte_c);  //update after adding
        }
      }  //This function is used to give the SET button to register only 1 time
      if (!input(PIN_D1))  //Check if the START button is pressed
      {
         delay_ms(10);
         if (input(PIN_D1) & (start_hold==0) & (byte_c>0))
         {
             start_hold=1;
         }
      }  //This function is used to give the START button to register only 1 time
      if (start_hold==1 & (byte_c>0))  //Check if the varibles is a positive number
      {
         byte_c--;
         output_c(byte_c); //Update after subtracting
         output_high(PIN_B0);
         delay_ms(500);
         output_low(PIN_B0);
         delay_ms(500);
         if (byte_c==0)  //Check if the varible reached 0
         {
            start_hold=0;
         }
      }
   }
}
//Submitted by 22842192
//Submitted to HCMC University of Technology and Education
//Available on https://github.com/CactusTheGuy/Microcontroller_PIC16F887 for archive
