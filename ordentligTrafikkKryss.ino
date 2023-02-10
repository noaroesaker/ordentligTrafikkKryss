// #include <lightControl.h>
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

#define northCrosswalkButton 18
#define southCrosswalkButton 19
#define eastCrosswalkButton 20
#define westCrosswalkButton 21 

#define northButtonWaitLed 22
#define southButtonWaitLed 23
#define eastButtonWaitLed 24
#define westButtonWaitLed 25

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
const byte delayTickAmount = 40;
const byte tickAmount = 20;

//counter
byte i = 0; // used for counting ticks and where in process the for loop is
byte j = 0; // used for delayPut where it is a delay looking for inputs

//memory
bool driveDirection0v1h = 0; // 0 = vertical, 1 = horizontal

// has the vertical light canged yet? 0 = not
bool verticalGreenChanged = 0;
bool verticalYellowChanged = 0;
bool verticalRedChanged = 0;

// has the horizontal light canged yet? 0 = not
bool horizontalGreenChanged = 0;    
bool horizontalYellowChanged = 0;
bool horizontalRedChanged = 0;

// has the vertical/horizontal light completely changed yet? 0 = not
bool verticalLightCompleteChanged = 0; 
bool horizontalLightCompleteChanged = 0;

// button was pressed and request fulfilled now is green light
bool walkRequestNorthGo = 0;
bool walkRequestSouthGo = 0;
bool walkRequestEastGo = 0;
bool walkRequestWestGo = 0;

// walk request when red light so it remembers that you want to go over at green light
bool walkRequestOnRedNorth = 0;
bool walkRequestOnRedSouth = 0;
bool walkRequestOnRedEast = 0;
bool walkRequestOnRedWest = 0;

// stored temporary value of tick for use with timing red
byte northTick = 0;
byte southTick = 0;
byte  eastTick = 0;  
byte  westTick = 0;  

//
bool northFunction = 0;
bool southFunction = 0;
bool  eastFunction = 0;
bool  westFunction = 0;

void setup(){
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

  pinMode(northCrosswalkButton, INPUT);
  pinMode(southCrosswalkButton, INPUT);
  pinMode(eastCrosswalkButton,  INPUT);
  pinMode(westCrosswalkButton,  INPUT);

  pinMode(northButtonWaitLed, OUTPUT);
  pinMode(southButtonWaitLed, OUTPUT);
  pinMode(eastButtonWaitLed,  OUTPUT);
  pinMode(westButtonWaitLed,  OUTPUT);

  Serial.begin(9600);

  startup(); // look down in code
}

