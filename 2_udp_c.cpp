// This is a C++ code for UDP from the side of the client.


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
    // defining ip and port values
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;
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
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    // creating char array with the message sent to the server
    char data[] = "hello";
    // saving the length of the data
    int data_len = sizeof(data);

    // sending data to the server with all the nesassary detaile (IP, UDP, data, etc)
    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    // checking that the input from the client was sent to the server
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    // creating new struct to recieve the input 
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];

    //recieveing the information from the server
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);

    // checking that the input from the client was sent to the server
    if (bytes < 0) {
        perror("error reading from socket");
    }
    // printing out the message from the server
    cout << "The server sent: " << buffer << endl;
    // closing socket
    close(sock);

    return 0;
}