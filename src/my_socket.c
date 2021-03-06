#include "OS_DEFINES.h"


int create_socket_heberger(int* server_fd,int* my_socket, int port){
    struct sockaddr_in address;
    int opt = 1;

    int address_len = sizeof(address);

    if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("create socket");
        return ERROR_SOCKET;
    }

    if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &opt, sizeof(opt))){
        perror("error opt");
        return ERROR_SOCKET;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(*server_fd, (struct sockaddr*)&address, sizeof(address))<0){
        perror("bind failed");
        return ERROR_SOCKET;
    }

    printf("En attente d'une connexion d'un client...\n");

    if (listen(*server_fd, 3) < 0){
        perror("listen");
        return ERROR_SOCKET;   
    }

    printf("listen terminé\n");
    if ((*my_socket = accept(*server_fd, (struct sockaddr *) &address, (socklen_t*) &address_len))<0){
        perror("accept");
        return ERROR_SOCKET;
    }

    printf("Connexion réussie.\n");

    int status = fcntl(*my_socket, F_SETFL, fcntl(*my_socket, F_GETFL, 0) | O_NONBLOCK);
    if (status == -1){
        perror("fcntl");
        return ERROR_SOCKET;
    }

    return NO_ERROR;
}

int create_socket_connexion(int* my_socket, char* addresse_char, int port){
    struct sockaddr_in address;

    if ((*my_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("\nErreur de création de socket\n");
        return ERROR_SOCKET;
    }
   
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, addresse_char, &(address.sin_addr))<=0) {
        printf("\nAddresse invalide\n");
        return ERROR_SOCKET;
    }
   
    printf("Tentative de connection...\n");
    if (connect(*my_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("\nConnection Failed \n");
        perror("connect");
        return ERROR_SOCKET;
    }

    printf("Connexion réussie\n");

    int status = fcntl(*my_socket, F_SETFL, fcntl(*my_socket, F_GETFL, 0) | O_NONBLOCK);
    if (status == -1){
        perror("fcntl");
        return ERROR_SOCKET;
    }

    return NO_ERROR;
}