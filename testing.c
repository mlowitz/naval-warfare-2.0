//
//  battleship.c
//  battleship_over_tux
//
//  Created by Ian Shinbrot on 1/28/14.
//  Copyright (c) 2014 rumford. All rights reserved.
//

#include <stdio.h>
#include "battleship_header.h"


int IP = 0;
int sockfd = 0, n = 0;
char Buff[6];
struct sockaddr_in serv_addr;
char rBuff[1];


int       conn_s;                /*  connection socket         */
short int port;                  /*  port number               */
struct    sockaddr_in servaddr;  /*  socket address structure  */
char     *szAddress;             /*  Holds remote IP address   */
char     *szPort;                /*  Holds remote port         */
char     *endptr;                /*  for strtol()              */
int play_num;
char ** bat, ** searchBoard;
bool started=false;
int p1=0;
int p2=0;
int p3=0;
int p4=0;




bool shipexists()
{
    return true;
}

bool hitpiece()
{
    return true;
}
/*
 This function converts a character containing input to the enumerated type.
 I used an enumerated type to make the code easier to read
 */
enum row convert(char * letter)
{
    enum row y;
    if (WordExists("A",letter))
    {
        y=a;
    }
    if (WordExists("B", letter))
    {
        y=b;
    }
    if (WordExists("C", letter))
    {
        y=c;
    }
    if (WordExists("D", letter))
    {
        y=d;
    }
    if (WordExists("E", letter))
    {
        y=e;
    }
    if (WordExists("F", letter))
    {
        y=f;
    }
    if (WordExists("G", letter))
    {
        y=g;
    }
    if (WordExists("H", letter))
    {
        y=h;
    }
    if (WordExists("I", letter))
    {
        y=i;
    }
    if (WordExists("J", letter))
    {
        y=j;
    }
    return y;
}
/*
 This function is used to determine if the placement is valid
 */
bool placevalid(int x, int y, bool is_vertical, int length, char ** board)
{
   
    if (is_vertical)                        // if the orientation is vertical
    {
        if (OutofBounds(x, y+length))       // determines if the ship will be out of bounds
        {
            return  false;
        }
        int ii;
        for ( ii=y; ii<y+length; ii++)
        {
          
            if (board[ii][x]!='-')
            return false;
            else
            {
              board[ii][x]=length;
                Buff[0]='W';
					 Buff[1]=length;
                Buff[2]=ii;
                Buff[3]=x;
					 Buff[4]='P';
                Buff[5]=play_num;
                Writeline(sockfd, Buff, 6);
                
            }
        }
    }
    else if (!is_vertical)                       // if the orientation is horizontal
    {
        if (OutofBounds(x+length,y))
        {
            return false;
        }
        int ii;
        for (ii=x; ii<x+length; ii++)   // determines if the ship will be out of bounds
        {
            
            if (board[y][ii]!='-')
            return false;
            else board[y][ii]=length;
            Buff[0]='W';
            Buff[1]=y;
            Buff[2]=ii;
            Buff[3]=play_num;
            Writeline(sockfd, Buff, strlen(Buff));
        }
    }
    return true;
}
void placePiece_Begin(bool is_vertical, char ** board, int length)
{
    int x ;
    enum row y;
    char *letter = malloc(sizeof(char)*1);
    bool placed=false;
    
    printf("Please pick the coordinates that you would like to place your piece at (in the format of A #: ");
    scanf("%s", letter);
    
    
    scanf("%d", &x);
    
    y = convert(letter);
    
    
    while (!placed)                             // determines if a piece has been placed
    {
        if (placevalid(x,y,is_vertical, length, board))
        {
            if (!is_vertical)               // determines if artifact will be vertical
                    {
                        int jj;
                    for ( jj = x; jj<x+length; jj++)
                    {
                        placed=true;
                        board[y][jj] = length+48;
                    }
                    }
            
                else if (is_vertical)
                    {
                        int jj;
                    for (jj = y; jj<y+length; jj++)
                    {
                        placed=true;
                        board[jj][x] = length+48;
                        }
                    
                    }
        }
        else
        {
            printf("Those coordinates didn't work. Please try picking the coordinates again (in the format of A #: ");
            scanf("%s", letter);
             scanf("%d", &x);
            
            y = convert(letter);
            }
        }

}
/*
 allows you to pick pieces from a board
 board is the matrix created
 */