void startup(){ // sets a default starting pont
  verticalRedLed();
  horizontalRed();
  walkNorthGreen();
  walkSouthRed();
  walkEastRed();
  walkWestRed();
  
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
  for(i=0; i <= tickAmount; i++){
    delayPut();

    if(!driveDirection0v1h && !verticalLightCompleteChanged){
      if(!verticalYellowChanged){
        verticalYellowLed();
        verticalYellowChanged = 1;
      }
      if(!verticalGreenChanged){
        verticalGreenLed();
        verticalGreenChanged = 1;
      }
      if(verticalYellowChanged && verticalGreenChanged){
        verticalLightCompleteChanged = 1;
      }

      //no cars on one road so car will be prioritized
      if(driveRequestHorizontal && !driveRequestVertical){
        if(verticalYellowChanged){
          verticalGreenLed();
          i = 0;
          driveDirection0v1h = 0;
        }
        if(!verticalYellowChanged){
          verticalYellowLed();
          verticalYellowChanged;
        }
      }

      // inverted from above
      // if(!driveRequestHorizontal && driveRequestVertical){
        
      // }
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
  driveDirection0v1h = !driveDirection0v1h;

  walkRequestNorthGo = 0; walkRequestSouthGo = 0; 
   walkRequestEastGo = 0;  walkRequestWestGo = 0;
            northTick = 0;           southTick = 0;           
             eastTick = 0;            westTick = 0;

  verticalGreenChanged = 0; verticalYellowChanged = 0; verticalRedChanged = 0;
  horizontalGreenChanged = 0; horizontalYellowChanged = 0; verticalRedChanged = 0;

  if(driveDirection0v1h){
    verticalLightCompleteChanged = 0;
  }
  if(!driveDirection0v1h){
    horizontalLightCompleteChanged = 0;
  } //hellooo
}

void functions(){
  northFunction = !driveDirection0v1h && walkRequestNorth && !walkRequestNorthGo && i <= 10;

  // southFunction = !driveDirection0v1h && walkRequestSouth && !walkRequestSouthGo && i <= 10;
  // eastFunction = driveDirection0v1h && walkRequestEast && !walkRequestEastGo && i <= 10;
  // westFunction = driveDirection0v1h && walkRequestWest && !walkRequestWestGo && i <= 10;
}

void northCrosswalk(){
  if(northFunction){
    walkNorthGreen();
    walkRequestNorthGo = 1;
    northTick = i;
  }
  if(i == northTick + 10){ // waits for 10 ticks / 10 sec
    walkNorthRed();
  }
  if(driveDirection0v1h && walkRequestNorth && !walkRequestNorthGo){ // puts in memory a request for walking 
    walkRequestOnRedNorth = 1;
  }
  if(walkRequestOnRedNorth && !driveDirection0v1h){
    walkNorthGreen();
    walkRequestOnRedNorth = 0;
  }
}
void southCrosswalk(){
  // if(walkRequestSouth && !walkRequestSouthGo && i <= 10){
      //   walkSouthGreen();
      //   walkRequestEastGo = 1; 
      //   southTick = i;
      // }
      // if(i == southTick + 10){
      //   walkSouthRed();
      // }
}
void eastCrosswalk(){
  // if(walkRequestEast && !walkRequestEastGo && i <= 10){
      //   walkEastGreen();
      //   walkRequestEastGo = 1; 
      //   eastTick = i;
      // }
      // if(i == eastTick + 10){
      //   walkEastRed();
      // }
}
void westCrosswalk(){
  // if(walkRequestWest && !walkRequestWestGo && i <= 10){
      //   walkWestGreen();
      //   walkRequestWestGo = 1; 
      //   westTick = i;
      // }
      // if(i == westTick + 10){
      //   walkWestRed();
      // }
}

void sensorRead(){
  driveRequestVertical =   digitalRead(roadVerticalSense);
  driveRequestHorizontal = digitalRead(roadHorizontalSense);

  walkRequestNorth = digitalRead(northCrosswalkButton);
  walkRequestSouth = digitalRead(southCrosswalkButton);
  walkRequestEast =  digitalRead(eastCrosswalkButton);
  walkRequestWest =  digitalRead(westCrosswalkButton);
}

void verticalGreenLed(){
  digitalWrite(roadLightVerticalGreen,  HIGH);
  digitalWrite(roadLightVerticalYellow,  LOW);
  digitalWrite(roadLightVerticalRed,     LOW);
}
void verticalYellowLed(){
  digitalWrite(roadLightVerticalGreen,   LOW);
  digitalWrite(roadLightVerticalYellow, HIGH);
  digitalWrite(roadLightVerticalRed,     LOW);
}
void verticalRedLed(){
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

void crosswalkButton(){
  if(walkRequestNorth){
    digitalWrite(northButtonWaitLed, HIGH);
  }
  if(walkRequestSouth){
    digitalWrite(southButtonWaitLed, HIGH);
  }
  if(walkRequestEast){
    digitalWrite(eastButtonWaitLed, HIGH);
  }
  if(walkRequestWest){
    digitalWrite(westButtonWaitLed, HIGH);
  }
}

void delayPut(){
  for(j = 0; j < delayTickAmount; j++)
  sensorRead();
  crosswalkButton();
  serialPlotter();
  delay(forDelay);
}
