#include "stack.h"

Stack *createStack() {
  Stack *out = NULL;
  out = (Stack*)malloc(sizeof(Stack));
  if (out == NULL) {
    exit(OUT_OF_MEMORY);
  }
  out->size = INIT_SIZE;
  out->data = (char*)malloc(out->size * sizeof(char));
  if (out->data == NULL) {
    free(out);
    exit(OUT_OF_MEMORY);
  }
  out->top = 0;
  return out;
}

void deleteStack(Stack **stack) {
  free((*stack)->data);
  free(*stack);
  *stack = NULL;
}

void resize(Stack *stack) {
  stack->size *= MULTIPLIER;
  stack->data = (char*)realloc(stack->data, stack->size * sizeof(char));
  if (stack->data == NULL) {
    exit(STACK_OVERFLOW);
  }
}

char pop(Stack *stack) {
  if (stack->top == 0) {
    exit(STACK_UNDERFLOW);
  }
  stack->top--;
  if (stack->top != 0) {
    stack->priority = check_priority(stack->data[stack->top - 1]);
  } else {
    stack->priority = 0;
  }
  return stack->data[stack->top];
}

void push(Stack *stack, char value) {
  if (stack->top >= stack->size) {
    resize(stack);
  }
  stack->data[stack->top] = value;
  stack->top++;
  stack->priority = check_priority(value);
}

/* Цифры от 48 до 57, x, унарный + - приоритет 0
( приоритет 1
+ - приоритет 2
* /  приоритет 3
cos(x) - a
sin(x) - b
tan(x) - c
acos(x) - d
asin(x) - e
atan(x) - f
sqrt(x) - g
ln(x) - h
log(x) - i
mod - m
^ - ^     приоритет 4
*/
int check_priority(char ch) {
  int result = 0;
  switch (ch) {
    case '(':
      result = 1;
      break;
    case '+':
    case '-':
      result = 2;
      break;
    case '*':
    case '/':
      result = 3;
      break;
    default:
      result = 4;
      break;
  }
  return result;
}
