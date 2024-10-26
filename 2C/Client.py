import paho.mqtt.client as mqtt
import time
import random

# MQTT broker details (replace with your AWS EC2 public IP)
broker = ""
port = 1883
topic = "SoilStatus"

# Create an MQTT client instance
client = mqtt.Client()

# Connect to the MQTT broker on AWS
client.connect(broker, port)

# Continuously publish sensor data
while True:
    # Simulate temperature data (e.g., between 20 and 30 degrees Celsius)
    temperature = round(random.uniform(20.0, 30.0), 2)
    message = f"Temperature: {temperature}°C"
    print(f"Publishing: {message}")

    # Publish the message to the MQTT topic
    client.publish(topic, message)

    # Wait 5 seconds before sending the next message
    time.sleep(5)
