#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


//Method declarations
void lit(int i);      //creates a new node and puts it on the list
void printList();
void out();             //Pops the top integer from the list and prints it
void swap();            //Swaps the top two nodes in the list
void dup(int n);        //Duplicates the top n elements of the list (dup 2: A B... A B A B)
void in();              //Reads the next integer from the console and pushes it to the list
void drop();     //Pops the top element of the list and returns it
void add();             //Adds the top two elements in the list and pushes the result to the list
void subtrc();         //Subtracts top two elements in the list and pushes the result
void mult();
void DIV();
void mod();
void and();
void or();
void jump();
void ifeq();
void iflt();

//Globals
int counter;
char* ptr;
char* ptr2;

void main() {

    FILE *myFile;
    char str[500];

//Reads the first line of the input file
    myFile = fopen("instructions.txt", "r");
    fgets(str, 500, myFile);

//Puts line one as the array size
    char* num1;
    num1 = strstr(str, &str[0]);
    int arraySize = atoi(num1);
    char array[arraySize][100];

//Reads each line
    for (int i = 0; i < arraySize; i++) {
        fgets(str, 500, myFile);
        strcpy(array[i], str);
    }
    fclose(myFile);

//Conditionals for instructions
 for(counter = 0; counter < arraySize; counter++){
      ptr = array[counter];
      ptr2 = strtok(ptr, "\n");

     if(strcmp(ptr2, "IN") == 0){
         //IN case
         in();
     } else if(strncmp(ptr2, "LIT", 3) == 0){
         //LIT case
         char* num;
         num = strstr(ptr2, &ptr[4]);
         lit(atoi(num));
     }else if(strcmp(ptr2, "OUT") == 0){
         //OUT case
         out();
     } else if(strcmp(ptr2, "DROP") == 0){
         //DROP case
         drop();
     } else if(strncmp(ptr2, "DUP", 3) == 0){
         //DUP case
         char* number;
         number = strstr(ptr2, &ptr[4]);
         dup(atoi(number));
     } else if(strcmp(ptr2, "SWAP") == 0){
         //SWAP case
        swap();
     } else if(strcmp(ptr2, "ADD") == 0){
         //ADD case
         add();
     } else if(strcmp(ptr2, "SUB") == 0){
         //SUB case
         subtrc();
     } else if(strcmp(ptr2, "MUL") == 0){
         //MUL case
         mult();
     } else if(strcmp(ptr2, "DIV") == 0){
         //DIV case
         DIV();
     } else if(strcmp(ptr2, "MOD") == 0){
         //MOD case
         mod();
     } else if(strcmp(ptr2, "AND") ==0){
         //AND case
         and();
     } else if(strcmp(ptr2, "OR") == 0){
         //OR case
         or();
     } else if(strncmp(ptr2, "JUMP", 4) == 0){
         //JUMP case
            jump();
     } else if(strncmp(ptr2, "IFEQ", 4) == 0){
         //IFEQ case
         ifeq();
     } else if(strncmp(ptr2, "IFLT", 4) == 0){
         iflt();
     }
 }
printList();
}

//Struct for a node
struct node {
    int value;
    struct node *next;
};

struct node *head = NULL;


void lit(int value) {
    //Creates a node
    struct node *Node = (struct node*) malloc(sizeof(struct node));
    Node->value = value;

    //Point to old node
    Node->next = head;
    //Point to the new first node
    head = Node;
}

//Prints out each node in the list
void printList() {
    struct node *ptr4 = head;

    while(ptr4 !=NULL){
        printf("[%d]\n", ptr4->value);
        ptr4 = ptr4 ->next;
    }

}

//Removes the top integer from the list and prints it
//Instruction called "OUT" in project 1
void out(){
    struct node Node;
    //If the node is empty
    if(head == NULL){
        printf("The list is empty\n");
    } else{
        //pointer to original head node
        struct node *tempHead = head;

        //Node being removed
        int temp = head->value;

        //Head set to neighbor node
        head = head->next;

        free(tempHead);
        printf("The value removed is [%d]\n", temp);

    }
}

