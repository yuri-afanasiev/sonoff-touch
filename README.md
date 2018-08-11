# Прошивка для Sonoff Touch

## Для примера настройки MQTT

- Имя устройства switch
- Группа  Комната 1
- Уровень устройства /home/room1/switch/sonoff-touch
- Уровень комнаты /home/room1/sonoff-touch
- Уровень дома /home/sonoff-touch


## Нажатие на сенсорную поверхность при подключенном mqtt
#### Включение  
``` Topic /home/room1/switch/sonoff-touch/relay/status```

```Message  {"status":"1","activated":"0"} ``` 
#### Выключение
``` Topic /home/room1/switch/sonoff-touch/relay/status```  

``` Message  {"status":"0","activated":"0"}```

## Включение реле через mqtt (Уровень устройства)
#### Включение
```Topic /home/room1/switch/sonoff-touch/relay```  

```Message  {"status":"1"}```
#### Ответ 
``` Topic /home/room1/switch/sonoff-touch/relay/status ``` 

```Message  {"status":"1","activated":"2"}```
#### Выключение
``` Topic /home/room1/switch/sonoff-touch/relay  ```  

```Message  {"status":"0"}```
#### Ответ 
```Topic /home/room1/switch/sonoff-touch/relay/status  ``` 

``` Message  {"status":"0","activated":"2"}```

## Включение реле через mqtt (Уровень комнаты)
- На команды реагируют все выключатели которые находятся в комнате
#### Включение
``` Topic /home/room1/sonoff-touch/relay    ```

``` Message  {"status":"1"}```
#### Ответ
``` Topic /home/room1/switch/sonoff-touch/relay/status  ```

``` Message  {"status":"1","activated":"2"}```
#### Выключение
``` Topic /home/room1/sonoff-touch/relay  ```    

``` Message  {"status":"0"}```
#### Ответ
```Topic /home/room1/switch/sonoff-touch/relay/status```

``` Message  {"status":"0","activated":"2"}```

## Включение реле через mqtt (Уровень дома)
- На команды реагируют все выключатели которые находятся в доме
#### Включение  
``` Topic /home/sonoff-touch/relay```

``` Message  {"status":"1"}```
#### Ответ 
```Topic /home/room1/switch/sonoff-touch/relay/status ``` 

``` Message  {"status":"1","activated":"2"}```
#### Выключение 
```Topic /home/sonoff-touch/relay ```       

```Message  {"status":"0"}```
#### Ответ 
``` Topic /home/room1/switch/sonoff-touch/relay/status  ```

``` Message  {"status":"0","activated":"2"}```


## Управление светодиодом по  mqtt (Уровень устройства)
- Состояние светодиода не сохраняется при перезагрузке
#### Включение
```Topic /home/room1/switch/sonoff-touch/led ```
```Message  {"status":"1"}```

#### Ответ
```Topic /home/room1/switch/sonoff-touch/led/status  ```
```Message  {"status":"1","activated":"2"}```

#### Выключение 
```Topic /home/room1/switch/sonoff-touch/led ```
```Message  {"status":"0"}```

#### Ответ
```Topic /home/room1/switch/sonoff-touch/led/status ``` 
```Message  {"status":"0","activated":"2"}```

## Управление светодиодом по  mqtt (Уровень комнаты)
- На команды реагируют все выключатели которые находятся в комнате
Включение
```Topic /home/room1/sonoff-touch/led ``` 
```Message  {"status":"1"}```

#### Ответ 
```Topic /home/room1/switch/sonoff-touch/led/status	```
```Message  {"status":"1","activated":"2"} ```

#### Выключение 
```Topic /home/room1/sonoff-touch/led   ```     
```Message  {"status":"0"}```
#### Ответ
```Topic /home/room1/switch/sonoff-touch/led/status```	
```Message  {"status":"0","activated":"2"} ```

## Управление светодиодом по  mqtt (Уровень дома)
- На команды реагируют все выключатели которые находятся в доме


#### Включение
``` Topic /home/sonoff-touch/led ```  
``` Message  {"status":"1"} ```

#### Ответ
``` Topic /home/room1/switch/sonoff-touch/led/status ```
``` Message  {"status":"1","activated":"2"} ```

#### Выключение
``` Topic /home/sonoff-touch/led ```         
```Message  {"status":"0"} ```

#### Ответ
``` Topic /home/room1/switch/sonoff-touch/led/status ```  
``` Message  {"status":"0","activated":"2"} ```


## Управление сенсорной поверхностью (Уровень устройства)
- Сенсор можно выключить и тогда он не будет реагировать на прикосновения
- Состояние сенсора не сохраняется при перезагрузке

