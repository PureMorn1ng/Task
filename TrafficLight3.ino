/*
Задание 3.
@Petrov Ivan 2024
*/



short int Button3 = 5;  // пины кнопок для 1,2 и 3 светофора
short int Button2 = 6;
short int Button1 = 7;

short int R_PIN1 = 8;  //пины для красного и зеленого светодиода
short int G_PIN1 = 9;  //1,2 и 3 светофора
short int R_PIN2 = 10;
short int G_PIN2 = 11;
short int R_PIN3 = 12;
short int G_PIN3 = 13;

short int gate1 = 2;  //пины для заслонок 1,2 и 3 загона
short int gate2 = 3;
short int gate3 = 4;

short int St_last = 1;            //предыдущее состояние системы от 1 до 3
short int St_new = 1;             //новое состояние системы от 1 до 3
long unsigned int timeStnew = 0;  //время получения нового состояния с кнопки
long unsigned int tlast = 0;      //время начала текущего состояния
long unsigned int tYlast = 0;     //время наступления желтого режима светофора в текущем состоянии

long unsigned int firstTimeY = 0;  //счетчик одноразового включения желтого света

void setup() {
  pinMode(R_PIN1, OUTPUT);
  pinMode(G_PIN1, OUTPUT);


  pinMode(R_PIN2, OUTPUT);
  pinMode(G_PIN2, OUTPUT);

  pinMode(gate1, OUTPUT);
  pinMode(gate2, OUTPUT);

  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  pinMode(Button3, INPUT);

  //pinMode(13, OUTPUT);

  digitalWrite(gate1, 0);  // сначала работы программы все заслонки
  digitalWrite(gate2, 0);  // в закрытом положении
  digitalWrite(gate3, 0);
  ligthsInput(R_PIN1, G_PIN1, 1, 0);
  ligthsInput(R_PIN2, G_PIN2, 1, 0);
  ligthsInput(R_PIN3, G_PIN3, 1, 0);
}

void loop() {

  statusState();
  buttonCheck();
}
void ligthsInput(short int R_PIN, short int G_PIN, short int valR, short int valG) {

  digitalWrite(R_PIN, valR);  // Red pin signal
  digitalWrite(G_PIN, valG);  // Green pin signal
}
void buttonCheck() {
  short int But1 = digitalRead(Button1);
  if (But1 == HIGH && St_new != 1) {  //проверка повторного нажатия кнопки из загона
    St_new = 1;                       //получение нового состояния
  }
  short int But2 = digitalRead(Button2);
  if (But2 == HIGH && St_new != 2) {
    St_new = 2;
  }
  short int But3 = digitalRead(Button3);
  if (But3 == HIGH && St_new != 3) {
    St_new = 3;
  }
}

void statusState() {

  if (millis() - tlast < 15000) {  //проверка, горит ли зеленый 15 секунд
    switch (St_last) {             //переход по текущему состоянию
      case 1:
        ligthsInput(R_PIN1, G_PIN1, 0, 1);  //включение зеленого света
        digitalWrite(gate1, 1); //открытие заслонки
        break;
      case 2:
        ligthsInput(R_PIN2, G_PIN2, 0, 1);
        digitalWrite(gate2, 1);
        break;
      case 3:
        ligthsInput(R_PIN3, G_PIN3, 0, 1);
        digitalWrite(gate3, 1);
        break;
    }
  }
  if (millis() - tlast > 15000 && St_new != St_last) {  //проверка условия горит ли зеленый больше 15 сек
                                                        // и изменилось ли состояние
    if (firstTimeY == 0) {                              // определяем время начала желтого света
      tYlast = millis();
      firstTimeY = 1;
    }
    if (millis() - tYlast < 5000) {  //загорание желтого цвета при условии,
                                     //что он еще не отгорел свои 5 секунд
      switch (St_last) {             //включение желтого света по текущему состоянию
        case 1:
          ligthsInput(R_PIN1, G_PIN1, 1, 1);
          break;
        case 2:
          ligthsInput(R_PIN2, G_PIN2, 1, 1);
          break;
        case 3:
          ligthsInput(R_PIN3, G_PIN3, 1, 1);
          break;
      }
    } else {
      switch (St_last) {  //если желтый свет отгорел, то все 3 светофора становятся красными
                          // но только при условии, что новое состояние отличается от текущего
        case 1:
          ligthsInput(R_PIN1, G_PIN1, 1, 0);
          digitalWrite(gate1, 0); //закрытие заслонки
          break;
        case 2:
          ligthsInput(R_PIN2, G_PIN2, 1, 0);
          digitalWrite(gate2, 0); //закрытие заслонки
          break;
        case 3:
          ligthsInput(R_PIN3, G_PIN3, 1, 0);
          digitalWrite(gate3, 0); //закрытие заслонки
          break;
      }
      firstTimeY = 0;    // обнуление переменной горения желтого
      St_last = St_new;  // переход к новому состоянию
      tlast = millis();  // обновление времени последнего состояния
    }
  }
}
