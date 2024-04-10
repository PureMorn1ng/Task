/*
  Задание 3.
  В данной задаче я выделил 6 состояний системы
  1: G1 R2 R3
  2: R1 G2 R3
  3: R1 R2 G3
  4: Y1 R2 R3
  5: R1 Y2 R3
  6: R1 R2 Y3
  Переход из состояний 1-3 в состояния 4-6 происходит по нажатию кнопки и выполнению условия горения зеленого света
  Переход из состояний 4-6 в состояния 1-3 происходит по нажатой кнопке и выполнению условия горения желтого света

  @Petrov Ivan 2024
*/



short int ButtonCowsPin = A1;  // пины кнопок для 1,2 и 3 светофора
short int ButtonSheepsPin = A2;
short int ButtonGoatsPin = A3;

short int R_PIN1 = 8;
short int G_PIN1 = 9;
short int Y_PIN1 = 10;

short int R_PIN2 = 11;
short int G_PIN2 = 12;
short int Y_PIN2 = 13;

short int R_PIN3 = 5;
short int G_PIN3 = 6;
short int Y_PIN3 = 7;

short int gate4Cows = 2;
short int gate4Sheeps = 3;
short int gate4Goats = 4;

short int St_last = 1;            //предыдущее состояние системы от 1 до 3
short int St_new = 1;             //новое состояние системы от 1 до 3
long unsigned int timeStnew = 0;  //время получения нового состояния с кнопки
long unsigned int tlast = 0;      //время начала текущего состояния
long unsigned int tYlast = 0;     //время наступления желтого режима светофора в текущем состоянии
bool GreenFlag, YellowFlag;

long unsigned int firstTimeY = 0;  //счетчик одноразового включения желтого света

void setup() {
  pinMode(R_PIN1, OUTPUT);
  pinMode(G_PIN1, OUTPUT);
  pinMode(Y_PIN1, OUTPUT);

  pinMode(R_PIN2, OUTPUT);
  pinMode(G_PIN2, OUTPUT);
  pinMode(Y_PIN2, OUTPUT);

  pinMode(R_PIN3, OUTPUT);
  pinMode(G_PIN3, OUTPUT);
  pinMode(Y_PIN3, OUTPUT);

  pinMode(gate4Cows, OUTPUT);
  pinMode(gate4Sheeps, OUTPUT);
  pinMode(gate4Goats, OUTPUT);

  pinMode(ButtonCowsPin, INPUT);
  pinMode(ButtonSheepsPin, INPUT);
  pinMode(ButtonGoatsPin, INPUT);

  digitalWrite(gate4Cows, 0);  // сначала работы программы все заслонки
  digitalWrite(gate4Sheeps, 0);  // в закрытом положении
  digitalWrite(gate4Goats, 0);
}

void loop() {


  readButtons();
  doState();
  gatesControl();
  checkTrafficLigths();
  stateTransfer();
  //  statusState();
  // buttonCheck();
}

void controlTrafficLigths(short int R_PIN, short int G_PIN, short int Y_PIN, short int valR, short int valG, short int valY) {

  digitalWrite(R_PIN, valR);  // Red pin signal
  digitalWrite(G_PIN, valG);  // Green pin signal
  digitalWrite(Y_PIN, valY);  // Yellow pin signal , можно отказаться, т.к. не используется
}

bool buttonInput(short int ButtonPin) {
  int buttonVal = analogRead(ButtonPin); //читаем с заданного аналогового пина
  if (buttonVal > 0) { //если значение не ноль -> то присваиваем единицу , в других случаях получится ноль
    buttonVal = 1;
  }
  return bool(buttonVal);
}

void gatesControl() {
  short int State = St_last;
  switch (State) {
    case 1:
      digitalWrite(gate4Cows, 1); //при единице на воротах, она открыта)0)
      digitalWrite(gate4Sheeps, 0);
      digitalWrite(gate4Goats, 0);
      break;

    case 2:
      digitalWrite(gate4Cows, 0);
      digitalWrite(gate4Sheeps, 1);
      digitalWrite(gate4Goats, 0);
      break;

    case 3:
      digitalWrite(gate4Cows, 0);
      digitalWrite(gate4Sheeps, 0);
      digitalWrite(gate4Goats, 1);
      break;
  }
}

