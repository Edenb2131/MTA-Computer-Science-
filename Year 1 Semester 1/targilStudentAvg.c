//
// Created by Eden Bar on 25/11/2021.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 10
#define MIN_NUMBER_OF_EX 2
#define MAX_NUMBER_OF_EX 13
#define MIN_NUMBER_OF_LIMIT 0
#define MAX_NUMBER_OF_LIMIT 100
#define PASSING_GRADE 60
#define FIRST_MIN_GRADE 30
#define LAST_MAX_GRADE 100


//Declaring the courseInfo struct
struct CourseInfo
{
    int courseNum;
    int grade ;
};
typedef struct CourseInfo COURSE_INFO;

//Getting user input on semester course information
void courseInput(COURSE_INFO data[], int size);

//Sorting the course-array by Course Number of the semester
void sortCourses( COURSE_INFO data[], int size);

//Sorting an integer Array
void sortIntArray(int data[], int size);

//Printing the Course-Array's
void printCourses( COURSE_INFO data[], int size);

//Uniting two Course-Array's into one - or in semester A or in semster B
int unite (COURSE_INFO dataA[], int sizeA,COURSE_INFO dataB[], int sizeB, int uniteCourse[] );

//Courses the common to semester A and semester B
int intersect (COURSE_INFO dataA[], int sizeA,COURSE_INFO dataB[], int sizeB, int interCourse[] );

//Finding min grade in semester and returning Course
COURSE_INFO findMinGrade( COURSE_INFO data[], int size);

//Getting grades in array
void gettingGrades(int grades[], int size);

//Printing gradeArray
void printArray(int grades[], int size);

//Swapping between integers in Array
void swapInt(int grades[], int i,int j);

//Changing first and last grade in Grade-Array
void changeFirstLast(int grades[], int size);

//finding Failed grades follows by passing grade
int findFailPass (const int grades[], int size);

//Reordering Grade-Array from lowest to limit and limit to highest
int reorderGrades (int grades[], int size, int limit);

void main() {

    //Declaring variables
    COURSE_INFO semesterA[MAX_SIZE] = {};
    COURSE_INFO semesterB[MAX_SIZE] = {};
    int unitedCourseNum[MAX_SIZE] = {}; // united course-array
    int intersectCourseNum[MAX_SIZE] = {}; //intersected course-array
    int numOfCoursesInSemesterA = 0, numOfCoursesInSemesterB = 0; //how many courses are in each semester
    int numOfCoursesInUnitedArray = 0, numOfCoursesInIntersectedArray = 0; //length of new arrays
    int i = 0, numOfEX = 0, numOfLimit = 0;
    int grades[MAX_SIZE] = {};


    //Printing welcome massage
    printf(" Welcome students!!\nand bye bye Pizzeria\n");

    //Getting input for semester A
    printf("Please enter number of courses in semester A:\n");
    scanf("%d",&numOfCoursesInSemesterA);
    courseInput(semesterA,numOfCoursesInSemesterA);

    //Getting input for semester B
    printf("Please enter number of courses in semester B:\n");
    scanf("%d",&numOfCoursesInSemesterB);
    courseInput(semesterB,numOfCoursesInSemesterB);


    //Sorting by Course Number semester A
    sortCourses(semesterA ,numOfCoursesInSemesterA);

    //Sorting by Course Number semester A
    sortCourses(semesterB ,numOfCoursesInSemesterB);


    //Printing the sorted Course-Array
    printf("Sorted courses of semester A:\n"); // printing semester A
    printCourses(semesterA,numOfCoursesInSemesterA);

    printf("Sorted courses of semester B:\n"); // printing semester B
    printCourses(semesterB,numOfCoursesInSemesterB);


    //checking to see how many courses are in semester A or in semester B and returning integer
    numOfCoursesInUnitedArray = unite(semesterA,numOfCoursesInSemesterA,semesterB,numOfCoursesInSemesterB,unitedCourseNum);

    //printing United-Array
    printf("courses taken in semester A or semester B: ");

    for(i= 0; i<numOfCoursesInUnitedArray; i++)
        printf("%d ",unitedCourseNum[i]);
    printf("\n");


    //checking to see how many courses are in semester A AND in semester B and returning integer
    numOfCoursesInIntersectedArray = intersect(semesterA,numOfCoursesInSemesterA,semesterB,numOfCoursesInSemesterB,intersectCourseNum);

    //printing Intersected-Array
    printf("courses taken in semester A and semester B: ");
    for(i= 0; i<numOfCoursesInIntersectedArray; i++)
        printf("%d ",intersectCourseNum[i]);
    printf("\n");

    COURSE_INFO minGrade = findMinGrade(semesterA,numOfCoursesInSemesterA);

    //Printing the minimum grade in semester A:
    printf("Minimum grade in semester A is: %d in course #%d\n", minGrade.grade, minGrade.courseNum);

    //Asking how many exercises were
    printf("How many exercises were given in course #%d? \n",minGrade.courseNum);
    scanf("%d",&numOfEX);

    //Checking to see if valid input
    while(numOfEX < MIN_NUMBER_OF_EX || numOfEX > MAX_NUMBER_OF_EX){
        printf("Invalid input. Try again.");
        printf("How many exercises were given in course #%d? \n",minGrade.courseNum);
        scanf("%d",&numOfEX);
    }

    //Getting grades-array
    gettingGrades(grades,numOfEX);

    //Changing the first and last grade to 30 and 100
    changeFirstLast(grades,numOfEX);

    //printing grades-array
    printf("Exercise grades: ");
    printArray(grades,numOfEX);
    printf("\n");

    //Telling the user of the index of Fail-Pass
    printf("Index of Fail-Pass is: %d\n", findFailPass(grades,numOfEX));
    printf("\n");

    //Asking the user for a Limit index
    printf("Please enter a limit grade:\n");
    scanf("%d",&numOfLimit);

    //Checking to see if valid input
    while(numOfLimit < MIN_NUMBER_OF_LIMIT || numOfLimit > MAX_NUMBER_OF_LIMIT){
        printf("Invalid input. Try again.\n");
        printf("Please enter a limit grade:\n");
        scanf("%d",&numOfLimit);
    }


    printf("After reordering grades, the grades smaller than %d are: ",numOfLimit);
    printArray(grades, reorderGrades(grades,numOfEX,numOfLimit));
}


