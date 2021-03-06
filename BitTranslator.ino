#include <Wire.h>

// Pins
int const sda = 0;
int const scl = 2;

// Constants
int const address = 60;
int const commands = 0x00;
int const onecommand = 0x80;
int const data = 0x40;
int const onedata = 0xC0;

// OLED display **********************************************

// Character set for text - stored in program memory
const uint8_t CharMap[][6] PROGMEM = {
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, 
{ 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00 }, 
{ 0x00, 0x07, 0x00, 0x07, 0x00, 0x00 }, 
{ 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00 }, 
{ 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00 }, 
{ 0x23, 0x13, 0x08, 0x64, 0x62, 0x00 }, 
{ 0x36, 0x49, 0x56, 0x20, 0x50, 0x00 }, 
{ 0x00, 0x08, 0x07, 0x03, 0x00, 0x00 }, 
{ 0x00, 0x1C, 0x22, 0x41, 0x00, 0x00 }, 
{ 0x00, 0x41, 0x22, 0x1C, 0x00, 0x00 }, 
{ 0x2A, 0x1C, 0x7F, 0x1C, 0x2A, 0x00 }, 
{ 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 }, 
{ 0x00, 0x80, 0x70, 0x30, 0x00, 0x00 }, 
{ 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 }, 
{ 0x00, 0x00, 0x60, 0x60, 0x00, 0x00 }, 
{ 0x20, 0x10, 0x08, 0x04, 0x02, 0x00 }, 
{ 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00 }, 
{ 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00 }, 
{ 0x72, 0x49, 0x49, 0x49, 0x46, 0x00 }, 
{ 0x21, 0x41, 0x49, 0x4D, 0x33, 0x00 }, 
{ 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00 }, 
{ 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 }, 
{ 0x3C, 0x4A, 0x49, 0x49, 0x31, 0x00 }, 
{ 0x41, 0x21, 0x11, 0x09, 0x07, 0x00 }, 
{ 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 }, 
{ 0x46, 0x49, 0x49, 0x29, 0x1E, 0x00 }, 
{ 0x00, 0x00, 0x14, 0x00, 0x00, 0x00 }, 
{ 0x00, 0x40, 0x34, 0x00, 0x00, 0x00 }, 
{ 0x00, 0x08, 0x14, 0x22, 0x41, 0x00 }, 
{ 0x14, 0x14, 0x14, 0x14, 0x14, 0x00 }, 
{ 0x00, 0x41, 0x22, 0x14, 0x08, 0x00 }, 
{ 0x02, 0x01, 0x59, 0x09, 0x06, 0x00 }, 
{ 0x3E, 0x41, 0x5D, 0x59, 0x4E, 0x00 }, 
{ 0x7C, 0x12, 0x11, 0x12, 0x7C, 0x00 }, 
{ 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00 }, 
{ 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00 }, 
{ 0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00 }, 
{ 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00 }, 
{ 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00 }, 
{ 0x3E, 0x41, 0x41, 0x51, 0x73, 0x00 }, 
{ 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00 }, 
{ 0x00, 0x41, 0x7F, 0x41, 0x00, 0x00 }, 
{ 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00 }, 
{ 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00 }, 
{ 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00 }, 
{ 0x7F, 0x02, 0x1C, 0x02, 0x7F, 0x00 }, 
{ 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00 }, 
{ 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00 }, 
{ 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00 }, 
{ 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00 }, 
{ 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00 }, 
{ 0x26, 0x49, 0x49, 0x49, 0x32, 0x00 }, 
{ 0x03, 0x01, 0x7F, 0x01, 0x03, 0x00 }, 
{ 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00 }, 
{ 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00 }, 
{ 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00 }, 
{ 0x63, 0x14, 0x08, 0x14, 0x63, 0x00 }, 
{ 0x03, 0x04, 0x78, 0x04, 0x03, 0x00 }, 
{ 0x61, 0x59, 0x49, 0x4D, 0x43, 0x00 }, 
{ 0x00, 0x7F, 0x41, 0x41, 0x41, 0x00 }, 
{ 0x02, 0x04, 0x08, 0x10, 0x20, 0x00 }, 
{ 0x00, 0x41, 0x41, 0x41, 0x7F, 0x00 }, 
{ 0x04, 0x02, 0x01, 0x02, 0x04, 0x00 }, 
{ 0x40, 0x40, 0x40, 0x40, 0x40, 0x00 }, 
{ 0x00, 0x03, 0x07, 0x08, 0x00, 0x00 }, 
{ 0x20, 0x54, 0x54, 0x78, 0x40, 0x00 }, 
{ 0x7F, 0x28, 0x44, 0x44, 0x38, 0x00 }, 
{ 0x38, 0x44, 0x44, 0x44, 0x28, 0x00 }, 
{ 0x38, 0x44, 0x44, 0x28, 0x7F, 0x00 }, 
{ 0x38, 0x54, 0x54, 0x54, 0x18, 0x00 }, 
{ 0x00, 0x08, 0x7E, 0x09, 0x02, 0x00 }, 
{ 0x18, 0xA4, 0xA4, 0x9C, 0x78, 0x00 }, 
{ 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00 }, 
{ 0x00, 0x44, 0x7D, 0x40, 0x00, 0x00 }, 
{ 0x20, 0x40, 0x40, 0x3D, 0x00, 0x00 }, 
{ 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00 }, 
{ 0x00, 0x41, 0x7F, 0x40, 0x00, 0x00 }, 
{ 0x7C, 0x04, 0x78, 0x04, 0x78, 0x00 }, 
{ 0x7C, 0x08, 0x04, 0x04, 0x78, 0x00 }, 
{ 0x38, 0x44, 0x44, 0x44, 0x38, 0x00 }, 
{ 0xFC, 0x18, 0x24, 0x24, 0x18, 0x00 }, 
{ 0x18, 0x24, 0x24, 0x18, 0xFC, 0x00 }, 
{ 0x7C, 0x08, 0x04, 0x04, 0x08, 0x00 }, 
{ 0x48, 0x54, 0x54, 0x54, 0x24, 0x00 }, 
{ 0x04, 0x04, 0x3F, 0x44, 0x24, 0x00 }, 
{ 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00 }, 
{ 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00 }, 
{ 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00 }, 
{ 0x44, 0x28, 0x10, 0x28, 0x44, 0x00 }, 
{ 0x4C, 0x90, 0x90, 0x90, 0x7C, 0x00 }, 
{ 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00 }, 
{ 0x00, 0x08, 0x36, 0x41, 0x00, 0x00 }, 
{ 0x00, 0x00, 0x77, 0x00, 0x00, 0x00 }, 
{ 0x00, 0x41, 0x36, 0x08, 0x00, 0x00 }, 
{ 0x00, 0x06, 0x09, 0x06, 0x00, 0x00 },  // degree symbol = '~'
{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 }
};
// Global Variables
int inits = 0;
const byte NONE = 0;
char state[9]={'0','0','0','0','0','0','0','0','\0'}; 
const byte keypadPin = A0;
byte key = 0;
const int ledCount = 8;
int ledPins[] = {
  5, 6, 7, 8, 9, 10, 11, 12
};  
// Current plot position
int x0;
int y0;

