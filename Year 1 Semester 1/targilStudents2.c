//
// Created by Eden Bar on 02/12/2021.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LEN 11
#define MAX_FULL_NAME_LEN 22
#define MAX_COURSES 10
#define GROUP_STUDENT_NUMBER 3
#define STUDENTS_NUMBER 6
#define MAX_STUDENT_NUMBER 7
#define GROUP_A 0
#define GROUP_B 1
#define GROUP_C 2
#define GROUP_NAME_LEN 8
#define GROUP_A_NAME "GROUP A"
#define GROUP_B_NAME "GROUP B"
#define GROUP_C_NAME "GROUP C"


//Declaring the courseInfo struct
struct CourseInfo
{
    int courseNum;
    int grade ;
};
typedef struct CourseInfo COURSE_INFO;

//Declaring the Student struct
struct Student
{
    char name[MAX_FULL_NAME_LEN];
    int identity;
    int nofCourses; //number of courses taken in semesterA
    COURSE_INFO course_info[MAX_COURSES];
};
typedef struct Student STUDENT;

//Printing welcome massage
void welcomeStudents();

//Getting input for Student-Array
void studentInput(STUDENT Student[][STUDENTS_NUMBER]);

//getting Name of students
void gettingNameOfStudent(STUDENT Student[][STUDENTS_NUMBER], int i, int j);

//Printing StudentName - Array
void printStudentNameArray(char stuNames[][MAX_FULL_NAME_LEN + GROUP_NAME_LEN], int size);

//Getting user input on semester course information
void courseInput(COURSE_INFO data[], int size);

//Getting Students that learn this Course
int getStudentNames( STUDENT stuData[][STUDENTS_NUMBER], int rows, int cols,int courseNum,char stuNames[][MAX_FULL_NAME_LEN + GROUP_NAME_LEN]);

//Switching Lois to Lane - First and Last name if needed
void switchingLoisToLane(char stuNames[][MAX_FULL_NAME_LEN + GROUP_NAME_LEN], int size);

//Deleting the name Lex from studentName-Array
void deleteLexName(char stuNames[][MAX_FULL_NAME_LEN + GROUP_NAME_LEN], int size);

//Checking if has Lex in name
bool isStringHasLex(char string[]);

//Making a two dem Grades-Array that took specific course
void setAndPrintGrades(int courseGrades[][MAX_STUDENT_NUMBER],STUDENT stuData[][STUDENTS_NUMBER],int courseNum, int size);

//Searching for the second maximum number in Grade-Array
void secondMaxGradeInGradeArray(int courseGrades[][MAX_STUDENT_NUMBER]);

void main() {
    //Declaring variables
    STUDENT students[GROUP_STUDENT_NUMBER][STUDENTS_NUMBER] = {};
    char stuNames[GROUP_STUDENT_NUMBER*MAX_STUDENT_NUMBER][MAX_FULL_NAME_LEN + GROUP_NAME_LEN] = {};
    int courseGrades[GROUP_STUDENT_NUMBER][MAX_STUDENT_NUMBER];
    int courseNumToCheck = 0,numOfStudentGoingToCourseCheck = 0;

    //Printing welcome massage
    welcomeStudents();

    //Getting input for Student-Array
    studentInput(students);

    //Getting course number to check for which student studied it
    printf("\nEnter a course number: ");
    scanf("%d",&courseNumToCheck);
    numOfStudentGoingToCourseCheck = getStudentNames(students,GROUP_STUDENT_NUMBER,STUDENTS_NUMBER,courseNumToCheck,stuNames);

    //Changing Lois name to Lane
    printf("Names after changing \"Lois\" to \"Lane\":\n");
    switchingLoisToLane(stuNames, numOfStudentGoingToCourseCheck);

    //Deleting Lex name from studentName - Array
    printf("\nNames after deleting names with \"Lex\": \n");
    deleteLexName(stuNames, numOfStudentGoingToCourseCheck);

    //Making a two dem Grades-Array that took specific course
    printf("\nGrades in course#%d:\n",courseNumToCheck);
    setAndPrintGrades(courseGrades,students,courseNumToCheck,numOfStudentGoingToCourseCheck);


    //Searching for the second maximum number in Grade-Array
    printf("\nMaximum grades in course#%d:\n",courseNumToCheck);
    secondMaxGradeInGradeArray(courseGrades);

}


