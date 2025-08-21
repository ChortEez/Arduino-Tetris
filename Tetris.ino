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
const int soundPin  = 8;



const int joystickXinput = A0;
const int joystickYinput = A1;
const int joystickBinput = A2;


const int row[8] = {33, 24, 37, 30, 26, 36, 27, 34}; // anode
const int col[8] = {25, 28, 29, 32, 35, 31, 23, 22}; // cathod
int field[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};
int col[2][1] = {
                {2},
                {2} 
                };


int joystickXvalue = 0;
int joystickYvalue = 0;
int joystickBvalue = 0;

const unsigned long interval = 200;  // game interval
const unsigned long joystickInterval = 250; // Інтервал оновлення позиції джойстику
const int updateTime = 0; // Швидкість оновлення матриці
unsigned long lastTime = 0; // Зміна для рахування мілісекунд які пройшли з початку гри.
int matrixPosX = 0;
int matrixPosY = 0;
String direction;

// int tempPositionX = matrixPosX++;
// int tempPositionY = matrixPosY++;




void setup() {
Serial.begin(9600);
for (int i = 0; i < 8; i++){
  pinMode(row[i], OUTPUT);
  pinMode(col[i], OUTPUT);
} 
pinMode(joystickXvalue, INPUT);
pinMode(joystickYvalue, INPUT);
pinMode(joystickBvalue, INPUT);

pinMode(soundPin, OUTPUT);

check();
clear();
Debug();
newFigure();

}

void loop(){
  matrixRefresh();

  if (millis() - lastTime > interval){ // Внутрішньоігровий таймер який не зупиняє час.
    // Debug();
    // DebugField();
    getCommand();
    // playSound();
    checkIsRowFull();
    fallDown();

    
    


    lastTime = millis();
  }
}
void getCommand(){ // need to write some code
  joystickXvalue = analogRead(joystickXinput);
  joystickYvalue = analogRead(joystickYinput);
  joystickBvalue = digitalRead(joystickBinput);

  if (joystickXvalue == 1023 && joystickYvalue < 1023 && matrixPosX  < 7){ // joystick is RIGHT. Тут йобнута помилка, якщо крапка рухається по діагоналі то крапку яка вже стоїть - стирає. Функція перевіряє й також чи не виходить за межі
    if (field[matrixPosX+1][matrixPosY]== 0){
      erasePixel(matrixPosX, matrixPosY);
      matrixPosX++;
      drawPixel(matrixPosX, matrixPosY);
      direction = "RIGHT";
    }
    
  } else if (joystickXvalue == 0 && joystickYvalue < 1023 && matrixPosX  > 0){ // joystick is LEFT. Перевірка на вихід за межі
    if (field[matrixPosX-1][matrixPosY] == 0){
      erasePixel(matrixPosX, matrixPosY);
      matrixPosX--;
      drawPixel (matrixPosX, matrixPosY);
      direction = "LEFT";
    }
  } 
}

void Debug(){
  Serial.print("X:");
  Serial.print(analogRead(joystickXinput));
  Serial.print("\t");
  Serial.print("Y:");
  Serial.print(analogRead(joystickYinput));
  Serial.print("\t");
  Serial.print("B:");
  Serial.print(analogRead(joystickBinput));
  Serial.print("\t");

  Serial.print("matrixX:");
  Serial.print(matrixPosX);
  Serial.print("\t");
  Serial.print("matrixY:");
  Serial.print(matrixPosY);
  Serial.print("\t");


  Serial.println(" ");
}

