

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
bool driveRequestVertical = 0;   // active when a car is sensed at the intersection
bool driveRequestHorizontal = 0; // active when a car is sensed at the intersection

//check for human at point
bool walkRequestNorth = 0; // active when someone pressed crosswalk button
bool walkRequestSouth = 0; // active when someone pressed crosswalk button
bool walkRequestEast = 0;  // active when someone pressed crosswalk button
bool walkRequestWest = 0;  // active when someone pressed crosswalk button

//timers
const byte forDelay = 25; // delay used every count of the for loop instead of individual timers, cause this will improve response times
const byte tickAmount = 40;

//counter
byte i = 0; // used for counting ticks and where in process the for loop is

//memory
bool direction = 0;    // 0 = vertical, 1 = horizontal

bool vertGreen = 0;    // has the vertical placed green canged yet? 0 = not
bool vertYellow = 0;   // has the vertical placed yellow canged yet? 0 = not
bool vertRed = 0;      // has the vertical placed red canged yet? 0 = not
bool vertLightCha = 0; // has the vertical light completely changed yet? 0 = not

bool horiGreen = 0;    // has the vertical placed green canged yet? 0 = not
bool horiYellow = 0;   // has the vertical placed yellow canged yet? 0 = not
bool horiRed = 0;      // has the vertical placed red canged yet? 0 = not
bool horiLightCha = 0; // has the horizontal light completely changed yet? 0 = not

bool requestNorthAck = 0;
bool requestSouthAck = 0;
bool requestEastAck = 0;
bool requestWestAck = 0;

byte northTick = 0;
byte southTick = 0;
byte eastTick = 0;
byte westTick = 0;


void setup()
{
  // road section
  pinMode(roadLightVerticalGreen,  OUTPUT);
  pinMode(roadLightVerticalYellow, OUTPUT);
  pinMode(roadLightVerticalRed,    OUTPUT);

  pinMode(roadLightHorizontalGreen,  OUTPUT);
  pinMode(roadLightHorizontalYellow, OUTPUT);
  pinMode(roadLightHorizontalRed,    OUTPUT);

  pinMode(roadVerticalSense,   INPUT);
  pinMode(roadHorizontalSense, INPUT);

  // crosswalk section
  pinMode(northCrosswalkGreen, OUTPUT);
  pinMode(northCrosswalkRed,   OUTPUT);

  pinMode(southCrosswalkGreen, OUTPUT);
  pinMode(southCrosswalkRed,   OUTPUT);

  pinMode(eastCrosswalkGreen, OUTPUT);
  pinMode(eastCrosswalkRed,   OUTPUT);
  
  pinMode(westCrosswalkGreen, OUTPUT);
  pinMode(westCrosswalkRed,   OUTPUT);

  pinMode(northCrosswalkSwitch, INPUT);
  pinMode(southCrosswalkSwitch, INPUT);
  pinMode(eastCrosswalkSwitch,  INPUT);
  pinMode(westCrosswalkSwitch,  INPUT);

  Serial.begin(9600);

  startup(); // look down in code
}

void startup(){ // sets a default starting pont
  verticalRed();
  horizontalRed();
  walkNorthGreen();
  walkSouthRed();
  walkEastRed();
  walkWestRed();

  Serial.print("inshalla feil bro");
  
  // digitalWrite(roadLightHorizontalGreen,  LOW);
  // digitalWrite(roadLightHorizontalYellow, LOW);
  // digitalWrite(roadLightHorizontalRed,   HIGH); //alt LOW?
  // digitalWrite(roadLightVerticalGreen,   HIGH); //alt LOW?
  // digitalWrite(roadLightVerticalYellow,   LOW);
  // digitalWrite(roadLightVerticalRed,      LOW);
  // digitalWrite(northCrosswalkGreen, LOW);
  // digitalWrite(northCrosswalkRed,  HIGH);
  // digitalWrite(southCrosswalkGreen, LOW);
  // digitalWrite(southCrosswalkRed,  HIGH);
  // digitalWrite(eastCrosswalkGreen,  LOW);
  // digitalWrite(eastCrosswalkRed,   HIGH);
  // digitalWrite(westCrosswalkGreen,  LOW);
  // digitalWrite(westCrosswalkRed,   HIGH);
}

void loop(){
  for(i=0; i <= 20; i++){
    delayPut();

    if(!direction && !vertLightCha){
      if(vertYellow == 0){
        verticalYellow();
      }
      else if(vertGreen == 0){
        verticalGreen();
      }
    }
    else{
      continue;
    }

    northCrosswalk();
      
    southCrosswalk();
      
    eastCrosswalk();

    westCrosswalk();
    
    
  } // for end

  memReset();
}

void memReset(){
  direction = !direction;

  requestNorthAck = 0;
  requestSouthAck = 0;
  requestEastAck = 0;
  requestWestAck = 0;

  northTick = 0;
  southTick = 0;
  eastTick = 0;
  westTick = 0;


  if(direction){
    vertLightCha = 0;
  }
  if(!direction){
    horiLightCha = 0;
  } //hellooo
}

void northCrosswalk(){
  if(!direction && walkRequestNorth && !requestNorthAck && i <= 10){
        walkNorthGreen();
        requestNorthAck = 1; 
        northTick = i;
      }
      if(i == northTick + 10){ // waits for 10 ticks / 10 sec
        walkNorthRed();
      }
      if(direction && walkRequestNorth && !requestNorthAck){
        walkReqestRedNorth = 1;
      }
      if(walkReqestRedNorth && !direction){
        walkNorthGreen();
        walkRequestRedNorth = 0;
      }
}
void southCrosswalk(){
  // if(walkRequestSouth && !requestSouthAck && i <= 10){
      //   walkSouthGreen();
      //   requestEastAck = 1; 
      //   southTick = i;
      // }
      // if(i == southTick + 10){
      //   walkSouthRed();
      // }
}
void eastCrosswalk(){
  // if(walkRequestEast && !requestEastAck && i <= 10){
      //   walkEastGreen();
      //   requestEastAck = 1; 
      //   eastTick = i;
      // }
      // if(i == eastTick + 10){
      //   walkEastRed();
      // }
}
void westCrosswalk(){
  // if(walkRequestWest && !requestWestAck && i <= 10){
      //   walkWestGreen();
      //   requestWestAck = 1; 
      //   westTick = i;
      // }
      // if(i == westTick + 10){
      //   walkWestRed();
      // }
}


void sensorRead()
{
  driveRequestVertical =   digitalRead(roadVerticalSense);
  driveRequestHorizontal = digitalRead(roadHorizontalSense);

  walkRequestNorth = digitalRead(northCrosswalkSwitch);
  walkRequestSouth = digitalRead(southCrosswalkSwitch);
  walkRequestEast =  digitalRead(eastCrosswalkSwitch);
  walkRequestWest =  digitalRead(westCrosswalkSwitch);
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

void serialPlotter(){
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

  Serial.println("------------------------");

  Serial.print("i loop nr: ");
  Serial.println(i);
}

void delayPut(){
  for(i=0; i<tickAmount; i++)
  sensorRead();
  serialPlotter();
  delay(forDelay);
}
