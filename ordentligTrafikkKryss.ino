#define roadVerticalSense 6

#define roadLightVerticalGreen 16
#define roadLightVerticalYellow 15
#define roadLightVerticalRed 14

#define roadHorizontalSense 10

#define roadLightHorizontalGreen 19
#define roadLightHorizontalYellow 18
#define roadLightHorizontalRed 17

#define northCrosswalkGreen 9
#define northCrosswalkRed 8
#define northCrosswalkSwitch 7

#define southCrosswalkGreen 5
#define southCrosswalkRed 4
#define southCrosswalkSwitch 3

#define eastCrosswalkGreen 2
#define eastCrosswalkRed 1
#define eastCrosswalkSwitch 0

#define westCrosswalkGreen 13
#define westCrosswalkRed 12
#define westCrosswalkSwitch 11 

//check for car at point
bool driveRequestVertical = 0;
bool driveRequestHorizontal = 0;

//check for human at point
bool walkRequestNorth = 0;
bool walkRequestSouth = 0;
bool walkRequestEast = 0;
bool walkRequestWest = 0;

//timers
const int driveTimerVertical = 5000;
const int driveTimerHorizontal = 2500;
const int driveTimerHorizontalShort = 1250;
const int walkTimer = 10000;
const int lightChangeTimer = 2000;

byte i = 0;
bool j = 0; //0 = vertical, 1 = horizontal
bool k = 0;
byte l = 0;
byte m = 0;

void setup()
{
  pinMode(roadLightVerticalGreen, OUTPUT);
  pinMode(roadLightVerticalYellow, OUTPUT);
  pinMode(roadLightVerticalRed, OUTPUT);

  pinMode(roadVerticalSense, INPUT);

  pinMode(roadLightHorizontalGreen, OUTPUT);
  pinMode(roadLightHorizontalYellow, OUTPUT);
  pinMode(roadLightHorizontalRed, OUTPUT);

  pinMode(roadHorizontalSense, INPUT);

  pinMode(northCrosswalkGreen, OUTPUT);
  pinMode(northCrosswalkRed, OUTPUT);
  pinMode(northCrosswalkSwitch, INPUT);

  pinMode(southCrosswalkGreen, OUTPUT);
  pinMode(southCrosswalkRed, OUTPUT);
  pinMode(southCrosswalkSwitch, INPUT);

  pinMode(eastCrosswalkGreen, OUTPUT);
  pinMode(eastCrosswalkRed, OUTPUT);
  pinMode(eastCrosswalkSwitch, INPUT);

  pinMode(westCrosswalkGreen, OUTPUT);
  pinMode(westCrosswalkRed, OUTPUT);
  pinMode(westCrosswalkSwitch, INPUT);

  Serial.begin(9600);

  startup();
}

void loop()
{
  for(i=0; i <= 30; i++){
    sensorRead();
    if(j == 0 && k == 0){
      
    } 
    else{
      continue;
    } 
  }
  j = !j;
 

  delay(1000);

//   if(walkRequestNorth){
//     digitalWrite(northCrosswalkGreen, HIGH);
//   }
//   else{
//     digitalWrite(northCrosswalkGreen, LOW);
//   }
}

void sensorRead()
{
  driveRequestVertical =   digitalRead(roadVerticalSense);
  driveRequestHorizontal = digitalRead(roadHorizontalSense);

  walkRequestNorth = digitalRead(northCrosswalkSwitch);
  walkRequestSouth = digitalRead(southCrosswalkSwitch);
  walkRequestEast =  digitalRead(eastCrosswalkSwitch);
  walkRequestWest =  digitalRead(westCrosswalkSwitch);



  Serial.println("________________________");

  Serial.print("driveRequestVertical:   ");
  Serial.println(driveRequestVertical);
  Serial.print("driveRequestHorizontal: ");
  Serial.println(driveRequestHorizontal);

  Serial.println("------------------------");

  Serial.print("walkRequestNorth: ");
  Serial.println(walkRequestNorth);
  Serial.print("walkRequestSouth: ");
  Serial.println(walkRequestSouth);
  Serial.print("walkRequestEast:  ");
  Serial.println(walkRequestEast);
  Serial.print("walkRequestWest:  "); 
  Serial.println(walkRequestWest);
}

