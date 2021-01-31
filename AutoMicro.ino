
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(0,1,2,3,4,5);
LiquidCrystal lcd1(0,6,2,3,4,5);
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'0','1','2','3'},
  {'4','5','6','7'},
  {'8','9','A','B'},
  {'C','D','E','F'}
};
byte rowPins[ROWS] = {23, 22, 21, 20}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {19, 18, 17, 16}; //connect to the column pinouts of the keypad

const int switchplusx=24;
const int switchminusx=25;
const int switchplusy=26;
const int switchminusy=27;  
const int switchplusz=28;
const int switchminusz=29;    

const int pul1=7;
const int dir1=8;          //X  
const int en1=9;

const int pul2=10;
const int dir2=11;        //  y
const int en2=12;

const int pul3=13;
const int dir3=14;        //  Z
const int en3=15;

float lengthmovedX=0;
float lengthmovedY=0;
float lengthX=0;
float lengthY=0;
boolean countinous=1;
boolean stepped=1;

boolean state=0;

char flag=0;
char holdKey;
char customKey;
char mode=0;

// unsigned long t_hold;
unsigned int md=100;

 
int interval=5;
// Tracks the time since last event fired
unsigned long previousMillis=0;
unsigned long currentMillis;


Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void checklimitswitch()
{
 if( digitalRead(switchplusx)==LOW)
    { enable_motors(); 
      lcd.setCursor(0, 0);
      lcd.print("STAGE-RIGHT SIDE");
      lcd.setCursor(0, 1);
      lcd.print("LIMIT REACHED   ");
      while(digitalRead(switchplusx)==LOW)
      {
       movex(0,md);
         
      }
      disable_motors();
      displayContinousModeSelected();
    }
   
    if(digitalRead(switchminusx)==LOW)
      { enable_motors(); 
      lcd.setCursor(0, 0);
      lcd.print("STAGE-LEFT SIDE ");
      lcd.setCursor(0, 1);
      lcd.print("LIMIT REACHED   ");
      while(digitalRead(switchminusx)==LOW)
      {
         movex(1,md);
       
      }
      disable_motors();
    displayContinousModeSelected();
    }
    if(digitalRead(switchplusy)==LOW)
      {  enable_motors(); 
      lcd.setCursor(0, 0);
      lcd.print("STAGE-NEAR LIMIT");
      lcd.setCursor(0, 1);
      lcd.print("REACHED         ");
      
      while(digitalRead(switchplusy)==LOW)
      {movey(0,md);
      }
      disable_motors();
      displayContinousModeSelected();
    }
    if(digitalRead(switchminusy)==LOW)
    {  enable_motors(); 
      lcd.setCursor(0, 0);
      lcd.print("STAGE-FAR LIMIT ");
      lcd.setCursor(0, 1);
      lcd.print("REACHED         ");
      
      while(digitalRead(switchminusy)==LOW)
      {
         movey(1,md);
      }
      disable_motors();
    displayContinousModeSelected();
    }
    if(digitalRead(switchplusz)==LOW)
    { enable_motors(); 
      lcd.setCursor(0, 0);
      lcd.print("FOCUSING-UP     ");
      lcd.setCursor(0, 1);
      lcd.print("LIMIT REACHED   ");
      while(digitalRead(switchplusz)==LOW)
      {
         movez(1,md);
      
      }
      disable_motors();
      displayContinousModeSelected();
    }
    if(digitalRead(switchminusz)==LOW)
    {
       enable_motors(); 
      lcd.setCursor(0, 0);
      lcd.print("FOCUSING- DOWN  ");
      lcd.setCursor(0, 1);
      lcd.print("LIMIT REACHED   ");
      while(digitalRead(switchminusz)==LOW)
      {
          movez(0,md);
      }
      disable_motors();
     displayContinousModeSelected();
    }/*else
    {
      disable_motors();
      // lcd.setCursor(0, 0);
   // lcd.print("RELEASED");
    }*/
}

void disable_motors()
{
digitalWrite(en1, LOW);
digitalWrite(en2, LOW);
digitalWrite(en3, LOW);
}

void enable_motors()
{
digitalWrite(en1, HIGH);
digitalWrite(en2, HIGH);
digitalWrite(en3, HIGH);
}

void movex(char direction1,int delay1)
{
       digitalWrite(dir1, direction1);
       digitalWrite(pul1, HIGH);
       delayMicroseconds(delay1);
       digitalWrite(pul1, LOW);
       delayMicroseconds(delay1);
}

void movey(char direction1,int delay1 )
{
  digitalWrite(dir2, direction1);
       digitalWrite(pul2, HIGH);
       delayMicroseconds(delay1);
       digitalWrite(pul2, LOW);
       delayMicroseconds(delay1);
}

