const int analogSensorPin = 26; // ADC를 지원하는 핀으로 변경
const int ledPin = LED_BUILTIN; // 내장 LED 핀 번호
const int sampleRate = 1000; // 샘플링 레이트를 1000Hz로 변경
const int sampleTime = 1; // 샘플링 시간 (초)
const int totalSamples = sampleRate * sampleTime; // 총 샘플 수, 이제 100개의 샘플
int sensorValues[totalSamples]; // 소리 데이터 저장 배열을 전역 변수로 선언
unsigned long startTime; // 시작 시간을 전역 변수로 선언

void setup() {
  Serial.begin(9600); // 시리얼 통신 시작
  pinMode(ledPin, OUTPUT); // 내장 LED 핀을 출력으로 설정
}

void loop() {
  digitalWrite(ledPin, HIGH); // 내장 LED 점등
  startTime = millis(); // 시작 시간을 업데이트

  // 아날로그 센서 값 읽기
  for (int i = 0; i < totalSamples; i++) {
    sensorValues[i] = analogRead(analogSensorPin); // 센서값 읽기
    while (millis() < startTime + (i * 1000.0 / sampleRate)); // 다음 샘플 시간까지 대기, 이제 10ms 간격
  }

  digitalWrite(ledPin, LOW); // 내장 LED 소등

  // sensorValues 배열의 값들을 시리얼 모니터로 출력
  for (int i = 0; i < totalSamples; i++) {
    Serial.println(sensorValues[i]);
  }

  delay(2000); // 2초 딜레이
}