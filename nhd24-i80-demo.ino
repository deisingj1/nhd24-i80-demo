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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(dc, OUTPUT);
  pinMode(wr, OUTPUT);
  pinMode(rd, OUTPUT);
  pinMode(res, OUTPUT);          
  digitalWrite(res,HIGH);
  dispInit();
}

void loop() {

//Cycle colors
//  displayWrite(44,B11111100,B00000000,B00000000);
//  delay(10);
//  displayWrite(44,B00000000,B11111100,B00000000);
//  delay(10);
//  displayWrite(44,B00000000,B00000000,B11111100);
//  delay(10);
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

