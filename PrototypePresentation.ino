
/* YourDuinoStarter_SerialMonitor_SEND_RCVE<br> - WHAT IT DOES: 
   - Receives characters from Serial Monitor
   - Displays received character as Decimal, Hexadecimal and Character
   - Controls pin 13 LED from Keyboard
 - SEE the comments after "//" on each line below
 - CONNECTIONS:
   - None: Pin 13 built-in LED
   - 
 - V1.00 02/11/13
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include "dht.h"
#include <SPI.h>
#include <MFRC522.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define led 13  // built-in LED
#define dht_apin A0 // Analog Pin sensor is connected to
#define Enable 8
#define DIRA 6
#define DIRB 7 
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
dht DHT;
/*-----( Declare objects )-----*/
/*-----( Declare Variables )-----*/
int ByteReceived;
int redPin = 13;
int greenPin = 12;
int bluePin = 11;

int BlueL = 9;
int GreenR = 10;

int tempPin = A0;

int temp;
int tempMin = 26;   // the temperature to start the fan
int tempMax = 30;   // the maximum temperature when fan is at 100%
int fanSpeed;

// Color arrays
int black[3]  = { 0, 0, 0 };
int white[3]  = { 100, 100, 100 };
int red[3]    = { 100, 0, 0 };
int green[3]  = { 0, 100, 0 };
int blue[3]   = { 0, 0, 100 };
int yellow[3] = { 40, 95, 0 };
int dimWhite[3] = { 30, 30, 30 };
// etc.


// Set initial color
int redVal = black[0];
int grnVal = black[1]; 
int bluVal = black[2];

int wait = 10;      // 10ms internal crossFade delay; increase for slower fades
int hold = 0;       // Optional hold when a color is complete, before the next crossFade
int DEBUG = 1;      // DEBUG counter; if set to 1, will write values back via serial
int loopCount = 60; // How often should DEBUG report?
int repeat = 0;     // How many times should we loop before stopping? (0 for no stop)
int j = -100;          // Loop counter for repeat
int W = 0;

