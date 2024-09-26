// Arduino 핀 할당
#define PIN_LED  9
#define PIN_TRIG 12   // 초음파 센서 TRIGGER
#define PIN_ECHO 13   // 초음파 센서 ECHO

// 설정 가능한 파라미터
#define SND_VEL 346.0     // 24도에서의 음속 (단위: m/sec)
#define INTERVAL 25      // 샘플링 간격 (단위: msec)
#define PULSE_DURATION 10 // 초음파 펄스 지속 시간 (단위: usec)
#define _DIST_MIN 100.0   // 측정할 최소 거리 (단위: mm)
#define _DIST_MAX 300.0   // 측정할 최대 거리 (단위: mm)

#define TIMEOUT ((INTERVAL / 2) * 1000.0) // 최대 에코 대기 시간 (단위: usec)
#define SCALE (0.001 * 0.5 * SND_VEL) // 지속 시간을 거리로 변환하는 계수

unsigned long last_sampling_time;   // 단위: msec

void setup() {
  // GPIO 핀 초기화
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  // 초음파 센서 TRIGGER
  pinMode(PIN_ECHO, INPUT);   // 초음파 센서 ECHO
  digitalWrite(PIN_TRIG, LOW);  // 초음파 센서 꺼짐
  
  // 시리얼 포트 초기화
  Serial.begin(57600);
}

void loop() { 
  float distance;

  // 다음 샘플링 시간까지 대기 (폴링)
  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO); // 거리 측정

  if ((distance == 0.0) || (distance > _DIST_MAX)) {
    distance = _DIST_MAX + 10.0;    // 더 높은 값으로 설정
    analogWrite(PIN_LED, 255);      // LED 꺼짐 (최소 밝기)
  } else if (distance < _DIST_MIN) {
    distance = _DIST_MIN - 10.0;    // 더 낮은 값으로 설정
    analogWrite(PIN_LED, 255);      // LED 꺼짐 (최소 밝기)
  } else {
    // LED 밝기 제어
    int brightness = calculateBrightness(distance);
    analogWrite(PIN_LED, brightness);
  }

  // 시리얼 포트에 거리 출력
  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(",distance:");  Serial.print(distance);
  Serial.print(",Max:");       Serial.print(_DIST_MAX);
  Serial.println("");
  
  // 마지막 샘플링 시간 업데이트
  last_sampling_time += INTERVAL;
}

// 초음파 센서로부터 거리 측정. 반환 값은 밀리미터 단위.
float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // 단위: mm
}

// 장애물 거리에 따라 LED 밝기 계산 (active low, 0이 최대 밝기, 255가 최소 밝기)
int calculateBrightness(float distance) {
  if (distance <= 100.0 || distance >= 300.0) {
    return 255;  // 최대 거리에서 최소 밝기
  } else if (distance == 150.0 || distance == 250.0) {
    return 128;  // 중간 거리에서 50% 밝기
  } else if (distance > 100.0 && distance < 200.0) {
    // 100mm ~ 200mm 사이 거리에서 점점 밝게
    return map(distance, 100, 200, 255, 0);
  } else if (distance > 200.0 && distance < 300.0) {
    // 200mm ~ 300mm 사이 거리에서 점점 어둡게
    return map(distance, 200, 300, 0, 255);
  }
  return 255; // 기본적으로 최소 밝기
}
