#include "cutest/CuTest.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Add your tests here
 * A few sample tests
 * are provided
 */


// Tests for integer equals
void TestOne(CuTest *tc) {
  int two = 2;
  int four = 4;
  CuAssertIntEquals(tc, four, two+two);
}

// Test for string equals
void TestTwo(CuTest *tc) {
  char* lol = "lol";
  char* alsoLol = "lol";
  CuAssertStrEquals(tc, lol, alsoLol);
}

/*
Tests for True and False
pay attention to cleanStack function call as
you will be using it in your every test case
*/
void TestTrueFalse(CuTest *tc) {
  Stack* s = makeStack(10);
  CuAssertTrue(tc, isEmpty(s));
  push(s, 1, "black");
  CuAssertFalse(tc, isEmpty(s));
  cleanStack(s);
}


// Tests for Pointer equals
void TestPtrEquals(CuTest *tc) {
  Element* e = NULL;
  CuAssertPtrEquals(tc, NULL, e);
}

void TestPopEmptyTrue(CuTest *tc) {
  Stack* s = makeStack(3);
  push(s, 0, "0");
  push(s, 1, "1");
  push(s, 2, "2");
  pop(s);
  pop(s);
  pop(s);
  CuAssertTrue(tc, isEmpty(s));
  cleanStack(s);
}

void TestGetCapacity(CuTest *tc)
{
    Stack* s = makeStack(10);
    CuAssertIntEquals(tc, 10, getCapacity(s));
    cleanStack(s);
}


void TestMultiPopK(CuTest *tc)
{
    Stack* s = makeStack(5);
    push(s, 0, "0");
    push(s, 1, "1");
    push(s, 2, "2");
    Element** arr = multiPop(s, 2);
    //printf("%d\n", arr[0]->key);
    CuAssertIntEquals(tc, peek(s)->key, 0);
    CuAssertIntEquals(tc, currentSize(s), 1);
    //how to check the size of the produced array
    free(arr);
    cleanStack(s);
    
}

void TestPushCap(CuTest *tc)
{
    Stack* s = makeStackG(10, 0.5f);
    push(s, 0, "0");
    push(s, 0, "0");
    push(s, 0, "0");
    push(s, 0, "0");
    //CuAssertIntEquals(tc, 10, getCapacity(s));
    push(s, 0, "0");
    push(s, 0, "0");
    CuAssertIntEquals(tc, 20, getCapacity(s));
    cleanStack(s);

}

void TestClearSize(CuTest *tc) {
Stack* s = makeStack(10);
push(s, 1, "black");

// this logically speaking has effect of clearing all the elements in stack such that a call to isEmpty(s) return True,

// now here you will think i have to call cleanStack to deallocate all memory

// but look at next line you are calling the cleanStack just after clear function

clear(s);
//push(s, 3, "3");
//CuAssertIntEquals(tc, 0, currentSize(s));
cleanStack(s);
}

//wtf test push after clear
void TestClearPush(CuTest *tc)
{
    Stack* s = makeStack(5);
    push(s, 13, "22");
    push(s, 12, "33");
    push(s, 11, "11");
    push(s, 19, "19");
    push(s, 14, "19");
    Element* e = pop(s);
    free(e);
    //clear(s);
    //free(e);
    push(s, 16, "16");
    //free(e);
    cleanStack(s);

}



/*
void TestPopHint(CuTest *tc) {
Stack* s = makeStack(10);
push(s, 1, "black");

// returns the pointer at current top, then decrease top,  note memory is still occupied at loaction pointed by e.

// this memory allocation was done while creating makeStack

Element* e = pop(s);
CuAssertIntEquals(tc, 1, e->key);
CuAssertStrEquals(tc, "black", e->value);

// now when you call this function it will free all the memory including the one pointed by e
cleanStack(s);
}
*/

//VICTOR

void TestPush(CuTest *tc)
{
    Stack* s = makeStack(10);
    push(s, 1, "blue");
    push(s, 2, "red");
    CuAssertStrEquals(tc, peek(s)->value, "red");
    CuAssertIntEquals(tc, s->top, 2);
    CuAssertIntEquals(tc, getCapacity(s), 10);
    cleanStack(s);
}