// Initialize color variables
int prevR = redVal;
int prevG = grnVal;
int prevB = bluVal;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600); 

  ////////////////Temp Code//////////////////
  delay(500);//Delay to let system boot
  delay(1000);//Wait before accessing Sensor
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  pinMode(Enable, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  ///////////////End of Temp Code////////////////////
  pinMode(BlueL, OUTPUT);
  pinMode(GreenR, OUTPUT);
  /////////////////RFID CODE/////////////////
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  ////////////////////////////////////////////
 
 
}
//--(end setup )---

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
//  {
//    if (W<2){
//        // Look for new cards///////////////////
//              if ( ! mfrc522.PICC_IsNewCardPresent()) 
//                 {
//                  return;
//                 }
//                
//      // Select one of the cards///////////////////
//      
//              if ( ! mfrc522.PICC_ReadCardSerial()) 
//                 {
//                  return;
//                 }
//                 
//     //Show UID on serial monitor/////////////////////
//     
//              Serial.print("UID tag :");
//              String content= "";
//              byte letter;
//              for (byte i = 0; i < mfrc522.uid.size; i++) 
//                    {
//                      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//                      Serial.print(mfrc522.uid.uidByte[i], HEX);
//                      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//                      content.concat(String(mfrc522.uid.uidByte[i], HEX));
//                    }
//              Serial.println();
//              Serial.print("Message : ");
//              content.toUpperCase();
//              if (content.substring(1) == "B0 87 E9 A2") //change here the UID of the card/cards that you want to give access
//                    {
//                      Serial.println("Authorized access");
//                      Serial.println();
//                      delay(3000);
//                      W = 4;
//                    } 
//              else 
//                      {
//                        Serial.println(" Access denied");
//                        delay(3000);
//                      }
//          } 
//  }


          
////// End of RFID Code///////////////

  if (Serial.available() > 0)
      {
        ByteReceived = Serial.read();
        digitalWrite(Enable, HIGH);

        if(ByteReceived == '1') // Single Quote! This is a character.
            {
              setColor(0, 255, 255);  // purple;
            }
            
        if(ByteReceived == '2') // Single Quote! This is a character.
            {
              setColor(255, 0, 0);  // red;
            }
            
        if(ByteReceived == '3') // Single Quote! This is a character.
            {
              setColor(0, 255, 0);  // green;
            }
          
        if(ByteReceived == '4') // Single Quote! This is a character.
            {
              setColor(0, 0, 255);  // blue; 
            }
          
        if(ByteReceived == '5') // Single Quote! This is a character.
            {
              setColor(255, 255, 0);  // Aqua;
            }
          
        if(ByteReceived == '6') // Single Quote! This is a character.
            {
              setColor(80, 0, 80);  // Yellow;
            }
            
        if(ByteReceived == '7') // Single Quote! This is a character.
            {
              setColor(255, 255, 255);  // White;
            }
            
        if (ByteReceived =='8')
            {
              digitalWrite(GreenR, HIGH);
            }
            
        if (ByteReceived =='Y')
            {
              digitalWrite(GreenR, LOW);
            }
    
        if (ByteReceived =='Q')
            {
              digitalWrite(BlueL, HIGH);
            }
            
        if (ByteReceived =='X')
            {
              digitalWrite(BlueL, LOW);
            }
    
    
        if(ByteReceived == 'A')
           {
              { crossFade(red);
                crossFade(green);
                crossFade(blue);
                crossFade(yellow);
      
                if (repeat) // Do we loop a finite number of times?
                    {
                      j += 1;
                    }
                    
                if (j >= repeat)  // Are we there yet?
                    {
                      exit(j);         // If so, stop.
                    }
                    
                }
             }
           
        if(ByteReceived == '9') // Single Quote! This is a character.
          
           {
               setColor(30, 30, 30);  // DimWhite;
           }
           
        if(ByteReceived == '0') // Light turns off
           
           {
              setColor(0, 0, 0);
           }

           
      ///////////////////////////////////////////////////////// Temp Code//////////////////////////////

      
        if(ByteReceived == 'T')
             {
              DHT.read11(dht_apin);
              
              Serial.print("Current humidity = ");
              Serial.print(DHT.humidity);
              Serial.print("%  ");
              Serial.print("temperature = ");
              Serial.print(DHT.temperature); 
              Serial.println("C  ");
              
              delay(3000);//Wait 5 seconds before accessing sensor again.
           
            //Fastest should be once every two seconds.///////////////////// End of Temp Code/////////////////////
              }

      }
 Serial.println();    // End the line

 // END Serial Available////////////////////////////////
 
  DHT.read11(dht_apin);
  temp = DHT.temperature;  // get the temperature
  
  if(temp < tempMin)    // if temp is lower than minimum temp
     {
         digitalWrite(Enable, LOW);
         delay(1000);       
     } 
   
  if((temp >= tempMin) && (temp <= tempMax))   // if temperature is higher than minimum temp
     {
         digitalWrite(Enable, HIGH); 
         digitalWrite(DIRA,HIGH); // the actual speed of fan
         digitalWrite(DIRB,LOW);
     }
     
  
  
}



//--(end main loop )---

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

/*-----( Declare User-written Functions )-----*/
int calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}

/* The next function is calculateVal. When the loop value, i,
*  reaches the step size appropriate for one of the
*  colors, it increases or decreases the value of that color by 1. 
*  (R, G, and B are each calculated separately.)
*/

int calculateVal(int step, int val, int i) {
  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}

/* crossFade() converts the percentage colors to a 
*  0-255 range, then loops 1020 times, checking to see if  
*  the value needs to be updated each time, then writing
*  the color values to the correct pins.
*/

void crossFade(int color[3]) {
  // Convert to 0-255
  int R = (color[0] * 255) / 100;
  int G = (color[1] * 255) / 100;
  int B = (color[2] * 255) / 100;

  int stepR = calculateStep(prevR, R);
  int stepG = calculateStep(prevG, G); 
  int stepB = calculateStep(prevB, B);

  for (int i = 0; i <= 1020; i++) {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);

    analogWrite(redPin, redVal);   // Write current values to LED pins
    analogWrite(greenPin, grnVal);      
    analogWrite(bluePin, bluVal); 

    delay(wait); // Pause for 'wait' milliseconds before resuming the loop

//    if (DEBUG) { // If we want serial output, print it at the 
//      if (i == 0 or i % loopCount == 0) { // beginning, and every loopCount times
//        Serial.print("Loop/RGB: #");
//        Serial.print(i);
//        Serial.print(" | ");
//        Serial.print(redVal);
//        Serial.print(" / ");
//        Serial.print(grnVal);
//        Serial.print(" / ");  
//        Serial.println(bluVal); 
//      } 
//      DEBUG += 1;
//    }
    }
  // Update current values for next loop
  prevR = redVal; 
  prevG = grnVal; 
  prevB = bluVal;
  delay(hold); // Pause for optional 'wait' milliseconds before resuming the loop
}
/*********( THE END )***********/
