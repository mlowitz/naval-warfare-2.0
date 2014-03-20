
#ifndef serverFunctions
#define serverFunctions

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
//#include "server_functions.h"
#define BUFSIZE 6
char shipnum[2];
char player_num[2];
char buf[BUFSIZE]; /* message buffer */
char position[2];
char rBuff[1];
#if 0
/*
 * Structs exported from netinet/in.h (for easy reference)
 */

/* Internet address */
struct in_addr {
	unsigned int s_addr;
};

/* Internet style socket address */
struct sockaddr_in  {
	unsigned short int sin_family; /* Address family */
	unsigned short int sin_port;   /* Port number */
	struct in_addr sin_addr;	 /* IP address */
	unsigned char sin_zero[...];   /* Pad to size of 'struct sockaddr' */
};

/*
 * Struct exported from netdb.h
 */

/* Domain name service (DNS) host entry */
struct hostent {
	char    *h_name;        /* official name of host */
	char    **h_aliases;    /* alias list */
	int     h_addrtype;     /* host address type */
	int     h_length;       /* length of address */
	char    **h_addr_list;  /* list of addresses */
}

#endif
#define BOARD_MAX_position 50
struct square {
    char *position;
    char * P1;
    char * P2;
    struct square *nxt;
};

typedef struct board {
    struct square **tbl;
    int size;
} board;

/*
 * error - wrapper for perror
 */

int  _hash()
{
    /*
     *program hashes using sum of charters in word from 1-26
     */
    
  int a = (position[0]) + 10;
  int b = (position[1]) + 10;
  int c = 100*a +b;

  //unsigned long hash=wordToInt(position);
    
    
    return c;
    
}
void board_add(board *board)
{
    if (!board) return;
    
    int idx =_hash();
    struct square *n = board->tbl[idx];
    while (n) {
        if (strcmp(position, n->position) == 0) {
            n->position = calloc(1, strlen(position) + 1);
            if(player_num[1]=='1')
            {
                n->P1= calloc(1, strlen(shipnum)
                              + 1);//creates plaer 1
                strcpy(n->P1,shipnum[0]);
            }
            if(player_num[1]=='2')
            {
                n->P2= calloc(1,
                              strlen(shipnum) +1);
                strcpy(n->P2,shipnum[0]);
            }
            
            break;
        }
        
        
        n = n->nxt;
    }
}
void parsePosition()
{
    position[0] = buf[2];
    position[1] = buf[3];
    
    
}

void playerNum()
{
    player_num[0] = buf[4];
    player_num[1] = buf[5];
    
}

void shipNum()
{
    shipnum[0]=buf[1];
}






struct board *board_create(int size)
{
    /*
     *program creates hash tables
     
     */
    board *board = malloc(sizeof(struct board)*size);
    
    board->size = size;
    
    board->tbl = calloc(1, size * sizeof(struct square *));
    
    return board;
}
//free memory from hash table

/*
 void board_destroy(board *board)
 {
 if (!board) return;
 
 int i;
 for (i = 0; i < board->size; i++) {
 struct square *n = board->tbl[i];
 while (n) {
 struct square *n_old = n;
 
 n = n->nxt;
 
 free(n_old->position);
 n_old->position = NULL;
 free(n_old);
 n_old = NULL;
 }
 }
 
 free(board->tbl);
 free(board);
 
 board = NULL;
 }
 */

//will fetch and print entire linked list from hashvalue
void  board_get(board *board)
{
    if (!board) return NULL;
	 int idx = _hash();
	 if (!board->tbl[idx])
	 { rBuff[0]='0';
		 return; }
    
     idx = _hash();
     int val;
    struct square *n = board->tbl[idx];
    /* while (n) {
     return n->val;
     n = n->nxt;*/
    if (player_num[1]=='\002')
    {
		 if (!n->P2)
			 rBuff[0]= '0';
		 else{
		   rBuff[0]= n->P2[0];
		   // rBuff[0]=val+P3;
		 }
    }
    else if(player_num[1]=='\001')
    {
		 if (!n->P1)
			 rBuff[0]='0';
		 else{
		   //val=n->P1;
			 rBuff[0] = n->P1[0];
		     //  rBuff[0]=n->P1 + 3;
		 }
       //retrun player 2
    }
    
    else
        rBuff[0]='0';
}
//will fetch linked list same as board_get but will scan for false positives
void *ana_get(board *board, char *position)
{
    /*  if (!board) return NULL;
     
     dx = _hash(position) % board->size;
     
     struct board_node *n = board->tbl[idx];
     /* while (n) {
     return n->val;
     n = n->nxt;
     }
     while (n) {
     
     if (match(position,n->val)){
     printf("%s\n",n->val) ;}
     n = n->nxt;
     //return list->str;
     
     }*/
    return NULL;
}



//function to add to hasboardable
void board_put(board *board)
{
    if (!board) return;
    
    int  idx =_hash();
    if(!board->tbl[idx]){
        struct square *n_new = calloc(1, sizeof(struct square));
        n_new->position = calloc(1, strlen(position)+1);
        strncpy(n_new->position,position,2);
        if(player_num[1]=='\001')
        {
            n_new->P1= calloc(1, strlen(shipnum) +
                              1);//creates plaer 1
            strcpy(n_new->P1,shipnum);
        }
        if(player_num[1]=='\002')
        {
            n_new->P2= calloc(1, strlen(shipnum)
                              +1);
            strcpy(n_new->P2,shipnum);
        }
        
        n_new->nxt = board->tbl[idx];
        board->tbl[idx] = n_new;}
    else
        board_add(board);
}
//adds players ship  to already existing square.



