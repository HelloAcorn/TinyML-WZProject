import tensorflow as tf
import pandas as pd
import numpy as np

# 저장된 모델 불러오기
model = tf.keras.models.load_model('my_test_model.h5')

# 예측을 위한 새로운 데이터 로드 (이 예제에서는 예시를 위해 기존 데이터를 사용합니다)
# 실제 사용 시에는 새로운 데이터를 로드해야 합니다.
file_path = 'sensor_data.csv'  # 새로운 데이터 파일 경로
new_data = pd.read_csv(file_path)

# 새로운 데이터에서 입력 데이터 선택
new_sensor_data = np.array([[10, 28.9, 6, 28.8, 6, 28.3, 9, 29]])

# 모델을 사용하여 예측 수행
predictions = model.predict(new_sensor_data)

# 예측 결과 출력
print("예측 결과:")
print(predictions)
