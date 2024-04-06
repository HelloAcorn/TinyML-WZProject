import serial
import numpy as np
import librosa
import csv

# 아두이노에서 데이터 읽어오기
ser = serial.Serial('COM13', 9600)

sampleRate = 1028  # 샘플레이트
sampleTime = 1  # 샘플 시간
totalSamples = sampleRate * sampleTime  # 총 샘플 수

while True:
    try:
        data = []
        while len(data) < totalSamples:
            if ser.in_waiting:
                value = ser.readline().decode().strip()  # 시리얼 데이터 읽기
                if value:
                    data.append(float(value))  # 데이터 배열에 추가

        # 데이터 전처리
        data = np.array(data)
        data = data / 1023.0  # 정규화

        # FFT 적용
        fft_result = np.fft.fft(data)  # FFT 변환
        fft_magnitude = np.abs(fft_result)  # 진폭 스펙트럼 계산

        # 주파수 축 생성
        freqs = np.fft.fftfreq(len(fft_result)) * sampleRate

        # 스펙트럼 데이터를 CSV 파일로 저장
        with open('nothing.csv', 'a', newline='') as csvfile:
            writer = csv.writer(csvfile)
            # FFT 결과 저장 (진폭과 주파수)
            writer.writerows(zip(freqs, fft_magnitude))

        # 스펙트럼 시각화 또는 다른 처리
        # ...

    except KeyboardInterrupt:
        break

ser.close()
