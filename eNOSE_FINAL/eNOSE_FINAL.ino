//// eNOSE
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 13, 8, 9, 10, 11);  // (rs,en,d4,d5,d6,d7)

#include <SoftwareSerial.h>
#define BZ 3
#define FAN 2

int state;
int FAN_ON = 15;  // TEST TIME DELAY
int AVG = 3;

//int MQ2=A0; int MQ3=A1; int T00=A2; int T02=A3; int MQ9=A4; int MQ6=A5;
int MQ2, MQ2_START, MQ2_NEW, MQ2_NET;
int MQ3, MQ3_START, MQ3_NEW, MQ3_NET;
int T00, T00_START, T00_NEW, T00_NET;
int T02, T02_START, T02_NEW, T02_NET;
int MQ6, MQ6_START, MQ6_NEW, MQ6_NET;
int MQ9, MQ9_START, MQ9_NEW, MQ9_NET;


void setup() {
  Serial.begin(9600);
  pinMode(FAN, OUTPUT);
  digitalWrite(FAN, LOW);
  pinMode(BZ, OUTPUT);
  digitalWrite(BZ, HIGH);
  delay(500);
  digitalWrite(BZ, LOW);  // BEEP
  lcd.begin(20, 4);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Welcome  TO  ");
  lcd.setCursor(0, 1);
  lcd.print(" A C PATIL COE ");
  delay(1000);
  lcd.clear();
}

void loop() {
  digitalWrite(FAN, HIGH);
  delay(4500);
  digitalWrite(FAN, LOW);  // FAN ON
  READ_SENSOR();
  Serial.print("VALUE ");
  SERIAL_OUT();
  LCD_DISPLAY();
  delay(3000);
  lcd.setCursor(0, 3);
  lcd.print("                    ");  // CLEAR LINE

  if (Serial.available() > 0) {  // Ckeck for command Recieved
    state = Serial.read();       // Serial.println(state);    // flag=0;
  }

  if (state == '0') {  // 000
    lcd.clear();
    digitalWrite(FAN, HIGH);  // FAN ON
    lcd.setCursor(0, 0);
    lcd.print("    KEEP EMPTY   ");
    lcd.setCursor(0, 1);
    lcd.print("CLEANING CAN/SENSOR");
    for (int i = (FAN_ON); i > -1; --i) {  // TEST TIME * DELAY
      lcd.setCursor(12, 3);
      lcd.print("Wait    ");
      lcd.setCursor(17, 3);
      lcd.print(i);
      delay(1000);  // COUNT UP
    }
    lcd.clear();
    lcd.setCursor(10, 3);
    lcd.print("TEST NOW  ");
    digitalWrite(FAN, LOW);  // FAN OFF
    digitalWrite(BZ, HIGH);
    delay(500);
    digitalWrite(BZ, LOW);  // BEEP
  }

  // TEST 1  BANANA
  else if (state == '1') {   // 011 SW OF OLD
    digitalWrite(FAN, LOW);  // FAN OFF

    START();
    Serial.print("START ");
    SERIAL_OUT_START();
    delay(1000);  // GET INITIAL READING

    lcd.clear();
    LCD_DISPLAY();
    delay(1000);
    lcd.setCursor(0, 3);
    lcd.print("                    ");  // CLEAR BOTTEM LINE
    lcd.setCursor(0, 3);
    lcd.print("KEEP BANANA ");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0, 3);
    lcd.print("BANANA");      // LCD PRINT TEST NAME
    digitalWrite(FAN, HIGH);  // FAN ON

    COUNT_DOWN();  // COUNT DOWN TIMER
    READ_NEW();    //
    NEW();
    Serial.print("NEW   ");
    SERIAL_OUT_NEW();
    delay(1000);
    NET_VALUE();
    Serial.print("NET   ");
    SERIAL_OUT_NET();
    delay(1000);
    LCD_DISPLAY();

    digitalWrite(FAN, LOW);  // FAN OFF
    digitalWrite(BZ, HIGH);
    delay(500);
    digitalWrite(BZ, LOW);  // BEEP
  }
}

///////////////////////////////////////////////////////////////////////////
void READ_SENSOR() {
  MQ2 = analogRead(A0);
  MQ3 = analogRead(A1);
  T00 = analogRead(A2);
  T02 = analogRead(A3);
  MQ9 = analogRead(A4);
  MQ6 = analogRead(A5);
}

void SERIAL_OUT() {
  Serial.print(MQ2);
  Serial.print(", ");
  Serial.print(MQ3);
  Serial.print(", ");
  Serial.print(T00);
  Serial.print(", ");
  Serial.print(T02);
  Serial.print(", ");
  Serial.print(MQ9);
  Serial.print(", ");
  Serial.print(MQ6);
  Serial.println(".");
}