void PickPiece(char ** board)
{
    int piece =0;           // number as defined in menu
    bool is_vertical;
    int num_picked=0;
  
    bool orientation=false;
    bool piece1=false,piece2=false,piece3=false,piece4=false,piece5=false;
    char *response = malloc(Ship_Size);
    
    printf("Please type the number of the piece that you would like to place?\n");
   
    while (num_picked<5)
    {
         orientation=false;
        displayBoard(board);
        if (!piece1)
        printf("1: AIRCRAFT\n");
        if (!piece2)
        printf("2: BATTLESHIP \n");
        if (!piece3)
         printf("3: SUBMARINE \n");
        if (!piece4)
              printf("4: DESTROYER \n");
        if (!piece5)
        printf("5: PATROL BOAT \n");
       //  scanf("%d", &piece);
        while (!(( !piece1 && piece==1) || (!piece2 && piece==2) || (!piece3 && piece==3) || (!piece4 && piece==4) || (!piece5 && piece==5)))
        {
            printf("please type a valid piece\n");
             scanf("%d", &piece);
        }
 
       
        if (piece==1)
        {
            piece1=true;
            num_picked++;
          
        }
        if (piece==2)
        {
            piece2=true;
            num_picked++;
           
        }
        if (piece==3)
        {
            piece3=true;
            num_picked++;
        
        }
        if (piece==4)
        {
            piece4=true;
            num_picked++;
    
        }
        if (piece==5)
        {
            piece5=true;
            num_picked++;
        }
        
        int size=0;
    
    
    
        do
           {
               printf("What orientation would you like to have the piece (vertical/horizontal)\n");
               scanf("%s", response);
           
               if (WordExists(response, "horizontal"))
               {
                   orientation=true;
                   is_vertical=false;
               }
               else if (WordExists(response, "vertical"))
               {
                   orientation=true;
                   is_vertical=true;
               }
    }while (!orientation);
    
        switch (piece)
        {
            case 1:     // aircraft picked
            size=5;
            break;
        
            case 2:     // battleship picked
            size=4;
            break;
        
            case 3:     // submarine picked
            size=3;
            break;
        
            case 4:     // destroyer picked
            size=3;
            break;
        
            case 5:     // patrol boat picked
                size=2;
            break;
        }
        placePiece_Begin(is_vertical, board, size);
    }
    displayBoard(board);
}

char ** newBoard()      // creates a matrix initializing everything to a
{
    char ** matrix;
    
    matrix = (char**)malloc(sizeof(char*)*10);
    int i;
    for (i=0; i<10;i++)
    {
        
        matrix[i] = (char*)malloc(sizeof(char));
        int j;
        for (j=0;j<10;j++)
        {
            matrix[i][j]=(char)malloc(sizeof(char)*1);
            matrix[i][j]='-';
        }
    }
    return matrix;
    
}
bool WordExists(char word[32], char *letter)
{
    if (strcmp(letter, word) == 0)
    return true;
    else return false;
}

