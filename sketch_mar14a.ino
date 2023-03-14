const int buttonPin = 2;
const int spaceButtonPin = 3;
const int ledPin = 13;
const int buzzerPin = 8;

int buttonState = 0;
int spaceButtonState = 0;
int lastButtonState = 0;
int lastSpaceButtonState = 0;

String code = "";

int timerStart = 0;
int timerEnd = 0;

void calculate_code(int time) {
  if (time <= 200) {
    code += ".";
  } else {
    code += "-";
  }
  Serial.println(code);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!");
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  spaceButtonState = digitalRead(spaceButtonPin);

  if (buttonState == HIGH) {
    if (lastButtonState != buttonState) {
      timerStart = millis();
      lastButtonState = buttonState;
    }
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 750);
  } else {
    if (lastButtonState != buttonState) {
      timerEnd = millis();
      lastButtonState = buttonState;
      calculate_code(timerEnd - timerStart);
    }
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }

  if (spaceButtonState == HIGH) {
    if (lastSpaceButtonState != spaceButtonState) {
      code += " ";
      tone(buzzerPin, 300);
      digitalWrite(ledPin, HIGH);
      Serial.println(code);
      lastSpaceButtonState = spaceButtonState;
    }
  } else {
    lastSpaceButtonState = spaceButtonState;
  }
}