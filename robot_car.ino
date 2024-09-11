/**************************MOSA2 robot****************************************************
breif:MOSA2 robot
names: arwa gamal
       ahmed osama
       mayar
      sara
      omar
Date : 9/7/2024

**************************MOSA2 robot****************************************************/

/**************************library files start****************************************************/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define in1 14 //L298n Motor Driver pins.
#define in2 15
#define in3 16
#define in4 17
/**************************library files end****************************************************/

/**************************pins definitio start****************************************************/
//L298n Motor Driver pinsdifinition
#define in1 14 
#define in2 15
#define in3 16
#define in4 17

//  LED pins definitio
#define light_F  3    //LED Front Right   pin A0 for Arduino Uno
#define light_L  4   //LED Front Left    pin A1 for Arduino Uno
#define light_R  5   //LED Back Right    pin A2 for Arduino Uno
#define light_B  6   //LED Back Left     pin A3 for Arduino Uno
//  LCD pins definitio
LiquidCrystal_I2C lcd(0x27, 16, 2);//size of screen 16x2

//  VARIABLES definitio
int command; //Int to store app command state.
int Speed = 204; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.
/**************************pins definitio end****************************************************/

/**************************setup start****************************************************/

void setup() {
    //motor mode
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

      //leds mode
   pinMode(light_F, OUTPUT);
    pinMode(light_L, OUTPUT);
    pinMode(light_R, OUTPUT);
    pinMode(light_B, OUTPUT);
    
  
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
   
    //lcd mode 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("M O S A2");//first massage

    delay(10000);
  lcd.clear();
}
/**************************setup start****************************************************/

/**************************loop start****************************************************/

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    Stop(); //Initialize with motors stoped.
    

    switch (command) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
        
    }
    Speedsec = Turnradius;
    if (brkonoff == 1) {
      brakeOn();
    } else {
      brakeOff();
    }
  }
}

//movement  forward
void forward() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
  digitalWrite(light_F, HIGH);  // Activate Light for forward movement
  digitalWrite(light_L, LOW);
  digitalWrite(light_R, LOW);
  digitalWrite(light_B, LOW);
  // Display "forword" on the LCD when moving forward
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Forword");
  lcd.setCursor(0, 1);
lcd.print("Speed: ");
lcd.print(Speed);


}
//movement  back
void back() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
  // Activate Light for back movement
  digitalWrite(light_F, LOW);  
  digitalWrite(light_L, LOW);
  digitalWrite(light_R, LOW);
  digitalWrite(light_B, HIGH);
   
   // Display "forword" on the LCD when moving back
lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Back");
  lcd.setCursor(0, 1);
lcd.print("Speed: ");
lcd.print(Speed);
 

}
//movement  left
void left() {
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);

  // Activate Light for left movement
   digitalWrite(light_F, LOW);  
  digitalWrite(light_L, HIGH);
  digitalWrite(light_R, LOW);
  digitalWrite(light_B, LOW);

    // Display "forword" on the LCD when moving left
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("left");
  lcd.setCursor(0, 1);
lcd.print("Speed: ");
lcd.print(Speed);


}
//movement  right
void right() {
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);

   // Activate Light for right movement
  digitalWrite(light_F, LOW); 
  digitalWrite(light_L,LOW );
  digitalWrite(light_R, HIGH);
  digitalWrite(light_B, LOW);

      // Display "forword" on the LCD when moving right
lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Right");
  lcd.setCursor(0, 1);
lcd.print("Speed: ");
lcd.print(Speed);

}
//movement  forwardleft
void forwardleft() {
  analogWrite(in1, Speedsec);
  analogWrite(in3, Speed);

     // Activate Light for forwardleft movement
  digitalWrite(light_F, HIGH);  
  digitalWrite(light_L, HIGH);
  digitalWrite(light_R, LOW);
  digitalWrite(light_B, LOW);
        
        // Display "forwardleft" on the LCD when moving right
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Forward left");
  lcd.setCursor(0, 1);
lcd.print("Speed: ");
lcd.print(Speed);

}
//movement  forwardright
void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speedsec);
       // Activate Light for forwardright movement
  digitalWrite(light_F, HIGH);  
  digitalWrite(light_L, LOW);
  digitalWrite(light_R, HIGH);
  digitalWrite(light_B, LOW);
          // Display "forwardright" on the LCD when moving right
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Forward Right");
  lcd.setCursor(0, 1);
lcd.print("Speed: ");
lcd.print(Speed);
}
//movement  backright
void backright() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speedsec);
   // Activate Light for backright movement
   digitalWrite(light_F, LOW);  
  digitalWrite(light_L, LOW);
  digitalWrite(light_R, HIGH);
  digitalWrite(light_B, HIGH);
   // Display "backright" on the LCD when moving right
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Back Right");
  lcd.setCursor(0, 1);
lcd.print("Speed: ");
lcd.print(Speed);
}
//movement  backleft
void backleft() {
  analogWrite(in2, Speedsec);
  analogWrite(in4, Speed);
     // Activate Light for backleft movement
  digitalWrite(light_F, LOW);  
  digitalWrite(light_L, HIGH);
  digitalWrite(light_R, LOW);
  digitalWrite(light_B, HIGH);
    // Display "backleft" on the LCD when moving right
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Back left");
  lcd.setCursor(0, 1);
lcd.print("Speed: ");
lcd.print(Speed);
}
//stop the robot
void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
   // Turn off all Light when the car stops
   digitalWrite(light_F, LOW);  
  digitalWrite(light_L,LOW);
  digitalWrite(light_R, LOW);
  digitalWrite(light_B, LOW);
  lcd.clear();
   

}

void brakeOn() {
  //Here's the future use: an electronic braking system!
  // read the pushbutton input pin:
  buttonState = command;
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == 'S') {
      if (lastButtonState != buttonState) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        delay(brakeTime);
        Stop();
      }
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonState = buttonState;
  }
}
void brakeOff() {

}
/**************************loop end****************************************************/
/**************************MOSA2 robot****************************************************
breif:MOSA2 robot
names: arwa gamal
       ahmed osama
       mayar
      sara
      omar
Date of last change : 11/9/2024

**************************MOSA2 robot****************************************************/