void readButtons() {

  bool ButtonCowsVal = buttonInput(ButtonCowsPin);
  if (ButtonCowsVal == 1 && St_last != 1) {  //проверка повторного нажатия кнопки из загона
    St_new = 1;                       //получение нового состояния
  }
  bool ButtonSheepsVal = buttonInput(ButtonSheepsPin);
  if (ButtonSheepsVal == HIGH && St_last != 2) {
    St_new = 2;
  }
  bool ButtonGoatsVal = buttonInput(ButtonGoatsPin);
  if (ButtonGoatsVal == HIGH && St_last != 3) {
    St_new = 3;
  }
}

void doState() {
  short int State = St_last; // выполнение текущего состояния системы
  switch (State) {
    case 1:
      controlTrafficLigths(R_PIN1, G_PIN1, Y_PIN1, 0, 1, 0);
      controlTrafficLigths(R_PIN2, G_PIN2, Y_PIN2, 1, 0, 0);
      controlTrafficLigths(R_PIN3, G_PIN3, Y_PIN3, 1, 0, 0);
      break;

    case 2:
      controlTrafficLigths(R_PIN1, G_PIN1, Y_PIN1, 1, 0, 0);
      controlTrafficLigths(R_PIN2, G_PIN2, Y_PIN2, 0, 1, 0);
      controlTrafficLigths(R_PIN3, G_PIN3, Y_PIN3, 1, 0, 0);
      break;

    case 3:
      controlTrafficLigths(R_PIN1, G_PIN1, Y_PIN1, 1, 0, 0);
      controlTrafficLigths(R_PIN2, G_PIN2, Y_PIN2, 1, 0, 0);
      controlTrafficLigths(R_PIN3, G_PIN3, Y_PIN3, 0, 1, 0);
      break;

    case 4:
      controlTrafficLigths(R_PIN1, G_PIN1, Y_PIN1, 0, 0, 1);
      controlTrafficLigths(R_PIN2, G_PIN2, Y_PIN2, 1, 0, 0);
      controlTrafficLigths(R_PIN3, G_PIN3, Y_PIN3, 1, 0, 0);
      break;

    case 5:
      controlTrafficLigths(R_PIN1, G_PIN1, Y_PIN1, 1, 0, 0);
      controlTrafficLigths(R_PIN2, G_PIN2, Y_PIN2, 0, 0, 1);
      controlTrafficLigths(R_PIN3, G_PIN3, Y_PIN3, 1, 0, 0);
      break;

    case 6:
      controlTrafficLigths(R_PIN1, G_PIN1, Y_PIN1, 1, 0, 0);
      controlTrafficLigths(R_PIN2, G_PIN2, Y_PIN2, 1, 0, 0);
      controlTrafficLigths(R_PIN3, G_PIN3, Y_PIN3, 0, 0, 1);
      break;
  }
}

void checkTrafficLigths() {
  GreenFlag = 0; YellowFlag = 0;
  if (millis() - tlast > 15000) {
    GreenFlag = 1;
  }

  if (GreenFlag == 1 && St_new != St_last) { //зеленый отсветил и новое состояние не равно текущему

    if (firstTimeY == 0) {                              // определяем время начала желтого света
      tYlast = millis();
      firstTimeY = 1;
    }

    if (millis() - tYlast > 5000) {
      YellowFlag = 1;
    }
  }
}

void stateTransfer() {

if (St_last == 1 && St_new != 1 && GreenFlag== 1){
  St_last=4; 
}
if (St_last == 4 && YellowFlag== 1){
  if (St_new==2) {St_last=2; tlast= millis(); firstTimeY=0;}
  if (St_new==3) {St_last=3; tlast= millis(); firstTimeY=0;}
}
if (St_last == 2 && St_new != 2 && GreenFlag== 1){
  St_last=5; 
}
if (St_last == 5 && YellowFlag== 1){
  if (St_new==1) {St_last=1; tlast= millis(); firstTimeY=0;}
  if (St_new==3) {St_last=3; tlast= millis(); firstTimeY=0;}
}
if (St_last == 3 && St_new != 3 && GreenFlag== 1){
  St_last=6; 
}
if (St_last == 6 && YellowFlag== 1){
  if (St_new==1) {St_last=1; tlast= millis(); firstTimeY=0;}
  if (St_new==2) {St_last=2; tlast= millis(); firstTimeY=0;}
}

}
