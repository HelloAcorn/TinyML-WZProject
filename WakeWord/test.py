import serial
import numpy as np
import librosa
import librosa.display
import matplotlib.pyplot as plt

# 아두이노에서 데이터 읽어오기
ser = serial.Serial('COM13', 9600)  # 시리얼 포트와 보드레이트 설정
sampleRate = 1000  # 샘플링 레이트
sampleTime = 1  # 샘플링 시간 (초)
totalSamples = sampleRate * sampleTime  # 총 샘플 수

plt.figure(figsize=(12, 8))
while True:
    try:
        data = []
        while len(data) < totalSamples:
            if ser.in_waiting:
                value = ser.readline().decode().strip()
                if value:
                    data.append(float(value))

        # 데이터 전처리
        data = np.array(data)
        data = data / 1023.0  # 아두이노 ADC 값을 0~1 범위로 정규화

        # 오디오 데이터 변환
        sr = sampleRate  # 샘플링 레이트
        audio = librosa.resample(data, orig_sr=sr, target_sr=sr)  # 리샘플링
        stft = librosa.stft(audio, n_fft=256, hop_length=32)  # STFT 적용
        spectrogram = librosa.amplitude_to_db(np.abs(stft), ref=np.max)  # 스펙트로그램 변환

        # 스펙트로그램 시각화
        plt.clf()
        librosa.display.specshow(spectrogram, sr=sr, x_axis='time', y_axis='hz')
        plt.colorbar(format='%+2.0f dB')
        plt.title('Spectrogram')
        plt.draw()
        plt.pause(0.001)

    except KeyboardInterrupt:
        break

ser.close()  # 시리얼 포트 연결 해제
plt.close()