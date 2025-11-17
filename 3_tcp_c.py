#This is a python code for TCP from the side of the client.

#importing full socket library
import socket 

# defining socket using the socket library
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#defining IP number and port for binding
dest_ip = '127.0.0.1'
dest_port = 12345
#connect to the server with the destination IP and Port
s.connect((dest_ip, dest_port))

# Asking the user for a message, reading the input message, 
# and saveing it in msg.
msg = input("Message to send: ")
#instead of quit i did nox
#while loop ready to accept text from the client until he writes nox
while not msg == 'nox':
    #sending to the client the msg 
    s.send(bytes(msg, 'utf-8'))
    #saving the data input from the server
    data = s.recv(4096)
    #printing out the message recieved
    print("Server sent: ", data.decode('utf-8'))
    #recive input again from the server
    msg = input("Message to send: ")

#closing socket
s.close()