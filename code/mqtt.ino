void mqtt_connect(){// подключение к MQTT серверу
     mqttclient.set_server(mqw2,mqw3);      
     if (mqttclient.connect(MQTT::Connect(mqw6).set_auth(mqw4.c_str(), mqw5.c_str()))) {
         mqttclient.set_callback(callback);
         //Serial.println("Connected to MQTT server ");
         // подписываемся под топики
         //mqttclient.subscribe("/home/#");
          mqttclient.subscribe(top3 + "sonoff-touch/relay");
          mqttclient.subscribe(top2 + "sonoff-touch/relay");
          mqttclient.subscribe(top1 + "sonoff-touch/relay");

          mqttclient.subscribe(top3 + "sonoff-touch/led");
          mqttclient.subscribe(top2 + "sonoff-touch/led");
          mqttclient.subscribe(top1 + "sonoff-touch/led");

          mqttclient.subscribe(top3 + "sonoff-touch/button");
          mqttclient.subscribe(top2 + "sonoff-touch/button");
          mqttclient.subscribe(top1 + "sonoff-touch/button");

          mqttclient.subscribe(top3 + "sonoff-touch/status");

          mqttclient.subscribe(top3 + "sonoff-touch/reset");
          mqttclient.subscribe(top2 + "sonoff-touch/reset");
          mqttclient.subscribe(top1 + "sonoff-touch/reset");
          
          mqttclient.subscribe(top3 + "sonoff-touch/update");
          
          mqttclient.subscribe(top3 + "sonoff-touch/save_state");
          
        } 
}
 
