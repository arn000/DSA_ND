#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"

int main()
{
  int err;
  Bigint a = init("78978978978978978978978978978978978978978978978978979889798789", &err);
  Bigint b = init("1231231231231231231231223123", &err);

  printBigint(a);
  printf("   Negatives:%d   Length:%d   Err:%d\n", a.negative, a.length, err);
  printBigint(b);
  printf("   Negatives:%d   Length:%d   Err:%d\n", b.negative, b.length, err);

  printf("Add:\n");
  Bigint sum = add(a, b, &err);
  printBigint(sum);
  printf("   Negatives:%d   Length:%d   Err:%d\n", sum.negative, sum.length, err);
  destroy(sum);

  printf("Subtract:\n");
  Bigint difference = subtract(a, b, &err);
  printBigint(difference);
  printf("   Negatives:%d   Length:%d   Err:%d\n", difference.negative, difference.length, err);
  destroy(difference);

  printf("Multiply:\n");
  Bigint product = multiply(a, b, &err);
  printBigint(product);
  printf("   Negatives:%d   Length:%d   Err:%d\n", product.negative, product.length, err);
  destroy(product);

  printf("Divide:\n");
  Bigint remainder;
  Bigint quotient = divide(a, b, &remainder, &err);
  printf("\tQuotient:\n\t");
  printBigint(quotient);
  printf("   Negatives:%d   Length:%d   Err:%d\n", quotient.negative, quotient.length, err);
  printf("\tRemainder:\n\t");
  printBigint(remainder);
  printf("   Negatives:%d   Length:%d   Err:%d\n", remainder.negative, remainder.length, err);
  destroy(quotient);
  destroy(remainder);
  destroy(a);
  destroy(b);
  return 0;
}
