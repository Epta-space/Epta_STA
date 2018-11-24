int led = 13;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

}

void loop() {
  if (Serial.available()>0){
    String info;
    info = Serial.readStringUntil('\n');
    if(info.equals("ON")){
      digitalWrite(led, HIGH);
      Serial.println("LED is ON");
      }
    else if(info.equals("OFF")){
      digitalWrite(led, LOW);
      Serial.println("LED is OFF");
      }
    }
  }