//Printing welcome massage
void welcomeStudents(){
    printf(" ********************\n");
    printf("* Welcome Students *\n");
    printf("********************\n");
}

//Getting input for Student-Array
void studentInput(STUDENT student[][STUDENTS_NUMBER]){

    int i = 0,j = 0;
    //printf("\n");
    for(i = 0; i < GROUP_STUDENT_NUMBER; i ++){
        if(i == GROUP_A)
            printf("Enter students data for %s:",GROUP_A_NAME);
        if(i == GROUP_B)
            printf("Enter students data for %s:",GROUP_B_NAME);
        if(i == GROUP_C)
            printf("Enter students data for %s:",GROUP_C_NAME);

        printf("\n________________________________\n");

        for(j = 0; j < STUDENTS_NUMBER; j ++){
            int studentID = 0;

            gettingNameOfStudent(student, i , j);

            //printf("\n");

            printf("Enter student ID: ");
            scanf("%d",&studentID);

            printf("\nEnter number of courses taken in semester A: ");
            scanf("%d",&student[i][j].nofCourses);
            courseInput(student[i][j].course_info,student[i][j].nofCourses);


        }
        //printf("\n");
    }

}

//getting Name of students
void gettingNameOfStudent(STUDENT student[][STUDENTS_NUMBER], int i, int j){

    char firstName[MAX_NAME_LEN] = {};
    char lastName[MAX_NAME_LEN] = {};
    char fullName[MAX_FULL_NAME_LEN] = {};
    printf("\nEnter student first name and last name (seperated by spaces): ");
    scanf("%s",firstName);
    scanf("%s",lastName);

    strcat(firstName," ");

    strcat(fullName, firstName);

    strcat(fullName, lastName);

    //strcat(fullName, "\0");

    strcat(student[i][j].name, fullName);

}

//Printing StudentName - Array
void printStudentNameArray(char stuNames[][MAX_FULL_NAME_LEN + GROUP_NAME_LEN], int size){
    int i=0;
    for(i = 0; i < size; i ++)
        printf("%s\n",stuNames[i]);


}

//Getting user input on semester course information
void courseInput(COURSE_INFO data[], int size){
    int i=0;
    for(i = 0; i < size; i++){
        printf("Enter Course number and grade: ");
        scanf("%d %d",&data[i].courseNum, &data[i].grade);
        //printf("\n");
    }
    //printf("\n");
}

//Getting Students that learn this Course
int getStudentNames( STUDENT stuData[][STUDENTS_NUMBER], int rows, int cols,int courseNum,char stuNames[][MAX_FULL_NAME_LEN + GROUP_NAME_LEN]){
    int numOfStudentsTakingThisCourse = 0;
    int i = 0, j = 0,k = 0;

    printf("Names of students in course#%d:\n",courseNum);

    for(i = 0; i < GROUP_STUDENT_NUMBER; i++) {
        for (j = 0; j < STUDENTS_NUMBER; j++) {
            for (k = 0; k < MAX_COURSES; k++) {
                if (stuData[i][j].course_info[k].courseNum == courseNum) {

                    if (i == GROUP_A) { //Checking for group A
                        strcat(stuNames[numOfStudentsTakingThisCourse], "GroupA ");

                        strcat(stuNames[numOfStudentsTakingThisCourse], stuData[i][j].name);
                        numOfStudentsTakingThisCourse++;
                    }

                    else if (i == GROUP_B) { //Checking for group B
                        strcat(stuNames[numOfStudentsTakingThisCourse], "GroupB ");

                        strcat(stuNames[numOfStudentsTakingThisCourse], stuData[i][j].name);
                        numOfStudentsTakingThisCourse++;
                    }

                    if (i == GROUP_C) { //Checking for group B
                        strcat(stuNames[numOfStudentsTakingThisCourse], "GroupC ");

                        strcat(stuNames[numOfStudentsTakingThisCourse], stuData[i][j].name);
                        numOfStudentsTakingThisCourse++;
                    }

                }
            }

        }
        //printf("%s\n",stuNames[numOfStudentsTakingThisCourse]);
    }
    printStudentNameArray(stuNames, numOfStudentsTakingThisCourse);
    printf("\n");
    return numOfStudentsTakingThisCourse;
}

