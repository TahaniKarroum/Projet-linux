
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main()
{ int st,af,type,prot;
int fin = 0;
int portserveur;
int s;
struct sockaddr_in serveur;
char * adrserveur;
struct sockaddr name;
int lgname;
char * mes;
adrserveur = (char *) malloc(32);
mes = (char *) malloc(256);
printf("Client Projet Tahani Abdallah Karroum\n");
printf("Entrer l'@ du serveur (x.x.x.x):\n");
do {
scanf("%s",adrserveur);
// "inet_aton" Convertit les adresses IP à partir d'une chaîne de points et numéros à un in_addr struct et retour.
if (inet_aton(adrserveur, &serveur.sin_addr)!=0)// il doit retourner une valeur differente que 0.
fin=2;
else
printf("@ incorecte, recommencer ou fin pour terminer: ");
} while (fin==0);
if (fin==2) {
printf("Entrer le numero de port du serveur:\n");
scanf("%d",&portserveur);
printf("\n Create socket\n");
s = socket (AF_INET,SOCK_STREAM,IPPROTO_TCP); // creation du socket.
if (s==-1) {
printf("Il ya un erreur en creation du socket, impossible de continuer \n");
return (-1);
}
printf ("Demande de connexion \n");
serveur.sin_family = AF_INET;
serveur.sin_port = htons(portserveur); // host to network short
st = connect(s,(const struct sockaddr *)&serveur,sizeof(serveur));
if (st!=0) {
printf("Connexion refuse\n\n");
return (-1);
}
printf("\nConnexion a etablie\nattendre un message de hello\n");
st = recv(s,&mes[0],256,0);
if (st > 0) {
mes[st] = 0;
printf("Message recu: %s\n",mes);
}
else if(st<0) {
printf ("Erreur dans la fonction recv.");
return(-1);
}
// la connexion est etablie; phase de dialogue
do {
printf("Veuillez entrer un message afin d´envoyer au serveur ou 'fin' pour terminer:\n");
scanf("%s",mes);
st = send(s,mes,strlen(mes),0);
if (st!=strlen(mes))
printf("le message n'est pas envoye en entier ou La connexion est coupee ");
else {
printf("Message a envoye, attente la reponse du serveur\n");
st = recv(s,&mes[0],256,0);
if (st > 0) {
mes[st] = 0;
printf("Reponse du serveur: %s\n",mes);
}
else printf("PB dans la reception de la reponse du serveur. %d",st);
}
}while (strcmp(mes,"fin")!=0);
}
}
