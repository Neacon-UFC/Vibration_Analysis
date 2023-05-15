<template>
    <v-content>
      <v-container>
        <h1>MQTT Messages</h1>
        <v-card v-for="message in messages" :key="message" class="mx-auto">
          <v-card-title>
            {{ message }}
          </v-card-title>
        </v-card>
      </v-container>
    </v-content>    
</template>

<script>
import mqtt from 'mqtt'
import mqtt_config from '@/mqtt'

export default {

    data() {
        return {
            messages: [],
        }
    },
    created() {
        var client = mqtt.connect(mqtt_config.broker, mqtt_config.options)

        client.subscribe('test')

        client.on('message', (topic, message) => {
            this.messages.push(message.toString())
        })

        this.$once('hook:beforeDestroy', () => {
            client.end()
        })
    }
}
</script>
