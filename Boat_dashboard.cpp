/* I builed this program to run a dashboart in my boat */
#include <SoftwareSerial.h>
#include <TinyGPS++.h> // http://arduiniana.org/libraries/tinygpsplus/

// INTRO //
int key = 4; // Start motor
int p100 = 25;

// Buttons //
int b0 = 5;
int b1 = 6; 
int b2 = 7; 
int b3 = 8; 
int b4 = 9; 
int b5 = 10; 
int b6 = 11;

// GPS VAL //
int kmph = 0;
int hour = 0;
int min = 0;
int sat = 0;
int GPS = 0;

// RPM VAL //
int j  = 0;
int j0 = 0; int j1 = 0; int j2 = 0; int j3 = 0; int j4 = 0; int j5 = 0; int j6 = 0;
int t0 = 0;

// Warning //
int p0 = 0; int p1 = 0; int p2 = 0; int p3 = 0; int p4 = 0; int p5 = 0;
int p00 = 0; int p10 = 0; int p20 = 0; int p30 = 0; int p40 = 0; int p50 = 0;

SoftwareSerial ss(3, 2); //D2 = TX D3 = RX
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  ss.begin(9600);

  //pinMode(key, INPUT);
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  pinMode(b6, OUTPUT);

  Serial.print("p100.pic=");
  Serial.print(24);
  Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);

  delay(2000);
}

