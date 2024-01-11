import pandas as pd
import tensorflow as tf
from sklearn.model_selection import train_test_split
import numpy as np

# 데이터 파일 경로
file_path = 'sensor_data_test.csv'

# 데이터 로드
sensor_data = pd.read_csv(file_path)

# 입력 및 타겟 데이터 선택
X = sensor_data[['Low1_Humidity', 'Low1_Temperature', 'Low2_Humidity', 'Low2_Temperature', 'Low3_Humidity', 'Low3_Temperature', 'Low4_Humidity', 'Low4_Temperature']]
y = sensor_data[['High_Humidity', 'High_Temperature']]

# 데이터 분할
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 모델 생성
model = tf.keras.Sequential([
    tf.keras.layers.Dense(64, activation='relu' ,input_shape=(X_train.shape[1],)),
    tf.keras.layers.Dense(64, activation='relu' ),
    tf.keras.layers.Dense(2)  # High_Humidity와 High_Temperature에 대한 출력
])

# 모델 컴파일
model.compile(optimizer='adam', loss='mean_squared_error', metrics=['mean_squared_error'])

# 모델 훈련
model.fit(X_train, y_train, epochs=100, batch_size=32)

# 모델 평가
loss, mse = model.evaluate(X_test, y_test)
rmse = np.sqrt(mse)
print(f"Test MSE: {mse}, Test RMSE: {rmse}")