#### Включение 
``` Topic /home/room1/switch/sonoff-touch/button ```
``` Message {"status":"1"} ```

#### Ответ
``` Topic /home/room1/switch/sonoff-touch/button/status ```   
``` Message {"status":"1","activated":"2"} ```

#### Выключение
``` Topic /home/room1/switch/sonoff-touch/button  ```    
``` Message {"status":"0"} ```

#### Ответ
``` Topic /home/room1/switch/sonoff-touch/button/status  ```
``` Message {"status":"0","activated":"2"} ```

## Управление сенсорной поверхностью (Уровень комнаты)
#### Включение 
``` Topic /home/room1/sonoff-touch/button ```   
``` Message {"status":"1"} ```

#### Ответ
``` Topic /home/room1/switch/sonoff-touch/button/status ```
``` Message {"status":"1","activated":"2"} ```

#### Выключение 
``` Topic /home/room1/sonoff-touch/button ```     
``` Message {"status":"0"} ```

#### Ответ 
``` Topic /home/room1/switch/sonoff-touch/button/status ```   
``` Message {"status":"0","activated":"2"} ```

## Управление сенсорной поверхностью (Уровень дома)
#### Включение 
```Topic /home/sonoff-touch/button ```   
``` Message {"status":"1"}```

#### Ответ 
``` Topic /home/room1/switch/sonoff-touch/button/status ``` 
``` Message {"status":"1","activated":"2"} ```

#### Выключение
``` Topic /home/sonoff-touch/button  ``` 
``` Message {"status":"0"} ```

#### Ответ 
``` Topic /home/room1/switch/sonoff-touch/button/status  ```
``` Message {"status":"0","activated":"2"} ```


## Основные параметры
``` Topic /home/room1/switch/sonoff-touch/status ```  
``` Message - ```
      
#### Ответ
``` Topic /home/room1/switch/sonoff-touch/status/status ```   
``` Message {"relay":"0","led":"0","button":"1"} ```

## Перезагрузка (Уровень устройства)
``` Topic /home/room1/switch/sonoff-touch/reset   ```                   
``` Message - ```

#### (Уровень комнаты)
```Topic /home/room1/sonoff-touch/reset```
``` Message - ```

#### (Уровень дома)
- Перезагрузятся устройства только sonoff-touch

```Topic /home/sonoff-touch/reset```    
```Message - ```

#### Ответ 
``` Topic /home/room1/switch/sonoff-touch/reset/status```
``` Message {"status":"1"}```

## Обновления
```Topic /home/room1/switch/sonoff-touch/update```  
```Message  {"code":"","fs":""}```  

#### Ответ
```Topic /home/room1/switch/sonoff-touch/update/status ``` 
```Message  {"status":"1"}```


## url api
#### Запрос 
```/esp_update```

Параметры 
- fs_bin 
- code_bin

#### Ответ
```{"status":"1"}```

#### Запрос 
 ``` /config ```

#### Ответ  ```{"ssid":"test","password":"test","apssid":"ESP8266","appassword":"12345678","www_username":"admin","www_password":"admin","connection_time":"30","time_reconnect":"600"}```


#### Запрос 
 ```/api19  ```
Параметры
- on_off  0-off 1-on
- server_mqtt
- port
- username_mqtе      
- password_mqtt
- name
- group

Например 
 ``` /api19?on_off=1&server_mqtt=&port=&username_mqtt=&password_mqtt=&name=switch&group=room1  ```

#### Ответ
 ```  {"status":"1"}  ```

#### Запрос
```/json19``` 

#### Ответ

```{"on_off":"1","server_mqtt":"","port":"","username_mqtt":"","password_mqtt":"","name":"switch","group":"room1","device_level":"/home/room1/switch/sonoff-touch","room_level":"/home/room1/sonoff-touch","house_level":"/home/sonoff-touch"} ```


#### Запрос /reset

Ответ 
  ```{"status":"1"} ```

#### Запрос
```/relay/on```

 Ответ
 ```{"status":"1","activated":"1"} ```

#### Запрос
 ```/relay/off ```
 
#### Ответ 
 ``` {"status":"0","activated":"1"} ```

#### Запрос 
```/led/on```

#### Ответ
 ```{"status":"1","activated":"1"} ```

#### Запрос
```/led/off```

#### Ответ
 ```{"status":"0","activated":"1"} ```

#### Запрос 
```/status```

#### Ответ
 ```{"relay":"1","led":"0","button":"1","version":"0.01"} ```

#### Запрос
/button/on

#### Ответ
 ```{"status":"1","activated":"1"} ```

#### Запрос 
```/button/off```

#### Ответ
 ``` {"status":"0","activated":"1"}  ```


