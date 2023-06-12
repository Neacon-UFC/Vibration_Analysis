from django.urls import path
from rest_framework.urlpatterns import format_suffix_patterns
from vibrations import views

urlpatterns = [
    # Request to get all users.
    path('', views.VibrationList.as_view()),
    # Request to get specific user by id.
    path('<int:pk>/', views.VibrationDetail.as_view()),
]

urlpatterns = format_suffix_patterns(urlpatterns)