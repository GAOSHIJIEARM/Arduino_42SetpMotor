
int Buff[10];
int Dir,Speed,Distance;

void setup() 
{
  Serial.begin(4800);
}
void loop() 
{
	static int aa = 0,i = 0;
	int Rec,Val;

		Serial.write(Dir);
		delay(1);
		Serial.write(Speed);
		delay(1);
		Serial.write(Distance);
		delay(1);

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
}


  
