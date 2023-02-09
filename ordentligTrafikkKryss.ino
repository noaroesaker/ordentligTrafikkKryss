

#define roadLightVerticalGreen 2
#define roadLightVerticalYellow 3
#define roadLightVerticalRed 4

#define roadLightHorizontalGreen 5
#define roadLightHorizontalYellow 6
#define roadLightHorizontalRed 7

#define roadVerticalSense 8
#define roadHorizontalSense 9

#define northCrosswalkGreen 10
#define northCrosswalkRed 11

#define southCrosswalkGreen 12
#define southCrosswalkRed 13

#define eastCrosswalkGreen 14
#define eastCrosswalkRed 15

#define westCrosswalkGreen 16
#define westCrosswalkRed 17

#define northCrosswalkSwitch 18
#define southCrosswalkSwitch 19
#define eastCrosswalkSwitch 20
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

void horizontalGreen(){
  digitalWrite(roadLightHorizontalGreen,  HIGH);
  digitalWrite(roadLightHorizontalYellow,  LOW);
  digitalWrite(roadLightHorizontalRed,     LOW);
}
void horizontalYellow(){
  digitalWrite(roadLightHorizontalGreen,   LOW);
  digitalWrite(roadLightHorizontalYellow, HIGH);
  digitalWrite(roadLightHorizontalRed,     LOW);
}
void horizontalRed(){
  digitalWrite(roadLightHorizontalGreen,   LOW);
  digitalWrite(roadLightHorizontalYellow,  LOW);
  digitalWrite(roadLightHorizontalRed,    HIGH);
}

void walkNorthGreen(){
  digitalWrite(northCrosswalkGreen, HIGH);
  digitalWrite(northCrosswalkRed,    LOW);
}
void walkNorthRed(){
  digitalWrite(northCrosswalkGreen, LOW);
  digitalWrite(northCrosswalkRed,  HIGH);
}

void walkSouthGreen(){
  digitalWrite(southCrosswalkGreen, HIGH);
  digitalWrite(southCrosswalkRed,    LOW);
}
void walkSouthRed(){
  digitalWrite(southCrosswalkGreen, LOW);
  digitalWrite(southCrosswalkRed,  HIGH);
}

void walkEastGreen(){
  digitalWrite(eastCrosswalkGreen, HIGH);
  digitalWrite(eastCrosswalkRed,    LOW);
}
void walkEastRed(){
  digitalWrite(eastCrosswalkGreen, LOW);
  digitalWrite(eastCrosswalkRed,  HIGH);
}

void walkWestGreen(){
  digitalWrite(westCrosswalkGreen, HIGH);
  digitalWrite(westCrosswalkRed,    LOW);
}
void walkWestRed(){
  digitalWrite(westCrosswalkGreen, LOW);
  digitalWrite(westCrosswalkRed,  HIGH);
}

void startup(){
  digitalWrite(roadLightHorizontalGreen,  LOW);
  digitalWrite(roadLightHorizontalYellow, LOW);
  digitalWrite(roadLightHorizontalRed,   HIGH); //alt LOW?
  digitalWrite(roadLightVerticalGreen,   HIGH); //alt LOW?
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
