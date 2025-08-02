// const int cathodH = 22;
// const int cathodG = 23;
// const int anode1 = 24;
// const int cathodeA = 25;
// const int anode4 = 26;
// const int anode6 = 27;
// const int cathodeB = 28;
// const int cathodeC = 29;
// const int anode3 = 30;
// const int cathodeF = 31;
// const int cathodeD = 32;
// const int anode0 = 33;
// const int anode7 = 34;
// const int cathodeE = 35;
// const int anode5 = 36;
// const int anode2= 37;

const int joystickXinput = A0;
const int joystickYinput = A1;
const int joystickBinput = A2;


const int row[8] = {33, 24, 37, 30, 26, 36, 27, 34}; // anode
const int col[8] = {25, 28, 29, 32, 35, 31, 23, 22}; // cathod

int joystickXvalue = 0;
int joystickYvalue = 0;
int joystickBvalue = 0;

void setup() {
Serial.begin(9600);
for (int i = 0; i < 8; i++){
  pinMode(row[i], OUTPUT);
  pinMode(col[i], OUTPUT);
} 
pinMode(joystickXvalue, INPUT);
pinMode(joystickYvalue, INPUT);
pinMode(joystickBvalue, INPUT);
  
check();
clear();
digitalWrite(row[0], HIGH);
digitalWrite(col[0], LOW);

}

void loop(){
  Serial.println(analogRead(joystickXvalue));
  delay(250);
  Serial.println(analogRead(joystickYvalue));
  delay(250);
  Serial.println(analogRead(joystickBvalue));
  delay(250);
}

void check (){ // check if all connected right
  for (int i = 0; i < 8; i++){
    digitalWrite(row[i], HIGH);
    digitalWrite(col[i], LOW);
    delay(100);
  }
}
void clear (){ // clear LED matrix
  for (int i = 0; i < 8; i++){
    digitalWrite(row[i], LOW);
    digitalWrite(col[i], HIGH);
    delay(100);
  }
  
}