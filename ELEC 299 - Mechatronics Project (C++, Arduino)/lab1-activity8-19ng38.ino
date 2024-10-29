//Digital Pins Used
const int trigPin = 6;
const int echoPin = 5;
const int ledPin = 2;

long duration;
int distance;
int ledState = LOW;

long interval;
unsigned long previousMillis = 0;        // will store last time LED was updated 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  /*----------Measure Distance----------*/
  //Making sure trigPin starts LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //10 microsecond pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  
  //Serial.print("Distance:");
  //Serial.println(distance);
  /*----------Blink LED----------*/
  unsigned long currentMillis = millis();
  interval = ((distance-2)/398.0)*990 + 10;

  //Max Interval
  if (interval > 1000){
    interval = 1000;
  }

  if (currentMillis - previousMillis >= interval) {
    
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    
    
    Serial.print("Distance:");
    Serial.println(distance);
    Serial.println(interval);
  }
  
}
