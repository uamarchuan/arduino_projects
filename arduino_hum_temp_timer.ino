/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

/*-----( Declare Constants )-----*/
DHT dht;
const int tInterval = 60; //60
int tBrake = tInterval;
int tRest = 7;
  String sH = "H(%):";
  String sT = "T('C):";
  String sS = " ";
unsigned long seconds = 1000L; // !!! SEE THE CAPITAL "L" USED!!!
//unsigned long minutes = seconds * 59;
//unsigned long hours = minutes * 60;
const int buttonPin = 4;     // the number of the pushbutton pin
boolean sBlicking = false;
  
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 16 chars 2 line display
// A FEW use address 0x3F
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/*-----( Declare Variables )-----*/
//NONE

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  //pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT);
  dht.setup(2); // data pin 2 for sensor
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
  //-------- Write characters on the display ------------------
  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Arduino!");
  lcd.setCursor(0,1);
  lcd.print("Hello Andriy :)");  
  
  //Serial.begin(9600);
}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  sensor();
  rTime();
 
  //Serial.println(sBlicking);
  
  if (sBlicking == false) {
    //delay(minutes);
    int x = 0;
    while (x < 59) {
      delay(seconds);
      int buttonValue = digitalRead(buttonPin);
      if (buttonValue == HIGH) {
        tBrake = tInterval;
        break;
      }
      x++;
     }
  } 
}/* --(end main loop )-- */

void sensor(){
  lcd.setCursor(0,0);
  lcd.print("Waiting for data");
  delay(dht.getMinimumSamplingPeriod()); 
  int h = dht.getHumidity();
  int t = dht.getTemperature();
  String sPrintLine1 = sH+h+sS+sT+t;
  
  lcd.clear();
  lcd.setCursor(0,0); lcd.print(sPrintLine1);
}

void rTime() {
  if (tBrake > tRest){
    lcd.setCursor(0,1);
    //lcd.print("Brake in "); lcd.print(tBrake); lcd.print(" min.");
    lcd.print("Eyes rest in "); lcd.print(tBrake); lcd.print("m");
    sBlicking = false;

  }else if(tBrake > 0 && tBrake <= tRest){
    lcd.setCursor(0,1);
    lcd.print("Make a coffee ;)");
    int x = 0;
    while (x < 29) {
      lcd.display();
      delay(seconds);
      lcd.noDisplay();
      delay(seconds);
      lcd.display();
      int buttonValue = digitalRead(buttonPin);
      if (buttonValue == HIGH) {
        tBrake = tInterval+1;
        break;
      }
      x++;
    }
    sBlicking = true;
    
  } else{
    lcd.setCursor(0,1);
    lcd.print("Back to work!");
    tBrake = tInterval;
    sBlicking = false;
  }
  tBrake = tBrake-1;
}
/* ( THE END ) */
