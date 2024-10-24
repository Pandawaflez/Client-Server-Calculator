//calcualtorTest.c

#include<stdio.h>
#include"calculator.h"

int main(){
   
   printf("Testing...\n");
   
   char str[] = "* 30 100";
   printf("sigma\n");
   char* result = calculator( str );
   printf("Alpha\n");
   printf("Result: %s\n", result);
   
}
