//LED: PB4/PB5/PC2/PC3
#define Set_Bit(val, bitn)    (val |=(1<<(bitn)))
#define Clr_Bit(val, bitn)     (val&=~(1<<(bitn)))
#define Get_Bit(val, bitn)    (val &(1<<(bitn)) )
//MS PD2/3/4
//SETP PD6,PWM接口
//DIR PD5
//EN PB0
//LIMIT PB1
#define DEV_ID 0x01

#define LedRed1 Set_Bit(PORTB,4);Set_Bit(PORTC,3)
#define LedRed0 Clr_Bit(PORTB,4);Clr_Bit(PORTC,3)
#define LedGreen1 Set_Bit(PORTB,5);Set_Bit(PORTC,2)
#define LedGreen0 Clr_Bit(PORTB,5);Clr_Bit(PORTC,2)

#define Limit (PINB & 0x02) == 0x02
#define En1 Set_Bit(PORTB,0)
#define En0 Clr_Bit(PORTB,0)
#define P1 Set_Bit(PORTD,6)
#define P0 Clr_Bit(PORTD,6)
#define D1 Set_Bit(PORTD,5)
#define D0 Clr_Bit(PORTD,5)
#define MS1_1 Set_Bit(PORTD,2)
#define MS1_0 Clr_Bit(PORTD,2)
#define MS2_1 Set_Bit(PORTD,3)
#define MS2_0 Clr_Bit(PORTD,3)
#define MS3_1 Set_Bit(PORTD,4)
#define MS3_0 Clr_Bit(PORTD,4)

#define Set 1
#define Reset 0

int Buff[10];
int Dir,Speed,Distance;


void setup()
{
  DDRC = 0xff;//c端口初始化为输出
  DDRB = 0xff;
  PORTB = 0xff;//b端口初始化为高电平
  LedGreen0;
  LedRed1;
  En0;//驱动使能
  MS1_1;
  MS2_1;
  MS3_1;//
  Serial.begin(4800);
}

void Run(int DIR,int SPEED,int DISTANCE)//方向 速度 距离
{
  unsigned int STEP;
  STEP = DISTANCE*3200*5;
  if(DIR == Reset)
  {D1;}
  else if(DIR == Set)
  {D0;}
  while(STEP--)
  {
    LedGreen0;
    LedRed1;
    P1;
    delayMicroseconds(70-(SPEED*5));//频率越大速度越大
    P0;
    delayMicroseconds(70-(SPEED*5));
  }
  LedGreen1;
  LedRed0;
}
void Motor_Reset()
{
    while(Limit)
    {
      Run(Reset,5,1);
     }
}
void loop()
{
	static int aa = 0,i = 0;
	int Rec,Val;
	
	while(Serial.available())
	{
		Rec = Serial.read();
		if(Rec == 0xaa)//接收第一个字节 起始位
			aa=0x80;
		if(aa==0x80)
			Buff[i++]=Rec;
		if((i==6)&&(Buff[5]==0xff))//校验终止位
		{
			i=0;
			aa=0;
			Val = Buff[1]+Buff[2]+Buff[3];
			if(Val == Buff[4])
			{
				Dir = Buff[1];
				Speed = Buff[2];
				Distance = Buff[3];
			}
		}
	}
	delay(500);
	
	Run(Dir,Speed,Distance);
	
	Dir = 0;
	Speed = 0;
	Distance = 0;
  
} 
