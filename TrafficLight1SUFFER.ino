/*
Данный вариант решения первой задачи допускает некое насилие при столкновении животных))0)0)))
@Petrov Ivan 2024
*/



int dTr1 = 0;
int dTr2 = 0;
int dTr3 = 0;
int dTr4 = 0;
int dTr5 = 0;  // глобальные переменные для однократного включения
//светодиодов во время работы светофора в каком либо режиме
unsigned long t_init = 0;

short int R_PIN1 = 8;
short int G_PIN1 = 9;
short int B_PIN1 = 10;

short int R_PIN2 = 11;
short int G_PIN2 = 12;
short int B_PIN2 = 13;



void setup() {
  pinMode(R_PIN1, OUTPUT);
  pinMode(G_PIN1, OUTPUT);
  pinMode(B_PIN1, OUTPUT);

  pinMode(R_PIN2, OUTPUT);
  pinMode(G_PIN2, OUTPUT);
  pinMode(B_PIN2, OUTPUT);
}

void loop() {
  t_init = checkState(t_init);  // функция в которой реализована логика работы программы
  //на вход принимает "начальное время" - на деле является временем начала цикла работы обоих
  //светофоров
}

void ligthsInput(short int R_PIN, short int G_PIN, short int B_PIN, short int valR, short int valG, short int valB) {

  digitalWrite(R_PIN, valR);  // Red pin signal
  digitalWrite(G_PIN, valG);  // Green pin signal
  digitalWrite(B_PIN, valB);  // Blue pin signal , можно отказаться, т.к. не используется
}

unsigned long checkState(unsigned long t_init) {
  if (millis() - t_init < 5000)  //условие достижения первых 5 секунд работы цикла
  {
    if (dTr1 == 0) {                                 //подобные этому флаги используются для одноразового включения-выключения
                                                     //светодиодов за время работы цикла
      ligthsInput(R_PIN1, G_PIN1, B_PIN1, 0, 1, 0);  // 1- G, 2 - Y
      ligthsInput(R_PIN2, G_PIN2, B_PIN2, 1, 1, 0);
      dTr1 = 1;
    }
  }

  if (millis() - t_init < 15000 && millis() - t_init > 5000)  //условие первого переключения второго светофора
  {
    if (dTr2 == 0) {
      ligthsInput(R_PIN2, G_PIN2, B_PIN2, 0, 0, 0);  // второй светофор выключается
                                                     // 1- G, 2 - R
      ligthsInput(R_PIN2, G_PIN2, B_PIN2, 1, 0, 0);  // второй светофор включает красный свет
      dTr2 = 1;
    }
  }

  if (millis() - t_init < 20000 && millis() - t_init > 15000) {
    if (dTr3 == 0) {
      ligthsInput(R_PIN1, G_PIN1, B_PIN1, 0, 0, 0);  //выключаются оба светофора
      

      ligthsInput(R_PIN1, G_PIN1, B_PIN1, 1, 1, 0);  // На светофорах включается 1 -Y, 2- R      
      dTr3 = 1;
    }
  }
  if (millis() - t_init < 35000 && millis() - t_init > 20000) {
    if (dTr4 == 0) {
      ligthsInput(R_PIN1, G_PIN1, B_PIN1, 0, 0, 0);  //turning off

      ligthsInput(R_PIN1, G_PIN1, B_PIN1, 1, 0, 0);  // 1-R 2- G
      ligthsInput(R_PIN2, G_PIN2, B_PIN2, 0, 1, 0);
      dTr4 = 1;
    }
  }


  if (millis() - t_init == 35000)  //условие окончания работы цикла
  {
    ligthsInput(R_PIN1, G_PIN1, B_PIN1, 0, 0, 0);  //turning off
    ligthsInput(R_PIN2, G_PIN2, B_PIN2, 0, 0, 0);

    t_init = millis();
    dTr1 = 0;
    dTr2 = 0;
    dTr3 = 0;
    dTr4 = 0;
  }
  return t_init;
}
