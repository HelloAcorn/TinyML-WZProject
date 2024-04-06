import serial
import numpy as np
import librosa
import csv

# 아두이노에서 데이터 읽어오기
ser = serial.Serial('COM13', 9600)

sampleRate = 1028
sampleTime = 1
totalSamples = sampleRate * sampleTime

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
        data = data / 1023.0  # 정규화

        # 오디오 데이터 변환
        sr = sampleRate  # 샘플링 레이트
        audio = librosa.resample(data, orig_sr=sr, target_sr=sr)  # 리샘플링
        stft = librosa.stft(audio, n_fft=512, hop_length=256)  # STFT 적용
        spectrogram = librosa.amplitude_to_db(np.abs(stft), ref=np.max)  # 스펙트로그램 변환

        # 스펙트로그램 데이터를 CSV 파일로 저장
        with open('huu.csv', 'a', newline='') as csvfile:
            writer = csv.writer(csvfile)
            writer.writerows(spectrogram)

        # 스펙트로그램 시각화 또는 다른 처리
        # ...

    except KeyboardInterrupt:
        break

ser.close()