###########################################################################################
# Imports                                                                                 #
###########################################################################################
from django.http import Http404

from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.decorators import api_view
from rest_framework import authentication, permissions
from rest_framework import status
from rest_framework.pagination import PageNumberPagination

from vibrations.serializers import *

###########################################################################################
# Pagination Classes                                                                      #
###########################################################################################
class StandardUserSetPagination(PageNumberPagination):
    page_size = 10
    page_size_query_param = 'page_size'
    max_page_size = 1000

###########################################################################################
# Requests Classes                                                                        #
###########################################################################################
# .../vibration/
class VibrationList(APIView, StandardUserSetPagination):
    """
    List all vibrations, or create a new object.
    """
    pagination_class = StandardUserSetPagination

    def get(self, request, format=None):
        queryset = Vibration.objects.get_queryset().order_by('id')

        page = self.paginate_queryset(queryset, request)

        if page is not None:
            serializer = VibrationSerializer(page, many=True)
            return self.get_paginated_response(serializer.data)

        serializer = VibrationSerializer(queryset, many=True)
        return Response(serializer.data)


    def post(self, request, format=None):
        # Getting vibration data.
        device = request.POST.get('device', None)
        sensor = request.POST.get('sensor', None)
        motor = request.POST.get('motor', None)
        voltage = request.POST.get('voltage', None)
        frequency = request.POST.get('frequency', None)
        data_x = request.POST.get('data_x', None)
        data_y = request.POST.get('data_y', None)
        data_z = request.POST.get('data_z', None)

        # Making data json.
        data = {
            'device': device,
            'sensor': sensor,
            'motor': motor,
            'voltage': voltage,
            'frequency': frequency,
            'data_x': data_x,
            'data_y': data_y,
            'data_z': data_z,
        }

        serializer = VibrationSerializer(data=data)

        if serializer.is_valid():
            serializer.save()

            return Response(serializer.data, status=status.HTTP_201_CREATED)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
    
###########################################################################################
# .../vibration/<id>/
class VibrationDetail(APIView):
    """
    Retrieve, update or delete a vibration instance.
    """
    def get_object(self, pk):
        # Getting the user by id.
        try:
            return Vibration.objects.get(pk=pk)
        # Return 404 if the user don't exist.
        except Vibration.DoesNotExist:
            raise Http404

    def get(self, request, pk, format=None):
        vibration = self.get_object(pk)
        serializer = VibrationSerializer(vibration)
        return Response(serializer.data)

    def put(self, request, pk, format=None):
        vibration = self.get_object(pk)

        # Getting vibration data.
        device = request.POST.get('device', None)
        sensor = request.POST.get('sensor', None)
        motor = request.POST.get('motor', None)
        voltage = request.POST.get('voltage', None)
        frequency = request.POST.get('frequency', None)
        data_x = request.POST.get('data_x', None)
        data_y = request.POST.get('data_y', None)
        data_z = request.POST.get('data_z', None)

        # Making data json.
        data = {
            'device': device,
            'sensor': sensor,
            'motor': motor,
            'voltage': voltage,
            'frequency': frequency,
            'data_x': data_x,
            'data_y': data_y,
            'data_z': data_z,
        }

        serializer = VibrationSerializer(instance=vibration, data=data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, pk, format=None):
        vibration = self.get_object(pk)
        vibration.delete()
        
        return Response(status=status.HTTP_204_NO_CONTENT)

###########################################################################################