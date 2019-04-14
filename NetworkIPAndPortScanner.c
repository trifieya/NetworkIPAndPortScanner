//NetworkIPAndPortScanner
//Author : Eya Trifi
//Email : eya.trifi.19@gmail.com


#include <stdio.h>
#include <string.h> /* pour strncpy */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include<errno.h>
#include<netdb.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include<pthread.h>

pthread_t tid[2];


void* scan_ipv4_adress(void *arg)
{
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    /* Chercher les IPv4 address */
    ifr.ifr_addr.sa_family = AF_INET;

    /* Chercher les IPv4 attachées a l'interface "eth0" : interface par défaut sous linux*/
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);

    ioctl(fd, SIOCGIFADDR, &ifr);

    close(fd);

    /* Afficher les résultats */
    printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

    return 0;
}



void* open_port_scanner(void *arg)
{
    //la structure hostent
    struct hostent *host;

    int err, i , sock ,start , end;

    //le nom de la machine ou adresse IPv4
    char hostname[100];

    //la structure adresse
    struct sockaddr_in sa;

    //Récupérer l'adresse IPv4 ou nom de la machine
    printf("Entrer l'addresse IPv4 ou nom de la machine : ");
    gets(hostname);


    //-----Définition de l'intervalle
    //Récupérer le numéro de port de début
    printf("\n Entrer le numéro de port de début : ");
    scanf("%d" , &start);

    //Récupérer le numéro de port de fin
    printf("\n Entrer le numéro de port de fin : ");
    scanf("%d" , &end);


    //Initialiser sockaddr_in dans la sturcture structure
    strncpy((char*)&sa , "" , sizeof sa);
    sa.sin_family = AF_INET;

    //Si ip addresse, on l'utilise
    if(isdigit(hostname[0]))
    {
        printf("Commencer inet_addr...");
        sa.sin_addr.s_addr = inet_addr(hostname);
        printf("Terminer\n");
    }
    //Sinon convertir le nom de la machine en addresse IPv4
    else if( (host = gethostbyname(hostname)) != 0)
    {
        printf("Commencer gethostbyname...");
        strncpy((char*)&sa.sin_addr , (char*)host->h_addr , sizeof sa.sin_addr);
        printf("Terminer\n");
    }
    else
    {
        herror(hostname);
        exit(2);
    }

    //Commencer le scan des ports dans une loop
    printf("Commencer le scan des ports dans une loop : \n");
    for( i = start ; i <= end ; i++)
    {
        //Initialiser le numéro de port
        sa.sin_port = htons(i);
        //Créer une socket de type internet
        sock = socket(AF_INET , SOCK_STREAM , 0);

        //Vérifier si le socket est bien créée
        if(sock < 0)
        {
            perror("\nSocket");
            exit(1);
        }
        //Se connecter en utilisant socket et la structure sockaddr
        err = connect(sock , (struct sockaddr*)&sa , sizeof sa);

        //non connectée
        if( err < 0 )
        {
            //printf("%s %-5d %s\r" , hostname , i, strerror(errno));
            fflush(stdout);
        }
        //connectée donc afficher les ports ouverts
        else
        {
            printf("%-5d open\n",  i);
        }
        close(sock);
    }

    printf("\r");
    fflush(stdout);
    return(0);
}

int main()
{
    //Thread scan_ipv4_adress
    int err;
    err = pthread_create(&(tid[0]), NULL, &scan_ipv4_adress,NULL);
    if (err != 0)
        printf("\nErreur dans la création du thread :[%s]", strerror(err));
    else
        printf("\n Thread scan_ipv4_adress est bien crée\n");
    sleep(2);
    
    //Thread open_port_scanner
    int err2;
    err2 = pthread_create(&(tid[1]), NULL, &open_port_scanner,NULL);
    if (err2 != 0)
        printf("\nErreur dans la création du thread :[%s]", strerror(err2));
    else
        printf("\n Thread open_port_scanner est bien crée\n");
    sleep(300);
}