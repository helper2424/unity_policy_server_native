# Policy server

About Unity3d security model for Web Player you can read [here](http://docs.unity3d.com/Manual/SecuritySandbox.html).

## Installing

### 1. Dependencies
To install project you need utilities: git, cmake, make, gcc; and some libraries: tbb, libev, boost.
*Command line for debian*:  
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
`make`  
`sudo make install` 
### 5. Check Installation
To check installation run command `unity_policy_server -h`.If you see somthing like this 
```
2015-08-30 17:32:00,450 INFO  [default] Usage: unity_policy_server [ -h | -d [-c <handlers_count>] [-p <port>]... [-x <your_xml> | -f <path_to_xml>] ] 
:
  -h [ --help ]         Print help messages
  -x [ --xml ] arg      Xml for respondong to requests
  -f [ --file ] arg     Path to xml with policy
  -p [ --ports ] arg    Ports to listen requests, by default 843 port used
  -d [ --daemon ]       Use daemon function to detach pipes and daemonize 
                        server
  -c [ --count ] arg    Handlers count. One handler - one thread.
```
then policy server successfully installed. Now, try `sudo unity_policy_server` and in other shell `nc 127.0.0.1 843`. If you something like this
```
<?xml version="1.0"?>
<cross-domain-policy>
  <allow-access-from domain="*" to-ports="*"/>
</cross-domain-policy>
```
then policy server successfully reponse policy xml.
### 3. Log
By default log file here `/var/log/unity_policy_server/policy.log` , because you need create directory for logs:  
`mkdir -p /var/log/unity_policy_server` 
You can customize log directory and log file name by parameter `-l` in server executable. 
### 5. Init scripts
If you want, you can setup init scripts for server. `init` directory has init script for debian/suse/opensuse/ubuntu. For other OS'es you can write custom scripts or ask me for this in email `helper2424@gmail.com`. So if this script fit for yor os then

`cd init/opensuse_debian`   
`vi unity_policy_server.example`    

Setup your values for `DAEMON` and `LOG_DIR`, copy init scripts to init.d directory:    

`sudo cp unity_policy_server.example /etc/init.d/unity_policy_server`   
`sudo chmod +x /etc/init.d/unity_policy_server`     
`sudo chown root:root /etc/init.d/unity_policy_server`      

Next, need add init scripts to startups directories.*Command line for debian*:  

`sudo update-rc.d unity_policy_server defaults`
### 6. Finish
So, now you can run server through init script: 
`/etc/init.d/unity_policy_server restart`
### 7. Troubleshooting
Check server from some host
`nc <your_server_ip> 843`  
If you get incorrect result, then check that server work correctly:
- `netstat -tupln | grep 843` - run on server, you must see only unity_policy_server, else somebody bind 843 port  
- `nmap <your_server_ip> -Pn -p 843` - run from remote host, you must see something like this, else 843 blocked, or filtered by firewall             
`Host is up (0.054s latency).`  
`PORT    STATE SERVICE`     
`843/tcp open  unknown`     

