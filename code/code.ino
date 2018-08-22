 

#include <ESP8266WiFi.h>            //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi
#include <WiFiClient.h>
#include <ESP8266WebServer.h>       //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
#include <ESP8266mDNS.h>            //https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS
#include <FS.h>                     //http://esp8266.github.io/Arduino/versions/2.1.0/doc/filesystem.html  
#include <ArduinoJson.h>            //https://bblanchon.github.io/ArduinoJson/
#include <PubSubClient.h>           //https://github.com/Imroy/pubsubclient
#include <ESP8266httpUpdate.h>      //https://github.com/Links2004/Arduino/tree/esp8266/hardware/esp8266com/esp8266/libraries/ESP8266httpUpdate        
#include <ESP8266HTTPClient.h>      //https://github.com/Links2004/Arduino/tree/libraries/ESP8266HTTPClient 
#include <ESP8266HTTPUpdateServer.h>//https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPUpdateServer 
#include <Wire.h>                   //https://github.com/esp8266/Arduino/tree/master/libraries/Wire 
#include <Ticker.h>                 //https://github.com/esp8266/Arduino/tree/master/libraries/Ticker 
#include <SPI.h>                    //http://www.arduino.cc/en/Reference/SPI

String w1,w2,w3,w4,w5,w6; //настройки wifi
int w7,w8;//настройки wifi

int var=1;//wifi 
int wifire;
int reconnect;
 
bool button_off;
bool task_mqtt_button;

#define pin_button 0  
#define pin_green_led 13      
#define pin_relay 12 

int relay_status;
bool led_status;
bool button_status=1;


volatile long lastEventTime = 0;
volatile bool lastState = HIGH;
  
#define DEBOUNCE_DELAY 3    
volatile bool isOn = false;
volatile bool isled = false; 
 

int mqw1,mqw3;//htm19
String mqw2,mqw4,mqw5,mqw6,mqw7;//htm19
String top1,top2,top3,top4; //адресное пространство MQTT 
int mqtt_data_status;
String mqtt_code_bin,mqtt_fs_bin;

float rev_code=0.01;//текущая версия кода
WiFiClient mqtttestclient; 
PubSubClient mqttclient(mqtttestclient);
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer server(80); 
WiFiClient client;
File fsUploadFile;


int re1;
  
