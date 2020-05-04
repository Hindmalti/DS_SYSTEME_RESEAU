#ifndef MARIO_H
#define MARIO_H


#define PEACH_PORT 31984
#define LUIGI_PORT 41984
#define MAXLINE 10000

int ecoutePeach();
int envoieLuigi(char *payload, int taille);
int envoiePeach(char *payload, int taille);
#endif