void TestPushG(CuTest *tc)
{
    Stack* s = makeStackG(10, 0.5f);
    push(s, 1, "blue");
    push(s, 2, "red");
    push(s, 4, "black");
    push(s, 21, "gogle");
    push(s, 13, "123");
    push(s, 123, "daf");
    CuAssertIntEquals(tc, s->capacity, 20);
    CuAssertStrEquals(tc, peek(s)->value, "daf");
    CuAssertIntEquals(tc, s->top, 6);
    Element* e = pop(s);
    //free(e);
    CuAssertIntEquals(tc, s->capacity, 20);
    CuAssertStrEquals(tc, e->value, "daf");
    CuAssertStrEquals(tc, peek(s)->value, "123");
    CuAssertIntEquals(tc, s->top, 5);
    CuAssertFalse(tc, isFull(s));
    CuAssertFalse(tc, isEmpty(s));
    cleanStack(s);
}

void TestPushOdd(CuTest *tc)
{
    Stack* s = makeStackGnS(9, 1.0f, 0.5f);
    push(s, 1, "blue");
    pop(s);
    CuAssertIntEquals(tc, getCapacity(s), 4);
    CuAssertTrue(tc, isEmpty(s));
    cleanStack(s);
}

void TestPushGnS(CuTest *tc)
{
    Stack* s = makeStackGnS(10, 0.5f, 0.3f);
    push(s, 1, "blue");
    push(s, 2, "red");
    push(s, 4, "black");
    push(s, 21, "gogle");
    push(s, 13, "123");
    push(s, 123, "daf");
    CuAssertIntEquals(tc, s->capacity, 20);
    CuAssertStrEquals(tc, peek(s)->value, "daf");
    CuAssertIntEquals(tc, s->top, 6);
    Element* e = pop(s);
    CuAssertIntEquals(tc, s->capacity, 10);
    CuAssertStrEquals(tc, e->value, "daf");
    CuAssertIntEquals(tc, s->top, 5);
    clear(s);
    CuAssertTrue(tc, isEmpty(s));
    cleanStack(s);
}

void TestPushFull(CuTest *tc)
{
    Stack* s = makeStack(1);
    push(s, 1, "blue");
    CuAssertFalse(tc, push(s, 2, "red"));
    CuAssertTrue(tc, isFull(s));
    cleanStack(s);

}

void TestPushTrue(CuTest *tc)
{
    Stack* s = makeStack(1);
    CuAssertTrue(tc, push(s, 1, "blue"));
    cleanStack(s);
}

void TestMultiPop(CuTest *tc)
{
    Stack* s = makeStack(10);
    push(s, 1, "yo");
    push(s, 2, "hey");
    push(s, 3, "DSF");
    push(s, 4, "ASDV");
    Element** e = multiPop(s, 3);
    CuAssertStrEquals(tc, e[0]->value, "ASDV");
    CuAssertStrEquals(tc, e[2]->value, "hey");
    free(e);
    cleanStack(s);
}

void TestMultiPopFull(CuTest *tc)
{
Stack* s = makeStack(10);
    push(s, 1, "yo");
    push(s, 2, "hey");
    push(s, 3, "DSF");
    push(s, 4, "ASDV");
    Element** e = multiPop(s, 20);
    CuAssertStrEquals(tc, e[0]->value, "ASDV");
    CuAssertStrEquals(tc, e[2]->value, "hey");
    CuAssertStrEquals(tc, e[3]->value, "yo");
    free(e);
    cleanStack(s);
    
}

void TestMultiPopNull(CuTest *tc)
{
    Stack* s = makeStack(10);
    Element** e = multiPop(s, 2);
    CuAssertPtrEquals(tc, e, NULL);
    cleanStack(s);
    
}

void TestReverse(CuTest *tc)
{
    Stack* s = makeStack(10);
push(s, 1, "yo");
    push(s, 2, "hey");
    push(s, 3, "DSF");
    push(s, 4, "ASDV");
    reverse(s);
    CuAssertStrEquals(tc, peek(s)->value, "yo");
    CuAssertIntEquals(tc, s->top, 4);
    CuAssertIntEquals(tc, currentSize(s), 4);
    Element* e = pop(s);
    CuAssertStrEquals(tc, e->value, "yo");
    cleanStack(s); 

}

void TestPushUnique(CuTest *tc)
{
    Stack* s = makeStack(5);
    push(s, 1, "yo");
    pushUnique(s, 2, "hey");
    CuAssertIntEquals(tc, currentSize(s), 2);
    CuAssertStrEquals(tc, peek(s)->value, "hey");
    CuAssertIntEquals(tc, s->top, 2);
    cleanStack(s);
}

