#include <Bai2.h>
unsigned int8 SegDis[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};  //Give pre-defined value for displaying 7-segment display
unsigned int8 UpDown, Count = 0;  //Give the variables a set value
unsigned int8 Ones, Tens;  //Initilize varible to calculate value while running

void main()
{
   set_tris_b(0xff);  //Give port B all input
   set_tris_c(0x00);  //Give port C all output
   set_tris_d(0x00);  //Give port C all output
   output_c(SegDis[0]);  //Make port C display a set value to tens 7-segment display
   output_d(SegDis[0]);  //Make port D display a set value to ones 7-segment display
   while(TRUE) //Program start
   {
      if (!input(PIN_B0))  //Check if the button is pressed
      {
         delay_ms(400);  //This delay must set high due to the slowless nature of simulator and unknown reasons slowness
         if (input(PIN_B0))  //Confirming if the button is released to register a click
         {
            UpDown++;
            if (UpDown>2)  //Check if the value is reached a compared value
            {
               UpDown=1;
            }
         }
      }
      if (UpDown==1 & (Count<99))  //Check if the first variable have the value and second variable don't reach the set value
      {
         Count++;
      }
      if (UpDown==2 & (Count>0))
      {
         Count--;
      }
      Tens=Count/10;  //Get the value by divide by remainder
      Ones=Count%10;  //Get the value by divide by integer
      output_c(SegDis[Tens]);  //Display the tens segment display by the calculated value
      output_d(SegDis[Ones]);  //Display the ones segment display by the calculated value
      delay_ms(300);  //delay for human readable
   }
}
//Submitted by 22842192
//Submitted to HCMC University of Technology and Education
//Available on https://github.com/CactusTheGuy/Microcontroller_PIC16F887 for archive
