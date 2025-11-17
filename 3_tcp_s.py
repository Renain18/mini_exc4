#This is a python code for TCP from the side of the server.

#importing full socket library
import socket

# defining socket using the socket library
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#defining IP number and port for binding. IP doesn't matter- accept any IP.
server_ip = ''
server_port = 12345

#Binding the ip to the port in the server in the touple (src_ip, src_port)
server.bind((server_ip, server_port))
#define a limit to the amount of clients waiting in line
#to connect to the server. 
#Here the limit was 5, and I changed it to 8
server.listen(8)

#continuous loop, awaiting contact from the client

while True:
    # accept the client if there is one in line
    # recieve the information in unique variables ("waiter") 
    # accept the client with the following touple of IP and Port#
    client_socket, client_address = server.accept()
    #printing out the address of the client that was accepted
    print('Connection from: ', client_address)
    # saving the data in 1024 characters at most.
    data = client_socket.recv(1024)
    # decode data as long as its version is not utf8.
    while not data.decode('utf-8') == '':
        # decode data and print it
        print('Received: ', data.decode('utf-8'))
        #echo the data back to the client
        client_socket.send(data.upper())
        #recieve the next data from the client
        data = client_socket.recv(1024)

    #print that the client disconnected from the client socket
    print('Client disconnected')
    
    #closing the client socket, not the main socket
    client_socket.close()