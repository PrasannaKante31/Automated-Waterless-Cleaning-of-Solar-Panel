/* 
╔══╗──────────╔╗──────╔═╗ ╔═╗╔═╗─────╔╗╔═╗╔═╗─╔╦═══╗
╚╣╠╝─────────╔╝║──────║╔╝ ║║╚╝║║─────║║║╔╝║║╚╗║╠╗╔╗║
 ║║──╔══╦╗╔╗ ╚╗║──╔══╦╝╚╗ ║╔╗╔╗╠╗─╔╗ ║╚╝╝╔╣╔╗╚╝║║║║║
 ║║──║╔╗║╚╝║──║║──║╔╗╠╗╔╝ ║║║║║║║─║║ ║╔╗║╠╣║╚╗║║║║║║
╔╣╠╗ ║╔╗║║║║ ╔╝╚╗ ║╚╝║║║──║║║║║║╚═╝║ ║║║╚╣║║─║║╠╝╚╝║
╚══╝ ╚╝╚╩╩╩╝ ╚══╝ ╚══╝╚╝──╚╝╚╝╚╩═╗╔╝ ╚╝╚═╩╩╝─╚═╩═══╝
 ──────────────────────────────╔═╝║
───────────────────────────────╚══╝

⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣠⣄    
⠄⠄⠄⠄⠄⠄⠄⢀⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⢠⣄⡀
⠄⠄⠄⠄⠄⠄⢠⣿⣿⣿⠿⢿⣿⣿⣿⣿⣿⡏⠄⠄⢸⣿⣿⡆
⠄⠄⠄⠄⠄⠄⣿⠟⣻⣿⡿⠛⢻⣿⣿⣿⣿⣷⣄⣠⣾⣿⡇
⠄⠄⠄⠄⠄⢸⣿⣿⠋⠻⣿⡀⠄⠙⠻⣿⣿⣿⣿⣿⣿⣿⣿⠆
⠄⠄⠄⠄⠄⢸⣿⡿⠄⠄⢻⣧⣀⠄⠄⣸⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣿⡇
⠄⠄⠄⠄⠄⠸⣿⣇⠄⠄⣼⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁
⠄⠄⠄⠄⠄⠄⢻⣿⣿⣿⣿⣿⠁⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯
⠄⠄⠄⠄⣀⣀⣤⣿⣿⣿⣿⣿⣶⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿
⠄⠄⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁
⠄⠄⠄⠈⢿⣿⡟⠛⠿⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆
⠄⠄⠄⠄⠄⠈⠁⠄⠄⠄⠉⠄⠙⠻⣿⣿⣿⣿⣿⣿⠿⠟⠁
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠉⠛⠿⢟
─╔═══╦╗╔═╗
─║╔═╗║║║╔╝
─║╚═╝║╚╝╝
─║╔══╣╔╗║
╔╣║──║║║╚╗
╚╩╝──╚╝╚═╝
*/
int vacuum=5;

// IR sensor 
int IR1 = 6;
int IR2 = 7;
//enable motor 1 and motor 2
int enA = 8;
int enB = 13;
// Motor 1 connections
int in1 = 9;
int in2 = 10;
// Motor 2 connections
int in3 = 11;
int in4 = 12;
//default position
int pos=-1;
//-1 => bottom part
// 0 => middle part
// 1 => upper part

// SET THESE VARIABLES //

//stop motor 1 for this much time after motor 2 does its iteration
int requiredBuffer= 2000;
//time taken by motor 2 to one way through section
int timeMotorTwo= 1000;
//in how many parts the section has been divided
//ie. motor One has to go in loop for these many times
int iterationOfMotorOne= 2;
int iterationOfMotorTwo= 3;
//how much time we want to run motor One in case of stepwise rotation
int pitchTimeMotorOne= 1000; 

void setup() {
    pinMode(vacuum, OUTPUT);

    pinMode(enA, OUTPUT);
    pinMode(enA, OUTPUT);

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    pinMode(IR1, INPUT);
    pinMode(IR2, INPUT);
	
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void loop() {
  //initial readings
  pos=-1;
  int reading1= digitalRead(IR1);
  int reading2= digitalRead(IR2);

  //if any one of the section is dirty then trigger the Util function
  if (reading1 || reading2) motorOneUtils(reading1, reading2);
}

//logic for the code, other functions are just agents
void motorOneUtils (int reading1, int reading2){
  //run this loop while any one of the section is dirty
  while (reading1 || reading2){
    int from= pos;
    int to= (from==-1 || from==1) ? 0 : (reading1) ? -1 : 1 ;
    //if we want to go stepwise 
    //intialize stepwise as true
    bool stepwise= true;
    
    //skip section2 if it is clean and move to section 1
    if (pos==1 && !reading2) stepwise= false;
    //skip section1 if it is clean and move to section 2
    else if (pos==-1 && !reading1) stepwise= false; 
    
    controlMotorOne(from, to, stepwise);
    //take reading again to check if the section is cleaned or not
    reading1= digitalRead(IR1);
    reading2= digitalRead(IR2);
    // if (reading1) reading1= false;
    // if (reading2) reading2= false;
    //change the current position
    pos= to;
  }
  //after cleaning send the motor to down position again
  controlMotorOne(pos, -1, false);
  pos=-1;
}

void controlMotorOne (int from, int to, bool stepwise){
  //how many times motor 1 has to stop
  int cnt= iterationOfMotorOne;
  //if we want to clean both the sections then double the num of times we want to stop the motor1
  cnt= cnt*(abs(to-from));
  //variable that ensures if we want to move motor 1 or not
  bool motion= true;
  while(cnt>0){
    //move motor1 with motion=true
    moveMotorOne(from, to, motion);
    //keep moving till it completes its one pitch
    delay(pitchTimeMotorOne);
    //if del is non-zero then we are moving stepwise
    if (stepwise) {
      //false => do not move the motor 1
      moveMotorOne(from, to, !motion);
      moveMotorTwo();
      //stop motor 1 and move motor 2 till del time
      delay(requiredBuffer);
    }
    cnt--;
  }
  //stop motor 1 after cleaning
  moveMotorOne(from, to, !motion);
}

//function to give direction to the motor
void moveMotorOne (int from, int to, bool motion){
  //if already at the position then dont do anything
  //if !motion => then it indicated we want to stop the motor
  if (from==to || !motion) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    return;
  }
  //rotate clockwise if we want to go from lower part to upper
  else if (from<to){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } 
  //rotate anti-clockwise if we want to go from upper part to lower
  else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
}

void moveMotorTwo() {
    analogWrite(enB, 255);
    //vacuum should be active till the motor 2 is moving
    digitalWrite(vacuum, HIGH);
    int cnt= iterationOfMotorTwo;  
    //run motor 2, cnt times to and fro
    while (cnt>0){
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      delay(timeMotorTwo);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      delay(timeMotorTwo);
      cnt--;
    }
    //stop the vacuum
    digitalWrite(vacuum, LOW);
    //stop motor 2
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}