#include "OS_DEFINES.h"


int start_chat(int mode){
    printf("\nLE CHAT\n");

    if (mode == 1){
        printf("veuillez indiquer l'adresse de l'hôte distant : ");
        char addresse [CMDLINE_MAX_SIZE];
	    fgets(addresse, CMDLINE_MAX_SIZE, stdin);
	    addresse[strlen(addresse) -1] = '\0';

        printf("veuillez indiquer le port de l'hôte distant : ");
        char port_str [CMDLINE_MAX_SIZE];
	    fgets(port_str, CMDLINE_MAX_SIZE, stdin);
	    port_str[strlen(port_str) -1] = '\0';
        int port = atoi(port_str);

        int socket_file_descriptor;
        int socket;

        int retour = create_socket_connexion(&socket_file_descriptor, &socket, addresse, port);
        if (retour != NO_ERROR) return retour;

        //connexion initialisée
        //demarer le chat
        chat(&socket_file_descriptor, &socket, "you", "me");
    }
    else if (mode == 2){
        printf("veuillez indiquer le port sur lequel vous hébergerez la conversation : ");
        char port_str [CMDLINE_MAX_SIZE];
	    fgets(port_str, CMDLINE_MAX_SIZE, stdin);
	    port_str[strlen(port_str) -1] = '\0';
        int port = atoi(port_str);

        int socket_file_descriptor;
        int socket;

        int retour = create_socket_heberger(&socket_file_descriptor, &socket, port);
        if (retour != NO_ERROR) return retour;

        //connexion initialisée
        //demarer le chat
        chat(&socket_file_descriptor, &socket, "you", "me");
    }
    else{
        return ERROR_ARGS;
    }

    return NO_ERROR;
}

int chat(int* socket_fils_descriptor, int* socket, char* name_distant_user, char* your_name){
    char input_user [CMDLINE_MAX_SIZE];
    char input_distant [CMDLINE_MAX_SIZE];
    //char historique [CMDLINE_MAX_SIZE][NB_LIGNE_HISTORIQUE_MAX];

    //on met stdin en non bloquant
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

    memset(input_user, 0, CMDLINE_MAX_SIZE);
    memset(input_distant, 0, CMDLINE_MAX_SIZE);
    /*for (int i=0; i < NB_LIGNE_HISTORIQUE_MAX; i++){
        memset(historique[i], 0, CMDLINE_MAX_SIZE);
    }*/

    while (strcmp(input_user, "/quit")){
        if (read(*socket, input_distant, 128) != -1){
            input_distant[strlen(input_distant)-1] = '\0';
            printf("<%s> %s\n", name_distant_user, input_distant);
        }
        if (read(0, input_user, CMDLINE_MAX_SIZE) != -1){
            input_user[strlen(input_user)-1] = '\0';
            printf("<%s> %s\n", your_name, input_user);
        }

        sleep(1);
    }

    //enleve le non bloquant sur stdin
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) & (~O_NONBLOCK));

    return NO_ERROR;
}