void loop() {
  {
    ////////////////// intro /////////////////////////
    {
      if (p100 < 277)
      {
        p100 ++;
        Serial.print("p100.pic=");
        Serial.print(p100);
        Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
        delay(80);

        if (p100 >= 277)
        { Serial.print("page page0");
          Serial.write(0xff); Serial.write(0xff); Serial.write(0xff);
        }
      }
    }

    ///////////////// Buttons ////////////////////////
    {
      if (p100 >= 277) {
        if (Serial.available()) {
          String button = "";
          delay(100);
          while (Serial.available()) {
            button += char (Serial.read());
          }
          Serial.print(button);
          sendData(button);

          if ((button == "start on") && (j < 100)) {
            (digitalWrite(b0, HIGH));
          }
          if (button == "start off") {
            (digitalWrite(b0, LOW));
          } 
          if (button == "horn on") {
            (digitalWrite(b1, HIGH));
          }
          if ((button == "horn off")) {
            (digitalWrite(b1, LOW));
          }
          if (button == "anchor on") {
            (digitalWrite(b2, HIGH));
          }
          if ((button == "anchor off") && (b2 == HIGH)) {
            (digitalWrite(b2, LOW));
          }
          if (button == "pump on") {
            (digitalWrite(b3, HIGH));
          }
          if ((button == "pump off") && (b3 == HIGH)) {
            (digitalWrite(b3, LOW));
          }
          if (button == "light on") {
            (digitalWrite(b4, HIGH));
          }
          if ((button == "light off") && (b4 == HIGH)) {
            (digitalWrite(b4, LOW));
      }
    }
  }
  
    /////////////////// RPM /////////////////////////
    {

      if (p100 >= 277) {
        t0 = j * 11;

        j = map(analogRead(A0), 1, 1025, 0, 700);
        if (j <= 100) {
          j0 = j;
        }

        if (j > 100) {
          j0 = 100;
          j1 = j - 100;
        } if (j < 100) (j1 = 0);

        if (j > 200) {
          j1 = 100;
          j2 = j - 200;
        }  if (j < 200) (j2 = 0);

        if (j > 300) {
          j2 = 100;
          j3 = j - 300;
        }  if (j < 300) (j3 = 0);

        if (j > 400) {
          j3 = 100;
          j4 = j - 400;
        }  if (j < 400) (j4 = 0);

        if (j > 500) {
          j4 = 100;
          j5 = j - 500;
        }  if (j < 500) (j5 = 0); // gaat dubbel zo snel

        if (j > 600) {
          j5 = 100;
          j6 = j - 600;
        }  if (j < 600) (j6 = 0); // gaat dubbel zo snel

        Serial.print("t0.txt=");
        Serial.print("\"");
        Serial.print(t0);
        Serial.print("\"");
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j0.val=");
        Serial.print(j0);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j1.val=");
        Serial.print(j1);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j2.val=");
        Serial.print(j2);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j3.val=");
        Serial.print(j3);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j4.val=");
        Serial.print(j4);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j5.val=");
        Serial.print(j5);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j6.val=");
        Serial.print(j6);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);
      }
    }

    ////////////////// GPS /////////////////////////
    {
      if (p100 >= 277) {

        while (ss.available() > 0)
          gps.encode(ss.read());

        if (gps.location.isUpdated())
        {
          kmph  = (gps.speed.kmph());
          hour  = ((gps.time.hour()) + 2);
          min   = (gps.time.minute());
          sat   = (gps.satellites.value());

          Serial.print("t1.txt=");
          Serial.print("\""); Serial.print(kmph); Serial.print("\"");
          Serial.write(0xff);      Serial.write(0xff);      Serial.write(0xff);

          Serial.print("t2.txt=");
          Serial.print("\""); Serial.print(hour); Serial.print("\"");
          Serial.write(0xff);      Serial.write(0xff);      Serial.write(0xff);

          Serial.print("t3.txt=");
          Serial.print("\""); Serial.print(min); Serial.print("\"");
          Serial.write(0xff);      Serial.write(0xff);      Serial.write(0xff);

          Serial.print("t4.txt=");
          Serial.print("\""); Serial.print(sat); Serial.print("\"");
          Serial.write(0xff);      Serial.write(0xff);      Serial.write(0xff);
        }
      }
    }

    ////////////////// Warning /////////////////////
    {
      if (p100 >= 277) {

      ///////////// Trim /////////////
        p00 = (analogRead(A1), 0, 1025, 0, 100); 
        if (p00 < 30 )
        {
          p0 = 23;
        }
          else
          {
            p0 = 278;
         }

        Serial.print("p0.pic=");
        Serial.print(p0);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j7.val=");
        Serial.print(p00);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

      ///////////// Battery ////////////////////
        p10 = map(analogRead(A2), 0, 1025, 0, 100);
        if (p10 < 30 || p10 > 80)
        {
          p1 = 23;
        }
          else
          {
            p1 = 278;
          }

        Serial.print("p1.pic=");
        Serial.print(p1);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j8.val=");
        Serial.print(p10);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

      ////////////// Oil ///////////////////
        p20 = map(analogRead(A3), 0, 1025, 0, 100);
        if (p20 < 30 || p20 > 80 )
        {
          p2 = 23;
        }
          else
          {
            p2 = 278;
          }
        Serial.print("p2.pic=");
        Serial.print(p2);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j9.val=");
        Serial.print(p20);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

      ////////////// Tempreture //////////////////
        p30 = map(analogRead(A4), 0, 1025, 0, 100);
        if (p30 < 30 || p30 > 80 )
        {
          p3 = 23;
        }
          else
          {
            p3 = 278;
          }

        Serial.print("p3.pic=");
        Serial.print(p3);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j10.val=");
        Serial.print(p30);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

      ////////////////Fuel ///////////////
        p40 = map(analogRead(A5), 0, 1025, 0, 100);
        if (p40 < 30 || p40 > 80 )
        {
          p4 = 23 ;
        }
          else
          {
            p4 = 278;
          }
        Serial.print("p4.pic=");
        Serial.print(p4);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);

        Serial.print("j11.val=");
        Serial.print(p40);
        Serial.write(0xff);    Serial.write(0xff);    Serial.write(0xff);
        }
      } 
  }
}

void sendData(String button){
  if(button == "start on"){
    (digitalWrite(b0, HIGH));
  }
  if(button == "start off"){
    (digitalWrite(b0, LOW));
  }
}