//Switching Lois to Lane - First and Last name if needed
void switchingLoisToLane(char stuNames[][MAX_FULL_NAME_LEN + GROUP_NAME_LEN], int size){
    int i,j;
    for(i = 0; i < size ; i++) {
        for(j = 0; j < strlen(stuNames[i]) ; j ++){

            if(stuNames[i][j] == 'L' && stuNames[i][j+1] == 'o' && stuNames[i][j+2] == 'i' && stuNames[i][j+3] == 's' ){
                stuNames[i][j] = 'L';
                stuNames[i][j+1] = 'a';
                stuNames[i][j+2] = 'n';
                stuNames[i][j+3] = 'e';
            }
        }
    //    printf("%s\n",stuNames[i]);
    }

    printStudentNameArray(stuNames,size);

}

//Deleting the name Lex from studentName-Array
void deleteLexName(char stuNames[][MAX_FULL_NAME_LEN + GROUP_NAME_LEN], int size){
    int i, j;
    int numberOfDeletedNames = 0;

    for (i = 0; i < size - numberOfDeletedNames; i++) {
        if (isStringHasLex(stuNames[i])) {
            for (j = i; j < size - 1; j++)
                strcpy(stuNames[j], stuNames[j + 1]);
            numberOfDeletedNames++;
            i -= 1;
        }
    }

    for (i = 0; i < size - numberOfDeletedNames; i++) {
        printf("%s\n", stuNames[i]);
    }
}

//if a string containing a Lex
bool isStringHasLex(char string[]) {
    int i = 0;

    for (i = 0; i < strlen(string); i++) {
        if (string[i] == 'L' && string[i + 1] == 'e' && string[i + 2] == 'x') {
            return true;
        }
    }

    return false;
}

//Making a two dem Grades-Array that took specific course
void setAndPrintGrades(int courseGrades[][MAX_STUDENT_NUMBER],STUDENT stuData[][STUDENTS_NUMBER],int courseNum, int size){
    int i,j,k;
    for(i = 0; i < GROUP_STUDENT_NUMBER ; i++){
        int  counter = 0;
        for(j = 0; j < STUDENTS_NUMBER; j++){
            for(k = 0; k < stuData[i][j].nofCourses; k++){
                if(stuData[i][j].course_info[k].courseNum == courseNum) {
                    courseGrades[i][counter+1] = stuData[i][j].course_info[k].grade;
                    counter++;
                }
            }
        }
        courseGrades[i][0] = counter;
    }


    for(i = 0; i < GROUP_STUDENT_NUMBER;i++) {
        if(i == GROUP_A)
            printf("GroupA:");
        if(i == GROUP_B)
            printf("GroupB:");
        if(i == GROUP_C)
            printf("GroupC:");
        //printf("%d ", courseGrades[i][0]);
        for (j = 1; j <= courseGrades[i][0]; j++) {
            printf(" %d", courseGrades[i][j]);
        }
        printf("\n");
    }

}

void secondMaxGradeInGradeArray(int courseGrades[][MAX_STUDENT_NUMBER]) {
    int i, j;
    int firstMaximumGrade = -1, secondMaximumGrade = -1;
    int maximumNumberOfGradesInGroup;
    char currentGroupName;

    for (i = 0; i < GROUP_STUDENT_NUMBER; i++) {
        if(i == GROUP_A)
            currentGroupName = 'A';
        if(i == GROUP_B)
            currentGroupName = 'B';
        if(i == GROUP_C)
            currentGroupName = 'C';

        firstMaximumGrade = -1;
        maximumNumberOfGradesInGroup = courseGrades[i][0];

        for (j = 1; j <= maximumNumberOfGradesInGroup; j++) {
            if (courseGrades[i][j] > firstMaximumGrade) {
                secondMaximumGrade = firstMaximumGrade;
                firstMaximumGrade = courseGrades[i][j];
            } else if (courseGrades[i][j] <= firstMaximumGrade && courseGrades[i][j] > secondMaximumGrade) {
                secondMaximumGrade = courseGrades[i][j];
            }
        }

        if (firstMaximumGrade != -1 && secondMaximumGrade != -1) {
            printf("Group%c: max grade is: %d and second max is: %d\n", currentGroupName, firstMaximumGrade,
                   secondMaximumGrade);
        } else if (firstMaximumGrade != -1 && secondMaximumGrade == -1) {
            printf("Group%c: max grade is: %d (no second max found)\n", currentGroupName, firstMaximumGrade);
        } else {
            printf("Group%c: no grades found in group\n", currentGroupName);
        }
    }
}