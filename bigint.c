#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"

void optimize(Bigint *a);

Bigint init(char *str, int *err)
{
  Bigint bigint;

  bigint.negative = 0;
  if(str[0] == '-') {
    bigint.negative = 1;
    str++;
  }

  int i = 0,
      length = strlen(str);

  char *num = calloc( length + 1, sizeof(char) );

  if(num == NULL) {
    *err = 1;
    return bigint;
  }

  i = 0;
  while(i < length) {
    num[i++] = str[length-1 - i];
  }

  bigint.num = num;
  bigint.length = strlen(num);

  optimize(&bigint);

  *err = 0;
  return bigint;
}

void destroy(Bigint a)
{
  free(a.num);
}

Bigint add(Bigint a, Bigint b, int *err)
{
  Bigint bigint = a;

  if(b.length > a.length) {
    a = b;
    b = bigint;
  }
  bigint.num = NULL;

  char *num = malloc( (a.length + 2) * sizeof(char) );
  if(num == NULL) {
    *err = 1;
    return bigint;
  }

  int i = 0,
      carry = 0,
      x;

  while( a.num[i] != '\0' ) {
    // printf("%d+C%d", (a.num[i]-'0'), carry);
    x = (a.num[i]-'0') + carry;

    if(i < b.length && b.num[i] != '\0') {
      // printf("+%d", (b.num[i]-'0'));
      x += (b.num[i]-'0');
    }

    if(x > 9) {
      carry = 1;
      x -= 10;
    } else
      carry = 0;

    // printf("=%d       ", x);
    num[i++] = x + '0';
  }

  num[i++] = carry ? carry + '0' : '\0';
  num[i] = '\0';

  // printf("%s + %s = %s\n",a.num, b.num, num);
  bigint.num = num;
  bigint.negative = 0;
  bigint.length = strlen(num);

  *err = 0;
  return bigint;
}

Bigint subtract(Bigint a, Bigint b, int *err)
{
  Bigint bigint = a;
  int negative = 0;

  // Making a >= b
  if(a.length < b.length) {
    a = b;
    b = bigint;
    negative = 1;
  }
  else if(a.length == b.length) {
    int i = a.length - 1;
    while(i >= 0) {
      if(a.num[i] > b.num[i]) {
        break;
      }

      if(a.num[i] < b.num[i]) {
        // printf("Swaping\n" );
        a = b;
        b = bigint;
        negative = 1;
        break;
      }
      i--;
    }
  }
  bigint.num = NULL;

  char *num = malloc( (a.length + 2) * sizeof(char) );
  if(num == NULL) {
    *err = 1;
    return bigint;
  }

  int i = 0,
      carry = 0,
      x;

  while( a.num[i] != '\0' ) {
    x = (a.num[i]-'0') - carry;

    if(i < b.length && b.num[i] != '\0')
      x -= (b.num[i]-'0');

    if(x < 0) {
      carry = 1;
      x += 10;
    } else
      carry = 0;

    num[i++] = x + '0';
  }

  num[i++] = carry ? carry + '0' : '\0';
  num[i] = '\0';

  bigint.num = num;
  bigint.negative = negative ? 1 : 0;
  bigint.length = strlen(num);

  optimize(&bigint);
  // printf("%s - %s = %s\n",a.num, b.num, num);
  *err = 0;
  return bigint;
}