//Swaps the top two elements of the stack
void swap() {
    //If the node is empty
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
        //References nodes
        struct node *node1 = head;
        struct node *node2 = head->next;

        //Points the head to the second node
        head = node2;

        //Points next of the first node to the next node of the head
        node1->next = head->next;

        //Points the next value to the first node(formally second node)
        head->next = node1;
    }
}

void dup(int n) {
    struct node *ptr3 = head;
    int array[100];
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
        int count = 0;
        while (ptr3 != NULL) {
            int val = ptr3->value;
            array[count] = val + 0;
            ptr3 = ptr3->next;
            count++;
        }
        for (int i = 0; i < 1; i++) {
            if (head->value < head->next->value) {
                for (int y = 0; y < n; y++) {
                    int vale = array[y];
                    lit(vale);
                }
            } else if(head->value > head->next->value) {
                for (int x = n; x > 0; x--) {
                    int vale = array[x-1];
                    lit(vale);
                }
            }
        }
    }
}
//Reads the next integer from the input stream and pushes it on the list
void in(){
    //Read an int
    int numInput = 0;
    printf("Enter an integer to push onto the stack: ");
    scanf("%d", &numInput);
    lit(numInput);
}

//Pops the top element of the list
void drop() {
    //If the node is empty
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
        //sets head value to its neighbor node
        struct node *tempHead = head;
        head = head->next;

       free(tempHead);
    }

}

//Pops top two ints and adds them
void add() {
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
        //Gets the values of the first two nodes in the list
        int value1 = head->value;
        int value2 = head->next->value;

        //Removes them from the list
        drop();
        drop();

        //Adds the value of nodes together and pushes the result
        int result = value1 + value2;
        lit(result);
    }
}
void subtrc() {
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
        //Gets the values of the first two nodes in the list
        int value1 = head->value;
        int value2 = head->next->value;

        //Removes them from the list
        drop();
        drop();

        //Adds the value of nodes together and pushes the result
        int result = value1 - value2;
        lit(result);
    }
}
void mult() {
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
        //Gets the values of the first two nodes in the list
        int value1 = head->value;
        int value2 = head->next->value;

        //Removes them from the list
        drop();
        drop();

        //Adds the value of nodes together and pushes the result
        int result = value1 * value2;
        lit(result);
    }
}
void DIV() {
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
//Gets the values of the first two nodes in the list
        int value1 = head->value;
        int value2 = head->next->value;

        //Removes them from the list
        drop();
        drop();

        //Adds the value of nodes together and pushes the result
        int result = value1 / value2;
        lit(result);
    }
}
void mod() {
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
        //Gets the values of the first two nodes in the list
        int value1 = head->value;
        int value2 = head->next->value;

        //Removes them from the list
        drop();
        drop();

        //Adds the value of nodes together and pushes the result
        int result = value1 % value2;
        lit(result);
    }
}
void and() {
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
        //Gets the values of the first two nodes in the list
        int value1 = head->value;
        int value2 = head->next->value;

        //Removes them from the list
        drop();
        drop();

        //Adds the value of nodes together and pushes the result
        int result = value1 & value2;
        lit(result);
    }
}
void or() {
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
        int value1 = head->value;
        int value2 = head->next->value;

        //Removes them from the list
        drop();
        drop();

        //Adds the value of nodes together and pushes the result
        int result = value1 | value2;
        lit(result);
    }
}
void jump(){
    char* n;
    n = strstr(ptr, &ptr[5]);
    int instruct =  atoi(n);
    counter = instruct - 2;
}

void ifeq() {
    if (head == NULL) {
        printf("The list is empty\n");
    } else {
        int value1 = head->value;
        int value2 = head->next->value;

        if (head == NULL) {
            printf("The list is empty\n");
        } else if (value1 == value2) {
            jump();
        }
        drop();
        drop();
    }
}
void iflt() {
    int value1 = head->value;
    int value2 = head->next->value;

    if (head == NULL) {
        printf("The list is empty\n");
    } else if (value1 < value2) {
        jump();
    } else {
        drop();
        drop();
    }
}