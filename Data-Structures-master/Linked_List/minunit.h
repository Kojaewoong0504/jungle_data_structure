// minunit.h
#ifndef MINUNIT_H
#define MINUNIT_H

#include <stdio.h>
#include <time.h>

extern int tests_run;
extern int tests_failed;

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)

#define mu_assert_eq_int(expected, actual) do { \
if ((expected) != (actual)) { \
static char msg[100]; \
sprintf(msg, "❌ Expected %d but got %d", (expected), (actual)); \
return msg; \
} \
} while (0)

// 확장된 테스트 실행 매크로
#define mu_run_test(test) do { \
clock_t start = clock(); \
printf("▶ Running %s...\n", #test); \
char *message = test(); tests_run++; \
clock_t end = clock(); \
double elapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000; \
if (message) { \
tests_failed++; \
printf("❌ %s failed: %s\n\n", #test, message); \
} else { \
printf("✅ Passed %s (%.2f ms)\n\n", #test, elapsed); \
} \
} while (0)



extern int tests_run;

#endif
