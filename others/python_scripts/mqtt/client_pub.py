#################################################################
# Lamotriz - Universidade Federal do Ceará                      #
# Author: Joel Pontes                                           #
# Data: 04/2023                                                 #
#################################################################

# Imports
import paho.mqtt.client as mqtt
import random
import time

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

# Scripts used in publish
def on_publish(client, userdata, mid):
    print("Message "+str(mid)+" published.")

# Creating mqtt Client
mqtt_client = mqtt.Client()

# Setting scripts to connect and publish
mqtt_client.on_connect = on_connect
mqtt_client.on_publish = on_publish

# Binding with mqtt broker
mqtt_client.connect(broker_address, broker_port)

# Setting message and publishint it.
while(1):
    message = random.randint(19,33)
    mqtt_client.publish(topic, message)
    time.sleep(5)

mqtt_client.disconnect()
