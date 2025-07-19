// Student Record Management System.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Date // structure to store date in day, month and year format.
{
    int day;
    int month;
    int year;
} date;

typedef struct Student_Record // structure to store all infromation regarding a student.
{
    long long int student_ID;
    char name[100];
    int age;
    char gender;
    long long int contact_number;
    char email[100];
    char address[100];
    char guardian_name[100];
    long long int guardian_contact;
    char course_enrollment[100];
    date yearof_enrollment;
} record;

int loadFromFile(record **);                // function prototype to load data stored in a file;
void addStudents(record *, int);            // function prototype to add neccessary student details.
void viewAllStudents(record *, int);        // function prototype to view all the students details.
void searchStudentbyID(record *, int);      // function prototype to search a student by its ID number.
void searchStudentbyContact(record *, int); // function prototype to search student by its contact number.
void updateStudentrecorD(record *, int);    // function prototype to update student record.
void deleteStudentrecorD(record *, int *);  // function prototype to delete student record.

int main()
{
    char password[50];
    int match;
    while (1)
    {
        match = 0;
        printf("Enter the password to access the Student Record Database:\n");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
        if (strcmp(password, "hridhiman06") == 0)
        {
            match = 1;
            record *rd = NULL;
            int total_count = loadFromFile(&rd);
            if (total_count == 0)
            {
                printf("No student records loaded from file. Starting fresh.\n");
            }
            else
            {
                printf("Loaded %d student record(s) from file.\n", total_count);
            }
            int choice;
            while (1)
            {
                printf("*******STUDENT RECORD MANAGEMENT SYSTEM*******\n");
                printf("Enter\n 1.To Add Students.\n2.To View All Students Record.\n3.To Search Student by Unique ID number.\n4.To Search Student by Contact number.\n5.To Update Student Record.\n6.To Delete Student record.\n7.To Exit.\n");
                printf("Enter your choice.");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                {
                    int n;
                    printf("How many students do you want to add? ");
                    scanf("%d", &n);
                    getchar();
                    rd = realloc(rd, (total_count + n) * sizeof(record));
                    if (rd == NULL)
                    {
                        printf("Memory allocation failed.\n");
                        return -1;
                    }
                    for (int i = total_count; i < total_count + n; i++)
                    {
                        addStudents(rd, i);
                    }
                    total_count += n;
                    break;
                }
                case 2:
                {
                    if (total_count == 0)
                    {
                        printf("No student records available to view. Please add students first.\n");
                    }
                    else
                    {
                        viewAllStudents(rd, total_count);
                    }
                    break;
                }
                case 3:
                {
                    if (total_count == 0)
                    {
                        printf("No student records available to search. Please add students first.\n");
                    }
                    else
                    {
                        searchStudentbyID(rd, total_count);
                    }
                    break;
                }
                case 4:
                {
                    if (total_count == 0)
                    {
                        printf("No student records available to search. Please add students first.\n");
                    }
                    else
                    {
                        searchStudentbyContact(rd, total_count);
                    }
                    break;
                }
                case 5:
                {
                    if (total_count == 0)
                    {
                        printf("No student records available to update. Please add students first.\n");
                    }
                    else
                    {
                        updateStudentrecorD(rd, total_count);
                    }
                    break;
                }
                case 6:
                {
                    if (total_count == 0)
                    {
                        printf("No student records available to delete. Please add students first.\n");
                    }
                    else
                    {
                        deleteStudentrecorD(rd, &total_count);
                    }
                    break;
                }
                case 7:
                {
                    char ch;
                    printf("You chose to exit.\nEnter Y to exit.\n Enter N to continue.\n");
                    getchar();
                    scanf("%c", &ch);
                    switch (ch)
                    {
                    case 'Y':
                    case 'y':
                    {
                        free(rd);
                        printf("Exiting program.\n");
                        return 0;
                        break;
                    }
                    case 'N':
                    case 'n':
                    {
                        printf("Returning to the menu.\n");
                        break;
                    }
                    }
                    break;
                }
                default:
                {
                    printf("Invalid choice.\n");
                    break;
                }
                }
            }
            break;
        }
        else
        {
            printf("Wrong password. Try again.\n");
        }
    }
}
void addStudents(record *rd, int i)
{
    printf("****************************\n");

    long long tempID;
    int duplicate;

    do
    {
        duplicate = 0;
        printf("Enter ID for student %d:\n", i + 1);
        scanf("%lld", &tempID);
        getchar();

        for (int j = 0; j < i; j++)
        {
            if (rd[j].student_ID == tempID)
            {
                printf("Error: ID %lld already exists. Try again.\n", tempID);
                duplicate = 1;
                break;
            }
        }
    } while (duplicate);

    rd[i].student_ID = tempID;
    printf("Please enter the student's %d full name:\n", i + 1);
    fgets(rd[i].name, sizeof(rd[i].name), stdin);
    rd[i].name[strcspn(rd[i].name, "\n")] = '\0';
    printf("Please enter the student's %d age:\n", i + 1);
    scanf("%d", &rd[i].age);
    getchar();
    printf("Please enter the student's %d gender:\n", i + 1);
    printf("Enter 'M' for Male or'F' for Female or 'T' for not to specify.\n");
    scanf("%c", &rd[i].gender);
    switch (rd[i].gender)
    {
    case 'M':
    case 'm':
    {
        printf("Gender specified as Male.\n");
        break;
    }
    case 'F':
    case 'f':
    {
        printf("Gender specified as Female.\n");
        break;
    }
    case 'T':
    case 't':
    {
        printf("Gender specified as prefer not to say.\n");
        break;
    }
    default:
    {
        printf("Invalid options.");
    }
    }
    printf("Please enter student's %d contact number:\n", i + 1);
    scanf("%lld", &rd[i].contact_number);
    getchar();
    printf("Please enter student's %d email address:\n", i + 1);
    fgets(rd[i].email, sizeof(rd[i].email), stdin);
    rd[i].email[strcspn(rd[i].email, "\n")] = '\0';
    printf("Please enter student's %d residential address:\n", i + 1);
    fgets(rd[i].address, sizeof(rd[i].address), stdin);
    rd[i].address[strcspn(rd[i].address, "\n")] = '\0';
    printf("Please enter the student's %d guardian's name:\n", i + 1);
    fgets(rd[i].guardian_name, sizeof(rd[i].guardian_name), stdin);
    rd[i].guardian_name[strcspn(rd[i].guardian_name, "\n")] = '\0';
    printf("Please enter the student's %d guardian's contact number:\n", i + 1);
    scanf("%lld", &rd[i].guardian_contact);
    getchar();
    printf("Please enter student's %d date of enrollment (DD MM YYYY):\n", i + 1);
    scanf("%d %d %d", &rd[i].yearof_enrollment.day, &rd[i].yearof_enrollment.month, &rd[i].yearof_enrollment.year);
    getchar();
    printf("Please enter name of the course enrolled:\n");
    fgets(rd[i].course_enrollment, sizeof(rd[i].course_enrollment), stdin);
    rd[i].course_enrollment[strcspn(rd[i].course_enrollment, "\n")] = '\0';
    printf("Student %d record added successfully.\n", i + 1);
    // loading the records in a File to save permanently.
    FILE *data;
    data = fopen("student_data.txt", "a");
    if (data == NULL)
    {
        printf("Error. File do not exist.");
        return;
    }
    fprintf(data, "Student ID: %lld.\nName: %s.\nAge: %d.\nGender: %c\nContact Number: %lld\nEmail Address: %s\nResidential Address: %s.\nGuardian Name: %s.\nGuardian Phone Number: %lld\nDate Of Enrollment%d-%d-%d\nEnrolled Course: %s.\n",
            rd[i].student_ID,
            rd[i].name,
            rd[i].age,
            rd[i].gender,
            rd[i].contact_number,
            rd[i].email,
            rd[i].address,
            rd[i].guardian_name,
            rd[i].guardian_contact,
            rd[i].yearof_enrollment.day,
            rd[i].yearof_enrollment.month,
            rd[i].yearof_enrollment.year,
            rd[i].course_enrollment);

    fclose(data);
}
void viewAllStudents(record *rd, int total_count)
{
    for (int i = 0; i < total_count; i++)
    {
        printf("...........................................\n");
        printf("Student's %d ID number:\n", i + 1);
        printf("%lld\n", rd[i].student_ID);
        printf("Student's %d full name:\n", i + 1);
        printf("%s\n", rd[i].name);
        printf("Student's %d age:\n");
        printf("%d\n", rd[i].age);
        printf("Student's %d gender:\n", i + 1);
        if (rd[i].gender == 'M' || rd[i].gender == 'm')
        {
            printf("Male.\n");
        }
        else if (rd[i].gender == 'F' || rd[i].gender == 'f')
        {
            printf("Female.\n");
        }
        else
        {
            printf("Gender not specified.\n");
        }
        printf("Student's %d contact number:\n", i + 1);
        printf("%lld\n", rd[i].contact_number);
        printf("Student's %d email address:\n", i + 1);
        printf("%s\n", rd[i].email);
        printf("Student's %d residential address:\n", i + 1);
        printf("%s\n", rd[i].address);
        printf("Student's %d guardian's name\n", i + 1);
        printf("%s\n", rd[i].guardian_name);
        printf("Student's %d guardian's contact number:\n", i + 1);
        printf("%lld\n", rd[i].guardian_contact);
        printf("Student's %d enrollment year:\n", i + 1);
        printf("%d %d %d\n", rd[i].yearof_enrollment.day, rd[i].yearof_enrollment.month, rd[i].yearof_enrollment.year);
        printf("Student's %d enrolled course:\n", i + 1);
        printf("%s\n", rd[i].course_enrollment);
        printf("\n");
    }
}
void searchStudentbyID(record *rd, int total_count)
{
    int found = 0;
    long int searchID;
    printf("Please enter the Student's ID number:\n");
    scanf("%lld", &searchID);
    getchar();
    for (int i = 0; i < total_count; i++)
    {
        if (searchID == rd[i].student_ID)
        {
            found = 1;
            if (found)
            {
                printf("Student's %d full name:\n", i + 1);
                printf("%s\n", rd[i].name);
                printf("Student's %d age:\n");
                printf("%d\n", rd[i].age);
                printf("Student's %d gender:\n", i + 1);
                printf("%c\n", rd[i].gender);
                printf("Student's %d contact number:\n", i + 1);
                printf("%lld\n", rd[i].contact_number);
                printf("Student's %d email address:\n", i + 1);
                printf("%s\n", rd[i].email);
                printf("Student's %d residential address:\n", i + 1);
                printf("%s\n", rd[i].address);
                printf("Student's %d guardian's name\n", i + 1);
                printf("%s\n", rd[i].guardian_name);
                printf("Student's %d guardian's contact number:\n", i + 1);
                printf("%lld\n", rd[i].guardian_contact);
                printf("Student's %d enrollment year:\n", i + 1);
                printf("%d %d %d\n", rd[i].yearof_enrollment.day, rd[i].yearof_enrollment.month, rd[i].yearof_enrollment.year);
                printf("Student's %d enrolled course:\n", i + 1);
                printf("%s\n", rd[i].course_enrollment);
                printf("\n");
            }
            break;
        }
    }
    if (!found)
    {
        printf("No records found.\n");
    }
}
void searchStudentbyContact(record *rd, int total_count)
{
    int found = 0;
    long int searchContact;
    printf("Please enter Student's contact number:\n");
    scanf("%ld", &searchContact);
    for (int i = 0; i < total_count; i++)
    {
        if (searchContact == rd[i].contact_number)
        {
            found = 1;
            if (found)
            {
                printf("Student's %d ID number:\n", i + 1);
                printf("%lld\n", rd[i].student_ID);
                printf("Student's %d full name:\n", i + 1);
                printf("%s\n", rd[i].name);
                printf("Student's %d age:\n");
                printf("%d\n", rd[i].age);
                printf("Student's %d gender:\n", i + 1);
                printf("%c\n", rd[i].gender);
                printf("Student's %d email address:\n", i + 1);
                printf("%s\n", rd[i].email);
                printf("Student's %d residential address:\n", i + 1);
                printf("%s\n", rd[i].address);
                printf("Student's %d guardian's name", i + 1);
                printf("%s\n", rd[i].guardian_name);
                printf("Student's %d guardian's contact number:\n", i + 1);
                printf("%lld\n", rd[i].guardian_contact);
                printf("Student's %d enrollment year:\n", i + 1);
                printf("%d %d %d\n", rd[i].yearof_enrollment.day, rd[i].yearof_enrollment.month, rd[i].yearof_enrollment.year);
                printf("Student's %d enrolled course:\n", i + 1);
                printf("%s\n", rd[i].course_enrollment);
                printf("\n");
            }
            break;
        }
    }
    if (!found)
    {
        printf("No records found.\n");
    }
}

