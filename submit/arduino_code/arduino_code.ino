
#include <Servo.h>
int p=0;
Servo grip;
Servo pitch;
Servo yaw;
Servo roll;
String s="";
//the servos for roll,pitch and yaw are to be separatly controlled by the robot using vision based system and inverse kinematics
//the input string is of format r120080040 where 120 is angle for pitch servo,80 for yaw and 40 for roll.
//If the input string is "pick" the grip will close.
// If the input string is "release" the grip will open.
void setup() {
  Serial.begin(9600);
  grip.attach(3);
  roll.attach(5);
  yaw.attach(6);
  pitch.attach(9);
  pinMode(10,INPUT);
}

void loop() {
  if(p==1)
  {
   if(digitalRead(10)==1)
          {
          Serial.println("itemFell");  
          Serial.write('f');//object fell
          } 
  }
  int d=0;
  grip.write(0);//open position

   if(Serial.available())
   {
     String s=Serial.readString();
     if(s=="pick")
    { grip.write(130);//close position
     
     delay(500);//delay to pick
     if(digitalRead(10)==0)
     {
     p=1;
       
     Serial.println("ItemPicked");
     Serial.write('p');//indicating item picked
     }
     else
     {
       Serial.println("Item not picked");
     Serial.write('n');//indicating item not picked
     }
    }
     else if (s=="release")
     {grip.write(0);//open position
       delay(500);
      p=0;
       Serial.println("ItemReleased");
     Serial.write('q');//indicating item released
     }
     else 
     {
      if(s[0]=='r')
      {
        if(p==1)
        {
          if(digitalRead(10)==1)
          {
          Serial.println("Item fell");  
          Serial.write('f');//object fell
          }
        }
        char a=s[1];char b=s[2];char c=s[3];char d=s[4];char e=s[5];char f=s[6];
        String api=String(a+b);
        int apitch=api.toInt();
        pitch.write(apitch);
        delay(500);
        Serial.println("moving pitch to :"+apitch);
        String aya=String(c+d);
        int ayaw=aya.toInt();
        yaw.write(ayaw);
         delay(500);
        Serial.println("moving yaw to :"+ayaw);
        String aro=String(e+f);
        int aroll=aro.toInt();
        roll.write(aroll);
         delay(500);
        Serial.println("moving roll to :"+aroll);
      }
      else
      {
        Serial.println("Incorrect input ");
        Serial.write('w');//incorrect input
      }
     }
     
   }

 
 
}
