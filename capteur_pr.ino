const int led = 4;
const int capteur = 2;
int val = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(capteur, INPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(capteur);

  if (val == HIGH) {
    digitalWrite(led, HIGH);
    delay(1000);
  } else {
    digitalWrite(led, LOW);
    delay(1000);
  }
}