void updateStudentrecorD(record *rd, int total_count)
{
    int choice, found = 0;
    long int tempID;
    printf("Please enter student'S ID number to update record:\n");
    scanf("%lld", &tempID);
    for (int i = 0; i < total_count; i++)
    {
        if (rd[i].student_ID == tempID)
        {
            found = 1;
            printf("Enter.\n1.To Update contact number.\n2. To Update email address.\n3.To Update residential address.\n4. To Update guardian's contact number.\n");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
            {
                printf("Please enter the new contact number:\n");
                scanf("%lld", &rd[i].contact_number);
                printf("Contact number updated successfully.\n");
                break;
            }
            case 2:
            {
                printf("Please enter the new email address:\n");
                getchar();
                fgets(rd[i].email, sizeof(rd[i].email), stdin);
                rd[i].email[strcspn((rd[i].email), "\n")] = '\0';
                printf("Email address updated successfully.\n");
                break;
            }
            case 3:
            {
                printf("Please enter the new residential address:\n");
                getchar();
                fgets(rd[i].address, sizeof(rd[i].address), stdin);
                rd[i].address[strcspn((rd[i].address), "\n")] = '\0';
                printf("Residential address updated successfully.\n");
                break;
            }
            case 4:
            {
                printf("Please enter guardian's new contact number:\n");
                scanf("%lld", &rd[i].guardian_contact);
                printf("Guardian's contact number updated successfully.\n");
                break;
            }
            default:
            {
                printf("Invalid choice.\n");
                break;
            }
            }
            FILE *file = fopen("student_data.txt", "w");
            for (int i = 0; i < total_count; i++)
            {
                fprintf(file, "Student ID: %lld.\nName: %s.\nAge: %d.\nGender: %c\nContact Number: %lld\nEmail Address: %s\nResidential Address: %s.\nGuardian Name: %s.\nGuardian Phone Number: %lld\nDate Of Enrollment%d-%d-%d\nEnrolled Course: %s.\n",
                        rd[i].student_ID,
                        rd[i].name,
                        rd[i].age,
                        rd[i].gender,
                        rd[i].contact_number,
                        rd[i].email,
                        rd[i].address,
                        rd[i].guardian_name,
                        rd[i].guardian_contact,
                        rd[i].yearof_enrollment.day,
                        rd[i].yearof_enrollment.month,
                        rd[i].yearof_enrollment.year,
                        rd[i].course_enrollment);
            }
            fclose(file);
        }
    }
    if (!found)
    {
        printf("No records found.\n");
    }
}
void deleteStudentrecorD(record *rd, int *total_count)
{
    long int tempID;
    int found = 0;
    printf("Please enter the student's ID number to delete record.\n");
    scanf("%lld", &tempID);
    for (int i = 0; i < *total_count; i++)
    {
        if (tempID == rd[i].student_ID)
        {
            found = 1;
            for (int j = i + 1; j < *total_count; j++)
            {
                rd[j - 1] = rd[j];
            }
            (*total_count)--;
            printf("Deleted successfully.\n");
            break;
        }
        FILE *file = fopen("student_data.txt", "w");
        for (int i = 0; i < *total_count; i++)
        {
            fprintf(file, "Student ID: %lld.\nName: %s.\nAge: %d.\nGender: %c\nContact Number: %lld\nEmail Address: %s\nResidential Address: %s.\nGuardian Name: %s.\nGuardian Phone Number: %lld\nDate Of Enrollment%d-%d-%d\nEnrolled Course: %s.\n",
                    rd[i].student_ID,
                    rd[i].name,
                    rd[i].age,
                    rd[i].gender,
                    rd[i].contact_number,
                    rd[i].email,
                    rd[i].address,
                    rd[i].guardian_name,
                    rd[i].guardian_contact,
                    rd[i].yearof_enrollment.day,
                    rd[i].yearof_enrollment.month,
                    rd[i].yearof_enrollment.year,
                    rd[i].course_enrollment);
        }
        fclose(file);
    }
    if (!found)
    {
        printf("No records found.\n");
    }
}
int loadFromFile(record **rd)
{
    FILE *file = fopen("student_data.txt", "r");
    if (file == NULL)
    {
        return 0;
    }

    int count = 0;
    record temp;
    *rd = NULL;

    while (fscanf(file,
                  "Student ID: %lld.\nName: %[^\n].\nAge: %d.\nGender: %c\nContact Number: %lld\nEmail Address: %[^\n]\nResidential Address: %[^\n].\nGuardian Name: %[^\n].\nGuardian Phone Number: %lld\nDate Of Enrollment%d-%d-%d\nEnrolled Course: %[^\n].\n",
                  &temp.student_ID,
                  temp.name,
                  &temp.age,
                  &temp.gender,
                  &temp.contact_number,
                  temp.email,
                  temp.address,
                  temp.guardian_name,
                  &temp.guardian_contact,
                  &temp.yearof_enrollment.day,
                  &temp.yearof_enrollment.month,
                  &temp.yearof_enrollment.year,
                  temp.course_enrollment) == 13)
    {

        *rd = realloc(*rd, (count + 1) * sizeof(record));
        if (*rd == NULL)
        {
            printf("Memory allocation error.\n");
            fclose(file);
            return count;
        }
        (*rd)[count++] = temp;
    }

    fclose(file);
    return count;
}