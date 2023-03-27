#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char * argv[])
{
    short pointsFlag = 0, iterationsFlag = 0;
    if (commandLineProceeding(argc, argv, &pointsFlag, &iterationsFlag) <= 0)
        return 0;
    float leftBoundary, rightBoundary, eps1; // left boundary, right boundary, eps1 - accuracy of abscissa of points search
    unsigned eps2, iterations = 0; // eps2 - accuracy of integral search, iterations - number of iterations
    float abscissaf1f2, abscissaf1f3, abscissaf2f3; // abscissa of the curves intersections
    system("clear");
    printf("\tWelcome to the Calculator of flat figure area v1.0\n\n");
    printf("Enter parameters in the next format: [left boundary] [right boundary] [accuracy of points search] [accuracy of integral search]\n");
    inputFunction(&leftBoundary, &rightBoundary, &eps1, &eps2);
    abscissaf1f2 = root(functionOne, functionTwo, leftBoundary, rightBoundary, eps1, &iterations);
    if (!abscissaf1f2)
    {
        printf("\nThere are no intersection points and it is impossible to calculate the area on this range. Enter another range:\n");
        inputFunction(&leftBoundary, &rightBoundary, &eps1, &eps2);
    }
    abscissaf1f3 = root(functionOne, functionThree, leftBoundary, rightBoundary, eps1, &iterations);
    if (!abscissaf1f3)
    {
        printf("\nThere are no intersection points and it is impossible to calculate the area on this range. Enter another range:\n");
        inputFunction(&leftBoundary, &rightBoundary, &eps1, &eps2);
    }
    abscissaf2f3 = root(functionTwo, functionThree, leftBoundary, rightBoundary, eps1, &iterations);
    if (!abscissaf2f3)
    {
        printf("\nThere are no intersection points and it is impossible to calculate the area on this range. Enter another range:\n");
        inputFunction(&leftBoundary, &rightBoundary, &eps1, &eps2);
    }
    if (pointsFlag)
        printAbscissa(abscissaf1f2, abscissaf1f3, abscissaf2f3);
    if (iterationsFlag)
        printf("\nNumber of iterations required to calculate the intersection abscissa = %u\n", iterations);
    float area = integral(abscissaf1f3, abscissaf1f2, eps2, functionOne) - integral(abscissaf2f3, abscissaf1f2, eps2, functionTwo) - integral(abscissaf1f3, abscissaf2f3, eps2, functionThree);
    printf("\nArea of the given figure = %.2f\n\n", area);
    return 0;
}
