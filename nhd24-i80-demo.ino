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
                  //G
                  { B00000000,B01111000,B00001100,B00000110,B01100110,B01000110,B01001100,B01111000 },
                  //H
                  { B00000000, B01100110, B01100110, B01100110, B01111110, B01100110, B01100110, B01100110 },
                  //I
                  { B00000000, B01111110, B00011000, B00011000, B00011000, B00011000, B00011000, B01111110 },
                  //J
                  { B00000000, B01111110, B01111110, B00110000, B00110000, B00110110, B00110110, B00011100 },
                  //K
                  { B00000000, B01100110, B00110110, B00011110, B00001110, B00011110, B00110110, B01100110 },
                  //L
                  { B00000000,B00000110,B00000110,B00000110,B00000110,B00000110,B00000110,B00111110 },
                  //M
                  { B00000000,B01000010,B01100110,B01011010,B01000010,B01000010,B01000010,B01000010 },
                  //N
                  { B00000000,
                    B01000110,
                    B01000110,
                    B01001010,
                    B01010010,
                    B01100010,
                    B01100010,
                    B01100010,
                  },
                  //O
                  {
                    B00000000,
                    B00011000,
                    B00111100,
                    B01100110,
                    B01100110,
                    B01100110,
                    B00111100,
                    B00011000
                  },
                  //P
                  { B00000000,B00111110,B01100110,B01100110,B00111110,B00000110,B00000110,B00000110 },
                  //Q
                  {
                    B00000000,
                    B00011000,
                    B00111100,
                    B01100110,
                    B01100110,
                    B01110110,
                    B00111100,
                    B11011000
                  },
                  //R
                  { B00000000,B00111110,B01100110,B01100110,B00111110,B00010110,B00100110,B01000110 },
                  //S
                  {
                    B00000000,
                    B01111000,
                    B00001100,
                    B00000110,
                    B00111100,
                    B01100000,
                    B01100000,
                    B00111110
                  },
                  //T
                  {
                    B00000000,
                    B01111110,
                    B01111110,
                    B00011000,
                    B00011000,
                    B00011000,
                    B00011000,
                    B00011000
                  },
                  //U
                  {
                    B00000000,
                    B01000010,
                    B01000010,
                    B01000010,
                    B01000010,
                    B01000010,
                    B01100110,
                    B00111100
                  },
                  
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
//  setAllOutput();
  PORTB = PORTB | 0x18;
  PORTB = PORTB & 0xDF;
  PORTD = command;
  PORTB = PORTB | 0x20;
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
//  screen[3][3] = 'A';
//  screen[3][4] = 'B';
//  screen[3][5] = 'C';
//  screen[3][6] = 'D';
//  screen[3][7] = 'E';
//  screen[3][8] = 'F';
//  screen[3][9] = 'G';
//  screen[3][10] = 'H';
//  screen[4][3] = 'I';
//  screen[4][4] = 'J';
//  screen[4][5] = 'K';
//  screen[4][6] = 'L';
//  screen[4][7] = 'M';
//  screen[4][8] = 'N';
//  screen[4][9] = 'O';
//  screen[4][10] = 'P';
//  screen[4][11] = 'Q';
//  screen[4][12] = 'R';
//  screen[5][2] = 'S';
//  screen[5][3] = 'T';
//  screen[5][4] = 'U';
  dispInit();
  commandWrite(0x2C);
}

byte red = 0xFF;
byte blue = 0xFF;
byte green = 0xFF;

int messageCounter = 0;

void loop() {
  byte dwightBitmap[15][8] = { 
      { B00000000,B00000000,B00000000,B00000000,B00000000,B11111000,B00000000,B00000000 },
      { B00000000,B00000000,B00000011,B11000000,B00001111,B11111110,B00000000,B00000000 },
      { B00000000,B00000000,B00001111,B11100000,B00111111,B11111111,B10000000,B00000000 }
      
    };
//  commandWrite(0x2C);
    long screenheight = 76800;
//  writeChar(letH,0);
  switch(messageCounter) {
    case 0: 
      screen[10][12] = 'F';
      screen[10][13] = 'A';
      screen[10][14] = 'C';
      screen[10][15] = 'T';
      messageCounter++;
      break;
    case 1:
      screen[12][6] = 'B';
      screen[12][7] = 'E';
      screen[12][8] = 'A';
      screen[12][9] = 'R';
      screen[12][10] = 'S';
      screen[12][12] = 'E';
      screen[12][13] = 'A';
      screen[12][14] = 'T';
      screen[12][16] = 'B';
      screen[12][17] = 'E';
      screen[12][18] = 'E';
      screen[12][19] = 'T';
      screen[12][20] = 'S';
            messageCounter++;
             break;

      break;
    case 2: 
      screen[18][6] = 'B';
      screen[18][7] = 'E';
      screen[18][8] = 'A';
      screen[18][9] = 'R';
      screen[18][10] = 'S';
            messageCounter++;
      break;

    case 3:
      screen[20][11] = 'B';
      screen[20][12] = 'E';
      screen[20][13] = 'E';
      screen[20][14] = 'T';
      screen[20][15] = 'S';
            messageCounter++;
      break;
    case 4: 
      screen[24][6] = 'B';
      screen[24][7] = 'A';
      screen[24][8] = 'T';
      screen[24][9] = 'T';
      screen[24][10] = 'L';
      screen[24][11] = 'E';
      screen[24][12] = 'S';
      screen[24][13] = 'T';
      screen[24][14] = 'A';
      screen[24][15] = 'R';
      screen[25][12] = 'G';
      screen[25][13] = 'A';
      screen[25][14] = 'L';
      screen[25][15] = 'A';
      screen[25][16] = 'C';
      screen[25][17] = 'T';
      screen[25][18] = 'I';
      screen[25][19] = 'C';
      screen[25][20] = 'A';
            messageCounter++;
      break;
  }
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
  delay(1000);
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
 


