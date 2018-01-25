int dc = 11;
int wr = 13;
int rd = 12;
int res = 10;

int db0 = 8;
int db1 = 9;
int db2 = 7;
int db3 = 6;
int db4 = 4; 
int db5 = 5; 
int db6 = 3;
int db7 = 2;

char screen[40][30] = {0};

byte font[27][8] = {
                  //A
                  { B00000000,B00011000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110 },
                  //B
                  { B00000000,B00111110,B01100110,B01100110,B00111110,B01100110,B01100110,B00111110 },
                  //C
                  { B00000000,B01111000,B00001100,B00000110,B00000110,B00000110,B00001100,B01111000 },
                  //D
                  { B00000000,B00011110,B00100110,B01000110,B01000110,B01000110,B00100110,B00011110 },
                  //E
                  { B00000000,B00111110,B00000110,B00000110,B00111110,B00000110,B00000110,B00111110 },
                  //F
                  { B00000000,B00111110,B00000110,B00000110,B00011110,B00000110,B00000110,B00000110 },
                  //H
                  { B00000000, B01100110, B01100110, B01100110, B01111110, B01100110, B01100110, B01100110 },
                  //I
                  { B00000000, B01111110, B00011000, B00011000, B00011000, B00011000, B00011000, B01111110 },
                  //SPACE
                  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }
};
byte letSp[8] = { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 };

void displayWrite(byte command, byte red, byte green, byte blue) {
  setAllOutput();
//  digitalWrite(rd,HIGH);
  digitalWrite(dc,LOW);
  digitalWrite(wr,LOW);
  digitalWrite(db7,bitRead(command,7));
  digitalWrite(db6,bitRead(command,6));
  digitalWrite(db5,bitRead(command,5));
  digitalWrite(db4,bitRead(command,4));
  digitalWrite(db3,bitRead(command,3));
  digitalWrite(db2,bitRead(command,2));
  digitalWrite(db1,bitRead(command,1));
  digitalWrite(db0,bitRead(command,0));
  digitalWrite(wr, HIGH);
  digitalWrite(dc,HIGH);
  long pxl = 0;
  while(pxl++ < 76800) {
    //Red
    PORTB = PORTB & 0xDF;
    PORTD = red;
    PORTB = PORTB | 0x20;

    //Green
    PORTB = PORTB & 0xDF;
    PORTD = green;
    PORTB = PORTB | 0x20;

    //Blue
    PORTB = PORTB & 0xDF;
    PORTD = blue;
    PORTB = PORTB | 0x20;
  }
}

void dataWrite(byte command) {
  setAllOutput();
  digitalWrite(rd,HIGH);
  digitalWrite(dc,HIGH);
  digitalWrite(wr,LOW);
  digitalWrite(db7,bitRead(command,7));
  digitalWrite(db6,bitRead(command,6));
  digitalWrite(db5,bitRead(command,5));
  digitalWrite(db4,bitRead(command,4));
  digitalWrite(db3,bitRead(command,3));
  digitalWrite(db2,bitRead(command,2));
  digitalWrite(db1,bitRead(command,1));
  digitalWrite(db0,bitRead(command,0));
  digitalWrite(wr,HIGH);
}
void writeChar(byte letter[], int row) {
  for(int i = 0; i < 8; i++) {
    if(bitRead(letter[row],i) == 1) {
      dataWrite(0xFF);
      dataWrite(0xFF);
      dataWrite(0xFF);
    }
    else {
      dataWrite(0x00);
      dataWrite(0x00);
      dataWrite(0x00);
    }
  }
  
}

void commandWrite(byte command) {
  setAllOutput();
  digitalWrite(rd,HIGH);
  digitalWrite(dc,LOW);
  digitalWrite(wr,LOW);
  digitalWrite(db7,bitRead(command,7));
  digitalWrite(db6,bitRead(command,6));
  digitalWrite(db5,bitRead(command,5));
  digitalWrite(db4,bitRead(command,4));
  digitalWrite(db3,bitRead(command,3));
  digitalWrite(db2,bitRead(command,2));
  digitalWrite(db1,bitRead(command,1));
  digitalWrite(db0,bitRead(command,0));
  digitalWrite(wr,HIGH);
}

void setAllOutput() {
  pinMode(db0, OUTPUT);
  pinMode(db1, OUTPUT);
  pinMode(db2, OUTPUT);
  pinMode(db3, OUTPUT);
  pinMode(db4, OUTPUT);
  pinMode(db5, OUTPUT);
  pinMode(db6, OUTPUT);
  pinMode(db7, OUTPUT);
}

void dispInit() {
  setAllOutput();
  commandWrite(0x11); //Sleep Out
  commandWrite(0x29); //Display on
  commandWrite(0x36); //Start MADCTL
  dataWrite(0x00);
  displayWrite(0x2C,0x00,0x00,0x00);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(dc, OUTPUT);
  pinMode(wr, OUTPUT);
  pinMode(rd, OUTPUT);
  pinMode(res, OUTPUT);          
  digitalWrite(res,HIGH);
  screen[3][3] = 'A';
  screen[3][4] = 'B';
  screen[3][5] = 'C';
  screen[3][6] = 'D';
  screen[3][7] = 'E';
  screen[3][8] = 'F';
  screen[3][9] = 'G';
  screen[3][10] = 'H';
  dispInit();
  commandWrite(0x2C);
}

byte red = 0xFF;
byte blue = 0xFF;
byte green = 0xFF;

void loop() {
//  commandWrite(0x2C);
    long screenheight = 76800;
//  writeChar(letH,0);
  for(int i = 0; i < 320; i++) {
    for(int j = 0; j < 30; j++) {
      int charIndex = screen[i/8][j] - 65;
      if(charIndex >= 0 && charIndex < 27) {
        writeChar(font[charIndex],i%8);
      }
      else {
        writeChar(letSp,i%8);
      }
    }
  }
}

//    dataWrite(red);
//    dataWrite(green);
//    dataWrite(blue);
//  }
//  
//  i = 0;
//  while(i++ < 76800) {
//    dataWrite(red++);
//    dataWrite(green);
//    dataWrite(blue--);
//  }
//  
//  i = 0;
//  while(i++ < 76800) {
//    dataWrite(red);
//    dataWrite(green--);
//    dataWrite(blue++);
//  }
//Cycle colors
//  displayWrite(44,B11111100,B00000000,B00000000);
//  delay(10);
//  displayWrite(44,B00000000,B11111100,B00000000);
//  delay(10);
//  displayWrite(44,B00000000,B00000000,B11111100);
//  delay(10);
 


