#define LED_PIN 9   // GPIO 9번 핀에 LED 연결
#define ON_TIME 1000  // 1초 (1000ms)

void setup() {
  // LED_PIN을 출력으로 설정
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  //점점 밝아지는 LED
  // 1단계
  analogWrite(LED_PIN, 255);
  delay(ON_TIME);  // 1초 대기
  // 2단계
  analogWrite(LED_PIN, 191);
  delay(ON_TIME);  // 1초 대기
  // 3단계
  analogWrite(LED_PIN, 127);
  delay(ON_TIME);  // 1초 대기
  // 4단계
  analogWrite(LED_PIN, 64);
  delay(ON_TIME);  // 1초 대기
  // 5단계
  analogWrite(LED_PIN, 0);

  // 무한 루프
  while (1) {
  }
}
