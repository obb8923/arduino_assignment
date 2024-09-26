#define LED_PIN 7  // GPIO 7번 핀에 LED 연결

int period_us = 1000;  // 기본 period 1000us (1ms)
int duty_percent = 0;  // 기본 duty 0%

// period 설정 함수 (100 ~ 10000 us 범위)
void set_period(int period) {
  if (period >= 100 && period <= 10000) {
    period_us = period;
  }
}

// duty 설정 함수 (0 ~ 100%)
void set_duty(int duty) {
  if (duty >= 0 && duty <= 100) {
    duty_percent = duty;
  }
}

// LED 밝기 제어 함수 (PWM 방식, HIGH일 때 꺼지고 LOW일 때 켜짐)
void pwm_control() {
  int on_time = (period_us * duty_percent) / 100;  // 켜지는 시간
  int off_time = period_us - on_time;              // 꺼지는 시간

  // LED 켜기 (LOW)
  digitalWrite(LED_PIN, LOW);
  delayMicroseconds(on_time);

  // LED 끄기 (HIGH)
  digitalWrite(LED_PIN, HIGH);
  delayMicroseconds(off_time);
}

// 삼각형 패턴 밝기 제어 함수
void triangle_pattern() {
  // 밝기를 삼각형 패턴으로 변경 (0% ~ 100% ~ 0%)
  for (int duty = 0; duty <= 100; duty++) {
    set_duty(duty);  // duty 증가
    for (int i = 0; i < (1000 / period_us); i++) {  // 1초 동안 밝기 유지 (1000ms/period_us 반복)
      pwm_control();
    }
  }

  for (int duty = 100; duty >= 0; duty--) {
    set_duty(duty);  // duty 감소
    for (int i = 0; i < (1000 / period_us); i++) {  // 1초 동안 밝기 유지
      pwm_control();
    }
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);  // LED_PIN을 출력으로 설정
}

void loop() {
  // 주기 10ms 테스트
  set_period(10000);  // 10ms 설정
  triangle_pattern();  // 삼각형 패턴 실행

  // 주기 1ms 테스트
  set_period(1000);  // 1ms 설정
  triangle_pattern();  // 삼각형 패턴 실행

  // 주기 0.1ms 테스트
  set_period(100);  // 0.1ms 설정
  triangle_pattern();  // 삼각형 패턴 실행

}
