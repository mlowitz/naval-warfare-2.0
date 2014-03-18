//
//  battleship_header.h
//  battleship_over_tux
//
//  Created by Ian Shinbrot on 2/24/14.
//  Copyright (c) 2014 rumford. All rights reserved.
//


#ifndef battleship_over_tux_battleship_header_h
#define battleship_over_tux_battleship_header_h

#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
//#include "boardserver.c"

#define Ship_Size 10

enum ship_piece {patrol_boat=5, destroyer=4, submarine=3,battleship=2,aircraft_carrier=1};
enum row {a=0, b=1, c=2, d=3, e=4, f=5, g=6, h=7, i=8, j=9};
enum shipType {water=00, ship1=02, ship3=04, ship4=05, ship5=06};

char ** newBoard() ;
bool attackBoard(char ** searchBoard);
bool OutofBounds(int x, int y);
bool WordExists(char word[32], char *letter);
void displayBoard(char ** board);
ssize_t Writeline(int sockd, char Buff, int n);
ssize_t Readline(int sockd, char Buff, int n);
void introduction();
void morris();
#endif
