//ส่วนของการติดตั่งไลบลารี่
#include "DHT.h"
#include <WiFi.h>



//กำหนดค่าคงที่
const char* ssid = "MastreEWTC_2.4G";
const char* password = "12345abcde";


//กำหนดขาของ nodeMCU32s ให้รับค่าจาก DHT
#define DHTPIN 23 

// กำหนดชนิดของ DHT
#define DHTTYPE DHT11   // DHT 11



DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
//  For Chekc Internet
  Serial.println();
  Serial.println();
  Serial.print("Try to Connected to: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  
  while (WiFi.status() != WL_CONNECTED) {

      delay(500);
      Serial.print(".");
    
    }

    Serial.println();
    Serial.println("Can Connected WiFi");
    Serial.println("IP Address ==> ");
    Serial.println(WiFi.localIP());

//  For DHT
  Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
  // หน่วงเวลา ทุก 2 วินาที
  delay(2000);

//  กำหนดการอ่านเป็น องศาซี
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

//การแสดงผลบน Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
}