void START() {
  MQ2_START = MQ2;
  MQ3_START = MQ3;
  T00_START = T00;
  T02_START = T02;
  MQ6_START = MQ6;
  MQ9_START = MQ9;
}

void SERIAL_OUT_START() {
  Serial.print(MQ2_START);
  Serial.print(", ");
  Serial.print(MQ3_START);
  Serial.print(", ");
  Serial.print(T00_START);
  Serial.print(", ");
  Serial.print(T02_START);
  Serial.print(", ");
  Serial.print(MQ9_START);
  Serial.print(", ");
  Serial.print(MQ6_START);
  Serial.println(".");
}
void READ_NEW() {
  for (int j = (AVG); j > 0; --j) {  // TEST TIME * DELAY
    READ_SENSOR();
    MQ2_NEW = MQ2_NEW + MQ2;
    MQ3_NEW = MQ3_NEW + MQ3;
    T00_NEW = T00_NEW + T00;
    T02_NEW = T02_NEW + T02;
    MQ6_NEW = MQ6_NEW + MQ6;
    MQ9_NEW = MQ9_NEW + MQ9;
  }
}
void NEW() {
  MQ2_NEW = (MQ2_NEW / AVG);
  MQ3_NEW = (MQ3_NEW / AVG);
  T00_NEW = (T00_NEW / AVG);
  T02_NEW = (T02_NEW / AVG);
  MQ6_NEW = (MQ6_NEW / AVG);
  MQ9_NEW = (MQ9_NEW / AVG);
}

void SERIAL_OUT_NEW() {
  Serial.print(MQ2_NEW);
  Serial.print(", ");
  Serial.print(MQ3_NEW);
  Serial.print(", ");
  Serial.print(T00_NEW);
  Serial.print(", ");
  Serial.print(T02_NEW);
  Serial.print(", ");
  Serial.print(MQ9_NEW);
  Serial.print(", ");
  Serial.print(MQ6_NEW);
  Serial.println(".");
}

void NET_VALUE() {
  MQ2_NET = MQ2_NEW - MQ2_START, MQ3_NET = MQ3_NEW - MQ3_START;
  T00_NET = T00_NEW - T00_START, T02_NET = T02_NEW - T02_START;
  MQ6_NET = MQ6_NEW - MQ6_START, MQ9_NET = MQ9_NEW - MQ9_START;
  if (MQ2_NET <= 0) { MQ2_NET = 0; }
  if (MQ3_NET <= 0) { MQ3_NET = 0; }
  if (T00_NET <= 0) { T00_NET = 0; }
  if (T02_NET <= 0) { T02_NET = 0; }
  if (MQ6_NET <= 0) { MQ6_NET = 0; }
  if (MQ9_NET <= 0) { MQ9_NET = 0; }
}

void SERIAL_OUT_NET() {
  Serial.print(MQ2_NET);
  Serial.print(", ");
  Serial.print(MQ3_NET);
  Serial.print(", ");
  Serial.print(T00_NET);
  Serial.print(", ");
  Serial.print(T02_NET);
  Serial.print(", ");
  Serial.print(MQ9_NET);
  Serial.print(", ");
  Serial.print(MQ6_NET);
  Serial.println(".");
}

void COUNT_DOWN() {
  for (int i = (FAN_ON); i > -1; --i) {  // TEST TIME * DELAY
    lcd.setCursor(12, 3);
    lcd.print("Wait    ");
    lcd.setCursor(17, 3);
    lcd.print(i);
    delay(1000);  // COUNT DOWN
  }
}

void LCD_DISPLAY() {
  lcd.setCursor(0, 0);
  lcd.print("MQ2     ");
  lcd.setCursor(4, 0);
  lcd.print(MQ2);
  lcd.setCursor(10, 0);
  lcd.print("MQ3     ");
  lcd.setCursor(14, 0);
  lcd.print(MQ3);
  lcd.setCursor(0, 1);
  lcd.print("T00     ");
  lcd.setCursor(4, 1);
  lcd.print(T00);
  lcd.setCursor(10, 1);
  lcd.print("T02     ");
  lcd.setCursor(14, 1);
  lcd.print(T02);
  lcd.setCursor(0, 2);
  lcd.print("MQ9     ");
  lcd.setCursor(4, 2);
  lcd.print(MQ9);
  lcd.setCursor(10, 2);
  lcd.print("MQ6     ");
  lcd.setCursor(14, 2);
  lcd.print(MQ6);
}
