// This is a C++ code for TCP from the side of the server.
// importing libraries for i/o, sockets etc.

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// shortcut for std code use
using namespace std;

int main() {
// defining port number
    const int server_port = 5555;
// creating socket with IPv4 and TCP definitions
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // if the socket identifier number is negative= the function failed- it is not valid and returns an error
    if (sock < 0) {
        perror("error creating socket");
    }
// creating a struct that includes addresses 
    struct sockaddr_in sin;
    // clearing the memory of the struct sin along its entire length
    memset(&sin, 0, sizeof(sin));
    // defining the fields 
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    // htons- converting the humber in host to the number in the netword
    sin.sin_port = htons(server_port);
    // binding the socket and the port and returning error if not valid
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    // if there are more than 5 (or 8 in my case) clients 
    // that are waiting in line for the server, return error text
    if (listen(sock, 8) < 0) {
        perror("error listening to a socket");
    }

    // creating new struct where the new message info will be saved
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    // accepting the client with its IP and port to this client socket 
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);
    // checking that the input from the client was recieved well
    if (client_sock < 0) {
        perror("error accepting client");
    }
    // saving buffer variable to save the info recieved to echo it back
    char buffer[4096];
    // saving length of client input
    int expected_data_len = sizeof(buffer);
    // reading the information from the client
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
    // checking client input, echoing it only if input is detected
    if (read_bytes == 0) {
    // connection is closed
    }
    else if (read_bytes < 0) {
    // error
    }
    else {
        cout << buffer;
    }

    // sending the message back to the client
    int sent_bytes = send(client_sock, buffer, read_bytes, 0);
    // printing out error if message was not sent.
    if (sent_bytes < 0) {
        perror("error sending to client");
    }

    // close both client socket and the whole socket.
    close(client_sock);
    close(sock);


    return 0;
}