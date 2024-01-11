import serial
import csv
from datetime import datetime

# 시리얼 포트 설정
ser = serial.Serial('COM13', 9600)  # COM포트 부분은 아두이노가 연결된 포트로 변경해야 합니다.

# CSV 파일 설정
filename = "sensor_data.csv"
with open(filename, 'a', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Timestamp", "Low1_Humidity", "Low1_Temperature", "Low2_Humidity", "Low2_Temperature", 
                     "Low3_Humidity", "Low3_Temperature", "Low4_Humidity", "Low4_Temperature", 
                     "High_Humidity", "High_Temperature"])  # 컬럼명 설정

    print("온,습도를 기록중입니다...")
    while True:
        if ser.in_waiting:
            data = ser.readline().decode('utf-8').rstrip()  # 데이터 읽기
            if data:  # 데이터가 존재하면
                data_list = data.split(" ")  # 공백으로 데이터 분리
                data_list.insert(0, datetime.now().strftime("%Y-%m-%d %H:%M:%S"))  # 현재 시간 추가
                writer.writerow(data_list)  # CSV 파일에 작성
                file.flush()