Bigint multiply(Bigint a, Bigint b, int *err)
{
  Bigint bigint = a;

  if(b.length > a.length) {
    a = b;
    b = bigint;
  }
  bigint.num = NULL;

  int ai,
      bi = 0,
      carry = 0,
      x, i;

  bigint = init("0", err);
  Bigint intTemp1;
  Bigint intTemp2;
  char *temp = malloc( (a.length + b.length + 2) * sizeof(char) );
  if(temp == NULL || *err) {
    *err = 1;
    return bigint;
  }

  while( b.num[bi] != '\0' ) {
    ai = 0;
    i = 0;
    carry = 0;

    while(i < bi)
      temp[i++] = '0';

    while( a.num[ai] != '\0' ) {
      // printf("%d*%d+%d", (b.num[bi]-'0'), (a.num[ai]-'0'), carry);
      x = (b.num[bi]-'0') * (a.num[ai]-'0') + carry;
      if(x > 9) {
        carry = x/10;
        x = x%10;
      } else
        carry = 0;
      // printf("=%d     ", x);
      temp[bi + ai++] = x + '0';
    }

    temp[bi + ai++] = carry ? carry + '0' : '\0';
    temp[bi + ai] = '\0';

    intTemp2.num = temp;
    intTemp2.length = strlen(temp);

    // printf("%s + %s \n", bigint.num, intTemp2.num );
    intTemp1 = add(bigint, intTemp2, err);
    destroy(bigint);
    bigint = intTemp1;

    if(*err) {
      *err = 1;
      destroy(bigint);
      destroy(intTemp2);
      return bigint;
    }

    bi++;
  }

  destroy(intTemp2);
  // printf("Result = %s\n", bigint.num);

  if(a.negative ^ b.negative) {
    bigint.negative = 1;
  }

  return bigint;
}

Bigint divide(Bigint a, Bigint b, Bigint *remainder, int *err)
{
  Bigint bigint;
  // a >= b

  if(b.length == 1 && b.num[0] == '0') {
    *err = 2;
    return bigint;
  }

  Bigint intTemp1;
  Bigint intTemp2;
  char *num = calloc( a.length + 1, sizeof(char) );
  char *temp = calloc( b.length + 2, sizeof(char) );
  if(num == NULL || temp == NULL) {
    *err = 1;
    return bigint;
  }

  int x,
      i = 0,
      ri = 0,
      ai = a.length - 1;

  while(i < b.length) {
    temp[i] = a.num[ai - i];
    i++;
  }

  ai -= i;
  while(ai >= -1) {

    intTemp2 = init(temp, err);
    intTemp1 = subtract(intTemp2, b, err);
    if(*err) return bigint;

    if(intTemp1.negative) {
      // printf("1. ");
      // printBigint(intTemp1);
      temp[i++] = a.num[ai--];
      temp[i] = '\0';

      destroy(intTemp1);
      destroy(intTemp2);

      continue;
    }

    i = 0;
    x = 0;
    while(!intTemp1.negative) {
      // printf("2. ");
      // printBigint(intTemp1);
      x++;
      destroy(intTemp2);
      intTemp2 = intTemp1;
      intTemp1 = subtract(intTemp2, b, err);
      if(*err) return bigint;
    }

    num[ri++] = x + '0';

    while(i < intTemp2.length) {

      temp[i] = intTemp2.num[intTemp2.length - 1 - i];
      i++;
    }
    temp[i++] = ai >= 0 ? a.num[ai] : '\0';
    temp[i] = '\0';

    destroy(intTemp1);
    destroy(intTemp2);

    ai--;
  }

  // printf("Result: %s \nRemainder: %s\n", num, temp);
  i = 0;
  while(i + 1 < strlen(temp) && temp[i] == '0') {
    num[ri++] = '0';
    i++;
  }

  bigint = init(num, err);
  *remainder = init(temp, err);

  if(a.negative ^ b.negative) {
    bigint.negative = 1;
  }

  free(num);
  free(temp);

  return bigint;
}
void optimize(Bigint *a)
{
  int i = a->length - 1;
  while(i && a->num[i] == '0') {
    a->length--;
    a->num[i--] = '\0';
  }
}

void printBigint(Bigint a)
{
  if(a.negative) {
    printf("-");
  }
  int i = a.length;
  while(i) {
    printf("%c", a.num[i-1]);
    i--;
  }
  // printf("\t\tN:%d   L:%d", a.negative, a.length);
  // printf("   %s", a.num);
  // printf("\n");
}

