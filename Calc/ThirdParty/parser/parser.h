#ifndef _PARSER_H_
#define _PARSER_H_

#include <math.h>

#include "../stack/stack.h"

#define is_digit(c) (c >= 48 && c <= 57 || c == 'x' || c == '.')
// #define is_separator(c) (c == '.' || c == ',')

typedef struct string {
  char* str;
  int len;
} string;

struct noded {
  float data;
  struct noded* next;
};

struct noded* pushd(struct noded* head, float data);
struct noded* popd(struct noded* head, float* t);
int emptyd(struct noded* head);
float calc_binary(char c, float first, float second);

int shunting_yard(const char* input, char* output);
char* convert_trigonometry(char* str, char* result);
float calculate_rpn(const char* input, double x);
float calculator(char* input, double x);

int is_operation(char ch);
int is_unary_operation(char d);

#endif  // _PARSER_H_
