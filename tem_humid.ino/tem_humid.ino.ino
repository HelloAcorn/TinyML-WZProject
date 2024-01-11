#include "DHT.h"

//0,1,7,15,16
#define low_dt1 0
#define low_dt2 1
#define low_dt3 7
#define low_dt4 15
#define high_dt 22


DHT low_Dht1(low_dt1, DHT11);
DHT low_Dht2(low_dt2, DHT11);
DHT low_Dht3(low_dt3, DHT11);
DHT low_Dht4(low_dt4, DHT11);
DHT high_Dht(high_dt, DHT22);

void setup() {
  Serial.begin(9600);
  low_Dht1.begin();
  low_Dht2.begin();
  low_Dht3.begin();
  low_Dht4.begin();
  high_Dht.begin();
}
 
void loop() {

    // 센서의 온도와 습도를 읽어온다.
  float low1_h = low_Dht1.readHumidity();
  float low1_t = low_Dht1.readTemperature();
  float low2_h = low_Dht2.readHumidity();
  float low2_t = low_Dht2.readTemperature();
  float low3_h = low_Dht3.readHumidity();
  float low3_t = low_Dht3.readTemperature();
  float low4_h = low_Dht4.readHumidity();
  float low4_t = low_Dht4.readTemperature();
  float high_h = high_Dht.readHumidity();
  float high_t = high_Dht.readTemperature();
  
  if (isnan(low1_h) || isnan(low1_t)|| isnan(low2_h) || isnan(low2_t)|| isnan(low3_h) 
  || isnan(low3_t)|| isnan(low4_h) || isnan(low4_t)|| isnan(high_h) || isnan(high_t) ) {
    //값 읽기 실패시 시리얼 모니터 출력
    Serial.println("Failed to read from DHT");
  } else {
    //온도, 습도 표시 시리얼 모니터 출력
    Serial.print(String(low1_h) + " "+String(low1_t) + " "+String(low2_h) + " "+String(low2_t) + " "+String(low3_h) + " "+String(low3_t) + 
    " "+String(low4_h) + " "+String(low4_t) + " "+String(high_h) + " "+String(high_t)+ "\n");
  }
  delay(10000);
 
}
 
