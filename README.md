# DS_SR
## Echauffement

Pour cet exercice, la méthode pour trouver le flag est :
* Lancer un: 
``` ltrace ./question1 ```
* Nous pouvons voir en clair : 

```strcmp("L1B3re3", "hjr\n") ```
* Le mot de passe est donc : ```L1B3re3```

## Super Mario

On fait un ltrace ```./peach``` et on obtient sur la première ligne: 

```socket(2, 2, 0)       = 3```

* Sachant que la signature dans le man de socket est : 

```int socket(int domain, int type, int protocol)```

* Le type du protocole est  le 2ème argument, il vaut donc : 2 => SOCK_DGRAM d'après le sock_type.h : 

```SOCK_STREAM = 1,		/* Sequenced, reliable, connection-based
				   byte streams.  */
#define SOCK_STREAM SOCK_STREAM
  SOCK_DGRAM = 2,		/* Connectionless, unreliable datagrams
				   of fixed maximum length.  */
#define SOCK_DGRAM SOCK_DGRAM
```

* Le protocole de niveau 4 utilisé par PEACH est ```UDP```

## Le port épique

Le port utilisé par Peach pour envoyer un message à Luigi est le : ```31984```

En effet, à l'aide de Wireshark, on détecte le paquet UDP envoyé par Peach qui est le suivant :
```
Frame 13: 76 bytes on wire (608 bits), 76 bytes captured (608 bits) on interface 0
Linux cooked capture
Internet Protocol Version 4, Src: 127.0.0.1, Dst: 127.0.0.1
User Datagram Protocol, Src Port: 50546, Dst Port: 31984
    Source Port: 50546
    Destination Port: 31984
    Length: 40
    Checksum: 0xfe3b [unverified]
    [Checksum Status: Unverified]
    [Stream index: 1]
Data (32 bytes)
    Data: 7cf7af4640311b1cb26087f23f48f2cbaa6a6cf8bfcce01c...
    [Length: 32]
```
## Le port salut 

Le port utilisé par Luigi est : ```  41984```

En effet à l'aide de la commande ```"netstat -tupan"``` on détecte le port de la socket ouverte par Luigi"
```
tcp        0      0 0.0.0.0:41984           0.0.0.0:*               LISTEN      25117/./luigi
```
## Same player, play again

Pour cette question, j'ai utilisé l'outil ``` Cutter```

* En lisant le main du code décompilé du binaire ``` question2```, dans le main on peut voir : 
```
0x000011b3      mov     byte [var_97h], 0x47 ; 'G'
0x000011ba      mov     byte [var_96h], 0x75 ; 'u'
0x000011c1      mov     byte [var_95h], 0x31 ; '1'
0x000011c8      mov     byte [var_94h], 0x4e ; 'N'
0x000011cf      mov     byte [var_93h], 0x33 ; '3'
0x000011d6      mov     byte [var_92h], 0x73 ; 's'
0x000011dd      mov     byte [var_91h], 0x53 ; 'S'
```
* Le flag est bien : ```Gu1N3sS```
# Ceci n'est pas une pipe
## Objectif 
Le code qui nous est demandé de créer un code intermédiaire entre Peach et Luigi, il nous faut : 

 * Créer un Serveur UDP sur le port d'envoi de Peach pour lire son message
 * Créer un client TCP qui envoie message au serveur de Luigi pour transferer le message de Peach
 * Recevoir la réponse du serveur de Luigi et l'envoyer à Peach 
 * Récupérer le flag que Peach nous print qui est : ```Je@n a de L0ngues Moustach3s```