// Write a single command
void Single (uint8_t x) {
  Wire.write(onecommand);
  Wire.write(x);
}
  
void InitDisplay () {
  Wire.beginTransmission(address);
  Wire.write(commands);

//  Wire.write(0xA0);  // Flip horizontal
//  Wire.write(0xDA);
//  Wire.write(0x22);
//  Wire.write(0xC0);    
  Wire.write(0xAF);  // Display on
  Wire.endTransmission();

}
void flipScreenVertically() {
  sendCommand(0x0a0);              //SEGREMAP   //Rotate screen 180 deg
  sendCommand(0x0c8);
//  sendCommand(0x22);
//  sendCommand(0xC0);            //COMSCANDEC  Rotate screen 180 Deg
}
void sendCommand(unsigned char com) {
   Wire.beginTransmission(address);      //begin transmitting
   Wire.write(0x80);                          //command mode
   Wire.write(com);
   Wire.endTransmission();                    // stop transmitting
}
void ClearDisplay () {
  for (int p = 0 ; p < 8; p++) {
    Wire.beginTransmission(address);
    Single(0xB0 + p);
    Wire.endTransmission();
    for (int q = 0 ; q < 8; q++) {
      Wire.beginTransmission(address);
      Wire.write(data);
      for (int i = 0 ; i < 20; i++) Wire.write(0);
      Wire.endTransmission();
    }
  }
}


// Move current plot position to x,y
void MoveTo (int x, int y) {
  x0 = x;
  y0 = y;
}

uint8_t ReverseByte (uint8_t x) {
  x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
  x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
  x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
  return x;    
}

// Plot an ASCII character with bottom left corner at x,y
void PlotChar (int c, int x, int y) {
  int h = y & 0x07;
  for (int p = 0; p < 2; p++) {
    Wire.beginTransmission(address);
    Single(0xB0 + (y >> 3) + p);          // Page
    for (int col=0; col<6; col++) {
      Single(0x00 + ((x+2+col) & 0x0F));  // Column low nibble
      Single(0x10 + ((x+2+col)>>4));      // Column high nibble
      Single(0xE0);                       // Read modify write
      Wire.write(onedata);
      Wire.endTransmission();
      Wire.requestFrom(address, 2);
      Wire.read();                        // Dummy read
      int j = Wire.read();
      Wire.beginTransmission(address);
      Wire.write(onedata);
      int bits = ReverseByte(pgm_read_byte(&CharMap[c-32][col]));
      Wire.write((bits<<h)>>(p<<3) | j);
      Single(0xEE);                       // Cancel read modify write
    }
    Wire.endTransmission();
  }
}

