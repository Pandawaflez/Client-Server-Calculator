//calculator.c
//a basic calculator using prefix notation.  Takes and operator and two operands.

#include<stdio.h>
#include<stdlib.h>
#include"calculator.h"

//recieves a string, 
//calculates the string's value as a prefix expression of one operator and two operands,
//parses the expression, calculates using the calculate function
//returns this value as a string
char* calculator(char* input){
   
   char operator;
   int a;
   int b;
   printf("Input: %s\n", input);
   sscanf(input, "%c %d %d", &operator, &a, &b);
   
   printf( "operator: %c\n", operator );
   printf( "a: %d\n", a );
   printf( "b: %d\n", b );
   
   int result = calculate ( operator, a, b );
   
   printf( "result: %d\n", result );
   
   sprintf( input, "%d\n", result );
   
   return input;
   
}

//recieves an operator and two operands (integers),
//returns the value of the expression as an integer
int calculate( char operator, int a, int b ){
   
   switch (operator) {
      case '+':  
         return (a + b); 
         break;
      case '-':  
         return (a - b); 
         break;
      case '*':  
         return (a * b); 
         break;
      case '/':  
         if ( b == 0 ) { 
            printf( "Invalid Input, cannot divide by 0"); 
            return 0; 
         } 
         else { 
            return (a / b); 
         } 
         break;
      case '%':  
         return (a % b); 
         break;
      default: 
         printf( "Invalid Operator: %c\n", operator ); 
         return 0; 
         break;
   }
   
}



