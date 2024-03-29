# Generated by Django 4.2.1 on 2023-06-01 18:18

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Vibration',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('device', models.CharField(default='', max_length=50)),
                ('sensor', models.CharField(default='', max_length=50)),
                ('motor', models.CharField(max_length=50)),
                ('data_x', models.TextField()),
                ('data_y', models.TextField()),
                ('data_z', models.TextField()),
                ('date', models.DateTimeField(default=django.utils.timezone.now)),
            ],
        ),
    ]
