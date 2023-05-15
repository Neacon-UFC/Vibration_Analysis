// Defining the broker url
const broker = "10.101.94.54"
const port = "1883"
const brokerUrl = 'mqtt://'+broker+':'+port

// Defining mqtt client settings
const options = {
    // Clean session
    clean: true,
    connectTimeout: 4000,
}

const mqtt_config = {
    broker: brokerUrl,
    options: options,
}

export default mqtt_config