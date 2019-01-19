#include <LMP91000.h>
#include <Wire.h>

LMP91000 pstat = LMP91000();

int rate = 200;
//int rate = 1000;
int settling_time = 50;

const uint8_t menb = 4;
const uint8_t mux = 3;

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  analogReference(EXTERNAL);

  pinMode(menb,OUTPUT);
  pinMode(mux,OUTPUT);

  digitalWrite(menb,LOW);
  digitalWrite(mux,LOW);
  

  delay(50);
  pstat.standby();
  delay(50);
  pstat.disableFET();
  pstat.setGain(0);
  pstat.setRLoad(0);
  //pstat.setExtRefSource();
  pstat.setIntRefSource();
  pstat.setIntZ(1);
  pstat.setThreeLead();
  delay(2000); //warm-up time for the gas sensor


  while(!Serial.available());
  Serial.read();


  Serial.println("Time(ms),Vref,ADC(10-bit 3.3V)");
  for (int j = 0; j < 6; j++)
  //for (int j = 0; j < 2; j++)
  {
    pstat.setNegBias();
    for (int i = 1; i < 9; i++)
    {
      pstat.setBias(i);
      delay(settling_time);
      Serial.print(millis());
      Serial.print(",");
      Serial.print(i*-1);
      Serial.print(",");
      Serial.println(analogRead(A0));
      delay(rate);
    }
    for (int i = 7; i >= 0; i--)
    {
      pstat.setBias(i);
      delay(settling_time);
      Serial.print(millis());
      Serial.print(",");
      Serial.print(i*-1);
      Serial.print(",");
      Serial.println(analogRead(A0));
      delay(rate);
    }
    pstat.setPosBias();
    for (int i = 1; i < 3; i++)
    {
      pstat.setBias(i);
      delay(settling_time);
      Serial.print(millis());
      Serial.print(",");
      Serial.print(i*1);
      Serial.print(",");
      Serial.println(analogRead(A0));
      delay(rate);
    }
    for (int i = 1; i >= 0; i--)
    {
      pstat.setBias(i);
      delay(settling_time);
      Serial.print(millis());
      Serial.print(",");
      Serial.print(i*1);
      Serial.print(",");
      Serial.println(analogRead(A0));
      delay(rate);
    }
  }
  
  pstat.setBias(0);

}

void loop() {
  // put your main code here, to run repeatedly:

}
