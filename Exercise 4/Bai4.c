#include <Bai4.h>
#define RS PIN_E0
#define RW PIN_E1
#define E PIN_E2
unsigned int16 temp;
float StepSize = 4.887;

void lcd_command(unsigned int8 cm)
{
   output_low(RW);
   output_low(RS);
   output_d(cm);
   output_low(E);
   output_high(E);
   delay_ms(1); 
}
void lcd_data(unsigned int8 dt)
{
   output_low(RW);
   output_high(RS);
   output_d(dt);
   output_low(E);
   output_high(E);
   delay_ms(1);   
}
void lcd_setup()
{
   delay_ms(5);
   lcd_command(0x38);
   delay_ms(5);
   lcd_command(0x0c);
   lcd_command(0x06);
   lcd_command(0x01);
   delay_ms(2);
}
void main()
{
   set_tris_a(0xff);
   set_tris_c(0x00);
   set_tris_d(0x00);
   set_tris_e(0x00);
   setup_adc(ADC_CLOCK_DIV_8);
   setup_adc_ports(sAN0);
   set_adc_channel(0);
   lcd_setup();
   while(TRUE)
   {
      temp=(StepSize*read_adc())/10;
      lcd_command(0x80);
      lcd_data("Nhiet Do: ");
      lcd_data(temp/10+ 0x30);
      lcd_data(temp%10+ 0x30);
      lcd_data(0xDF);
      lcd_data("C");
      if (temp>29)
      {
         output_high(PIN_C0);
      }
      else
      {
         output_low(PIN_C0);
      }
   }
}
//Submitted by 22842192
//Submitted to HCMC University of Technology and Education
//Available on https://github.com/CactusTheGuy/Microcontroller_PIC16F887 for archive
