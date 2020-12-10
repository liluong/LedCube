int columns[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
int rows[] = {A0, A1, A2, A3, A4};

int row; // Variable for a row
int column; // variable for a column
int soundPin = A5; //sound pin attach to

void setup() {
  // put your setup code here, to run once:
  int counter;

  for (int counter = 0; counter < 25; counter++) {
    pinMode(columns[counter], OUTPUT);
  }

  for (int counter = 0; counter < 5; counter++) {
    pinMode(rows[counter], OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(soundPin);
  Serial.println(value);
  if (value > 540) {
    fifthSound();
  } else if (value > 535 && value < 540) {
    fourthSound();
  } else if (value > 530 && value < 535) {
    thirdSound();
  } else if (value > 525 && value <= 530) {
    secondSound();
  } else if (value > 520 && value <= 525) {
    firstSound();
  } else {
    noSound();
  }
}

void noSound() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(rows[i], HIGH);
  }
  delay(250);
}

void firstSound() {
  for (int i = 0; i < 25; i++) {
    digitalWrite(rows[0], LOW);
    digitalWrite(rows[1], HIGH);
    digitalWrite(rows[2], HIGH);
    digitalWrite(rows[3], HIGH);
    digitalWrite(rows[4], HIGH);
    digitalWrite(columns[i], HIGH);
  }
  delay(250);
}

void secondSound() {
  for (int i = 0; i < 25; i++) {
    digitalWrite(rows[0], LOW);
    digitalWrite(rows[1], LOW);
    digitalWrite(rows[2], HIGH);
    digitalWrite(rows[3], HIGH);
    digitalWrite(rows[4], HIGH);
    digitalWrite(columns[i], HIGH);
  }
  delay(250);
}

void thirdSound() {
  for (int i = 0; i < 25; i++) {
    digitalWrite(rows[0], LOW);
    digitalWrite(rows[1], LOW);
    digitalWrite(rows[2], LOW);
    digitalWrite(rows[3], HIGH);
    digitalWrite(rows[4], HIGH);
    digitalWrite(columns[i], HIGH);
  }
  delay(250);
}

void fourthSound() {
  for (int i = 0; i < 25; i++) {
    digitalWrite(rows[0], LOW);
    digitalWrite(rows[1], LOW);
    digitalWrite(rows[2], LOW);
    digitalWrite(rows[3], LOW);
    digitalWrite(rows[4], HIGH);
    digitalWrite(columns[i], HIGH);
  }
 delay(250);
}

void fifthSound() {
  for (int i = 0; i < 25; i++) {
    digitalWrite(rows[0], LOW);
    digitalWrite(rows[1], LOW);
    digitalWrite(rows[2], LOW);
    digitalWrite(rows[3], LOW);
    digitalWrite(rows[4], LOW);
    digitalWrite(columns[i], HIGH);
  }
  delay(250);
}

void TestLed() {
  for (int i = 0; i < 25; i++) {
    digitalWrite(rows[1], HIGH);
    digitalWrite(columns[i], LOW);
  }
 delay(250);
}
