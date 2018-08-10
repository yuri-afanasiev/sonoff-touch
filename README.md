# Прошивка для Sonoff Touch
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
