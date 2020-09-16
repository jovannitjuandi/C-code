// Test file to test the function "arrayAverage".

#include <stdio.h>
#include <math.h>

double arrayAverage(int a[], int size);

void checkArrayAverage(int test_no, int a[], int size, double expected_answer) {

    double student_answer = arrayAverage(a, size);
    
    printf("------------- \n");
    if (fabs(student_answer - expected_answer) < 0.000001) {
        printf("Test %d Passed\n\n", test_no);
        return;
    }
    
    printf("Test %d Failed!, see below for the expected answer.\n", test_no);
    int i = 0;
    printf("  Array is: ");
    while (i < size) {
        printf("%d, ", a[i]);
        i++; 
    }
    printf("\n");
    printf("  Average value, expected: %lf, your answer: %lf\n\n", expected_answer, student_answer);

}

int main(int argc, char *argv[]) {
 
    int a1[]  = {1, 2, 3};
    checkArrayAverage(1, a1, 3, 2.0); 
    
    int a2[]  = {5, 2, 6, 1};
    checkArrayAverage(2, a2, 4, 3.5);  

    int a3[]  = {-5, 7, 2, 0, 11, -12};
    checkArrayAverage(3, a3, 6, 0.5);  

    int a4[]  = {-3, 5, 6, 1, -2};
    checkArrayAverage(4, a4, 5, 1.4);  

    int a5[]  = {0, 0, 0, 0};
    checkArrayAverage(5, a5, 4, 0);  

    int a6[]  = {3, 4, 7};
    checkArrayAverage(6, a6, 3, 4.6666666);  

    //int a7[]  = {};
    //checkArrayAverage(7, a7, 0, void); 
 
    // Add more test cases here ... 


    return 0;
}


