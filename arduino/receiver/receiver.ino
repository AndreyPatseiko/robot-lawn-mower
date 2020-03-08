/*  Добавляем необходимые библиотеки */
#include <RH_ASK.h>

#define SPEED         (uint16_t)1200
#define RX_PIN        (uint8_t)11
#define TX_PIN        (uint8_t)12
#define PTT_PIN       (uint8_t)10
#define PTT_INVERTED  false

/* Пины выходов для включения реле */
byte leftForwardPin   = 2;
byte leftReversePin   = 3;
byte rightForwardPin  = 4;
byte rightReversePin  = 5;
byte trimmerPin       = 6;

/* ТАймер для отключения при потере сигнала */
unsigned long resiveDataTimeStamp = 0;
int stopDealy = 1000;

/*  Создаём экземпляр класса RH_ASK приёмника */
RH_ASK driver(SPEED, RX_PIN, TX_PIN, PTT_PIN, PTT_INVERTED);

void setup() {
  /* задаем скорость общения с компьютером */
  Serial.begin(115200);
  /* Инициализируем передатчик */
  if (! driver.init()) {
    Serial.println(F("RF init failed!"));
    while (true) {
      delay(1);
    }
  }
  /* Настройка встроенного светодиода */
  pinMode(LED_BUILTIN, OUTPUT);

  /* Активация пинов для включения реле */
  pinMode(leftForwardPin, OUTPUT);
  pinMode(leftReversePin, OUTPUT);
  pinMode(rightForwardPin, OUTPUT);
  pinMode(rightReversePin, OUTPUT);
  pinMode(trimmerPin, OUTPUT);

  /* Таймер */
  robotStop();
  resiveDataTimeStamp = millis();
}

void loop() {
  /* Буфер полученных данных */
  uint8_t data[3];
  /* Размер полученных данных */
  uint8_t buflen = sizeof(data);
  /* Проверяем наличие новых данных */
  if (driver.recv(data, &buflen)) {
    resiveDataTimeStamp = millis();
    /* Гасим светодиод */
    digitalWrite(LED_BUILTIN, LOW);
    /* Активируем реле для левого колеса */
    relayActivation(data);
    /* Включаем светодиод */
    digitalWrite(LED_BUILTIN, HIGH);    
  }
  
  if (millis() > resiveDataTimeStamp + stopDealy) {    
    robotStop();
  }
}
