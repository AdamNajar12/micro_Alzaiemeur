//LCD configuration


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
//fil main n7otto el configuration entree sortie (TRISA TRISB ..)wel configuration
//taa el intrruption (INTCON.GIE=0 ou 1 si on veux utilise interruption ou non)
//(INTCON.INTE =0 si 0 manataamlouhech jimla ou 1 si 1 raho 9olna lel systeme bich nastaamlo el inteeruption fil portb RB0!!!
//(INTCON.RBIE =0 si 0 manataamlouhech jimla ou 1 si 1 raho 9olna lel systeme bich nastaamlo el inteeruption fil portb RB4--->7!!!
//feha el affichage taa LCD bima feha les fonction mtaaha eli houma fil biblio :Lcd_Cmd Lcd_init()...
//elaffichage taa el LCD 3omro maysir fil void interrupt () !!!
void main() {
//config

Sound_init(& portc,3);
TRISB=0XF1;
TRISC=0;
TRISD=0;
TRISA=0;
//config inteeruptions
//el interruption maffam ken fil portB (idhakan fil RB0 :INTCON.INTE /idhakan min RB4-->RB7:INTCON.RBIE )
INTCON.GIE=1;// utiliser interruption//rana bich nestaamlo el interruption(bsifa 3amma)
INTCON.RBIE=1; //PORTB src interruption //rana bich nestammal el interruption amma fin ??portb RB4-->RB7(bsifa 5assa fil portb)


   //2 choisir la source RB0
    INTCON.INTE=1;
    option_reg.intedg=1;//RB0 transition de 0 a 1//front montant
//initialisation
//INTCON.INTF=0;
//INTCON.RBIF=0;
  Lcd_Init();                        // Initialize LCD

  Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
  Lcd_Out(1,1,"Anti Alzaimer SYS:");                 // Write text in first row

                   // Write text in second row
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
  ///////////////mesure de la temperature


      TRISA.RA0=1; //RA0 comme entree

      ADC_Init();  //initialiser ADC

  Lcd_Init();                        // Initialize LCD

  Lcd_Cmd(_LCD_CLEAR);               // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);          // Cursor off
               // Write text in second row
  Lcd_Cmd(_LCD_CLEAR);               // Clear display

  Lcd_Out(1,1,txt1);
  Lcd_Chr(2,8,233);
  Lcd_Chr(2,9,'C'); //ecrire 'C' comme celsuse

  temperature =0;
  do {
  temperature=ADC_Read(0);//recuperer 10-bit resultante du AD conversions

  mV= temperature*5000.0/1024.0;
      //convertir vers mV 1024.0 est un AD resolution 10-bits ,, 2^10=1024
  mV=mV/10.0;

    //convertire mV en temperature Celsuise
  if (mv <= 9)
  {
  test1=0;
  while (test1 ==0)
  {
  porta.ra2=1;
  delay_ms(500);
  porta.ra2=0;
  porta.ra2=1;
  delay_ms(500);    //led rouge clignote 3 fois
  porta.ra2=0;
  porta.ra2=1;
  delay_ms(500);
  porta.ra2=0;
  test1=1;
  }
   FloatToStr(mV,txt);
       //convertir la temperature en string (chaine de caracteres)
    txt[4]=0;
    Lcd_Out(2,3,txt);
    //ecrire cette chaine de caractere dans la 2eme ligne
    Delay_ms(500);
    //attendre 0.3 secondes
  }
  else if( mv <=39 && mv >9)
  {
    test2=0;
  while (test2==0)
  {
  porta.ra1=1;
  delay_ms(1000);     //led vert allume pendant une seconde
  porta.ra1=0;
  test2=1;
  }

   FloatToStr(mV,txt);
       //convertir la temperature en string (chaine de caracteres)
    txt[4]=0;
    Lcd_Out(2,3,txt);
    //ecrire cette chaine de caractere dans la 2eme ligne
    Delay_ms(1000);
    //attendre 0.3 secondes
  }
  else if (mv > 39)
  {
  test3=0;
  while (test3 ==0)
  {
  porta.ra3=1;
  delay_ms(1000);     //led bleu allume pendant une seconde
  porta.ra3=0;
  test3=1;
  }
   FloatToStr(mV,txt);
       //convertir la temperature en string (chaine de caracteres)
    txt[4]=0;
    Lcd_Out(2,3,txt);
    //ecrire cette chaine de caractere dans la 2eme ligne
    Delay_ms(1000);
    //attendre 0.3 secondes

  }

   FloatToStr(mV,txt);
       //convertir la temperature en string (chaine de caracteres)
    txt[4]=0;
    Lcd_Out(2,3,txt);
    //ecrire cette chaine de caractere dans la 2eme ligne
    Delay_ms(500);
    //attendre 0.3 secondes
  } while(1);

}
void interrupt()
{
INTCON.INTF //portb.rb0
if (INTCON.INTF==1) //changement sur RB0 0->1 --> intcon.intg=1 appel du flag
{
  Sound_Play(659, 250);//lorsque le malade appui sur l'alerte
  INTCON.INTF=0;
  porta.ra2=1;
  delay_ms(1000);
  porta.ra2=0;
  porta.ra2=1;
  delay_ms(1000);    //led rouge clignote 3 fois pendant 3 secondes (alertes)
  porta.ra2=0;
  porta.ra2=1;
  delay_ms(1000);
  porta.ra2=0;
}
if (INTCON.RBIF==1)
{
//STORE 1
      if (portb.rb4==1)
      {

       while(portb.rb5!=1 && portb.rb4!=0)//idhakan el bouton1 mezel ye5dem (fil 1)
          {
         //moteur horaire   //si rc2 ==1 et rc1 ==0 sens horaire
          portc.rc2=1;
          portc.rc1=0;//el moutour idour 3alisar
          porta.ra1=1;
          delay_ms(500); //tcha3al el led
          porta.ra1=0;
          //il faut arreter le moteur
          portc.rc2=0; //tasakr el moitour ou twa9fo
          portc.rc1=0;

          }

          INTCON.RBIF=0;//lezem dima naamlo intialisation taa les interrp elli fil potb bich ta9ra les interruptions lo5rina
      }
      else if (portb.rb5==1 && portb.rb4==0)
      {
         //moteur anti horaire
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

//STORE 2
      if (portb.rb6==1 && INTCON.INTF==0) //sortie avec payment
      { while(portb.rb7!=1 && portb.rb6!=0)
          {
         //moteur horaire   //si rc2 ==1 et rc1 ==0 sens horaire
          portc.rc5=1;
          portc.rc4=0;
          porta.ra1=1;
          delay_ms(1000);
          porta.ra1=0;
          portc.rc5=0;
          portc.rc4=0;
          //afficher sur lcd

          }
          INTCON.RBIF=0;
      }
      else if (portb.rb6==1 && INTCON.INTF==1) // //capt3 and BUZZEUR=1
      { while(portb.rb7!=0 && portb.rb6!=1)
          {
         //moteur horaire   //si rc2 ==1 et rc1 ==0 sens horaire  //fermeture du STORE2
          portc.rc5=0;
          portc.rc4=1;
          delay_us(1000);
          portc.rc5=0;
          portc.rc4=0;
          //LedROUGE



          }
                    porta.ra2=1;
          delay_ms(3000);
          porta.ra2=0;
          INTCON.RBIF=0;
      }
      else if (portb.rb7==1 && portb.rb6==0)
      {
         //moteur anti horaire
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