//Getting user input on semester course information
void courseInput(COURSE_INFO data[], int size){
    int i=0;
    for(i = 0; i < size; i++){
        printf("Enter course number and grade:");
        scanf("%d %d",&data[i].courseNum, &data[i].grade);
        printf("\n");
    }
}

//Sorting the course-array by Course Number of the semester
void sortCourses( COURSE_INFO data[], int size){
    //We will be using bubble sorting in this case so the efficiency is : O(n^2)

    int i, j;

    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - i - 1; j++){
            if(data[j].courseNum > data[j+1].courseNum){ // bubble sorting
                //making temp verbals - Can make swap func but don't need cuz occurring 1 time
                int tempCourseNum = data[j].courseNum;
                int tempCourseGrade = data[j].grade;

                //swapping between items
                data[j].courseNum = data[j+1].courseNum;
                data[j].grade = data[j+1].grade;

                data[j+1].courseNum = tempCourseNum;
                data[j+1].grade = tempCourseGrade;


            }

        }

    }

}

//Sorting an integer Array - with bubble sorting O(N^2)
void sortIntArray(int data[], int size){
    int i,j;

    for(i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if(data[j] > data[j+1]){
                //declaring temp
                int temp = data[j];
                //swapping
                data[j] = data[j+1];
                data[i+1] = temp;
            }
        }
    }


}

//Printing the Course-Array's
void printCourses( COURSE_INFO data[], int size){
    int i;
    //Printing header
    printf("Course# Grade\n");
    printf("======= =====\n");

    for(i=0;i<size;i++)
        printf("%d\t%d\n",data[i].courseNum, data[i].grade);

    printf("\n");
}

