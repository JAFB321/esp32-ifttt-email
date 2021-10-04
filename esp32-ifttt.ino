#include <HTTPClient.h>
#include <WiFi.h>

 // Wifi 
const char* ssid = "WIFI SSID";
const char* pass = "WIFI PASSWORD";

// IFTTT Webwook url
const String WebhookURL = "IFTTT WEBHOOK URL"; 


void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, pass);

  Serial.println("Connecting...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected");
  Serial.println(WiFi.localIP());
}

void loop() {
  const int pinTouch = touchRead(4);

  Serial.print("Value: ");
  Serial.println(pinTouch);

  if(pinTouch < 40 || pinTouch > 90){
    Serial.println("Touch detected: Sending email");

    if(SendEmail(pinTouch)){
      Serial.println("Email sent");
      Serial.println("Wait 10 seconds to detect pin touch again");
      delay(10000);
    }else{
      Serial.println("An error has been ocurred, try again");
    }
  }

  delay(500);
}

bool SendEmail(int value){
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;

    http.begin(WebhookURL);
    http.addHeader("Content-Type", "application/json");

    String _value = "";
    _value += value;

    const String json = "{\"value1\":\""+_value+"\"}"; 
    int httpResponseCode = http.POST(json);
    
    // Serial.println(json);
    // Serial.println(value);
    // Serial.println(_value);
    // Serial.println(httpResponseCode);

    if(httpResponseCode >= 200 && httpResponseCode < 300)
    return true;
    else return false;
  }
}
