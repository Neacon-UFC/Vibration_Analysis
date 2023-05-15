# --------------------------------------------------------------------------------------------------------------------- #
# Company : Lamotriz - UFC                                                                                              #
# Created by : Joel Pontes                                                                                              #
# Date : 04/2023                                                                                                        #
# Version : 1.0                                                                                                         #
# --------------------------------------------------------------------------------------------------------------------- #

# --------------------------------------------------------------------------------------------------------------------- #
# Imports ------------------------------------------------------------------------------------------------------------- #
# --------------------------------------------------------------------------------------------------------------------- #

import socket
import sys, os
import requests

# --------------------------------------------------------------------------------------------------------------------- #
# Define the Functions ------------------------------------------------------------------------------------------------ #
# --------------------------------------------------------------------------------------------------------------------- #

# The command to execute the script in shell is "python3 server.py"
# To this case, which aren't arguments, the address will set as default
# If you want to define an address, you can use "python3 server.py IP", example ("python3 server.py 127.0.0.1")
# If you want to define an address and port, use "python3 server.py IP Port", example ("python3 server.py 127.0.0.1 4000")

def define_server(args):
    # server = (Adress_IP, Port)
    if len(args) == 2:
        server = (args[1], 4242)
    
    elif len(args) == 3:
        server = (args[1], int(args[2]))
    
    else:
        # Adress default
        server = ('10.101.94.54', 4242)

    return server

# --------------------------------------------------------------------------------------------------------------------- #

# This is the function that will be executed by the child, after the fork
# This means that each client connected to the server will execute this script

def handle_client(connection, client):
    
    print("Connection from %s port %s" % client)
    
    while True:

        message = connection.recv(sizeMessage)
        print("Message received from %s port %s" % client)

        if len(message) > 5:
            print(str(message))

        else:
            print("Stopping connection with %s port %s" %client)
            break

    # Closing the connection
    connection.close()
    os._exit(0)

# --------------------------------------------------------------------------------------------------------------------- #


# --------------------------------------------------------------------------------------------------------------------- #
# Define variables ---------------------------------------------------------------------------------------------------- #
# --------------------------------------------------------------------------------------------------------------------- #

server = define_server(sys.argv)

sizeMessage = 3000

number_of_unnaccepted_clients = 5 # Suggested by socket library documentation


# --------------------------------------------------------------------------------------------------------------------- #
# Main ---------------------------------------------------------------------------------------------------------------- #
# --------------------------------------------------------------------------------------------------------------------- #


# Create a TCP/IP socket
# Protocole default to create the socket
# Print the message for each cas (success or error)
# In the case of don't be succeed to create the socket, the script will close (This can be changed to try sometimes before do it)

try:
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("Socket successfully created...\n")

except socket.error as err:
    print("Socket creation failed, error : " + str(err) + "\n")
    exit(0)

# Bind the socket to the port
# Protocole default to bind the server
# Print the message for each cas (success or error)
# In the case of don't be succeed to do the bind, the script will close (This can be changed to try sometimes before do it)
# The bind can have problems if the port is already in use, or if the IP is wrong

try:
    sock.bind(server)
    print('Starting up on %s port %s' % server)

except socket.error as err:
    print("Socket bind failed, error : " + str(err) + "\n")
    exit(0)


# Listen for income connections
# We use the sock.listen() to do the server start to wait for client's connections
# The number_of_unnaccepted_clients is a constant that means the number of clients that tried the connection but have not accepted
# When this happens, the client should try again

try:
    sock.listen(number_of_unnaccepted_clients)
    print("Server waiting for connection ...")
except socket.error as err:
    print("Socket listen failed, error : " + str(err) + "\n")
    exit(0)


# Infinity loop

while True:

    # So, when a client tried the connection, and the serve accept it, we will create a fork
    # The fork means we will create a copy of the script that will be executed by the client
    # But, at the same time, the server keep running
    # Look :
    # Parent (1 client) -> Parent and child scripts running
    # Parent (2 clients) -> Parent, child_1 and child_2 scripts running
    # ....

    connection, client = sock.accept()
    child_pid = os.fork()

    # child_pid = 0 means we are in the child fork, and we need to run the client script
    # child_pid = 1 means we are in the parent, and we need to run the server script
    # child_pid = -1 means some error

    if child_pid == 0 :
        handle_client(connection, client)
            
    elif child_pid > 0 :
        # Routine to be executed after the creation of a child
        pids = (os.getpid(), child_pid)
        print("\nParent: %d, Child: %d" %pids)