void check (){ // check if all connected right
  for (int i = 0; i < 8; i++){
    digitalWrite(row[i], HIGH);
    digitalWrite(col[i], LOW);
    delay(75);
  }
}
void clear (){ // clear LED matrix
  for (int i = 0; i < 8; i++){
    digitalWrite(row[i], LOW);
    digitalWrite(col[i], HIGH);
  }
}
void drawPixel(int x, int y){ // Вносить 1 в массив поля
  matrixPosX = x;
  matrixPosY = y;
  field[x][y] = 1;
}
void permanentDrawPixel(int x, int y){
  field[x][y] = 2;
}
void erasePixel(int x, int y){ // Прибирає 1 і вносить 0 в масив поля
  matrixPosX = x;
  matrixPosY = y;
  field[x][y] = 0;
}
void fallDown(){
  if (matrixPosY < 7 && field[matrixPosX][matrixPosY + 1] != 2){ // Якщо позиція нуль, то піксель "Падає" 
    erasePixel(matrixPosX, matrixPosY); // Стирання пікселя
    // tempPositionY++;
    matrixPosY++;
    collisionCheck();
    drawPixel(matrixPosX, matrixPosY);
    
   } else if (matrixPosY == 7){
    permanentDrawPixel(matrixPosX, matrixPosY);
    newFigure();
   } else if (field[matrixPosX][matrixPosY + 1] == 2){
    permanentDrawPixel(matrixPosX, matrixPosY);
    newFigure();
   }
  
}
void newFigure(){
matrixPosX = random(0,8);
  if (field[matrixPosX][0] ==0){ // Перевірка чи не зайнята позиція де має з'явитися фігура
    drawPixel(matrixPosX, 0); // Рандомна позиція фігури
  }
  
}

void collisionCheck(){
  int tempPositionX = matrixPosX;
  int tempPositionY = matrixPosY;
  tempPositionY++;
  // if (direction == String("RIGHT")){
  //   tempPositionX++;
  //   if (field[tempPositionX][tempPositionY] == 1){
  //     // matrixPosX = tempPositionX;
  //     drawPixel(matrixPosX,matrixPosY);
  //     newFigure();
  //   }
  // } else if (direction == String("LEFT")){
  //   tempPositionX--;
  //   if (field[tempPositionX][tempPositionY]){
  //     // matrixPosX = tempPositionX;
  //     drawPixel(matrixPosX, matrixPosY);
  //     newFigure();
  //   } 
   if (field[matrixPosX][tempPositionY] == 1){
    // matrixPosY = tempPositionY;
    drawPixel(matrixPosX, matrixPosY);
    newFigure();
  }


}
void matrixRefresh(){ // Мультиплексування матриці, швидко перевіряє кожен рядок і засвічує колонку що горить.
  for (int y = 0; y < 8; y++){
    digitalWrite(row[y], HIGH);
    for (int x = 0; x < 8; x++){
      if (field[x][y] == 1 || field[x][y] == 2){
      digitalWrite(col[x], LOW);
    } 
    delay(updateTime);
    digitalWrite(col[x], HIGH);
    }
    // delay(updateTime);
    digitalWrite(row[y], LOW);
  }
}
void DebugField() { //Написано ШІ
  Serial.println("===== LED MATRIX FIELD =====");
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      if (field[x][y] == 1) {
        Serial.print("1 ");
      } else if (field[x][y] == 2) {
        Serial.print("2 ");
      } else{
        Serial.print("0 ");
      }
    }
    Serial.println();
  }
  Serial.println("============================");
}

void checkIsRowFull(){ // Коротше, треба пробігтися по всіх рядках, якщо перший елемент - повний. То потрібно йти далі. Якщо ні, то переходиш на наступний рядок. Зараз голова не варить...
bool rowFull;
 for(int y = 7; y > - 1; y--){ // Йдемо по рядах починаючи з останнього. Рахуємо знизу, так логічніше
    // if (field[x][y] == 1){ // Якщо рядок X, і його елемент Y = 1 то запускається перевірка на наступний елемент
      for (int x = 0; x < 8; x++){ 
        if (field[x][y] == 1 || field[x][y] == 2) {
          rowFull = true;
        } else {
          rowFull = false;
          break;
        }
      }
    if (rowFull){
    eraseRow(y);
    }
    } 
    
    }

void eraseRow(int y){
  for (int x = 0; x < 9; x++){
    erasePixel(x, y);
  }
}
void playSound(){
  tone(soundPin, 25, 25); // 1 kHz tone
}

