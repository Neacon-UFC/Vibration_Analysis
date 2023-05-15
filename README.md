# IoT_Lamotriz

Project applied in the Lamotriz laboratory, at the University Federal of Ceará, with the objective to applied IoT in the embedded systems presents there. 

To achieve this objective, we choose to use MQTT protocol within a Raspberry Pi and an ESP32. The Raspberry Pi is the broker and the ESP32 are publishers and subscribers. To manage all that, we choose to build an interface using the node-red application, which will be hosted in the Raspberry.

So, we have :

- Mqtt:
    - Raspberry PI as Broker (Server Mqtt)
    - ESP32 as clients
    - Node-RED as interface (on Raspberry Pi)


# Setup the environment

To develop and test, we'll set a Linux environment to generate the mqtt broker and the node-red.

If you are using a Linux OS, you can follow this tutorial:

## Installing Mosquitto

### 1. Install the Mosquitto Server

You'll pull the mosquitto package from Ubuntu's software repository by executing the following steps.

1. Update the package information index.

```sh
    $ sudo apt update 
```

2. Install the mosquitto package.

```sh
    $ sudo apt install -y mosquitto
```

3. The mosquitto package should now load on your server. Confirm the status of the mosquitto service.

```sh
    $ sudo systemctl status mosquitto
```

Ensure the package is loaded and active.

```
    ● mosquitto.service - Mosquitto MQTT Broker
     Loaded: loaded (/lib/systemd/system/mosquitto.service; disabled; vendor preset: enabled)
     Active: active (running) since Mon 2023-04-24 16:36:34 -03; 1s ago
       Docs: man:mosquitto.conf(5)
             man:mosquitto(8)
    ...
```

4. Once running, you can manage the mosquitto services by executing the following commands.

    - Stop the mosquitto service:
    ```sh
        $ sudo systemctl stop mosquitto
    ```
    - Start the mosquitto service:
    ```sh
        $ sudo systemctl start mosquitto
    ```
    - Restart the mosquitto service:
    ```sh
        $ sudo systemctl restart mosquitto
    ```

After that, to allow the mosquitto to be hosted for all your network, instead just your localhost, you should go to mosquitto.conf, located in:

```
    /etc/mosquitto/mosquitto.conf
```

And then set the port you want, and set allow_anonymous as true.

```
    # Plain MQTT protocol
    listener 1883 
    allow_anonymous true
```

After that, anyone in your network will be allowed to send messages using the broker. 

**For now we'll use that, in the future we should add a security using login and password to access.**

### 2. Install Node-RED

You can follow the tutorial in [Node-RED site](https://nodered.org/docs/getting-started/local) or just follow the steps bellow.

0. Prerequisites

    To install Node-RED locally you will need a supported version of Node.js.

1. Installing with npm

    To install Node-RED you can use the npm command that comes with node.js:

```sh
    sudo npm install -g --unsafe-perm node-red
```

2. Running

    Once installed as a global module you can use the node-red command to start Node-RED in your terminal. You can use Ctrl-C or close the terminal window to stop Node-RED.

```
    $ node-red

    Welcome to Node-RED
    ===================

    30 Jun 23:43:39 - [info] Node-RED version: v1.3.5
    30 Jun 23:43:39 - [info] Node.js  version: v14.7.2
    30 Jun 23:43:39 - [info] Darwin 19.6.0 x64 LE
    30 Jun 23:43:39 - [info] Loading palette nodes
    30 Jun 23:43:44 - [warn] rpi-gpio : Raspberry Pi specific node set inactive
    30 Jun 23:43:44 - [info] Settings file  : /Users/nol/.node-red/settings.js
    30 Jun 23:43:44 - [info] HTTP Static    : /Users/nol/node-red/web
    30 Jun 23:43:44 - [info] Context store  : 'default' [module=localfilesystem]
    30 Jun 23:43:44 - [info] User directory : /Users/nol/.node-red
    30 Jun 23:43:44 - [warn] Projects disabled : set editorTheme.projects.enabled=true to enable
    30 Jun 23:43:44 - [info] Creating new flows file : flows_noltop.json
    30 Jun 23:43:44 - [info] Starting flows
    30 Jun 23:43:44 - [info] Started flows
    30 Jun 23:43:44 - [info] Server now running at http://127.0.0.1:1880/red/
```