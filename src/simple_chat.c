#include "OS_DEFINES.h"


int start_chat(int mode){
    printf("\nLE CHAT\n");

    if (mode == 1){
        printf("Veuillez indiquer l'adresse de l'hôte distant : ");
        char addresse [CMDLINE_MAX_SIZE];
	    fgets(addresse, CMDLINE_MAX_SIZE, stdin);
	    addresse[strlen(addresse) -1] = '\0';

        printf("Veuillez indiquer le port de l'hôte distant : ");
        char port_str [CMDLINE_MAX_SIZE];
	    fgets(port_str, CMDLINE_MAX_SIZE, stdin);
	    port_str[strlen(port_str) -1] = '\0';
        int port = atoi(port_str);

        int socket;

        int retour = create_socket_connexion(&socket, addresse, port);
        if (retour != NO_ERROR) return retour;

        //connexion initialisée
        //demarer le chat
        chat(&socket, "you", "me");
    }
    else if (mode == 2){
        printf("Veuillez indiquer le port sur lequel vous hébergerez la conversation : ");
        char port_str [CMDLINE_MAX_SIZE];
	    fgets(port_str, CMDLINE_MAX_SIZE, stdin);
	    port_str[strlen(port_str) -1] = '\0';
        int port = atoi(port_str);

        int socket;
        int server_fd;

        int retour = create_socket_heberger(&server_fd, &socket, port);
        if (retour != NO_ERROR) return retour;

        //connexion initialisée
        //demarer le chat
        chat(&socket, "distant", "local");
        close(server_fd);
    }
    else{
        return ERROR_ARGS;
    }

    return NO_ERROR;
}

int chat(int* socket, char* name_distant_user, char* your_name){
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

    while (strcmp(input_user, "/quit\n")){
        if (read(*socket, input_distant, 128) != -1){
            printf(GREEN"\a[%s]"DEF"\t%s\n", name_distant_user, input_distant);
            memset(input_user, 0, CMDLINE_MAX_SIZE);
        }
        if (read(0, input_user, CMDLINE_MAX_SIZE) != -1 && strcmp(input_user, "/quit\n")!= 0){
            input_user[strlen(input_user)-1] = '\0';
            send(*socket, input_user, strlen(input_user)+1, 0);
            memset(input_user, 0, CMDLINE_MAX_SIZE);
        }

        sleep(1);
    }

    //enleve le non bloquant sur stdin
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) & (~O_NONBLOCK));

    return NO_ERROR;
}