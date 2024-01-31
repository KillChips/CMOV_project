// define pin numbers
const int trigPin1 = 9;
const int echoPin1 = 10;
const int trigPin2 = 11;
const int echoPin2 = 12;
// define variables
long duration = 0;
int distance = 0;
int maxd_1 = 0;
int maxd_2 = 0;
int count = 0;

void setup() {

  //Sensor 1
  pinMode(trigPin1, OUTPUT); // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin1 as an Input

  //Sensor 2
  pinMode(trigPin2, OUTPUT); // Sets the trigPin2 as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin2 as an Input

  Serial.begin(9600); // Starts the serial communication

  maxd_1 = getDistance(trigPin1, echoPin1);
  //maxd_2 = getDistance2(trigPin2, echoPin2);
  maxd_2 = maxd_1;
  
}

int getDistance(int trig, int echo){
  // Clears the trigPin
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin1 on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echoPin1, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // Calculating the distance1
  distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  
  // Gets the distance
  int distance1 = getDistance(trigPin1, echoPin1);
  //int distance2 = getDistance2(trigPin2, echoPin2);
  int distance2 = maxd_1;
  

  // Assuming both sensors are the same value when no one is passing
  /*if(distance1 < distance2 && distance1 > 0){
    count++;
  } else if(distance2 < distance1 - 20) {
    count--;
  }*/

  if (distance1 < maxd_1 - 15) {
    int i = millis();
    while ((millis() - i) <= 3000) {
      distance2 = maxd_2 - 16;//getDistance(trigPin2, echoPin2);
      //Serial.print("sensor2 = "); 
      //Serial.println(sensor2());
      if (distance2 < maxd_2 - 15) {
        count++;
        break;
      }
    }
    // para demonstrar posso mudar o valor de d2 aqui
  } else if (distance2 < maxd_2 - 15) {
    int i = millis();
    while ((millis() - i ) <= 3000) {
      distance1 = getDistance(trigPin1, echoPin1);
      //Serial.print("sensor1 = "); 
      //Serial.println(sensor1());
      if (distance1 < maxd_1 - 15) {
        count--;
        break;
      }
    }
  }

  // Prints the distance1 on the Serial Monitor
  Serial.print("nperson=");
  Serial.print(count);
  
  Serial.print("\t");
  Serial.print(distance1);
  Serial.print("\t");
  Serial.print(distance2);
  Serial.print("\t");
  Serial.print(maxd_2);

  Serial.print("\n");
  
  delay(1000);
}
