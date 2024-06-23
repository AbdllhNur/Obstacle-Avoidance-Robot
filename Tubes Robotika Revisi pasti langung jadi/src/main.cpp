#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

void moveForward();
void moveBackward(); 
void turnLeft();
void turnRight();
void moveStop();
int readPing();
int lookLeft();
int lookRight();

#define TRIG_PIN A0
#define ECHO_PIN A1
#define MAX_DISTANCE 200
#define MAX_SPEED 75 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

const int irKanan = A2;
const int irKiri = A3;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup()
{
  Serial.begin(9600);
  myservo.attach(10);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  pinMode(irKanan, INPUT);
  pinMode(irKiri, INPUT);
}

void loop()
{
  myservo.write(0);
  delay(100);
  Serial.println(distance);
  int distanceR = 0;
  int distanceL = 0;
  delay(40);

  if (distance <= 35)
  {
    distanceR = 0;
    distanceL = 0;
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    Serial.println("kanan : ");
    Serial.println(distanceR);
    delay(200);
    distanceL = lookLeft();
    Serial.println("kiri : ");
    Serial.println(distanceL);
    delay(200);
    if(distanceL == 1 && distanceR ==1){
      turnRight();
      delay(100);
      moveStop();
      delay(100);
    }
    else if (distanceL == 10)
    {
      Serial.println("belok kanan");
      turnRight();
      delay(100);
      moveStop();
      delay(100);
    }
    else if (distanceR == 10)
    {
      Serial.println("belok kiri");
      turnLeft();
      delay(100);
      moveStop();
      delay(100);
    }
  }
  else
  {
    moveForward();
  }
  distance = readPing();
  myservo.write(180);
  delay(100);
}

int lookRight()
{
  int distance = digitalRead(A2);
  if(distance == 0){
    return 10;
  }
  else{
    return distance;
  }
  delay(100);
}

int lookLeft()
{
  int distance = digitalRead(A3);
  if(distance == 0){
    return 10;
  }
  else{
    return distance;
  }
  delay(100);
}

int readPing()
{
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void moveForward()
{
  if (!goesForward)
  {
  Serial.println("maju");
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) 
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward()
{
  Serial.println("mundur");
  goesForward = false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(300);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void turnLeft()
{
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(300);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}