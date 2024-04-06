#include <Arduino.h>
#line 1 "C:\\workspace\\PentaChord\\TinyML-WZPredict\\WakeWord\\WakeWord.ino"
#include <TensorFlowLite.h>

#define ARDUINO_EXCLUDE_CODE
#include "tensorflow/lite/micro/kernels/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#undef ARDUINO_EXCLUDE_CODE   

#include "voice_recognition_model.h"  // 변환된 모델 파일 포함

#include <fix_fft.h>

// 모델 관련 상수 정의
const int kTensorArenaSize = 8 * 1024;  // 텐서 아레나 크기 증가
const int kNumInputs = 1;
const int kNumOutputs = 1;
const int kInputFrames = 4;
const int kInputShape[4] = {1, 257, kInputFrames, 1};
const int kOutputSize = 3;
const int analogSensorPin = 26;
const int ledPin = LED_BUILTIN;
const int sampleRate = 1028;
const int sampleTime = 1;
const int totalSamples = sampleRate * sampleTime;
int16_t vReal[totalSamples];
int16_t vImag[totalSamples];
unsigned long startTime;


// 텐서 아레나 메모리 할당
uint8_t tensor_arena[kTensorArenaSize];

// 오디오 입력 버퍼
float audio_buffer[257 * kInputFrames];
int audio_buffer_index = 0;

// 모델 추론 함수
String inference(float* input_data) {
  // 에러 리포터 설정
  tflite::MicroErrorReporter micro_error_reporter;
  tflite::ErrorReporter* error_reporter = &micro_error_reporter;

  // 플랫버퍼 모델 포인터 설정
  const tflite::Model* model = ::tflite::GetModel(voice_recognition_model_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    return "Model schema mismatch";
  }

  // 모델 연산자 설정
  tflite::ops::micro::AllOpsResolver resolver;

  // 인터프리터 생성
  tflite::MicroInterpreter interpreter(model, resolver, tensor_arena, kTensorArenaSize, error_reporter);

  // 텐서 할당
  interpreter.AllocateTensors();

  // 입력 텐서 포인터 얻기
  TfLiteTensor* input = interpreter.input(0);

  // 입력 데이터 복사
  for (int i = 0; i < 257 * kInputFrames; i++) {
    input->data.f[i] = input_data[i];
  }

  // 추론 실행
  TfLiteStatus invoke_status = interpreter.Invoke();
  if (invoke_status != kTfLiteOk) {
    return "Invoke failed";
  }

  // 출력 텐서 포인터 얻기
  TfLiteTensor* output = interpreter.output(0);

  // 출력 결과 처리
  int predicted_class = 0;
  float max_probability = output->data.f[0];
  for (int i = 1; i < kOutputSize; i++) {
    if (output->data.f[i] > max_probability) {
      predicted_class = i;
      max_probability = output->data.f[i];
    }
  }

  // 결과 반환
  if (predicted_class == 0) {
    return "Nothing";
  } else if (predicted_class == 1) {
    return "WIZnet";
  } else if (predicted_class == 2) {
    return "You";
  }

  return "Unknown";
}

void fft_wrapper(int16_t* vReal, int16_t* vImag, int n, int inverse) {
  fix_fft((char*)vReal, (char*)vImag, n, inverse);
}


void setup() {
  // 시리얼 통신 초기화
  Serial.print("무야호");
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 오디오 입력 받기
  Serial.print("무야호2");
  if (audio_buffer_index < 257 * kInputFrames) {
    // digitalWrite(ledPin, HIGH);
    startTime = millis();
    for (int i = 0; i < totalSamples; i++) {
      vReal[i] = analogRead(analogSensorPin);
      vImag[i] = 0;  // 허수부는 0으로 초기화
      while (millis() < startTime + (i * 1000.0 / sampleRate));
    }
    // digitalWrite(ledPin, LOW);
    Serial.print("무야호3");
    // FFT 계산
    fft_wrapper(vReal, vImag, 10, 0);

    // FFT 결과를 audio_buffer에 저장
    for (int i = 0; i < totalSamples / 2; i++) {
      double magnitude = sqrt(vReal[i] * vReal[i] + vImag[i] * vImag[i]);
      audio_buffer[audio_buffer_index++] = magnitude;
    }
  }
  Serial.print("무야호4");
  // 오디오 버퍼가 가득 찼을 때 추론 수행
  if (audio_buffer_index >= 257 * kInputFrames) {
    // 추론 실행
    String result = inference(audio_buffer);

    // 결과 출력
    Serial.print("Recognized word: ");
    Serial.println(result);

    // 오디오 버퍼 초기화
    audio_buffer_index = 0;
  }

  delay(2500);  // 500밀리초 대기
}