// Plot text starting at the current plot position
void PlotText(PGM_P s) {
  int p = (int)s;
  while (1) {
    char c = pgm_read_byte(p++);
    if (c == 0) return;
    PlotChar(c, x0, y0);
    x0 = x0 + 6;
  }
}

void setup(void)
{
    Serial.begin(9600); 
  while (!Serial)   {  ;    }
  Serial.println(F("Start\n"));
    Wire.begin();
  ClearDisplay();
  InitDisplay();
  flipScreenVertically();
  pinMode(keypadPin, INPUT_PULLUP); // sets analog pin for input 
    for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
  MoveTo(15, 32); PlotText(PSTR("Obaidi, Amal A."));
  MoveTo(20, 20); PlotText(PSTR("PRESS ANY KEY"));
}

void loop(void)
{
      key = getKey();
      delay(200);


}
byte getKey()
{
    int val = 0;
    byte button = 0;
    val = analogRead(keypadPin);
    Serial.println(val);
    button = NONE; // use NONE as the default value
    if ( (val >= 755)  &&  (val <=768))  {
      if(state[7] != '0'){
//       Serial.println("bit1 high");
       state[7] = '0';
       digitalWrite(ledPins[0], LOW);
//          PORTD |= (0 << 5);
       }else{
//        Serial.println("bit1 low");
        digitalWrite(ledPins[0], HIGH);
//          PORTD |= (1 << 5);
        state[7] = '1';
       }
       get_char();
       delay(50);
    }
    else if ( (val >= 770)  &&  (val <=785)    )   {
      
       if(state[6] != '0'){
//       Serial.println("bit2 high");
       digitalWrite(ledPins[1], LOW);
       state[6] = '0';
       }else{
//        Serial.println("bit2 low");
        digitalWrite(ledPins[1], HIGH);
        state[6] = '1';
       }
       get_char();
       delay(50);
      
      }     // up
    else if ( (val >= 790) &&  (val <= 805 ) )   {
       if(state[5] != '0'){
//       Serial.println("bit3 high");
       digitalWrite(ledPins[2], LOW);
       state[5] = '0';
       }else{
//        Serial.println("bit3 low");
        digitalWrite(ledPins[2], HIGH);
        state[5] = '1';
       }
       get_char();
       delay(50);  
      }  
    else if ( (val >= 808) &&  (val <= 820)  )   {
       if(state[4] != '0'){
//       Serial.println("bit4 high");
       digitalWrite(ledPins[3], LOW);
       state[4] = '0';
       }else{
//        Serial.println("bit4 low");
        digitalWrite(ledPins[3], HIGH);
        state[4] = '1';
       }
       get_char();
       delay(50);  
      } 
       
    else if ( (val >= 823) &&  ( val <=835)  )   {
       if(state[3] != '0'){
//       Serial.println("bit5 high");
       digitalWrite(ledPins[4], LOW);
       state[3] = '0';
       }else{
//        Serial.println("bit5 low");
        digitalWrite(ledPins[4], HIGH);
        state[3] = '1';
       }
       get_char();
       delay(50);  
      } 
      
    else if ( (val >= 840) &&  (val <= 860 ) )   {

        if(state[2] != '0'){
//       Serial.println("bit6 high");
       digitalWrite(ledPins[5], LOW);
       state[2] = '0';
       }else{
//        Serial.println("bit6 low");
        digitalWrite(ledPins[5], HIGH);
        state[2] = '1';
       }
       get_char();
       delay(50);  
      } 
        
    else if ( (val >= 880) &&  (val <= 910)  )   { 
       if(state[1] != '0'){
//       Serial.println("bit7 high");
       digitalWrite(ledPins[6], LOW);
       state[1] = '0';
       }else{
//        Serial.println("bit7 low");
        digitalWrite(ledPins[6], HIGH);
        state[1] = '1';
       }
       get_char();
       delay(50);  
      }    
    else if ( (val >= 1000) &&  ( val <=1020)  )   { 
            if(state[0] != '0'){
//       Serial.println("bit8 high");
       digitalWrite(ledPins[7], LOW);
       state[0] = '0';
       }else{
//        Serial.println("bit8 low");
        digitalWrite(ledPins[7], HIGH);
        state[0] = '1';
       }
       get_char();
       delay(50);  
      }
      
    return button; 
}  
void get_char(){
//    char data[]={bit1_State,bit2_State,bit3_State,bit4_State,bit5_State,bit6_State,bit7_State,bit8_State }; 
    char c = strtol(state, 0, 2);
    ClearDisplay();
    PlotChar(c,64,35);
    MoveTo(42, 20);
  int i = 0;
  while (1) {
    char c = state[i++];
    if (c == 0) return;
    PlotChar(c, x0, y0);
    x0 = x0 + 6;
  }
//    Serial.println(c);
//    Serial.println(state);
}