void TestPushUniqueSame(CuTest *tc)
{
Stack* s = makeStack(5);
    push(s, 1, "yo");
    pushUnique(s, 1, "yo");
 CuAssertIntEquals(tc, currentSize(s), 1);
    CuAssertStrEquals(tc, peek(s)->value, "yo");
    CuAssertIntEquals(tc, s->top, 1);
pushUnique(s, 1, "yo");
pushUnique(s, 1, "yo");
pushUnique(s, 1, "yo");
pushUnique(s, 2, "yo");
CuAssertIntEquals(tc, currentSize(s), 2);
    CuAssertStrEquals(tc, peek(s)->value, "yo");
    CuAssertIntEquals(tc, s->top, 2);
pushUnique(s, 3, "yo");
pushUnique(s, 4, "yo");
pushUnique(s, 5, "yo");
CuAssertFalse(tc, pushUnique(s, 5, "yo"));
cleanStack(s);
    
}

void TestSearch(CuTest *tc)
{
    Stack* s = makeStack(5);
    push(s, 13, "yadf");
    push(s, 22, "fd");
    push(s, 11, "badsf");
    CuAssertIntEquals(tc, search(s, 22, "fd"), 2);
    cleanStack(s);
}

void TestSearchSame(CuTest *tc)
{
    Stack* s = makeStack(5);
    push(s, 13, "yadf");
    push(s, 22, "fd");
    push(s, 11, "badsf");
    push(s, 22, "fd");
    CuAssertIntEquals(tc, search(s, 22, "fd"), 1);
    CuAssertIntEquals(tc, getCapacity(s), 5);
    cleanStack(s);
}

void TestSearchNotFound(CuTest *tc)
{
 Stack* s = makeStack(5);
    push(s, 13, "yadf");
    push(s, 22, "fd");
    push(s, 11, "badsf");
    push(s, 22, "fd");
    CuAssertIntEquals(tc, search(s, 22, "fa"), -1);
CuAssertIntEquals(tc, getCapacity(s), 5);    
    cleanStack(s);
    
}

void TestClear1(CuTest *tc)
{
    Stack* s = makeStack(10);
    push(s, 1, "black");
    clear(s);
    
    cleanStack(s);
}

void TestPushh123(CuTest *tc)
{
    Stack* s = makeStack(3);
    push(s, 2, "123");
    push(s, 2, "abc");
    Element* e = pop(s);
    push(s, 2, "DF");
    push(s, 2, "DFD");
    free(e);
    CuAssertIntEquals(tc, s->top, 3);
    CuAssertIntEquals(tc, currentSize(s), 3);
    CuAssertIntEquals(tc, getCapacity(s), 3);
    CuAssertTrue(tc, isFull(s));
    CuAssertStrEquals(tc, peek(s)->value, "DFD");
    cleanStack(s);
    
}

  CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();

  /** ADD YOUR TESTS HERE **/
  SUITE_ADD_TEST(suite, TestOne);
  SUITE_ADD_TEST(suite, TestTwo);
  SUITE_ADD_TEST(suite, TestTrueFalse);
  SUITE_ADD_TEST(suite, TestPtrEquals);
  SUITE_ADD_TEST(suite, TestPopEmptyTrue);
  SUITE_ADD_TEST(suite, TestGetCapacity);
  SUITE_ADD_TEST(suite, TestMultiPopK);
  SUITE_ADD_TEST(suite, TestPushCap);
  SUITE_ADD_TEST(suite, TestClearSize);
  SUITE_ADD_TEST(suite, TestClearPush);
  //SUITE_ADD_TEST(suite, TestPopHint);
  SUITE_ADD_TEST(suite, TestPush);
  SUITE_ADD_TEST(suite, TestPushG);
  SUITE_ADD_TEST(suite, TestPushOdd);
  SUITE_ADD_TEST(suite, TestPushGnS);
  SUITE_ADD_TEST(suite, TestPushFull);
  SUITE_ADD_TEST(suite, TestMultiPop);
  SUITE_ADD_TEST(suite, TestMultiPopFull);
  SUITE_ADD_TEST(suite, TestMultiPopNull);
  SUITE_ADD_TEST(suite, TestReverse);
  SUITE_ADD_TEST(suite, TestPushUnique);
  SUITE_ADD_TEST(suite, TestPushUniqueSame);
  SUITE_ADD_TEST(suite, TestSearch);
  SUITE_ADD_TEST(suite, TestSearchSame);
  SUITE_ADD_TEST(suite, TestSearchNotFound);
  SUITE_ADD_TEST(suite, TestClear1);
  SUITE_ADD_TEST(suite, TestPushh123);


  return suite;
}

// Don't edit anything below this line

void RunAllTests(void) {
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();
  CuSuite* ourSuite = StrUtilGetSuite();

  CuSuiteAddSuite(suite, ourSuite);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  CuStringDelete(output);
  CuSuiteDelete(suite);
  free(ourSuite);
}

int main(void) {
  RunAllTests();
  return 0;
}
