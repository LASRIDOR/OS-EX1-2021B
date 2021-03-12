#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//#include <unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

// *****   declarations of types and constants   *****

typedef long long unsigned int lluint;

typedef int bool;
#define true 1
#define false 0
#define MAX_POLY_NAME 15
#define MAX_COMMAND   10
#define MAX_VERT      8   // maximum number of vertices (8 is for octagon)
#define BYTE 8 


enum POLY_TYPE {TRI = 3, HEXAGON = 6, OCTAGON = 8, BAD_POLY};
enum WHOM_TO_OUTPUT {CURRENT, ALL_POLY, NONE};

typedef struct point {
   int x, y;
}point;

typedef struct polygon {
     enum POLY_TYPE poly_type;
     struct point vertices[MAX_VERT];
     double perimeter;
     double area;
}polygon;

typedef struct Node {
    struct polygon* poly;
    struct Node* next;
}Node;

typedef struct List {
    Node* head;
    Node* tail;
}List;


//**************************** TZVI *********************************
// *****   declarations of function prototypes   *****
void my_exception(int line, const char* function, char* msg);
double calc_side(struct point pt1, struct point pt2);
double calc_triangle_area(struct point p1, struct point p2, struct point p3);
void print_point(struct point pt);
void print_polygon_name(enum POLY_TYPE poly, char* poly_name);

//***************************** DOR *********************************
//////////////list//////////////
List* makeEmptyList();
bool isEmptyList(List* list);
void addToEmptyList(List* list, Node* nodeToAdd);
void addToTail(List* list, Node* nodeToAdd); // assume list is not empty
void freeList(List* list);

//////////////my functions//////////////
bool run_ex1_q1(const char* command, List* polygonsList);
void newPol(const char* command, List* polygonsList);
polygon* createPolFromInput(const char* command);
void makeTriangle(polygon* pol, lluint num1); //4
void makeHexagon(polygon* pol, lluint num1, lluint num2); //6
void makeOctagon(polygon* pol, lluint num1, lluint num2); //8
void calcPolArea(polygon* pol);
void calcPolPerimeter(polygon* pol);
void convertVerticesFromHex(polygon* newPol, lluint numToConvert, int numOfVerticesToRead, int* index);
void printOutPut(const char* command, List* polygonsList);
void printNode(Node* nodeToPrint, bool needToPrintData, bool needToPrintPerimeter, bool needToPrintArea);
bool checkIfCharExist(const char* command, char charToCheck);
bool checkEndOfInput(const char* command);
bool checkNeedToCreateNewPol(const char* command);