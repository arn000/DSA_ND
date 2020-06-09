#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED

typedef struct Bigint
{
  unsigned int negative;
  int length;
  char *num;
} Bigint;

Bigint init(char *str, int *err);

Bigint add(Bigint a, Bigint b, int *err);
Bigint subtract(Bigint a, Bigint b, int *err);

Bigint multiply(Bigint a, Bigint b, int *err);
Bigint divide(Bigint a, Bigint b, Bigint *remainder, int *err);

void destroy(Bigint a);
void printBigint(Bigint a);

#endif // BIGINT_H_INCLUDED
