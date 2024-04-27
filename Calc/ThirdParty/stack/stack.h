#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY -102
#define MAX_STR_SIZE 10
#define INIT_SIZE 10
#define MULTIPLIER 2

typedef struct stack {
  int top;
  int size;
  int priority;
  char *data;
} Stack;

int check_priority(char ch);
void deleteStack(Stack **stack);
Stack *createStack();
void resize(Stack *stack);
void push(Stack *stack, char value);
char pop(Stack *stack);

#endif  // _STACK_H_
