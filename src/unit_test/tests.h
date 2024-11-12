#ifndef TESTS_H
#define TESTS_H

#include <check.h>
#include <stdio.h>

void runTests();
void runTestcase(Suite *testcase);
Suite *suite_tetris_base();

#endif