void callback(const MQTT::Publish& pub){
     String payload = pub.payload_string();
//relay     
     if(String(pub.topic()) == top3 + "sonoff-touch/relay"){ //уровень устройства
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     if (re1 == 1){ 
                        relay_status=1;
                        save27();
                        }
                     digitalWrite(pin_relay, HIGH);  
                     mqttclient.publish(top3 + "sonoff-touch/relay/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       mqttclient.publish(top3 + "sonoff-touch/relay/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt);
                       digitalWrite(pin_relay, LOW);
                       if (re1 == 1){ 
                           relay_status=0;
                           save27();
                           }
                    }    
                } 
      if(String(pub.topic()) == top2 + "sonoff-touch/relay"){ //уровень комнаты
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                    if (re1 == 1){ 
                        relay_status=1;
                        save27();
                        }
                       digitalWrite(pin_relay, HIGH);  
                       mqttclient.publish(top3 + "sonoff-touch/relay/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                      } else {
                        mqttclient.publish(top3 + "sonoff-touch/relay/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                        digitalWrite(pin_relay, LOW);
                          if (re1 == 1){ 
                             relay_status=0;
                             save27();
                            }
                      }    
                   
                }
     if(String(pub.topic()) == top1 + "sonoff-touch/relay"){ //уровень дома
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){
                    if (re1 == 1){ 
                        relay_status=1;
                        save27();
                        } 
                       digitalWrite(pin_relay, HIGH);  
                        mqttclient.publish(top3 + "sonoff-touch/relay/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                      } else {
                        mqttclient.publish(top3 + "sonoff-touch/relay/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                        digitalWrite(pin_relay, LOW);
                          if (re1 == 1){ 
                              relay_status=0;
                              save27();
                             }
                    }    
                      
                }     
//led
              if(String(pub.topic()) == top3 + "sonoff-touch/led"){ //уровень устройства
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     digitalWrite(pin_green_led, LOW); 
                     led_status=1;
                     mqttclient.publish(top3 + "sonoff-touch/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       led_status=0;
                       mqttclient.publish(top3 + "sonoff-touch/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       digitalWrite(pin_green_led, HIGH); 
                    }    
                }
              if(String(pub.topic()) == top2 + "sonoff-touch/led"){ //уровень комнаты 
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     digitalWrite(pin_green_led, LOW); 
                     led_status=1;
                     mqttclient.publish(top3 + "sonoff-touch/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       led_status=0;
                       mqttclient.publish(top3 + "sonoff-touch/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       digitalWrite(pin_green_led, HIGH); 
                    }    
                }

             if(String(pub.topic()) == top1 + "sonoff-touch/led"){ //уровень дома
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     digitalWrite(pin_green_led, LOW); 
                     led_status=1;
                     mqttclient.publish(top3 + "sonoff-touch/led/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       led_status=0;
                       mqttclient.publish(top3 + "sonoff-touch/led/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       digitalWrite(pin_green_led, HIGH); 
                    }    
                }

//button
             if(String(pub.topic()) == top3 + "sonoff-touch/button"){ //уровень устройства
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     button_off=0; 
                     button_status=1;
                     mqttclient.publish(top3 + "sonoff-touch/button/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       mqttclient.publish(top3 + "sonoff-touch/button/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       button_off=1; 
                       button_status=0;
                    }    
                }

             if(String(pub.topic()) == top2 + "sonoff-touch/button"){ //уровень комнаты 
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     button_off=0; 
                     button_status=1;
                     mqttclient.publish(top3 + "sonoff-touch/button/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       mqttclient.publish(top3 + "sonoff-touch/button/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       button_off=1; 
                       button_status=0;
                    }    
                }

           if(String(pub.topic()) == top1 + "sonoff-touch/button"){ //уровень дома 
                 DynamicJsonBuffer  jsonBuffer;
                 JsonObject& json = jsonBuffer.parseObject(payload);
                 mqtt_data_status = json["status"];// 
                 if (mqtt_data_status == 1){ 
                     button_off=0; 
                     button_status=1;
                     mqttclient.publish(top3 + "sonoff-touch/button/status","{\"status\":\"1\",\"activated\":\"2\"}");//status 1-on activated 2-mqtt
                     } else {
                       mqttclient.publish(top3 + "sonoff-touch/button/status","{\"status\":\"0\",\"activated\":\"2\"}");//status 0-off activated 2-mqtt
                       button_off=1; 
                       button_status=0;
                    }    
                }
//status
                if(String(pub.topic()) == top3 + "sonoff-touch/status"){  
                   String url;   
                          url += "{\"relay\":\""; 
                          url+=relay_status;
                          url += "\",\"led\":\"";
                          url+=led_status;
                          url += "\",\"button\":\"";
                          url+=button_status;
                          url +=  "\"}"; 
                   mqttclient.publish(top3 + "sonoff-touch/status/status",url); 
                 }    

//reset
                  if(String(pub.topic()) == top3 + "sonoff-touch/reset"){ // 
                     mqttclient.publish(top3 + "sonoff-touch/reset/status","{\"status\":\"1\"}"); 
                     ESP.restart(); 
                    }    
                  if(String(pub.topic()) == top2 + "sonoff-touch/reset"){ // 
                     mqttclient.publish(top3 + "sonoff-touch/reset/status","{\"status\":\"1\"}"); 
                     ESP.restart(); 
                    } 
                  if(String(pub.topic()) == top1 + "sonoff-touch/reset"){ // 
                     mqttclient.publish(top3 + "sonoff-touch/reset/status","{\"status\":\"1\"}"); 
                     ESP.restart(); 
                    }       

//update
                if(String(pub.topic()) == top3 + "sonoff-touch/update"){ //уровень устройства
                   DynamicJsonBuffer  jsonBuffer;
                   JsonObject& json = jsonBuffer.parseObject(payload);
                   String code_bin = json["code"];//code
                   String fs_bin = json["fs"];// fs 
                   mqtt_code_bin = code_bin;
                   mqtt_fs_bin = fs_bin;
                   mqttclient.publish(top3 + "sonoff-touch/update/status","{\"status\":\"1\"}"); 
                   esp_update(mqtt_fs_bin,mqtt_code_bin);
                }
//save_state
                if(String(pub.topic()) == top3 + "sonoff-touch/save_state"){ //уровень устройства
                   DynamicJsonBuffer  jsonBuffer;
                   JsonObject& json = jsonBuffer.parseObject(payload);
                   re1 = json["save_state"];// 
                   save20();//  запись в память модуля
                   mqttclient.publish(top3 + "sonoff-touch/save_state/status","{\"status\":\"1\"}"); 
                   
                }
                
                  
}

void setup(void){
     //Serial.begin(9600);
     SPIFFS.begin();
     pinMode(pin_button, INPUT); // 0 
     pinMode(pin_green_led, OUTPUT);
     pinMode(pin_relay, OUTPUT);
     attachInterrupt(pin_button,button_testing,CHANGE);
     openfile();//файл настроек 
     openfilehtm19();// файл настроек  htm19 MQTT
     openfilehtm20();// файл настроек  htm20 файл настроек
     openfilehtm27();// relay status

      
       
      top3 += "/home/"+mqw7+ "/"+mqw6+"/";//уровень устройства
      top2 += "/home/"+mqw7+"/";//уровень комнаты     
      top1 += "/home/";//уровень дома

      condition();//Запоминать % состояние  
      //Serial.println(top3);//уровень устройства
      //Serial.println(top2);//уровень комнаты
      //Serial.println(top1);//уровень дома
     wifi();//подключение к wifi 
     //Serial.println(WiFi.localIP());
     serveron();//запуск сервера порт 80  

}
void loop(void){   
     server.handleClient(); 
     wifitest(); 
     if (mqw1 == 1){//
         if (mqttclient.connected()){
             mqttclient.loop();
             }else {
              mqtt_connect();
             }
         if (task_mqtt_button == 1){//
         if (relay_status == HIGH){
             mqttclient.publish(top3 + "sonoff-touch/relay/status","{\"status\":\"1\",\"activated\":\"0\"}");//status 1-on activated 0-кнопка );
             task_mqtt_button=0;
            }
         if (relay_status == LOW){
             mqttclient.publish(top3 + "sonoff-touch/relay/status","{\"status\":\"0\",\"activated\":\"0\"}");//status 0-off activated 0-кнопка );
             task_mqtt_button=0;
            }
           }
      }
}


