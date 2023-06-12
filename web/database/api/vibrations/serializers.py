###########################################################################################
# Imports                                                                                 #
###########################################################################################
from rest_framework import serializers
from vibrations.models import Vibration

###########################################################################################
# Serializers                                                                             #
###########################################################################################
# Vibrations Serializer
class VibrationSerializer(serializers.ModelSerializer):

    class Meta:
        model = Vibration()
        ordering = ['id']
        fields = ['id', 'device', 'sensor', 'motor', 'voltage', 'frquency', 'data_x', 'data_y', 'data_z', 'date']

    # Making it nested with Profile and Token.
    def create(self, validated_data):
        # Crating user object
        vibration = Vibration.objects.create(**validated_data)
        
        return vibration

    def update(self, instance, validated_data):
        # Updating instance
        for key in validated_data.keys():
            setattr(instance, key, validated_data.get(key, getattr(instance, key)))
        instance.save()
        
        return instance
###########################################################################################
