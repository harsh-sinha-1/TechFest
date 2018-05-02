#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);                                             //lcd setup
const int alcohol_pin=8, relay_pin=7, starter=10;                             //pin naming
int i;                                                                        //loop counter
int start_time,end_time;                                                      //time manager
int count=0;                                                                  //loop counter
int l=0;                                                                      //blow counter
int value,limit=0;                                                            //mq3 input variables   
double avg;                                                                   //blow percentage calculator
void setup(){
  Serial.begin(9600);                                                         //sets the baud rate
  pinMode(alcohol_pin,INPUT);                                                 //limit of alcohol
  pinMode(relay_pin,OUTPUT);                                                  //relay
  pinMode(6,OUTPUT);                                                          //always on
  pinMode(starter,INPUT);                                                     //starter
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(0,0);
  lcd.print("Alcohol Level");
}

void loop(){
  count=0;
  l=0;
  
  digitalWrite(relay_pin,HIGH);
  lcd.setCursor(0,1);
  digitalWrite(6,HIGH);
  while(1){
   digitalWrite(relay_pin,HIGH);
    count=0;
    l=0;
    Serial.print(digitalRead(starter));
    Serial.println();
    if(digitalRead(starter)==HIGH){
      start_time=millis();
      end_time=start_time;

      while(end_time-start_time<=5000)
      {
        end_time=millis();
      l=l+digitalRead(starter);
      count++;
      value= analogRead(0);//reads the analaog value from the alcohol sensor's AOUT pin
      limit=digitalRead(alcohol_pin);
      Serial.print("Alcohol value: ");
      Serial.println(limit);//prints the alcohol value
      Serial.println(value);
      if (limit==0||value>500)
      {
        lcd.print("HIGH");//if limit has been reached, LED turns on as status indicator
        lcd.setCursor(0,0);
        lcd.clear();
        lcd.print("Car Locked");
        digitalWrite(relay_pin,HIGH);
        delay(20000000);  
      }
    }
  }
  if(l>0)
  {
  avg=((l/count)*100);
  if(avg>80.00){
   digitalWrite(relay_pin,LOW);
   lcd.print("LOW");
     delay(20000000);}
  else
  {
   continue; 
  }
  }
 
  }
}
