#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define SUBJECTS 5
#define NAME_LENGTH 50

const char *subjectNames[SUBJECTS] = {
    "C Programming",
    "DBMS",
    "Mathematics",
    "Web Technology",
    "Computer Networks"
};

typedef struct {
    char name[NAME_LENGTH];
    char rollNo[20];
    int marks[SUBJECTS];
    int total;
    float percentage;
    char grade;
    int passed;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

/* Calculate total, percentage, grade and result */
void analyzeStudent(Student *s) {
    s->total = 0;
    s->passed = 1;

    for (int i = 0; i < SUBJECTS; i++) {
        s->total += s->marks[i];

        if (s->marks[i] < 33) {
            s->passed = 0;
        }
    }

    s->percentage = (float)s->total / SUBJECTS;

    if (!s->passed)
        s->grade = 'F';
    else if (s->percentage >= 90)
        s->grade = 'A';
    else if (s->percentage >= 80)
        s->grade = 'B';
    else if (s->percentage >= 70)
        s->grade = 'C';
    else if (s->percentage >= 60)
        s->grade = 'D';
    else if (s->percentage >= 33)
        s->grade = 'E';
    else
        s->grade = 'F';
}

/* Find student using roll number */
int findStudent(const char rollNo[]) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].rollNo, rollNo) == 0) {
            return i;
        }
    }

    return -1;
}

/* Display one student's report */
void displayStudent(const Student *s) {
    printf("\n====================================\n");
    printf("       STUDENT PERFORMANCE REPORT\n");
    printf("====================================\n");

    printf("Name       : %s\n", s->name);
    printf("Roll Number: %s\n", s->rollNo);

    printf("\nSubject-wise Marks:\n");

    for (int i = 0; i < SUBJECTS; i++) {
        printf("%-22s : %d/100\n",
               subjectNames[i], s->marks[i]);
    }

    printf("------------------------------------\n");
    printf("Total Marks : %d/%d\n",
           s->total, SUBJECTS * 100);
    printf("Percentage  : %.2f%%\n", s->percentage);
    printf("Grade       : %c\n", s->grade);
    printf("Result      : %s\n",
           s->passed ? "PASS" : "FAIL");

    if (s->percentage >= 80 && s->passed)
        printf("Performance : Excellent\n");
    else if (s->percentage >= 60 && s->passed)
        printf("Performance : Good\n");
    else if (s->passed)
        printf("Performance : Needs Improvement\n");
    else
        printf("Performance : At Risk\n");

    printf("====================================\n");
}

/* Add a new student */
void addStudent(void) {
    Student s;

    if (studentCount >= MAX_STUDENTS) {
        printf("\nStudent record limit reached.\n");
        return;
    }

    printf("\n--- ADD STUDENT ---\n");

    printf("Enter student name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter roll number: ");
    scanf(" %19s", s.rollNo);

    if (findStudent(s.rollNo) != -1) {
        printf("This roll number already exists.\n");
        return;
    }

    for (int i = 0; i < SUBJECTS; i++) {
        while (1) {
            printf("Enter marks in %s (0-100): ",
                   subjectNames[i]);

            if (scanf("%d", &s.marks[i]) != 1) {
                printf("Invalid input. Enter a whole number.\n");

                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {
                }
                continue;
            }

            if (s.marks[i] < 0 || s.marks[i] > 100) {
                printf("Marks must be between 0 and 100.\n");
                continue;
            }

            break;
        }
    }

    analyzeStudent(&s);
    students[studentCount] = s;
    studentCount++;

    printf("\nStudent record saved successfully!\n");
    displayStudent(&s);
}

/* View all student records */
void viewAllStudents(void) {
    if (studentCount == 0) {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n================ STUDENT RECORDS ================\n");
    printf("%-15s %-15s %-8s %-12s %-8s %-8s\n",
           "Name", "Roll No", "Total", "Percentage",
           "Grade", "Result");

    for (int i = 0; i < studentCount; i++) {
        printf("%-15.15s %-15.15s %3d/500   %7.2f%%    %-8c %-8s\n",
               students[i].name,
               students[i].rollNo,
               students[i].total,
               students[i].percentage,
               students[i].grade,
               students[i].passed ? "PASS" : "FAIL");
    }

    printf("==================================================\n");
}

/* Search by roll number */
void searchStudent(void) {
    char rollNo[20];

    printf("\nEnter roll number to search: ");
    scanf(" %19s", rollNo);

    int index = findStudent(rollNo);

    if (index == -1) {
        printf("Student not found.\n");
    } else {
        displayStudent(&students[index]);
    }
}

/* Show subject-wise class averages */
void showSubjectAverages(void) {
    if (studentCount == 0) {
        printf("\nNo records available to analyze.\n");
        return;
    }

    printf("\n--- SUBJECT-WISE CLASS AVERAGES ---\n");

    for (int j = 0; j < SUBJECTS; j++) {
        int sum = 0;

        for (int i = 0; i < studentCount; i++) {
            sum += students[i].marks[j];
        }

        printf("%-22s : %.2f/100\n",
               subjectNames[j],
               (float)sum / studentCount);
    }
}

/* Main menu */
int main(void) {
    int choice;

    do {
        printf("\n\n====================================\n");
        printf("   STUDENT PERFORMANCE ANALYZER\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. View All Student Records\n");
        printf("3. Search Student\n");
        printf("4. Subject-wise Class Averages\n");
        printf("5. Exit\n");
        printf("====================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Please enter a valid menu number.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                viewAllStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                showSubjectAverages();
                break;

            case 5:
                printf("\nThank you for using the program!\n");
                break;

            default:
                printf("Invalid choice. Please select 1-5.\n");
        }

    } while (choice != 5);

    return 0;
}