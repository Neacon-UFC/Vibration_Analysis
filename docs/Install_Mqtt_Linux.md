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