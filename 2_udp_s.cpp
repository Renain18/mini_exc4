// This is a C++ code for UDP from the side of the server.

// importing libraries for i/o, sockets etc.
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// shortcut for std code
using namespace std;

int main() {
// defining port number
    const int server_port = 5555;
// creating socket with IPv4 and UDP definitions
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
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
// binding the socket and the port
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket");
    }
// creating new struct where the new message info will be saved
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
// saving buffer variablr to save the info recieved to echo it back
    char buffer[4096];
// reading the information from the client
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
// checking that the input from the client was recieved
    if (bytes < 0) {
        perror("error reading from socket");
    }

    cout << "The client sent: " << buffer << endl;

// sending the message back to the client
    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    close(sock);

    return 0;
}