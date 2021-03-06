#ifndef _STACK_H
#define _STACK_H

/* ET shorts for "ElementType" 
 */
typedef char VertexType; 
typedef VertexType ET; 

struct StackRecord;
typedef struct StackRecord* Stack;

/* Check if stack is empty
 */
int IsEmpty(Stack S);

/* Check if stack is full
 */
int IsFull(Stack S);

/* Creat a stack
 */
Stack createStack(int maxElements);

/* Delete the stack
 */
void disposeStack(Stack S);

/* Make the stack empty
 */
void MakeEmpty(Stack S);

/* Push an element on the stack
 */
void push (ET elem, Stack S);

/* Check the top element of the stack
 */
ET top(Stack S);

/* Pop the top element out of the stack
 */
void pop(Stack S);

/* Check the top element and pop it out of stack
 */
ET topAndPop(Stack S);

#endif


/* initialize the stack from the given array
 * with the array[0] being the bottom of the stack
 */
Stack initializeStack(int array[], int length);

/* print out the stack with the following format:
 * |elem|elem|elem| <-top
 */
void printStack(Stack S);
