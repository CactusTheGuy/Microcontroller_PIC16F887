#include <Work1.h>
unsigned int8 byte_c = 0; //Store the number of time LED blink
unsigned int8 start_hold = 0; //Make LED blinking even if START is released after press

void main()
{
   set_tris_b(0x00); //Setup port B to all input
   set_tris_c(0xff); //Setup port C to all output
   set_tris_d(0x00); //Setup port D to all input
   output_low(PIN_B0);
   while(TRUE) //Program start
   {
      if (!input(PIN_D0)) //Check if the SET button is pressed
      {
         byte_c++;
         output_c(byte_c);
         delay_ms(100);
      }
      if (!input(PIN_D1)) //Check if the START button is pressed
      {
         if (byte_c==0) //Check if the varible have possitive number
         {
            start_hold=0;
         }
         if (start_hold>1) //Check if the START button is being hold or pressed multiple times
         {
            start_hold=1;
         }
      else //Register the button into variable
      {
         start_hold++;
         delay_ms(100);
      }
      }
      if (start_hold>0 & (byte_c>0)) //Check if the varibles is a possitive number
      {
         byte_c--;
         output_c(byte_c);
         output_high(PIN_B0);
         delay_ms(500);
         output_low(PIN_B0);
         delay_ms(500);
         if (byte_c==0) //Check if the varible reached 0
         {
            start_hold=0;
         }
      }
   }
}
//Submitted by 22842192
//Submitted to HCMC University of Technology and Education
//Available on https://github.com/CactusTheGuy/Microcontroller_PIC16F887 for archive