bool OutofBounds(int x, int y)
{
    if (x>10 || y>10)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool PieceExists(int y, int x)
{
    int checkp;
    if (play_num==2)
    {
        checkp=1;
    }
    else if (play_num==1)
    {
        checkp=2;
    }
    else{                                   // this code will never run. I got issues if I didn't include
        printf("invalid number, try again");
  //      return false;;
    }
    Buff[0] = 'R';
	 Buff[1]= '0';
    Buff[2] = y;
    Buff[3] =x;
    Buff[5]=checkp;
    Buff[4]='P'; 
    if (searchBoard[x][y]!='-')
        return true;
    //Writeline(sockfd,Buff, 6); 
    // close(sockfd);
	 bzero(rBuff, 1);
	 //n =  Readline(sockfd, rBuff, 1);
	 morris();
	 if (n < 0)
			printf("error");
		close(sockfd);
		
    if (rBuff[0]!=0)
    {
        if (Buff[0]==1)
        {
            p1++;
        }
        if (Buff[0]==2)
        {
            p2++;
        }
        if (Buff[0]==3)
        {
            p3++;
        }
        if (Buff[0]==4)
        {
            p4++;
        }
        return true;
    }
    else return false;
}
ssize_t Readline(int sockd,char Buff, int maxlen) {
    ssize_t n, rc;
    char    c,* buffer;
   if (sockfd = socket(AF_INET, SOCK_STREAM, 0) <0)
	  	{
			printf("\n didn't create socket");
		return 1;
		}

serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(5001);

	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <
			0)
	{printf("\n Error: Connect failed \n");
		return 1;
	}

    
    for ( n = 1; n < maxlen; n++ ) {
        
        if ( (rc = read(sockd, &c, 1)) == 1 ) {
            *buffer++ = c;
            if ( c == '\n' )
            break;
        }
        else if ( rc == 0 ) {
            if ( n == 1 )
            return 0;
            else
            break;
        }
        else {
            if ( errno == EINTR )
            continue;
            return -1;
        }
    }
    
    *buffer = 0;
    return n;
}
ssize_t Writeline(int sockd, char  Buffk, int n) {
    int      nleft;
    ssize_t     nwritten;
    const char *buffer;
    
    nleft  = n;
    
     {
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                printf("\n Error : Could not create socket \n");
                return 1;
            }
            
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(5001);
            
            if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            {
                printf("\n Error : Connect Failed \n");
                return 1;
            }


        if ( (nwritten = write(sockd, Buff, nleft)) <= 0 ) {
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

bool attackBoard(char ** searchBoard)        // x and y are coordinates
{
    
    int x ;
    enum row y;
    char *letter = malloc(sizeof(char)*1);
    int hit = 43;
    bool placed=false;
    
    do {
        printf("Please pick the coordinates that you would like to guess (in the format of A #: ");
        scanf("%s", letter);
    
    
        scanf("%d", &x);
    
    
        y = convert(letter);
    
        if (!OutofBounds(x,y))
        {
            if (searchBoard[x][y]=='-') // not guessed yet
            {
                if (PieceExists(y, x))
                {
                
                searchBoard[y][x]=hit;
                placed=true;
                Buff[0]='R';
                Buff[1]='0';
		Buff[3]=x;
                Buff[2]=y;
                Buff[5]=play_num;
                Buff[4]='P';
		placed=true;
                //Writeline(sockfd, Buff, strlen(Buff));
                morris();
                return true;
                }
                else
                {
                    //searchBoard[x][y]='+';
                    return false;
                }
            }
        }
    }
        while (placed==false);
    return false;
}
void checkifShipSank()
{
    
}
void displayBoard(char ** board)
{
    printf("\n   ");
    int k;
    for ( k = 0;k < 10; k++)
    printf("%d  ", k);
    printf("\n");
    int i;
    // print rows of holes, with letters in leftmost column
    for ( i = 0; i < 10; i++)
    {
        printf("%c  ", 'A' + i);
        int j;
        for (j = 0; j < 10; j++)
        printf("%c  ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}
void deleteBoard(char **board)
{
    int i;
    for ( i=0; i<10;i++)
    {
        free(board[i]);
    }
     free(board);
}
int displayMenu()
{
    
    bat = newBoard();     // initialize board
    
    searchBoard = newBoard();
    int num=0;
      searchBoard = newBoard();    // that is the board the computer will see
    do
    {
    
    
    printf("Please select an option.\n");
    printf("1: Start a new Game\n");
    printf("2: Display Board\n");
    printf("3: Attack\n");
    printf("4: Cancel Game\n");
    printf("5: Quit\n\n\n");
    
    scanf("%d", &num);

        if (p1==1 && p2==2 && p3==3 && p4==4)
        {
            exit(0);
        }
    if (num==1 && !started)
    {
        started=true;
        // print top row of numbers
        PickPiece(bat);                   // this will allow you to select the ships
        // return contents;
        
    }
        if (num==1 && started)
        {
        printf("You started a game. One game can be played at a time");
        }
    else if (num==2 && started)
    {
        displayBoard(searchBoard);
    }
    else if (num==2)
    {
        printf("You have not started the game yet. Please start the game\n");
    }
    else if (num==3 && started)
    {
        attackBoard(searchBoard);
    }
    else if (num==4 && started)
    {
        deleteBoard(bat);
        deleteBoard(searchBoard);
        return 0;
    }
    else if (num==4)
    {
        return 0;       // return to server menu
    }
    
    else if (num==4)
    {
        deleteBoard(bat);
        deleteBoard(searchBoard);
        exit(0);
    }
    else{
        printf("Your answer was unrecognizable. Please try again\n\n\n");
    }
    } while (  num<4);
    return num;
}
int startGame(void);
int startGame(void)
{
    
    int num;
    
    do {
        num=displayMenu();
    } while (num==2);
    num = displayMenu();
    return num;
}
int MainMenu()
{
    
    int response=0;
    
    do
    {
        printf("Please select an option.\n");
        printf("1: Start a new Server\n");
        printf("2: Join Server\n");
        printf("3: Display the introduction again\n");
        printf("4: Quit\n\n\n");
        
    }
    while (response>5 || response<0);
    
    scanf("%d", &response);
    
    return response;
}
void introduction()
{
    printf("Welcome to the game battleship. This will be played over tux.\n");
    printf("First, you will be prompted where to select your ships.\n");
    printf("Then you will begin the game. Just select where to hit the pieces\n");
    printf("The menu will display now\n\n\n");
}

int main(int argc, const char * argv[])
{
    
    int num;
    introduction();
 
    

    pid_t t;
    
    do
    {
        num = MainMenu();
        if (num==1)
        {
            play_num=1;
            // start server function
            
           // server_fun();
            IP=atoi("127.0.0.1");
            
            
            if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                printf("\n Error : Could not create socket \n");
                return 1;
            }
            
				memset(&serv_addr, 0, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(5001);
            
            if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            {
                printf("\n Error : Connect Failed \n");
                return 1;
            }
            
           /* while ( (n = read(sockfd, Buff, sizeof(Buff)-1)) > 0)
            {
                Buff[n] = 0;
                if(fputs(Buff, stdout) == EOF)
                {
                    printf("\n Error : Fputs error\n");
                }
            }*/
        
        // make IP Address 127.0.0.1
        
        startGame();
        }
        
        if (num==2)
        {
            printf("Please enter an IP Address\n");
            
            scanf(" %d", &IP);
            while (isdigit(IP) && IP>0)        // has some isues
            {
                printf("Please enter an IP Address\n");
                
                scanf(" %d", &IP);
            }
            play_num=2;
            
            
            memset(Buff, '0',sizeof(Buff));
            if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            {
                printf("\n Error : Could not create socket \n");
                return 1;
            }
            
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(5000);
            
            if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
            {
                printf("\n Error : Connect Failed \n");
                return 1;
            }
            
            while ( (n = read(sockfd, Buff, sizeof(Buff)-1)) > 0)
            {
                Buff[n] = 0;
                if(fputs(Buff, stdout) == EOF)
                {
                    printf("\n Error : Fputs error\n");
                }
            }
            
            
            
            // join server function
            // join host
        }
        
        /*  Set the remote port  */
        
        port = strtol(szPort, &endptr, 0);      // unrecognizable function
        if ( *endptr ) {
            printf("ECHOCLNT: Invalid port supplied.\n");
            exit(EXIT_FAILURE);
        }
        
        
        /*  Create the listening socket  */
        
        if ( (conn_s = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
            fprintf(stderr, "ECHOCLNT: Error creating listening socket.\n");
            exit(EXIT_FAILURE);
        }
        
        
        /*  Set all bytes in socket address structure to
         zero, and fill in the relevant data members   */
        
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family      = AF_INET;
        servaddr.sin_port        = htons(port);
        
        
        /*  Set the remote IP address  */
        
        if ( inet_aton(szAddress, &servaddr.sin_addr) <= 0 ) {
            printf("ECHOCLNT: Invalid remote IP address.\n");
            exit(EXIT_FAILURE);
        }
        
        
        /*  connect() to the remote echo server  */
        
        if ( connect(conn_s, (struct sockaddr *) &servaddr, sizeof(servaddr) ) < 0 ) {
            printf("ECHOCLNT: Error calling connect()\n");
            exit(EXIT_FAILURE);
        }
        
        if (num==3)
        {
            introduction();
        }
        
    } while(num<4);
    
    
    return 0;
}


void morris()
{
  int sock;                        /* Socket descriptor */
  struct sockaddr_in echoServAddr; /* Echo server address */
  unsigned short echoServPort;     /* Echo server port */
  char *servIP;                    /* Server IP address (dotted quad) */
  char *echoString;                /* String to send to echo server */
  char echoBuffer[6];     /* Buffer for echo string */
  unsigned int echoStringLen;      /* Length of string to echo */
  int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv() 
				      and total bytes read */

  

  servIP = "127.0.0.1";             /* First arg: server IP address (dotted quad) */
  //  echoString = argv[2];         /* Second arg: string to echo */

  

  /* Create a reliable, stream socket using TCP */
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    printf("socket() failed");

  /* Construct the server address structure */
  memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
  echoServAddr.sin_family      = AF_INET;             /* Internet address family */
  echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
  echoServAddr.sin_port        = htons(5001); /* Server port */

  /* Establish the connection to the echo server */
  if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
    printf("connect() failed");

  echoStringLen = 6;          /* Determine input length */

  /* Send the string to the server */
  if (send(sock, Buff, echoStringLen, 0) != echoStringLen)
    printf("send() sent a different number of bytes than expected");

  /* Receive the same string back from the server */
  totalBytesRcvd = 0;
  printf("Received: ");                /* Setup to print the echoed string */
  while (totalBytesRcvd < echoStringLen)
    {
      /* Receive up to the buffer size (minus 1 to leave space for
	 a null terminator) bytes from the sender */
      if ((bytesRcvd = recv(sock, rBuff, 3 - 1, 0)) <= 0)
	//DieWithError("recv() failed or connection closed prematurely");
      totalBytesRcvd += bytesRcvd;   /* Keep tally of total bytes */
      echoBuffer[bytesRcvd] = '\0';  /* Terminate the string! */
      printf("%s", rBuff);      /* Print the echo buffer */
    }

  

  close(sock);
  
}
