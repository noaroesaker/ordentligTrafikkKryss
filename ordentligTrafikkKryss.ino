#define roadVerticalSense 2

#define roadLightVerticalGreen 3
#define roadLightVerticalYellow 4
#define roadLightVerticalRed 5

#define roadHorizontalSense 6

#define roadLightHorizontalGreen 7
#define roadLightHorizontalYellow 8
#define roadLightHorizontalRed 9

#define northCrosswalkGreen 10
#define northCrosswalkRed 11

#define northCrosswalkSwitch 12

#define southCrosswalkGreen 13
#define southCrosswalkRed 14

#define southCrosswalkSwitch 15

#define eastCrosswalkGreen 16
#define eastCrosswalkRed 17

#define eastCrosswalkSwitch 18

#define westCrosswalkGreen 19
#define westCrosswalkRed 20

#define westCrosswalkSwitch 21 

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
bool direction = 0; //0 = vertical, 1 = horizontal
bool vertLightCha = 0;
bool vertGreen = 0;
bool vertYellow = 0;
bool vertRed = 0;

bool horiLightCha = 0;
bool horiGreen = 0;
bool horiYellow = 0;
bool horiRed = 0;
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
    if(direction == 0 && vertLightCha == 0){
      if(vertYellow == 0){
        verticalYellow();
      }
      else if(vertGreen == 0){
        verticalGreen();
      }
      
      
    } 
    else if(direction == 1 && horiLightCha == 0){

    }
    else{
      continue;
    } 
  }
  direction = !direction;

  if(direction){
    vertLightCha = 0;
  }
  if(!direction){
    horiLightCha = 0;
  } //hellooo

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

void verticalGreen(){
  digitalWrite(roadLightVerticalGreen,  HIGH);
  digitalWrite(roadLightVerticalYellow,  LOW);
  digitalWrite(roadLightVerticalRed,     LOW);
}
void verticalYellow(){
  digitalWrite(roadLightVerticalGreen,   LOW);
  digitalWrite(roadLightVerticalYellow, HIGH);
  digitalWrite(roadLightVerticalRed,     LOW);
}
void verticalRed(){
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
