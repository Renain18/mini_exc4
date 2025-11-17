// This is a C++ code for TCP from the side of the client.

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
    // defining IP and port numbers
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;
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
    sin.sin_addr.s_addr = inet_addr(ip_address);
    // htons- converting the humber in host to the number in the network
    sin.sin_port = htons(port_no);
    //Try to connect to server, print error if rejected
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
    // creating char array with the message sent to the server
    char data_addr[] = "Im a message";
    // saving the length of the data
    int data_len = strlen(data_addr);
    // sending data to the server with all the nesassary detaile (IP, TCP, data, etc)
    int sent_bytes = send(sock, data_addr, data_len, 0);
    
    // checking that the message client was sent to the server socket
    if (sent_bytes < 0) {
    // error
    // i added the same error message from 2_udp_c
    perror("error writing to socket");
    }

    // saving buffer variable to save the info recieved 
    char buffer[4096];
    //saving the length of the buffer
    int expected_data_len = sizeof(buffer);
    // reading the information from the server and saving it in read_bytes
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    // checking server input, printing it only if input is detected
    if (read_bytes == 0) {
    // connection is closed
    }
    else if (read_bytes < 0) {
    // error
    }
    else {
        cout << buffer;
    }

    //closing socket
    close(sock);


    return 0;
}