#include "ex1_q1.h"

//-----------------------------------------------
void my_exception(int line, const char* function, char* msg)
{
			fprintf(stderr, "ERROR (line %d function: %s) !!!%s\n", line, function, msg);
      exit(1);
}

//-----------------------------------------------
double calc_side(struct point pt1, struct point pt2)
{
	double x = (double) pt1.x - (double) pt2.x;
	double y = (double) pt1.y - (double) pt2.y;
	return sqrt(x*x + y*y);	
}

//-----------------------------------------------
double calc_triangle_area(struct point p1, struct point p2, struct point p3)
{
	double area, 
	      x1 = p1.x, 
	      x2 = p2.x, 
	      x3 = p3.x, 
	      y1 = p1.y, 
	      y2 = p2.y, 
	      y3 = p3.y;		  
	area = 0.5*(x1*y2 + x2*y3 + x3*y1 - x2*y1 - x3*y2 -x1*y3);
	area = (area > 0) ? area : -area;
	return area;
}

//-----------------------------------------------
void print_point(struct point pt)
{
	printf("{%d, %d} ", pt.x, pt.y);
}

//-----------------------------------------------
void print_polygon_name(enum POLY_TYPE poly, char* poly_name)
{
  switch (poly)
  {
    case TRI:     sprintf(poly_name, "triangle"); break;
    case HEXAGON: sprintf(poly_name, "hexagon"); break;
    case OCTAGON: sprintf(poly_name, "octagon"); break;
    default: my_exception(__LINE__, __func__, "bad-polygon_type"); // BAD_POLY
  }
}


///////////////////////////////// DOR ////////////////////////////////////////////

//****************************** List ********************************************
List* makeEmptyList()
{
	List* list = (List*)malloc(sizeof(List));

	if (list != NULL) {
	list->head = NULL;
	list->tail = NULL;
	}

	return list;
}

bool isEmptyList(List* list)
{
	return list->head == NULL;
}

void addToEmptyList(List* list, Node* nodeToAdd)
{
	list->head = nodeToAdd;
	list->tail = nodeToAdd;
}

void addToTail(List* list, Node* nodeToAdd) // assume list is not empty
{
	list->tail->next = nodeToAdd;
	list->tail = nodeToAdd;
}

void freeList(List* list)
{
	Node* currNode = list->head;
	Node* prevNode = list->head;

	while (currNode != NULL)
	{
		prevNode = currNode;
		free(currNode->poly);
		currNode = currNode->next;
		free(prevNode);
	}

	free(list);
}

//*********************************** my func ***************************************

bool run_ex1_q1(const char* command, List* polygonsList)
{
	if (checkNeedToCreateNewPol(command))
		newPol(command, polygonsList);

	printOutPut(command, polygonsList);

	if (checkEndOfInput(command))
		return true;

	return false;
}

void newPol(const char* command, List* polygonsList)
{
	Node* newPol = (Node*)malloc(sizeof(Node));

	if (newPol != NULL) {
		newPol->poly = createPolFromInput(command);
		newPol->next = NULL;
	}


	if (isEmptyList(polygonsList))
	{
		addToEmptyList(polygonsList, newPol);
	}
	else
	{
		addToTail(polygonsList, newPol);
	}
}

polygon* createPolFromInput(const char* command)
{
	int ignore;
	lluint num1;
	lluint num2;
	polygon* pol = (polygon*)malloc(sizeof(polygon));;

	if (checkIfCharExist(command, 'T'))
	{
		ignore = scanf("%llx", &num1);
		makeTriangle(pol, num1);
	}
	else if (checkIfCharExist(command, 'H'))
	{
		ignore = scanf("%llx", &num1);
		ignore = scanf("%llx", &num2);
		makeHexagon(pol, num1, num2);
	}
	else if (checkIfCharExist(command, 'O'))
	{
		ignore = scanf("%llx", &num1);
		ignore = scanf("%llx", &num2);
		makeOctagon(pol, num1, num2);
	}

	calcPolArea(pol);
	calcPolPerimeter(pol);

	return pol;
}

void makeTriangle(polygon* pol, lluint num1){ //3 
	pol->poly_type = TRI;
	int index = 0;
	convertVerticesFromHex(pol, num1, 4, &index);
}

