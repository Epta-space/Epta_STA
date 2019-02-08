void setup() {
  Serial.begin(9600);

}

void loop() {

int distance = millis();
char* printar = new char[30];
float seno = (float) sin(0.001 * distance);
Serial.println(seno + 1);
    
  }
