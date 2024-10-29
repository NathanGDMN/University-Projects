//Digital Pins Used
const int trigPin = 6;
const int echoPin = 5;

long duration;
int distance;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  //Making sure trigPin starts LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //10 microsecond pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  Serial.print("Distance:");
  Serial.println(distance);
  
}
