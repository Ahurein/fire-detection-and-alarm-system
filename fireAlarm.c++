
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//defining pins
const int en = 2 , rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

//I2C address
const int i2c_addr = 0x27;

int smokeA0 = A0;
int smokeA2 = A2;
int buzzer = 13;
float sensorOneValue;
float sensorTwoValue;
int redLed = 12;
int greenLed = 10;


//Lcd safe message toggler
int showSafeText = 1;

//creating and instance
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

void setup()
{

  //
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(smokeA2, INPUT);
  Serial.begin(9600); 

  noTone(buzzer);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Set display type as 16 char, 2 rows
  lcd.begin(16,2);
  
  // Print on first row
  lcd.setCursor(0,0);
  lcd.print("You are safe");
  
  // Print on second row
  lcd.setCursor(0,1);
  lcd.print("------------");
  delay(1000);

 //shifting text to the left hand side
  if(showSafeText){
    for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
      lcd.scrollDisplayLeft();
      delay(200);
  }

//shifting text to the right hand side
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(200);
  }

//shifting text to the center
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(200);
  }

}

  
}
 
 
void loop()
{
//initializing the sensor variables
 sensorOneValue = analogRead(smokeA0);
 sensorTwoValue = analogRead(smokeA2);

Serial.print("sensorOneValue: ");
Serial.print(sensorOneValue);
Serial.print("sensorTwoValue: ");
Serial.println(sensorTwoValue);


// checking if threshold value is greater, lesser or equal to the sensor value
  if(sensorOneValue > 100){
     tone(buzzer, 1000,200);
     digitalWrite(redLed, HIGH);
     digitalWrite(greenLed, LOW);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Fire dectected");
     lcd.setCursor(0,1);
     lcd.print("L: R1, Find Exit");
     showSafeText = 0;
     
  }else if(sensorTwoValue > 150){
     tone(buzzer, 1000,200);
     digitalWrite(redLed, HIGH);
     digitalWrite(greenLed, LOW);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Fire dectected");
     lcd.setCursor(0,1);
     lcd.print("L: R2, Find Exit");
     showSafeText = 0;
     
    }else{
    noTone(buzzer);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    showSafeText = 1;

    if(sensorOneValue > 60 && sensorTwoValue > 150){
     tone(buzzer, 1000,200);
     digitalWrite(redLed, HIGH);
     digitalWrite(greenLed, LOW);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Fire dectected");
     lcd.setCursor(0,1);
     lcd.print("R1,R2 Find Exit");
     showSafeText = 0;
      
     }
    
      // Print on first row
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You are safe");
  
  // Wait 1 second
  //delay(1000);
  
  // Print on second row
   lcd.setCursor(0,1);
   lcd.print("-----------");


    
  }

 
}