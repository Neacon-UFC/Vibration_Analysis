###########################################################################################
# Imports                                                                                 #
###########################################################################################
from django.db import models
from django.utils import timezone

###########################################################################################
# Models                                                                                  #
###########################################################################################
# Model for vibrations analysis informations.
class Vibration(models.Model):
    device = models.CharField(max_length=50, default='')
    sensor = models.CharField(max_length=50, default='')
    motor = models.CharField(max_length=50, null=False)
    voltage = models.IntegerField(null=False, default=380)
    frequency = models.IntegerField(null=False, default=60)
    data_x = models.TextField(null=False)
    data_y = models.TextField(null=False)
    data_z = models.TextField(null=False)
    date = models.DateTimeField(default=timezone.now)