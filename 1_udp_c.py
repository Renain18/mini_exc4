#This is a python code for UDP from the side of the client.

#importing socket library, and specifically socket and the two criteria AF_INET and SOCK_DGRAM
from socket import socket, AF_INET, SOCK_DGRAM

#creating socket s using the socket constructor, inserting the data (AF_Inet= Ipv4, datagram=UDP)
s = socket(AF_INET, SOCK_DGRAM)

#defining IP number and port for binding
dst_ip = '127.0.0.1' #Home
dst_port = 12345

#sending a message to the server along with a touple of IP and Port number.
# I changed "Hello World!" to "Good morning! How are you doing?"
s.sendto(b'Good morning! How are you doing?', (dst_ip,dst_port))

#preparing to recieve the message from the server and saving it in data and sender_info
data, sender_info = s.recvfrom(2048)
#printing out the message
print(data.decode('utf-8'))
#printing out the sender info
print(sender_info)

#Adding another message before closing the socket
s.sendto(b'Good Night!', (dst_ip,dst_port))

#closing socket
s.close()
