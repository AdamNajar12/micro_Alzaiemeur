#line 1 "C:/Users/Public/Documents/Mikroelektronika/mikroC PRO for PIC/Examples/Projet microcontroleur/Micro Alzaiemeur/MicroAlzaiemer.c"
sbit LCD_RS at RD5_bit;
sbit LCD_EN at RD4_bit;
sbit LCD_D4 at RD0_bit;
sbit LCD_D5 at RD1_bit;
sbit LCD_D6 at RD2_bit;
sbit LCD_D7 at RD3_bit;

sbit LCD_RS_Direction at TRISD5_bit;
sbit LCD_EN_Direction at TRISD4_bit;
sbit LCD_D4_Direction at TRISD0_bit;
sbit LCD_D5_Direction at TRISD1_bit;
sbit LCD_D6_Direction at TRISD2_bit;
sbit LCD_D7_Direction at TRISD3_bit;

unsigned int temperature=0;

float mV;
float k;
unsigned char txt[15];
int i;


char txt1[] ="temp =";
int test1;
int test2;
int test3;

void main() {


Sound_init(& portc,3);
TRISB=0XF1;
TRISC=0;
TRISD=0;
TRISA=0;
INTCON.GIE=1;
INTCON.RBIE=1;



 INTCON.INTE=1;
 option_reg.intedg=1;



 Lcd_Init();

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1,1,"Anti Alzaimer SYS:");


 Delay_ms(1000);
 Lcd_Cmd(_LCD_CLEAR);
 Delay_ms(2000);
 Lcd_Out(1,1,"have a good Time !!!");
 Delay_ms(2000);
 Lcd_Cmd(_LCD_CLEAR);

 Lcd_Out(1,1,txt1);
 Lcd_Chr(2,8,233);

 Lcd_Cmd(_LCD_CLEAR);

 Lcd_Out(1,1,txt1);

 Delay_ms(1000);


 ADCON1=0x0E;




 TRISA.RA0=1;

 ADC_Init();

 Lcd_Init();

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);

 Lcd_Cmd(_LCD_CLEAR);

 Lcd_Out(1,1,txt1);
 Lcd_Chr(2,8,233);
 Lcd_Chr(2,9,'C');

 temperature =0;
 do {
 temperature=ADC_Read(0);

 mV= temperature*5000.0/1024.0;

 mV=mV/10.0;


 if (mv <= 9)
 {
 test1=0;
 while (test1 ==0)
 {
 porta.ra2=1;
 delay_ms(500);
 porta.ra2=0;
 porta.ra2=1;
 delay_ms(500);
 porta.ra2=0;
 porta.ra2=1;
 delay_ms(500);
 porta.ra2=0;
 test1=1;
 }
 FloatToStr(mV,txt);

 txt[4]=0;
 Lcd_Out(2,3,txt);

 Delay_ms(500);

 }
 else if( mv <=39 && mv >9)
 {
 test2=0;
 while (test2==0)
 {
 porta.ra1=1;
 delay_ms(1000);
 porta.ra1=0;
 test2=1;
 }

 FloatToStr(mV,txt);

 txt[4]=0;
 Lcd_Out(2,3,txt);

 Delay_ms(1000);

 }
 else if (mv > 39)
 {
 test3=0;
 while (test3 ==0)
 {
 porta.ra3=1;
 delay_ms(1000);
 porta.ra3=0;
 test3=1;
 }
 FloatToStr(mV,txt);

 txt[4]=0;
 Lcd_Out(2,3,txt);

 Delay_ms(1000);


 }

 FloatToStr(mV,txt);

 txt[4]=0;
 Lcd_Out(2,3,txt);

 Delay_ms(500);

 } while(1);

}
void interrupt()
{

if (INTCON.INTF==1)
{
 Sound_Play(659, 250);
 INTCON.INTF=0;
 porta.ra2=1;
 delay_ms(1000);
 porta.ra2=0;
 porta.ra2=1;
 delay_ms(1000);
 porta.ra2=0;
 porta.ra2=1;
 delay_ms(1000);
 porta.ra2=0;
}
if (INTCON.RBIF==1)
{

 if (portb.rb4==1)
 {

 while(portb.rb5!=1 && portb.rb4!=0)
 {

 portc.rc2=1;
 portc.rc1=0;
 porta.ra1=1;
 delay_ms(500);
 porta.ra1=0;

 portc.rc2=0;
 portc.rc1=0;

 }

 INTCON.RBIF=0;
 }
 else if (portb.rb5==1 && portb.rb4==0)
 {

 while(portb.rb5!=0 && portb.rb4!=1)
 {
 portc.rc2=0;
 portc.rc1=1;
 delay_ms(2000);
 portc.rc2=0;
 portc.rc1=0;

 }
 INTCON.RBIF=0;
 }


 if (portb.rb6==1 && INTCON.INTF==0)
 { while(portb.rb7!=1 && portb.rb6!=0)
 {

 portc.rc5=1;
 portc.rc4=0;
 porta.ra1=1;
 delay_ms(1000);
 porta.ra1=0;
 portc.rc5=0;
 portc.rc4=0;


 }
 INTCON.RBIF=0;
 }
 else if (portb.rb6==1 && INTCON.INTF==1)
 { while(portb.rb7!=0 && portb.rb6!=1)
 {

 portc.rc5=0;
 portc.rc4=1;
 delay_us(1000);
 portc.rc5=0;
 portc.rc4=0;




 }
 porta.ra2=1;
 delay_ms(3000);
 porta.ra2=0;
 INTCON.RBIF=0;
 }
 else if (portb.rb7==1 && portb.rb6==0)
 {

 while(portb.rb7!=0 && portb.rb6!=1)
 {
 portc.rc5=0;
 portc.rc4=1;
 delay_us(1000);
 portc.rc5=0;
 portc.rc4=0;
 }
 INTCON.RBIF=0;
 }

}



}
