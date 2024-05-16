#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUF_SIZE 1024

// Function to trim the newline character from the end of the string
void trim_newline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}

void read_server_response(int sock)
{
    char buffer[BUF_SIZE];
    int bytes_read = read(sock, buffer, BUF_SIZE - 1);
    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0';      // Null-terminate the string
        printf("SERVER- \n%s", buffer); // Debug print
    }
}

void send_input_to_server(int sock)
{
    printf(" (fgets taking ip here) ");
    char buffer[BUF_SIZE];
    fgets(buffer, BUF_SIZE, stdin); // Read user input
    trim_newline(buffer); // Trim newline character
    send(sock, buffer, strlen(buffer), 0);
    printf("Sent to server: %s\n", buffer); // Debug print
}

// Function to handle menu options received from the server
void handle_menu(int sock)
{
    char buffer[BUF_SIZE];
    int bytes_read;

    while (1)
    {
        // Read menu options from the server
        printf("Inside (handle_menu) while loop\n");
        // bytes_read = read(sock, buffer, BUF_SIZE - 1);
        // ------->>>ERROR IS COMING IN LINE ABOVE. It is never coming out of read
        // printf("read in (handle_menu) finished\n");
        buffer[bytes_read] = '\0'; // Ensure null-terminated string
        printf("Server menu:\n%s", buffer); // Print menu options

        // Prompt user for action
        printf("Enter your choice: ");
        send_input_to_server(sock); // Send user's choice to the server

        // Read server's response
        bytes_read = read(sock, buffer, BUF_SIZE - 1);
        buffer[bytes_read] = '\0'; // Ensure null-terminated string
        printf("Server response: %s\n", buffer); // Print server response

        if (strstr(buffer, "Exit") != NULL)
        {
            break; // Exit loop if the server indicates to exit
        }
    }
}

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Select role
    read_server_response(sock); // Prompt: Select role (1 for admin, 0 for user):
    send_input_to_server(sock); // Send role

    // Username
    read_server_response(sock); // Prompt: Username:
    send_input_to_server(sock); // Send username

    // Password
    read_server_response(sock); // Prompt: Password:
    send_input_to_server(sock); // Send password

    // Authentication response
    read_server_response(sock); // Read authentication response

    // Handle server responses
    while (1)
    {
        printf("In the while loop\n");
        read_server_response(sock); // Read server's response
        printf("After read_server_response(sock); in the while loop.\n");

        // Check if server prompts for another action
        // if (strstr(buffer, "Do you want to perform another action? (yes/no):") != NULL) {
        //     send_input_to_server(sock); // Send yes or no
        //     read_server_response(sock); // Read server's response
        //     if (strstr(buffer, "no") != NULL) {
        //         break; // Exit loop if the client doesn't want to perform another action
        //     }
        // }
        // Handle menu options for non-admin users

        // print the buffer
        // printf("Buffer: %s\n", buffer);

        // ----->>>>>> Error is in line below. The buffer is coming empty
        if (strstr(buffer, "Authentication successful (user)") != NULL);
        if(1)
        {
            // debug print
            printf("User authenticated\n");
            handle_menu(sock);
        }
    }

    close(sock);
    return 0;
}
