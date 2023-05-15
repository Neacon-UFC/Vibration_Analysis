#################################################################
# Lamotriz - Universidade Federal do Ceará                      #
# Author: Joel Pontes                                           #
# Data: 04/2023                                                 #
#################################################################

# Imports
import paho.mqtt.client as mqtt

# Defining mqtt host
#broker_address = "172.17.0.1"      # Docker adress
#broker_address = "192.168.1.15"    # PC adress
broker_address = "10.101.94.54"    # Lamotriz adress

# Default Port
broker_port = 1883

# Defining topic
topic = "sensor/status"

# Defining functions
# Script used in connect
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("sensor/status")

# Scripts used in subscriber
def on_message(client, userdata, msg):
    print("Message received on topic: "+msg.topic)
    print("Message content: "+str(msg.payload))

# Creating mqtt Client
mqtt_client = mqtt.Client()

# Setting scripts to connect and publish
mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message

# Binding with mqtt broker
mqtt_client.connect(broker_address, broker_port)

# To listent 4ever
mqtt_client.loop_forever()
