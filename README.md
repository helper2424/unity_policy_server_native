# Policy server

What is it
How it use

## Installing

### 1. Dependencies
To install project you need utilities git, cmake, make, gcc and some libraries tbb, libev, boost.

#### debian

`sudo aptitude install git cmake make gcc g++`
`sudo aptitude install libtbb-dev libev-dev libboost-program-options-dev`


### 2. Clone project

Copy project to some directory

`cd ~`  
`git clone https://github.com/helper2424/unity_policy_server_native.git`  

### 4. Build project 

`cd unity_policy_server_native`
`mkdir -p build`
`cd build`
`cmake ../`

### 3. Логирование

По-умолчанию логи пишутся в файл `/var/log/unity_policy_server/policy.log` , поэтому необходимо создать каталог `/var/log/unity_policy_server` :

`mkdir -p /var/log/unity_policy_server` 

### 4. Проверка работоспособности

Cервер использует порт 843, для того, чтобы его занять необходимы привилегии суперпользователя. Для проверки работоспособности сервера необходимо выполнить следующие команды:

`cd unity_policy_server/target`  
`sudo java -jar unity_policy_server-1.0-SNAPSHOT-jar-with-dependencies.jar`

После чего демон должен запуститься, для проверки того что сервер работает в другой консоли надо выполнить команду

`nc 127.0.0.1 843`

Если сервер работает корректно, то результатом работы последенй команды будет следующее:

`<?xml version="1.0"?>
<cross-domain-policy>
  <allow-access-from domain="*" to-ports="*"/>
</cross-domain-policy>`

### 5. Init скрипты

В каталоге init.d лежат примеры скриптов для автоматического запуска сервера. Вам необходимо прописать пути до jar файла и перенести необходимый вам скрипт в init.d каталог, пример для opensuse/debian/ubuntu

`cd init.d/opensuse_debian`  
`vi vi unity_policy_server.example`

Устанавливаете путь до jar файла

`sudo cp unity_policy_server.example /etc/init.d/unity_policy_server`
`sudo chmod +x /etc/init.d/unity_policy_server`  
`sudo chown root:root /etc/init.d/unity_policy_server`  

Далее необходимо добавить скрипт каталоги дла автозапуска (пример для дебиан):

`sudo update-rc.d unity_policy_server defaults`

### 6. Проверка

Если все прошло удачно, то на команду

`nc <your_server_ip> 843`  

Будет возвращаться полиси для юнити плагина, если же этого не происходит, то проверьте не занят ли 843 порт на вашем сервере, и открыт ли 843 порт файрволом:

`netstat -tupln | grep 843` - должен показать только нами запущенный сервер  
`nmap <your_server_ip> -Pn -p 843`  - с удаленной машины должен показать что-то вроде  

`Host is up (0.054s latency).`  
`PORT    STATE SERVICE`  
`843/tcp open  unknown`  


## Сборка кастомной версии 

Если вы решили что-то изменить в сервере, то для сборки используйте мавен, команда для сборки

`mvn  clean compile assembly:single`  

Результируюйщий jar архив должен замениться в каталоге  `target`

