#include <Bai4.h>
#define RS PIN_E0
#define RW PIN_E1
#define E PIN_E2
unsigned int16 Temp, VariRes;
float VR_Value, T_Value;
float StepSize = 4.887;

void lcd_command(unsigned int8 cm)  //This function is used to command where the characters is displaying to LCD display
{
   output_low(RW);
   output_low(RS);
   output_d(cm);
   output_low(E);
   output_high(E);
   delay_ms(1); 
}
void lcd_data(unsigned int8 dt)  //This function is used to display a set ASICII characters to LCD display
{
   output_low(RW);
   output_high(RS);
   output_d(dt);
   output_low(E);
   output_high(E);
   delay_ms(1);   
}
void lcd_setup()  //This function is used to set up the LCD display when powered on
{
   delay_ms(5);
   lcd_command(0x38);
   delay_ms(5);
   lcd_command(0x0c);
   lcd_command(0x06);
   lcd_command(0x01);
   delay_ms(2);
}
void main()  //Main program start
{
   set_tris_a(0xff);  //Set port A to all input
   set_tris_c(0x00);  //Set port C to all output
   set_tris_d(0x00);  //Set port D to all output
   set_tris_e(0x00);  //Set port E to all output
   lcd_setup();  //Run the function command
   setup_adc(ADC_CLOCK_DIV_8);  //Set up the ADC so the ADC is run at processor speed divide by 8
   setup_adc_ports(sAN0|sAN1|VSS_VDD);  //Set up what port of ADC is used
   while(TRUE)
   {
      set_adc_channel(0);  //Switch to channel 0 of ADC
      delay_ms(1);  //Add delay to switch the channel
      T_Value=read_adc();  //Read the value from ADC and import to a variable
      Temp=(StepSize*T_Value)/10;  //Calculate the tempeture using formula
      lcd_command(0x80); //Run the function command (Characters start at first line)
      lcd_data("Nhiet Do: ");  //Display the ASICII with specified word
      lcd_data((temp/10)+ 0x30);
      lcd_data((temp%10)+ 0x30);
      lcd_data(0xDF);  //Typing out the int8 data due to unable to type out the character
      lcd_data("C");
      set_adc_channel(1);  //Switch to channel 1 of ADC
      delay_ms(1);  //Add delay to switch the channel
      VR_Value=read_adc(); //Read the value from ADC and import to another variable
      VariRes=(100*VR_Value)/1023;  //Calculate the variable resistor using formula to output the set tempeture
      lcd_command(0xc0);  //Run the function command (Characters start at second line)
      lcd_data("Nhiet Do Dat: ");  //Display the ASICII with specified word
      lcd_data((VariRes/10)+ 0x30);
      lcd_data((VariRes%10)+ 0x30);
      lcd_data(0xDF);  //Typing out the int8 data due to unable to type out the character
      lcd_data("C");
      if (temp>VariRes)  //Check if the calculated tempeture value is higher than the calculated value of set tempeture
      {
         output_high(PIN_C0);
      }
      else  //If condition is not meet, run from this line instead
      {
         output_low(PIN_C0);
      }
   }
}
//Submitted by 22842192
//Submitted to HCMC University of Technology and Education
//Available on https://github.com/CactusTheGuy/Microcontroller_PIC16F887 for archive