void movez(char direction1,int delay1)
{
      digitalWrite(dir3, direction1);
       digitalWrite(pul3, HIGH);
       delayMicroseconds(delay1);
       digitalWrite(pul3, LOW);
       delayMicroseconds(delay1);
}
void  displayContinousModeSelected()
{
     
      lcd.setCursor(0, 0);
      lcd.print("CONTINOUS MODE  ");
      lcd.setCursor(0, 1);
      lcd.print("WORKING         ");
}

void origion()
{
   digitalWrite(en1, HIGH);
   digitalWrite(en2, HIGH);
   while(digitalRead(switchplusx)==HIGH ||  digitalRead(switchminusy)==HIGH)                      //logic to go to the origion
   { 
       if(digitalRead(switchplusx)==HIGH)
      { movex(1,1);
      }else
      {
      digitalWrite(en1, LOW);
      }
      if(digitalRead(switchminusy)==HIGH)
      {movey(1,1);
      }else
      {
      digitalWrite(en2, LOW);
      }
       
   }
   disable_motors();
}
void setup(){
  
  pinMode(pul1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(en1, OUTPUT);
  
  pinMode(pul2, OUTPUT);
  pinMode(dir2, OUTPUT); 
  pinMode(en2, OUTPUT);
  
  pinMode(pul3, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(en3, OUTPUT);
  
  pinMode(switchplusx, INPUT_PULLUP);
  pinMode(switchminusx,INPUT_PULLUP);
  pinMode(switchplusy, INPUT_PULLUP);
  pinMode(switchminusy,INPUT_PULLUP);
  pinMode(switchplusz, INPUT_PULLUP);
  pinMode(switchminusz,INPUT_PULLUP);
  lcd1.begin(16, 2);
  lcd.begin(16, 4);
  
   disable_motors(); 
  
   lcd1.setCursor(3, 0);
   lcd1.print("ERMASCOPE");
   lcd1.setCursor(2, 1);
   lcd1.print("DIGITAL MTR");
   lcd.setCursor(3, 0);
   lcd.print("ERMASCOPE");
   lcd.setCursor(2, 1);
   lcd.print("DIGITAL  MTR");
   lcd.setCursor(1, 2);
   lcd.print("MOTORIZED MODE");
   delay(3000);
   lcd.clear();
   lcd.print("SELECT MODE     ");
   lcd.setCursor(0, 1);
   lcd.print("1.CONTINOUS     ");
   lcd.setCursor(0, 2);
   lcd.print("2.STEPPED       ");
   lcd.setCursor(0, 3);
   lcd.print("3.SCAN          ");
  
}


   //**************************************  START OF while to check CONTINOUS & STEPPED MODE 
   void loop()
   {  
    
     //**************************************  START OF checking switch press of  CONTINOUS MODE
               customKey = customKeypad.getKey();                                                               // &stepped mode 
      if(customKey=='E')
     {  lcd.clear();
     displayContinousModeSelected();
      
          while(1)
     {
      customKey = customKeypad.getKey();
     // holdKey='!';
     if(customKey)
     { // lcd.setCursor(0, 1);
      //lcd.print(customKey);
      holdKey = customKey;
      md=100;
      
     }

     if(customKeypad.getState()==HOLD)
 {
      enable_motors();
      
      switch(holdKey)
    {
       case '1':
       movex(1,md);
       break;
       
        case '0':
        movex(0,md);
        break;
        
       case '9':
       movey(1,md);
       break;
       
       case '8':
       movey(0,md);
       break;
       
        case '3':
        movez(1,md);
        break;
       
        case '2':
        movez(0,md);
        break;
       
        case '7':
        movez(1,500);
        break;
       
        case '6':
        movez(0,500);
        break;
       
        case 'B':
        movez(1,1000);
        break;
       
        case 'A':
         movez(0,1000);
        break;
       
      
    }
    
     currentMillis = millis();
      if ((unsigned long)(currentMillis - previousMillis) >= interval)                  //To increase the speed of motor
    {    md--;
        previousMillis = currentMillis;
        
        if(md<50)
        {md=50;
        }
      //  delay(2);
    }
 
    } //*************************************  END OF if(customKeypad.getState()==HOLD)*******
   else
      {
  
    disable_motors();
      }
       checklimitswitch();
    }
    }  
     //**********end of countinous while        





     
     else if(customKey=='F')
     {   
    lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("STEPPED MODE");
    lcd.setCursor(0, 1);
   lcd.print("SELECTED");  
   md=200;
   char modex=1;
   char modey=1; 
   unsigned int steps_x=0;
   unsigned int steps_y=0;
  origion();
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("MOVED TO");
   lcd.setCursor(0, 1);
   lcd.print("ORIGION"); 
   lcd.clear();
   delay(1000);
   while(1)
   { customKey = customKeypad.getKey();
        
      // holdKey='!';
     if(customKey)
     {  lcd.setCursor(0, 1);
      lcd.print(customKey);
      holdKey = customKey;
      md=50;
     }
 if(customKeypad.getState()==HOLD)
    {
 /* if(micros()-t_hold>1)
    
     */ 
     enable_motors();
      
      switch(holdKey)
    {
       case '3':
        movez(1,md);
        break;
       
        case '2':
        movez(0,md);
        break;
       
        case '7':
        movez(1,500);
        break;
       
        case '6':
        movez(0,500);
        break;
       
        case 'B':
        movez(1,1000);
        break;
       
        case 'A':
         movez(0,1000);
        break;
    }

    currentMillis = millis();
      if ((unsigned long)(currentMillis - previousMillis) >= interval)                  //To increase the speed of motor
    {    md--;
         previousMillis = currentMillis;
        
        if(md<50)
        {md=50;
        }
       
    }
    goto down;
    
    }else
    {
      disable_motors();
    }
    
      if(customKeypad.getState()==PRESSED)
    {
       switch(holdKey)
    {
       case '0':
         modex--;
        if(modex<=0)
        {modex=4;
        }
        delay(1000);
        break;
        
        case '1':
         modex++;
        if(modex>=5)
        {modex=1;
        }
        delay(1000);
        break;
        
        case '8':
         modey--;
        if(modey<=0)
        {modey=4;
        }
        delay(1000);
        break;
        
        case '9':
         modey++;
        if(modey>=5)
        {modey=1;
        }
        delay(1000);
        break;

        case 'C':
        enable_motors(); 
        lengthmovedX=lengthmovedX+lengthX;
        
        while(steps_x)
        {
        digitalWrite(dir1, state);
        digitalWrite(pul1, HIGH);
        delayMicroseconds(1);
        digitalWrite(pul1, LOW);
        delayMicroseconds(1);
        if(lengthmovedX>=48.0)
        { lengthmovedX=0;
         if(state==0)
         {
          state=1;
         }else
         {
           state=0;
         }
          if(lengthmovedY<=20.0)
         {  lengthmovedY=lengthmovedY+lengthY;
          while(steps_y )
          {
             digitalWrite(dir2, LOW);
           digitalWrite(pul2, HIGH);
          delayMicroseconds(1);
           digitalWrite(pul2, LOW);
           delayMicroseconds(1);
       steps_y--;
          }
         }
          else
          {
            lengthmovedY=0;
          }
        }
        steps_x--;
        }
        disable_motors();
        break;
    }
    }

     lcd.setCursor(0, 1);
         lcd.print("X=");
        lcd.setCursor(7, 1);
        lcd.print("mm ");
        lcd.setCursor(3, 1);
   
      switch(modex)
    {  
       
       case 1:
       lcd.print("0   ");
       steps_x=0;
       lengthX=0;
       break;
       
       case 2:
       lcd.print("0.5 ");
       steps_x=6400;
        lengthX=0.5;
        break;
       
       case 3:
       lcd.print("1   ");
       steps_x=12800;
        lengthX=1;
       break;
       
       case 4:
       lcd.print("2   ");
       steps_x=25600;
        lengthX=2;
       break;
       
    }
    lcd.setCursor(0, 3);
         lcd.print("Y=");
        lcd.setCursor(7, 3);
        lcd.print("mm ");
        lcd.setCursor(3, 3);
     switch(modey)
    {  
       
       case 1:
       lcd.print("0   ");
       steps_y=0;
       lengthY=0;
       break;
       
       case 2:
       lcd.print("0.5 ");
        steps_y=6400;
        lengthY=0.5;
       break;
       
       case 3:
       lcd.print("1   ");
        steps_y=12800;
        lengthY=1;
       break;
       
       case 4:
       lcd.print("2   ");
        steps_y=25600;
        lengthY=2;
       break;
       
    }

    down:  if(0);
    }
    }
      
     else if(customKey=='4')
   {
    lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("SCAN MODE");
   lcd.setCursor(0, 1);
   lcd.print("SELECTED");
 int  steps_x=25600;
 int  steps_y=6400;
int   lengthx=24;
 int   lengthy=40;
   origion();

   while(lengthy)
  { while(lengthx)
   {
   while(steps_x)
        {
        movex(state,5);
        steps_x--;
        }
     lengthx--;
   }
    if(state==0)
         {
          state=1;
         }else
         {
           state=0;
         }
         while(steps_y)
        {
        movey(0,5);
        steps_y--;
        }
        lengthy--;
   steps_x=25600;
   steps_y=6400;
   lengthx=24;
  }
         
   /*     if(lengthmovedX>=48.0)
        { lengthmovedX=0;
         if(state==0)
         {
          state=1;
         }else
         {
           state=0;
         }
          if(lengthmovedY<=20.0)
         {  lengthmovedY=lengthmovedY+lengthY;
          while(steps_y )
          {
             digitalWrite(dir2, LOW);
           digitalWrite(pul2, HIGH);
          delayMicroseconds(1);
           digitalWrite(pul2, LOW);
           delayMicroseconds(1);
       steps_y--;
          }
         }
          else
          {
            lengthmovedY=0;
          }
        }
        steps_x--;
        }*/
        disable_motors();
    
   }
     
     }// *********************END OF LOOP

    
      
