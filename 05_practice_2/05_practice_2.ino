#define LED_PIN 7   // GPIO 7번 핀에 LED 연결
#define ON_TIME 1000  // 1초 (1000ms)
#define BLINK_TIME 200 // 깜빡일 때의 주기 (200ms)

void setup() {
  // LED_PIN을 출력으로 설정
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // 1초 동안 LED 켜기
  digitalWrite(LED_PIN, LOW);
  delay(ON_TIME);  // 1초 대기

  // LED를 5회 깜빡이기
  for (int i = 0; i <5 ; i++) {
    digitalWrite(LED_PIN, HIGH);  // LED 끄기
    delay(BLINK_TIME / 2);       // 반 주기 대기 (100ms)
    digitalWrite(LED_PIN, LOW); // LED 켜기
    delay(BLINK_TIME / 2);       // 반 주기 대기 (100ms)
  }

  // LED 끄기
  digitalWrite(LED_PIN, HIGH);

  // 무한 루프
  while (1) {
  }
}