int CharToInt(char c) {
    if(!isalpha(c))
    {return 0;}
    c = tolower(c);
    int x = (int) c - (int) 'a';
    return x + 1;
}

int wordToInt(char* s){
    int x=0; // return val of word
    int l = strlen(s);
    int i;
    for (i=0; i<l; i++)
    {
        if(s[i]!= '\n'){
            if(s[i]==' '){i++;}
            x=x+CharToInt(s[i]);
        }
    }
    //printf("%d",x);
    //printf("%s\n",s);
    return x;
    
}
void error(char *msg) {
	perror(msg);
	exit(1);
}
ssize_t Writeline(int sockd, char Buffk, int n) {
	    int     nleft;
		 ssize_t     nwritten;
		 const char *buffer;

					    
	    nleft  = n;


		    while ( nleft > 0 ) {
				if ( (nwritten = write(sockd, buffer,nleft)) <= 0 ) {
				if ( errno == EINTR )
						nwritten = 0;
				 	   else
				 		return -1;
				 	}
						nleft  -= nwritten;
						buffer += nwritten;
					 }

				    return n;
}


int  main() {
	int listenfd; /* listening socket */
	int connfd; /* connection socket */
	int portno; /* port to listen on */
	int clientlen; /* byte size of client's address */
	struct sockaddr_in serveraddr; /* server's addr */
	struct sockaddr_in clientaddr; /* client addr */
	struct hostent *hostp; /* client host info */
	
	char *hostaddrp; /* dotted decimal host addr string */
	int optval; /* flag value for setsockopt */
	int n; /* message byte size */
    
	//if (fork() ==0)
	// {
	/* check command line args */
	//setsockopt(SO_REUSEADDR);
	portno = 5001;
    
	/* socket: create a socket */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
		error("ERROR opening socket");
    
	/* setsockopt: Handy debugging trick that lets
     * us rerun the server immediately after we kill it;
     * otherwise we have to wait about 20 secs.
     * Eliminates "ERROR on binding: Address already in use" error.
     */
	optval = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
               (const void *)&optval, sizeof(int));
    
	/* build the server's internet address */
	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET; /* we are using the Internet */
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); /* accept reqs to any IP addr */
	serveraddr.sin_port = htons((unsigned short)portno); /* port to listen on */
	
	/*if ( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 )
     {
     perror("setsockopt");
     }
     
     if ( bind(sockfd, (struct sockaddr*)&svr, sizeof(svr) ) == -1 )
     {
     perror("server: bind");
     }
	 bind: associate the listening socket with a port */
	if (bind(listenfd, (struct sockaddr *) &serveraddr,
             sizeof(serveraddr)) < 0)
		error("ERROR on binding");
    
	/* listen: make it a listening socket ready to accept connection requests */
	if (listen(listenfd, 25) < 0) /* allow 5 requests to queue up */
		error("ERROR on listen");
    
	/* main loop: wait for a connection request, echo input line,
     then close connection. */
	clientlen = sizeof(clientaddr);
	board *board = board_create(16777216);
	while (1) {
        
        
		
        
		/* accept: wait for a connection request */
		connfd = accept(listenfd, (struct sockaddr *) &clientaddr, &clientlen);
		if (connfd < 0)
			error("ERROR on accept");
        
		/* gethostbyaddr: determine who sent the message */
		hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                              sizeof(clientaddr.sin_addr.s_addr), AF_INET);
		if (hostp == NULL)
			error("ERROR on gethostbyaddr");
		hostaddrp = inet_ntoa(clientaddr.sin_addr);
		if (hostaddrp == NULL)
			error("ERROR on inet_ntoa\n");
		printf("server established connection with %s (%s)\n",
               hostp->h_name, hostaddrp);
        
        
		/* read: read input string from the client */
		bzero(buf, BUFSIZE);
		n = read(connfd, buf, BUFSIZE);
		if (n < 0)
			error("ERROR reading from socket");
		printf("server received %d bytes: %s\n", n, buf);
		//data to be sent to server in format
		//[R/W]XYP[1/2]
		/*if sent data is enter*/
		if (buf[0] == 'W')
		{
			/*
             *function to place peice in server
             */
            //  char* player=malloc(2*sizeof(char*));
            //char* positon=malloc(2*sizeof(char*));
            //char* ship = malloc(1*sizeof(char*));
            
			playerNum();//get player number
            parsePosition();//get position
            shipNum();
			board_put(board);
			
            
			
		}
        
		else if(buf[0] == 'R')
		{
			/*
             *function to read from server
             */
            playerNum(buf);//get player number
            parsePosition(buf);//get position
             board_get(board);
			
		

		
				//retrun error in reading from server
	     printf("\n sent back %s\n",rBuff);
		n = write(connfd, rBuff, 2);














		if (n < 0)
			error("ERROR writing to socket");
		}   
		//close(connfd);
	}
	//}
	//else{
	
	//}
}



#endif

