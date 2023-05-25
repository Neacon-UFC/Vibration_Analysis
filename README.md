# IoT_Lamotriz

Project applied in the Lamotriz laboratory, at the University Federal of Ceará, with the objective to applied IoT in the embedded systems presents there. 

To achieve this objective, we choose to use MQTT protocol within a Raspberry Pi and an ESP32. The Raspberry Pi is the broker and the ESP32 are publishers and subscribers. To manage all that, we choose to build an interface using the node-red application, which will be hosted in the Raspberry.

So, we have :

- Mqtt:
    - ESP32 as clients:
        - ESP32 (Motor WEG - to study vibrations)
    - Raspberry PI:
        - Node-RED as server (on Raspberry Pi)
            - Broker (Server Mqtt) on Node-RED flow


