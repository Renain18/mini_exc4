#This is a python code for UDP from the side of the server.

#importing socket library, and specifically socket and the two criteria AF_INET and SOCK_DGRAM
from socket import socket, AF_INET, SOCK_DGRAM

#creating socket s using the socket constructor, inserting the data (AF_Inet= Ipv4, datagram=UDP)
s = socket(AF_INET, SOCK_DGRAM)

#defining IP number and port for binding. IP doesn't matter- accept any IP.
src_ip = ''
src_port = 12345

#Binding the ip to the port in the server in the touple (src_ip, src_port)
s.bind((src_ip, src_port))

#continuous loop, port open and awaiting contact from the client

while True:
    # recieve touple- data (message) and the info of the client
    data, sender_info = s.recvfrom(2048)
    # printing message recieved by the client
    print(data.decode('utf-8'))
    # printing the ip of the client
    print(sender_info)
    #Echo funciton, returning the same message recieved by the client
    s.sendto(data.upper(), sender_info)