void makeHexagon(polygon* pol, lluint num1, lluint num2) //6
{
	pol->poly_type = HEXAGON;
	int index = 0;
	convertVerticesFromHex(pol, num1, 4, &index);
	convertVerticesFromHex(pol, num2, 2, &index);
}

void makeOctagon(polygon* pol, lluint num1, lluint num2) //8
{
	pol->poly_type = OCTAGON;
	int index = 0;
	convertVerticesFromHex(pol, num1, 4, &index);
	convertVerticesFromHex(pol, num2, 4, &index);
}

void calcPolArea(polygon* pol)
{
	pol->area = 0;
	pol->area += calc_triangle_area(pol->vertices[0], pol->vertices[1], pol->vertices[2]);

	if (pol->poly_type != TRI)
	{
		pol->area += calc_triangle_area(pol->vertices[0], pol->vertices[2], pol->vertices[3]);
		pol->area += calc_triangle_area(pol->vertices[0], pol->vertices[3], pol->vertices[4]);
		pol->area += calc_triangle_area(pol->vertices[0], pol->vertices[4], pol->vertices[5]);
	}
	if (pol->poly_type == OCTAGON)
	{
		pol->area += calc_triangle_area(pol->vertices[0], pol->vertices[5], pol->vertices[6]);
		pol->area += calc_triangle_area(pol->vertices[0], pol->vertices[6], pol->vertices[7]);
	}
}

void calcPolPerimeter(polygon* pol)
{
	pol->perimeter = 0;
	int i, j = 1, sizeOfPol = pol->poly_type - 1;
	for (i = 0; i < (sizeOfPol); i++)
	{
		pol->perimeter += calc_side(pol->vertices[i], pol->vertices[j++]);
	}
	pol->perimeter += calc_side(pol->vertices[i], pol->vertices[0]);
}

void convertVerticesFromHex(polygon* newPol, lluint numToConvert, int numOfVerticesToRead, int* index)
{
	char mask = 0xFF; //1111 1111
	char res = 0;
	lluint tempNumToConvert = numToConvert;

	for (int i = 0; i < numOfVerticesToRead; i++)
	{
		res = mask & tempNumToConvert;
		newPol->vertices[*index].x = res;
		tempNumToConvert = tempNumToConvert >> BYTE;

		res = mask & tempNumToConvert;
		newPol->vertices[*index].y = res;
		tempNumToConvert = tempNumToConvert >> BYTE;

		(*index)++;
	}
}

void printOutPut(const char* command, List* polygonsList)
{
	bool needToPrintData = checkIfCharExist(command, 'd');
	bool needToPrintPerimeter = checkIfCharExist(command, 'p');
	bool needToPrintArea = checkIfCharExist(command, 'a');

	if (checkIfCharExist(command, 'A'))
	{
		Node* currNode = polygonsList->head;
		while (currNode != NULL)
		{
			printNode(currNode, needToPrintData, needToPrintPerimeter, needToPrintArea);
			currNode = currNode->next;
		}
	}
	else if (checkIfCharExist(command, 'C'))
	{
		Node* currNode = polygonsList->tail;
		printNode(currNode, needToPrintData, needToPrintPerimeter, needToPrintArea);
	}
}

void printNode(Node* nodeToPrint, bool needToPrintData, bool needToPrintPerimeter, bool needToPrintArea)
{
	if (needToPrintData)
	{
		char polyType[15];
		print_polygon_name(nodeToPrint->poly->poly_type, polyType);
		printf("%s ", polyType);
		for (int i = 0; i < nodeToPrint->poly->poly_type; i++)
		{
			print_point(nodeToPrint->poly->vertices[i]);
		}
		printf("\n");
	}
	if (needToPrintPerimeter)
	{
		printf("perimeter = %.1f \n", nodeToPrint->poly->perimeter);
	}
	if (needToPrintArea)
	{
		printf("area = %.1f \n", nodeToPrint->poly->area);
	}
}

bool checkIfCharExist(const char* command, char charToCheck)
{
	char* result = strchr(command, charToCheck);

	if (result != NULL)
		return true;

	return false;
}

bool checkEndOfInput(const char* command)
{
	return checkIfCharExist(command, 'L');
}

bool checkNeedToCreateNewPol(const char* command)
{
	return checkIfCharExist(command, 'N');
}