void verticalUp(){
  delay(lightChangeTimer);
  digitalWrite(roadLightVerticalGreen,   LOW);
  digitalWrite(roadLightVerticalYellow, HIGH);
  digitalWrite(roadLightVerticalRed,     LOW);
  delay(lightChangeTimer);
  digitalWrite(roadLightVerticalGreen,  HIGH);
  digitalWrite(roadLightVerticalYellow,  LOW);
  digitalWrite(roadLightVerticalRed,     LOW);
}
void verticalDown(){
  delay(lightChangeTimer);
  digitalWrite(roadLightVerticalGreen,   LOW);
  digitalWrite(roadLightVerticalYellow, HIGH);
  digitalWrite(roadLightVerticalRed,     LOW);
  delay(lightChangeTimer);
  digitalWrite(roadLightVerticalGreen,   LOW);
  digitalWrite(roadLightVerticalYellow,  LOW);
  digitalWrite(roadLightVerticalRed,    HIGH);
}

void horizontalUp(){
  delay(lightChangeTimer);
  digitalWrite(roadLightHorizontalGreen,   LOW);
  digitalWrite(roadLightHorizontalYellow, HIGH);
  digitalWrite(roadLightHorizontalRed,     LOW);
  delay(lightChangeTimer);
  digitalWrite(roadLightHorizontalGreen,   LOW);
  digitalWrite(roadLightHorizontalYellow,  LOW);
  digitalWrite(roadLightHorizontalRed,    HIGH);
}
void horizontalDown(){
  delay(lightChangeTimer);
  digitalWrite(roadLightHorizontalGreen,   LOW);
  digitalWrite(roadLightHorizontalYellow, HIGH);
  digitalWrite(roadLightHorizontalRed,     LOW);
  delay(lightChangeTimer);
  digitalWrite(roadLightHorizontalGreen,  HIGH);
  digitalWrite(roadLightHorizontalYellow,  LOW);
  digitalWrite(roadLightHorizontalRed,     LOW);
}

void walkNorthDown(){
  delay(lightChangeTimer);
  digitalWrite(northCrosswalkGreen, LOW);
  digitalWrite(northCrosswalkRed,  HIGH);
}
void walkNorthUp(){
  delay(lightChangeTimer);
  digitalWrite(northCrosswalkGreen, HIGH);
  digitalWrite(northCrosswalkRed,    LOW);
}

void walkSouthDown(){
  delay(lightChangeTimer);
  digitalWrite(southCrosswalkGreen, LOW);
  digitalWrite(southCrosswalkRed,  HIGH);
}
void walkSouthUp(){
  delay(lightChangeTimer);
  digitalWrite(southCrosswalkGreen, HIGH);
  digitalWrite(southCrosswalkRed,    LOW);
}

void walkEastDown(){
  delay(lightChangeTimer);
  digitalWrite(eastCrosswalkGreen, LOW);
  digitalWrite(eastCrosswalkRed,  HIGH);
}
void walkEastUp(){
  delay(lightChangeTimer);
  digitalWrite(eastCrosswalkGreen, HIGH);
  digitalWrite(eastCrosswalkRed,    LOW);
}

void walkWestDown(){
  delay(lightChangeTimer);
  digitalWrite(westCrosswalkGreen, LOW);
  digitalWrite(westCrosswalkRed,  HIGH);
}
void walkWestUp(){
  delay(lightChangeTimer);
  digitalWrite(westCrosswalkGreen, HIGH);
  digitalWrite(westCrosswalkRed,    LOW);
}

void startup(){
  digitalWrite(roadLightHorizontalGreen,  LOW);
  digitalWrite(roadLightHorizontalYellow, LOW);
  digitalWrite(roadLightHorizontalRed,   HIGH);
  digitalWrite(roadLightVerticalGreen,   HIGH);
  digitalWrite(roadLightVerticalYellow,   LOW);
  digitalWrite(roadLightVerticalRed,      LOW);
  digitalWrite(northCrosswalkGreen, LOW);
  digitalWrite(northCrosswalkRed,  HIGH);
  digitalWrite(southCrosswalkGreen, LOW);
  digitalWrite(southCrosswalkRed,  HIGH);
  digitalWrite(eastCrosswalkGreen,  LOW);
  digitalWrite(eastCrosswalkRed,   HIGH);
  digitalWrite(westCrosswalkGreen,  LOW);
  digitalWrite(westCrosswalkRed,   HIGH);
}



















// roadLightVerticalYellow
// roadLightVerticalRed
// roadVerticalSense
// roadLightHorizontalGreen
// roadLightHorizontalYellow
// roadLightHorizontalRed
// roadHorizontalSense
// northCrosswalkGreen
// northCrosswalkRed
// northCrosswalkSwitch
// southCrosswalkGreen
// southCrosswalkRed
// southCrosswalkSwitch
// eastCrosswalkGreen
// eastCrosswalkRed
// eastCrosswalkSwitch
// westCrosswalkGreen
// westCrosswalkRed
// westCrosswalkSwitch
