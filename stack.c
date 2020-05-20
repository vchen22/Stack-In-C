#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

// Edit only after this line //

#define HALF_TWO 2
#define DUB_TWO 2

/**
 * Removes the element at the top of the stack and returns it.
 * May shrink the size of the stack
 * */
Element* pop(Stack* s){
    if (isEmpty(s))
    {
        return NULL;
    }

    //check if need to shrink in size
    if (s->dynamic == true && s->shrinkFactor > 0 && 
            ((float)s->top/s->capacity) <= s->shrinkFactor)
    {
        s->capacity = s->capacity/HALF_TWO;

        Element** elemTemp = (Element**) malloc(s->capacity*sizeof(Element*));

        //iterate to pull all elements into new memory
        for (int i = 0; i < s->capacity; i++)
        {
            elemTemp[i] = s->elements[i];
        }

        //get rid of old elements
        free(s->elements);
        //set new memory with elements into elements again
        s->elements = elemTemp;
    }

    s->top--;
    return s->elements[s->top];    

}

/**
 * Pop k elements from the stack and returns them as an array
 * */
Element** multiPop(Stack* s, int k){
    if (isEmpty(s))
    {
        return NULL;
    }

    //make it so that it can pop all elements in array instead
    if (k > currentSize(s))
    {
        k = currentSize(s);

    }

    Element** elemTemp = (Element**) malloc(k*sizeof(Element*));

    //iterate through to put that number of removed elements into an arr
    for (int i = 0; i < k; i++)
    {
        elemTemp[i] = pop(s);
    }

    return elemTemp;

}

/*
 * Helper function to add a new element in push
 * */
void addE(Stack* s, int k, char* v) {
    Element* new_element = (Element*) malloc(sizeof(Element));
    //set the new elements with given key and value
    new_element->key = k;
    new_element->value = v;
    s->elements[s->top] = new_element;
}

/**
 * Helper function to expand the capacity in push
 * */
void expandCapacity(Stack* s) {
    s->capacity = s->capacity*DUB_TWO;
    Element** elemTemp = (Element**) malloc(s->capacity*sizeof(Element*));

    //iterate to pull all element into arr with new capacity
    for (int i = 0; i < s->top; i++)
    {
        elemTemp[i] = s->elements[i];
    }

    //get rid of old elements
    free(s->elements);
    //set elements to arr with new elements
    s->elements = elemTemp;

}

/**
 * Adds an element at the top of the stack. May grow size of stack
 * */
bool push(Stack* s, int k, char* v){
    if (isFull(s) && s->dynamic == false)
    {
        return false;
    }

    //check if need to grow in size
    if (s->dynamic == true && s->growthFactor > 0 && 
            ((float)s->top/(float)s->capacity >= s->growthFactor))
    {
        //call helper function to change size
        expandCapacity(s);
    }

    //call helper function to add the new element
    addE(s, k, v);

    s->top++;

    return true;
}

/**
 * Adds an element at the top of the stack only if the current top element of
 * the stack is not the same as the element that we want to push
 * */
bool pushUnique(Stack* s, int k, char* v){
    if (isFull(s) == true && s->dynamic == false)
    {
        return false;
    }

    //check if qualities are the same
    if (peek(s)->key == k && peek(s)->value == v)
    {
        return false;
    }
    else
    {
        //call push to add the unique element
        push(s,k,v);
        return true;
    }

}

/**
 * Reverse the elements in the stack
 * */
void reverse(Stack* s){
    //swap elements with its corresponding indices
    for (int i = 0; i < s->top/HALF_TWO; i++)
    {
        Element* temp_one = s->elements[i];
        Element* temp_two = s->elements[s->top-1-i];

        s->elements[i] = temp_two;
        s->elements[s->top-1-i] = temp_one;
    }

}

/**
 * Returns the pointer to the element at the top of the stack without 
 * removing it from the stack
 * */
Element* peek(Stack* s){
    if(isEmpty(s))
    {
        return NULL;
    }
    else
    {
        //check top element
        return s->elements[s->top-1];
    }

}

/**
 * Returns the distance of the element from the top of the stack
 * */
int search(Stack* s, int k, char* v){
    if (isEmpty(s))
    {
        return -1;
    }

    //iterate to see if element exist
    for (int i = s->top-1; i >= 0; i--)
    {
        //once found calculate distance
        if (s->elements[i]->key == k && s->elements[i]->value == v)
        {
            return s->top-i;
        }
    }

    return -1;

}

/**
 * Returns the total capacity of stack, the meximum number of elements it can
 * store currently
 * */
int getCapacity(Stack* s){
    return s->capacity;

}

/**
 * Check if stack is full
 * */
bool isFull(Stack* s){
    if (s->top == s->capacity)
    {
        return true;
    }
    else
    {
        return false;
    }

}

/**
 * Remove all elements from Stack
 * */
void clear(Stack *s) {
    s->top = 0;
}

/**
 * Clean all elements of stack and elements itself
 * */
void cleanStack(Stack *s) {
    for(int i = 0; i < s->capacity; i++) {
        free(s->elements[i]);
    }
    free(s->elements);
    free(s);
}

/**
 * Returns the total number of elements currently in the stack
 * */
int currentSize(Stack* s){
    return s->top;

}

/**
 * Check if stack is empty
 * */
bool isEmpty(Stack* s){
    if (s->top == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

/**
 * Initializes a stack with fixed capacity
 * */
Stack* makeStack(int cap){
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->top = 0;
    stack->capacity = cap;
    stack->growthFactor = 0;
    stack->shrinkFactor = 0;
    stack->dynamic = false;
    stack->elements = (Element**) malloc(stack->capacity*sizeof(Element*));
    return stack;

}

/**
 * Initalizes a stack with some initial capacity but can grow in size
 * */
Stack* makeStackG(int cap, float growF){
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->top = 0;
    stack->capacity = cap;
    stack->growthFactor = growF;
    stack->shrinkFactor = 0;
    stack->dynamic = true;
    stack->elements = (Element**) malloc(stack->capacity*sizeof(Element*));
    return stack;

}

/**
 * Initializes a stack with some initial capacity. It can grow or shrink
 * in size
 * */
Stack* makeStackGnS(int cap, float growF, float shrinkF){
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->top = 0;
    stack->capacity = cap;
    stack->growthFactor = growF;
    stack->shrinkFactor = shrinkF;
    stack->dynamic = true;
    stack->elements = (Element**) malloc(stack->capacity*sizeof(Element*));
    return stack;


}
