int soundsensor = 2;
int led = 12; 

void setup() 
{ 
  pinMode(soundsensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
  int sensorvalue = digitalRead(soundsensor);
                                                         
  if (sensorvalue == 1)                                    
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
  
}
