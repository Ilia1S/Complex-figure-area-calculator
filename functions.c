#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include "functions.h"

int commandLineProceeding(int argc, char * argv[], short *pointsFlag, short *iterationsFlag)
{
    static struct option long_options[] =
    {
        {"help", 0, 0, 'h'},
        {NULL, 0, NULL, 0}
    };
    int opt, option_index = 0;
    float leftBoundary, rightBoundary, eps1;
    unsigned eps2, iterations = 0;
    char *option = "-t"; // run test functions
    char *arg1 = NULL, *arg2 = NULL, *arg3 = NULL, *arg4 = NULL; // arguments of -t
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], option))
        {
            if (i+4 < argc)
            {
                arg1 = argv[i+1];
                arg2 = argv[i+2];
                arg3 = argv[i+3];
                arg4 = argv[i+4];
            }
            else
            {
                printf("\nError: option -t requires 4 arguments\n\n");
                return -1;
            }
        }
    }
    if (arg1 && arg2 && arg3 && arg4)
    {
        if (!strcmp(arg1, "F1") || !strcmp(arg1, "F2") || !strcmp(arg1, "F3"))
        {
            float intersectionAbscissa = 0;
            char *endptr;
            leftBoundary = strtof(arg2, &endptr);
            if (*endptr != '\0')
            {
                printf("\nError: invalid argument character\n\n");
                return -1;
            }
            rightBoundary = strtof(arg3, &endptr);
            if (*endptr != '\0')
            {
                printf("\nError: invalid argument character\n\n");
                return -1;
            }
            eps1 = strtof(arg4, &endptr);
            if (*endptr != '\0')
            {
                printf("\nError: invalid argument character\n\n");
                return -1;
            }
            if (eps1 > 0.5)
            {
                printf("\nError: accarucy of points search is too low (>0.5)\n\n");
                return -1;
            }
            else if (eps1 <= 0)
            {
                printf("\nError: accarucy of points search is invalid (<=0)\n\n");
                return -1;
            }
            if (!strcmp(arg1, "F1"))
            {
                intersectionAbscissa = root(functionOne, functionTwo, leftBoundary, rightBoundary, eps1, &iterations);
                if (intersectionAbscissa)
                {
                    printf ("\nFunction F1 intersects Function F2 at point x = %.2f\n\n", intersectionAbscissa);
                    return 0;
                }
            }
            else if (!strcmp(arg1, "F2"))
            {
                if (leftBoundary * rightBoundary <= 0)
                {
                    printf("\nError: invalid parameters. Zero cannot be between ranges\n\n");
                    return -1;
                }
                intersectionAbscissa = root(functionOne, functionThree, leftBoundary, rightBoundary, eps1, &iterations);
                if (intersectionAbscissa)
                {
                    printf ("\nFunction F1 intersects Function F3 at point x = %.2f\n\n", intersectionAbscissa);
                    return 0;
                }
            }
            else if (!strcmp(arg1, "F3"))
            {
                if (leftBoundary * rightBoundary <= 0)
                {
                    printf("\nError: invalid parameters. Zero cannot be between ranges\n\n");
                    return -1;
                }
                intersectionAbscissa = root(functionTwo, functionThree, leftBoundary, rightBoundary, eps1, &iterations);
                if (intersectionAbscissa)
                {
                    printf ("\nFunction F2 intersects Function F3 at point x = %.2f\n\n", intersectionAbscissa);
                    return 0;
                }
            }
            if (!intersectionAbscissa)
            {
                printf("\nThere are no intersection points on this range\n\n");
                return 0;
            }
        }
        else if (!strcmp(arg1, "F4") || !strcmp(arg1, "F5") || !strcmp(arg1, "F6"))
        {
            char *endptr;
            float testIntegral;
            leftBoundary = strtof(arg2, &endptr);
            if (*endptr != '\0')
            {
                printf("\nError: invalid argument character\n\n");
                return -1;
            }
            rightBoundary = strtof(arg3, &endptr);
            if (*endptr != '\0')
            {
                printf("\nError: invalid argument character\n\n");
                return -1;
            }
            if (leftBoundary > rightBoundary)
            {
                printf("\nError: left boundary cannot be greater than right\n\n");
                return -1;
            }
            eps2 = strtof(arg4, &endptr);
            if (*endptr != '\0')
            {
                printf("\nError: invalid argument character\n\n");
                return -1;
            }
            if (eps2 < 10)
            {
                printf("\nAccarucy of integral search is too low (<10)\n\n");
                return -1;
            }
            if (!strcmp(arg1, "F4"))
            {
                testIntegral = integral(leftBoundary, rightBoundary, eps2, functionOne);
                printf ("\nIntegral of F1 between %.2f and %.2f = %.2f\n\n", leftBoundary, rightBoundary, testIntegral);
                return 0;
            }
            else if (!strcmp(arg1, "F5"))
            {
                testIntegral = integral(leftBoundary, rightBoundary, eps2, functionTwo);
                printf ("\nIntegral of F2 between %.2f and %.2f = %.2f\n\n", leftBoundary, rightBoundary, testIntegral);
                return 0;
            }
            else if (!strcmp(arg1, "F6"))
            {
                if (leftBoundary * rightBoundary <= 0)
                {
                    printf("\nError: integral is divergent. Zero cannot be within ranges\n\n");
                    return -1;
                }
                testIntegral = integral(leftBoundary, rightBoundary, eps2, functionThree);
                printf ("\nIntegral of F3 between %.2f and %.2f = %.2f\n\n", leftBoundary, rightBoundary, testIntegral);
                return 0;
            }
        }
        else
        {
            printf("\nError: invalid function name\n\n");
            return -1;
        }
    }
    while ((opt = getopt_long(argc, argv, "pih", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
            case 'p':
                *pointsFlag = 1;
                break;
            case 'i':
                *iterationsFlag = 1;
                break;
            case 'h':
                helpFunc();
                return 0;
            default:
                printf("Unknown option. Refer to help using command -h or --help\n\n");
                return 0;
        }
        if (opt == 'h')
            break;
    }
    return 0;
}
void inputFunction(float *leftBoundary, float *rightBoundary, float *eps1, unsigned *eps2)
{
    int inputCheck;
    do
    {
        inputCheck = scanf("%f %f %f %u", leftBoundary, rightBoundary, eps1, eps2);
        if (inputCheck != 4)
        {
            printf("\nInput error: invalid parameters. Enter another parameters:\n");
            while (getchar() != '\n');
        }
    }
    while (inputCheck != 4);
    if (((*leftBoundary)*(*rightBoundary) <= 0) || (*leftBoundary) > (*rightBoundary) || ((*eps1) > 0.5) || ((*eps1) <= 0) || ((*eps2) < 10))
    {
        if ((*leftBoundary)*(*rightBoundary) <= 0)
            printf("\nError: left boundary cannot be greater than right\n");
        if ((*leftBoundary) > (*rightBoundary))
            printf("\nError: Zero cannot be within ranges\n");
        if ((*eps1) > 0.5)
            printf("\nError: accarucy of points search is too low (>0.5)\n");
        if ((*eps1) <= 0)
            printf("\nError: accarucy of points search is invalid (<=0)\n");
        if ((*eps2) < 10)
            printf("\nError: accarucy of integral search is too low (<10)\n");
        printf("\nEnter another parameters:\n");
        inputFunction(leftBoundary, rightBoundary, eps1, eps2);
    }
}
float root(float (*function1)(float), float (*function2)(float), float leftBoundary, float rightBoundary, float eps1, unsigned *iterations)
{
    float midPoint;
    do
    {
        (*iterations)++;
        midPoint = (leftBoundary + rightBoundary)/2.0;
        if ( (function1(leftBoundary) - function2(leftBoundary)) * (function1(midPoint) - function2(midPoint)) < 0)
            rightBoundary = midPoint;
        else
            leftBoundary = midPoint;
        if (fabs(leftBoundary - rightBoundary) < 0.0001)
            return 0;
    }
    while(fabs(function1(midPoint) - function2(midPoint)) > eps1);
    return midPoint;
}
float integral(float leftBoundary, float rightBoundary, unsigned eps2, float (*function)(float))
{
    float h = (rightBoundary - leftBoundary) / eps2;
    float sum = function(leftBoundary) + function(rightBoundary);
    for (unsigned i = 1; i < eps2; i += 2)
    {
        float x = leftBoundary + i * h;
        sum += 4 * function(x);
    }
    for (unsigned i = 2; i < eps2; i += 2)
    {
        float x = leftBoundary + i * h;
        sum += 2 * function(x);
    }
    return (h / 3) * sum;
}
float functionOne(float x)
{
    return 0.6*x + 3;
}
float functionTwo(float x)
{
    return (powf(x-2, 3) - 1);
}
float functionThree(float x)
{
    return 3/x;
}
void printAbscissa(float abscissaf1f2, float abscissaf1f3, float abscissaf2f3)
{
    printf("\nFunction F1 intersects Function F2 at point x = %.2f\n", abscissaf1f2);
    printf("Function F1 intersects Function F3 at point x = %.2f\n", abscissaf1f3);
    printf("Function F2 intersects Function F3 at point x = %.2f\n", abscissaf2f3);
}
void helpFunc(void)
{
    system("clear");
    printf("The Calculator of flat figure area v1.0 has the next command line options:\n");
    printf("\t--help - go to this page\n");
    printf("\t-p - print the abscissa of the curves intersections\n");
    printf("\t-i - print the number of iterations required to calculate the intersection abscissa\n");
    printf("\t-t - run functions testing. This options must have 4 arguments: function number (from F1 to F6), left boundary, right boundary and accuracy of search\n");
    printf("\tYou can run the program with or without options\n");
    printf("Enter any character to quit: ");
    char w;
    scanf("%c", &w);
}