//Uniting two Course-Array's into one ## efficiency O(N) ##
int unite (COURSE_INFO dataA[], int sizeA,COURSE_INFO dataB[], int sizeB, int uniteCourse[] ){
    //## efficiency O(N) ##
    int indexA = 0, indexB = 0, unitedLength = 0;

    while(indexA !=sizeA && indexB != sizeB){

        if(dataA[indexA].courseNum > dataB[indexB].courseNum){ // if semester A > semester B
            uniteCourse[unitedLength] = dataB[indexB].courseNum;
            indexB++;
            unitedLength++;
        }
        else if(dataA[indexA].courseNum < dataB[indexB].courseNum){ //if semester B > semester A
            uniteCourse[unitedLength] = dataA[indexA].courseNum;
            indexA++;
            unitedLength++;
        }
        else { // when they are equal
            uniteCourse[unitedLength] = dataA[indexA].courseNum;
            indexA++;
            indexB++;
            unitedLength++;
        }
    }
    //Adding all the other indexes that weren't included
    if(indexA == sizeA){ // if A is smaller then here
        while (indexB != sizeB){
            uniteCourse[unitedLength] = dataB[indexB].courseNum;
            indexB++;
            unitedLength++;
        }
    }
    else if(indexB == sizeB){ // if B is smaller then here
        while (indexA != sizeA){
            uniteCourse[unitedLength] = dataA[indexA].courseNum;
            indexA++;
            unitedLength++;
        }
    }

    return unitedLength;
}

//Courses that common to semester A and semester B ## efficiency O(N^2) ##
int intersect (COURSE_INFO dataA[], int sizeA,COURSE_INFO dataB[], int sizeB, int interCourse[] ){
    //## efficiency O(N^2) ##

    int interNum = 0, i = 0, j = 0;
    //checking to see which array is smaller

    if(sizeA > sizeB) {
        for (i = 0; i < sizeA; i++) {
            for (j = 0; j < sizeB; j++) {
                if (dataA[i].courseNum == dataB[j].courseNum) {
                    interCourse[interNum] = dataA[i].courseNum;
                    interNum++;
                }
            }
        }
    }
    else if(sizeA <= sizeB){
        for (i = 0; i < sizeA; i++) {
            for (j = 0; j < sizeB; j++) {
                if (dataA[i].courseNum == dataB[j].courseNum) {
                    interCourse[interNum] = dataA[i].courseNum;
                    interNum++;
                }
            }
        }
    }
    return interNum;

}

//Finding min grade in semester and returning Course
COURSE_INFO findMinGrade( COURSE_INFO data[], int size){

    int indexMin = 0, i;
    for(i = 0; i<size; i++){

        if(data[i].grade < data[indexMin].grade){
            indexMin = i;
        }
    }

    return data[indexMin];
}

//Getting grades in array
void gettingGrades(int grades[], int size){
    int i;
    printf("Enter exercises grades:\n");

    for(i = 0; i < size; i++){
        scanf("%d",&grades[i]);
    }

}

//Printing gradeArray
void printArray(int grades[], int size){
    int i;

    for(i = 0; i<size; i++)
        printf("%d ",grades[i]);
}

//Swapping between integers in Array
void swapInt(int grades[], int i,int j){

    int temp = grades[i];
    grades[i] = grades[j];
    grades[j] = temp;

}

//Changing first and last grade in Grade-Array
void changeFirstLast(int grades[], int size){
    grades[0] = FIRST_MIN_GRADE;
    grades[size-1] = LAST_MAX_GRADE;
}

//finding Failed grades follows by Passing grade ## efficiency Log(N) ##
int findFailPass (const int grades[], int size){
//    ## efficiency Log(N) ##
    int left = 0, right = size -1 , mid;
    while(left <= right){

        mid = (left + right)/2;
        if(grades[mid] < PASSING_GRADE && grades[mid+1] >= PASSING_GRADE)
            return mid;
        if(grades[mid]>=60)
            right = mid -1;
        else
            left = mid + 1;
    }
    // no match the function will return -1
    return -1;
}

//Reordering Grade-Array from lowest to limit and limit to highest ##efficiency O(N^2)##
int reorderGrades (int grades[], int size, int limit){
    //efficiency O(N^2)

    int i, j;
    int indexLowerHigher = 0;

    for (i = 0; i < size; i++) {
        if (grades[i] >= limit) {
            for (j = i + 1; j < size; j++) {
                if (grades[j] < limit) {
                    swapInt(grades, i, j);
                    indexLowerHigher++;
                    break;
                }
            }
        } else {
            indexLowerHigher++;
        }
    }

    return indexLowerHigher;
}
