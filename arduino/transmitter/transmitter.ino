/* Добавляем необходимые библиотеки */
#include <RH_ASK.h>

#define SPEED         (uint16_t)1200
#define RX_PIN        (uint8_t)11
#define TX_PIN        (uint8_t)12
#define PTT_PIN       (uint8_t)10
#define PTT_INVERTED  false

/* Пины для считывания сопротивлений и кнопок */
#define LEFT_R_PIN      (byte)3
#define RIGHT_R_PIN     (byte)4
#define TRIMMER_BTN_PIN (byte)6

/* Управление колесами и триммером */
byte FORWARD_MOTR  = 20;
byte STOP_MOTOR    = 10;
byte REVERSE_MOTOR = 0;
byte TRIMMER_ON    = 1;
byte TRIMMER_OFF   = 0;

/* Упровление индикацией */
#define LED_PIN       4
int startProgramTimer = 0;
int checkInterval = 3000;

/* Создаём экземпляр класса RH_ASK передатчика */
RH_ASK driver(SPEED, RX_PIN, TX_PIN, PTT_PIN, PTT_INVERTED);

/* Буфер данных для отправки
  0 - левое колесо  [10 - стоп, 0 - назад, 20 - вперед]
  1 - правое колесо
  3 - триммер
*/
uint8_t emitData[3] = {STOP_MOTOR, STOP_MOTOR, TRIMMER_OFF};

void setup() {
  /* задаем скорость общения с компьютером */
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  /* Инициализируем передатчик */
  if (!driver.init()) {
    Serial.println(F("RF init failed!"));
    while (true) {
      delay(1);
    }
  }
  /* Настройка встроенного светодиода */
  pinMode(LED_BUILTIN, OUTPUT);

  startProgramTimer = millis();
  /* Настройка кнопки переключения триммера */
  pinMode(TRIMMER_BTN_PIN, INPUT_PULLUP);
  digitalWrite(TRIMMER_BTN_PIN, HIGH);
}

void loop() {
  /* Отображаем одикатор работы */
  workIndication();

  /* Считываем сопротивления и именяем отпровляемые данные */
  setWheelActivity(LEFT_R_PIN, 0);
  setWheelActivity(RIGHT_R_PIN, 1);
  trimmer(TRIMMER_BTN_PIN);

  /* Гасим светодиод */
  digitalWrite(LED_BUILTIN, LOW);
  /* Передаём данные */
  driver.send(emitData, sizeof(emitData));
  /* Ждем пока передача будет окончена */
  driver.waitPacketSent();
  /* Выводим в терминал отправленные данные*/
  Serial.print("leftWheel : ");
  Serial.print(emitData[0]);
  Serial.print("; rightWheel : ");
  Serial.print(emitData[1]);
  Serial.print("; trimmer : ");
  Serial.println(emitData[2]);
  /* Включаем светодиод */
  digitalWrite(LED_BUILTIN, HIGH);
  /* Ждём */
  delay(500);
}
