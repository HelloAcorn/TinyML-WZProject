import serial
import csv
import os
from datetime import datetime

# 시리얼 포트 설정
ser = serial.Serial('COM13', 9600)

# CSV 파일 설정
filename = "sensor_data.csv"
file_exists = os.path.isfile(filename)  # 파일이 이미 존재하는지 확인
row_count = 0
with open(filename, 'r') as file:
    reader = csv.reader(file)
    row_count = sum(1 for row in reader)  # 모든 행을 순회하며 세기

with open(filename, 'a', newline='') as file:  # 'a' 모드로 파일 열기
    writer = csv.writer(file)
    if not file_exists:
        writer.writerow(["Timestamp", "Low1_Humidity", "Low1_Temperature", "Low2_Humidity", "Low2_Temperature", 
                         "Low3_Humidity", "Low3_Temperature", "Low4_Humidity", "Low4_Temperature", 
                         "High_Humidity", "High_Temperature"])  # 파일이 새로 생성되면 컬럼명 추가

    print("온,습도가 기록중입니다...")
    while True:
        if ser.in_waiting:
            data = ser.readline().decode('utf-8').rstrip()
            if data and "Failed to read from DHT" not in data:
                row_count += 1
                data_list = data.split(" ")
                data_list.insert(0, datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
                print(f"DataCount: {row_count} | DataStamp: {data_list}", end='\r')
                writer.writerow(data_list)
                file.flush()
