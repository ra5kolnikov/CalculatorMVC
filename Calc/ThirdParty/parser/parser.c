#include "parser.h"

float calculator(char *input, double x) {
  char convert[(100 * 2) + 2 + 1] = {'\0'};
  char substr[(100 * 2) + 2 + 1] = {'\0'};
  // validate expression
  float res = 0.0;
  convert_trigonometry(input, convert);
  shunting_yard(convert, substr);
  res = calculate_rpn(substr, x);
  return res;
}

char *convert_trigonometry(char *str, char *result) {
  int k = 0;
  for (int i = 0; i < (int)strlen(str); ++i) {
    if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
        str[i + 3] == 's') {
      result[k++] = 'o';
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
               str[i + 3] == 'n') {
      result[k++] = 'n';
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
               str[i + 3] == 'n') {
      result[k++] = 'a';
      i += 3;
    } else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
      result[k++] = 'c';
      i += 2;
    } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
      result[k++] = 's';
      i += 2;
    } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
      result[k++] = 't';
      i += 2;
    } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
      result[k++] = 'm';
      i += 2;
    } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
               str[i + 3] == 't') {
      result[k++] = 'q';
      i += 3;
    } else if (str[i] == 'l' && str[i + 1] == 'n') {
      result[k++] = 'l';
      i++;
    } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') {
      result[k++] = 'g';
      i += 2;
    } else if (i == 0 && str[i] == '-') {
      result[k++] = '0';
      result[k++] = '-';
    } else if (str[i] == '(' && str[i + 1] == '-') {
      result[k++] = '(';
      result[k++] = '0';
    } else if ((str[i] >= 48 && str[i] <= 56) &&
               (str[i + 1] == '(' || str[i + 1] == 'a' || str[i + 1] == 'c' ||
                str[i + 1] == 's' || str[i + 1] == 't' || str[i + 1] == 'l')) {
      result[k++] = str[i];
      result[k++] = '*';
    } else {
      result[k++] = str[i];
    }
  }
  return result;
}

int shunting_yard(const char *input, char *output) {
  Stack *stack = createStack();
  const char *currpos = input;
  char ch, *outpos = output;
  while (*currpos != '\0') {
    ch = *currpos;
    if (ch != ' ') {
      if (ch == '(') {
        push(stack, ch);
      } else if (ch == ')') {
        while (stack->data[stack->top - 1] != '(') {
          *outpos = ' ';
          outpos++;
          *outpos = pop(stack);
          outpos++;
        }
        pop(stack);
      } else if (is_operation(ch)) {
        *outpos = ' ';
        outpos++;
        while (stack->priority >= check_priority(ch)) {
          *outpos = pop(stack);
          outpos++;
          *outpos = ' ';
          outpos++;
        }
        push(stack, ch);
      } else if (is_digit(ch)) {
        *outpos = ch;
        outpos++;
      }
      currpos++;
    } else {
      currpos++;
    }
  }
  while (stack->top != 0) {
    *outpos = ' ';
    outpos++;
    *outpos = pop(stack);
    outpos++;
  }
  *outpos = ' ';
  outpos++;
  deleteStack(&stack);
  return 0;
}

float calculate_rpn(const char *input, double x) {
  struct noded *d = 0;
  float result = 0.;
  const char *currpos = input;
  char ch;
  while (*currpos != '\0') {
    ch = *currpos;
    if (ch != ' ') {
      if (is_digit(ch) && ch != 'x') {
        d = pushd(d, atof(currpos));
        while (*currpos != ' ') currpos++;
      } else if (is_operation(ch)) {
        if (is_unary_operation(ch)) {
          float second = 0;
          d = popd(d, &second);
          d = pushd(d, calc_binary(ch, 0, second));
        } else {
          float first = 0;
          float second = 0;
          d = popd(d, &second);
          d = popd(d, &first);
          float res = calc_binary(ch, first, second);
          d = pushd(d, res);
        }
        currpos++;
      } else if (ch == 'x') {
        d = pushd(d, x);
        while (*currpos != ' ') currpos++;
      }
    } else {
      currpos++;
    }
  }
  d = popd(d, &result);
  return result;
}

int is_operation(char ch) {
  int result = 0;
  switch (ch) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case 'o':
    case 'n':
    case 'a':
    case 'c':
    case 's':
    case 't':
    case 'm':
    case 'q':
    case 'l':
    case 'g':
      result = 1;
      break;
    default:
      break;
  }
  return result;
}

int is_unary_operation(char d) {
  int res = 0;
  switch (d) {
    case 'o':
    case 'n':
    case 'a':
    case 'c':
    case 's':
    case 't':
    case 'q':
    case 'l':
    case 'g':
      res = 1;
      break;
    default:
      break;
  }
  return res;
}

struct noded *pushd(struct noded *head, float data) {
  struct noded *tmp = (struct noded *)malloc(sizeof(struct noded));
  tmp->data = data;
  tmp->next = head;
  return tmp;
}

struct noded *popd(struct noded *head, float *t) {
  *t = head->data;
  struct noded *tmp = head;
  head = head->next;
  free(tmp);
  return head;
}

int emptyd(struct noded *head) { return head == NULL ? 1 : 0; }

float calc_binary(char c, float first, float second) {
  float result = 0;
  switch (c) {
    case '+':
      result = first + second;
      break;
    case '-':
      result = first - second;
      break;
    case '*':
      result = first * second;
      break;
    case '/':
      result = first / second;
      break;
    case '^':
      result = pow(first, second);
      break;
    case 'o':  // acos
      result = acos(second);
      break;
    case 'n':  // asin
      result = asin(second);
      break;
    case 'a':  // atan
      result = atan(second);
      break;
    case 'c':  // cos
      result = cos(second);
      break;
    case 's':  // sin
      result = sin(second);
      break;
    case 't':  // tan
      result = tan(second);
      break;
    case 'm':  // mod
      result = fmod(first, second);
      break;
    case 'q':  // sqrt
      result = sqrt(second);
      break;
    case 'l':  // ln
      result = log(second);
      break;
    case 'g':  // log
      result = log10(second);
      break;
    default:
      break;
  }
  return result;
}
