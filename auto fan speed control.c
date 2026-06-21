#include<pic.h>

#define rs RC5
#define rw RC6
#define en RC7
#define ena RC0
#define in2 RC1

void delay()
{
int i;
for(i=0;i<=1000;i++);
}

void cmd(char a)
{
  PORTD=a;
  rs=0;
  rw=0;
  en=1;
  delay();
  en=0;
}

void lcd_init()
{
  cmd(0x38);
  cmd(0x01);
  cmd(0x06);
  cmd(0x0C);
  cmd(0x80);
}

void dat(char b)
{
  PORTD=b;
  rs=1;
  rw=0;
  en=1;
  delay();
  en=0;
}

void print(char *s)
{
  while(*s)
	{
	dat(*s++);
	}
}

void duty_cycle(unsigned int duty)
{
 CCPR1L = duty >> 2;
 CCP1Y = duty & 0x02;
 CCP1X = duty & 0x01;
}

void adc()
{
	TRISA0=1;
    long temp;
    ADCON1=0xc0;                    
    ADCON0=0x85;                   
    while(GODONE);               
    temp=((ADRESH<<8)|(ADRESL));   
    temp=((temp*500)/1023);
    dat(((temp/100)%10)+48);
    dat(((temp/10)%10)+48);
    dat((temp%10)+48);  
	dat(0xDF);
	print("C"); 
	cmd(0xCB);
    if(temp<25)
	{
	 duty_cycle(0);
  	 cmd(0xCB);
	 print("OFF ");
	}
    else if(temp >= 25 && temp < 30)
	{
	 duty_cycle(256);
  	 cmd(0xCB);
	 print("LOW ");
	}
    else if(temp >= 30 && temp <= 50)
	{
	 duty_cycle(512);
  	 cmd(0xCB);
	 print("MED ");
	}
    else if(temp>50)
	{
	 duty_cycle(1023);
  	 cmd(0xCB);
	 print("HIGH");
	}
}

void pwm()
{
 TRISC2=0;
 PR2 = 249;     
 CCP1M3 = 1;
 CCP1M2 = 1;  
 T2CKPS1 = 0;
 T2CKPS0 = 1;     
 TMR2ON = 1;
}

void main()
{
  ena=0;
  TRISD=TRISC0=TRISC1=TRISC5=TRISC6=TRISC7=0;
  lcd_init();
  pwm();
  in2=0;
  cmd(0x80);
  print("TEM VAL:");
  cmd(0xC0);
  print("FAN SPEED:");
  while(1)
  {
	cmd(0x89);
	ena=1;
	adc();
    delay();
  }
}

