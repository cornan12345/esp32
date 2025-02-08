
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

const char* mqtt_server = "mqttgo.io";
const char* ssid = "xxxxxxxxx";//改成自己家裡的wifi名稱
const char* password = "yyyyyyyy";//改成自己家裡的wifi密碼
const char* mytopic="notrace0331";//改成自己的捲門代號。一定要至少12個字元以上。防止與別人重複。
#define DoorOpen 0 //開門指令，建議自行定義。
#define DoorClose 4//關門指令，建議自行定義。
#define STOP 15//暫停指令，建議自行定義。
#define BlueLED  2 // to test wifi connection 
void callback(char* topic, byte* message, unsigned int length) {
  pinMode(BlueLED, OUTPUT);
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if (String(topic) == mytopic) {
    Serial.print("Changing output to ");

    if(messageTemp == "on"){//flash once
      Serial.println("on");
      digitalWrite(DoorOpen, LOW);//garage door control
       delay(100);
       digitalWrite(DoorOpen, HIGH);//low active
      digitalWrite(BlueLED,HIGH);
    delay(1000);
    
    digitalWrite(BlueLED,LOW);
    }else if (messageTemp == "close"){//flash twice
      Serial.println("off"); 
      digitalWrite(DoorClose,LOW);
    delay(100);
    digitalWrite(DoorClose,HIGH);

    digitalWrite(2,HIGH);
    delay(100);
    digitalWrite(2,LOW);
    }else if(messageTemp == "stop"){
      Serial.println("off"); 
      digitalWrite(STOP,LOW);
    delay(100);
    digitalWrite(STOP,HIGH);

    digitalWrite(2,HIGH);
    delay(100);
    digitalWrite(2,LOW);
    }
  }
}
WiFiClient espClient;
PubSubClient client(mqtt_server,1883,callback,espClient);


//BluetoothSerial SerialBT; 
 // for motor  back and forth test
void setup() {
pinMode(BlueLED, OUTPUT);
pinMode(DoorOpen, OUTPUT);
pinMode(DoorClose, OUTPUT);
pinMode(STOP, OUTPUT);
Serial.begin(115200);
digitalWrite(DoorOpen, HIGH);//low active
digitalWrite(DoorClose, HIGH);
digitalWrite(STOP, HIGH);
 // WiFi.mode(WIFI_AP);
 // WiFi.softAP(ssid, password); 
 // server.begin();
  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   digitalWrite(BlueLED,HIGH);
    delay(100);
    digitalWrite(BlueLED,LOW);
    delay(600);
    digitalWrite(BlueLED,HIGH);
    delay(100);
    digitalWrite(BlueLED,LOW);

client.setServer(mqtt_server, 1883);
client.subscribe(mytopic);
  client.setCallback(callback);
     Serial.println("start...");
    

 


  
}

void loop() {
 if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("notrace","","")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe(mytopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
