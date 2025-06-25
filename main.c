#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

//---------------------------------------------------struct student-------------------------------------------------
struct note
{
    float TD;
    float TP;
    float Exame;
};

//---------------------------------------------------struct student-------------------------------------------------
struct module
{
    struct note Algo;
    struct note Analysis;
    struct note STM;
    struct note Algebra;
    struct note English;
};

//---------------------------------------------------struct student-------------------------------------------------
struct moyenne
{
    float Algo;
    float Analysis;
    float STM;
    float Algebra;
    float English;
};

//---------------------------------------------------struct student-------------------------------------------------
struct Student
{
    int id;
    char name[50];
    char Lastname[50];
    struct module M;
    struct moyenne m;
    float Moyenne;
};

//----------------------------------prosuder loading Spinner------------------------------

void loadingSpinner() {
    char spinner[] = "-\\|/";

    fflush(stdout);

    for (int i = 0; i < 20; i++) {
        printf("\rThe program is running, please wait... %c", spinner[i % 4]);
        fflush(stdout);
        Sleep(250);
    }

    printf("\b");
    printf("Done!\n");
    
}

//----------------------------------prosuder print_Student_Information_Art------------------------------

void printStudentInformationArt() {
    printf("      _             _            _     _        __                           _   _             \n");
    printf("     | |           | |          | |   (_)      / _|                         | | (_)            \n");
    printf("  ___| |_ _   _  __| | ___ _ __ | |_   _ _ __ | |_ ___  _ __ _ __ ___   __ _| |_ _  ___  _ __  \n");
    printf(" / __| __| | | |/ _` |/ _ \\ '_ \\| __| | | '_ \\|  _/ _ \\| '__| '_ ` _ \\ / _` | __| |/ _ \\| '_ \\ \n");
    printf(" \\__ \\ |_| |_| | (_| |  __/ | | | |_  | | | | | || (_) | |  | | | | | | (_| | |_| | (_) | | | |\n");
    printf(" |___/\\__|\\__,_|\\__,_|\\___|_| |_|\\__| |_|_| |_|_| \\___/|_|  |_| |_| |_|\\__,_|\\__|_|\\___/|_| |_|\n");
}

//----------------------------------function getPass***word------------------------------

void getPassword(char *password, int maxLength) {
    int index = 0;
    char ch;
    
    while (1) {
        ch = getch(); // قراءة حرف بدون ظهوره على الشاشة

        if (ch == 13) { // إذا ضغط Enter (رقمه 13)
            password[index] = '\0'; // نهاية النص
            printf("\n");
            break;
        } else if (ch == 8) { // إذا ضغط Backspace
            if (index > 0) {
                index--;
                printf("\b \b"); // حذف النجمة
            }
        } else if (index < maxLength - 1) {
            password[index++] = ch;
            printf("*"); // طباعة نجمة بدلاً من الحرف الحقيقي
        }
    }
}

//----------------------------------function login------------------------------

int login() {
    char username[20], password[20];
    int attempts = 3;
    int i;
    while (TRUE)
    {    
    while (attempts > 0) {
        printf("\n===== Login System =====\n");
        printf(" Username: ");
        scanf("%19s", username);

        printf(" Enter your password: ");
        getPassword(password, 20);

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            printf("\n[✅] Login successful! Welcome %s!\n", username);
            return 1;
            break;
        } else {
            attempts--;
            printf("\n[❌] Invalid credentials! Attempts left: %d\n", attempts);
        }
    }

    printf("\n[🚫] Too many failed attempts. Please wait 30 seconds before trying again.\n");

    printf("⏳ Waiting... %02d ",15);

    for ( i = 14; i >= 0; i--)
    {
        Sleep(1000); 
        printf("\b\b%02d",i);
        fflush(stdout);
    }
    system("cls");
    attempts = 3;
    }
}

//-----------------------------------------------function Moyenne module--------------------------------------------
void Moyenne_m(FILE *f){

    FILE *temp;
    struct Student student;

    temp = fopen("temp.bin", "wb");
            if (temp == NULL)
            {
                printf("\nError opening temporary file!");
                return;
            }

            while (fread(&student, sizeof(struct Student), 1, f) == 1)
            {
                
                student.m.Algo=((student.M.Algo.TP*0.2)+(student.M.Algo.TD*0.2)+(student.M.Algo.Exame*0.6));
        
                student.m.Algebra=((student.M.Algebra.TD*0.4)+(student.M.Algebra.Exame*0.6));
        
                student.m.Analysis=((student.M.Analysis.TD*0.4)+(student.M.Analysis.Exame*0.6));
        
                student.m.STM=((student.M.STM.TD*0.4)+(student.M.STM.Exame*0.6));
        
                student.m.English=student.M.English.Exame;

                student.Moyenne=(student.m.Algo*4+student.m.Algebra*3+student.m.Analysis*4+student.m.STM*3+student.m.English)/15;
                
                fwrite(&student, sizeof(struct Student), 1, temp);
                
            }

            fclose(f);
            fclose(temp);

            remove("student_info.bin");

            rename("temp.bin", "student_info.bin");
            
}

//--------------------------------------------function Total Moyenne------------------------------------------------
void Moyenne(FILE *f){

    struct Student student;

    while (fread(&student, sizeof(struct Student), 1, f) == 1)
    {
        student.Moyenne=(student.m.Algo*4+student.m.Algebra*3+student.m.Analysis*4+student.m.STM*3+student.m.English)/15;
        fwrite(&student.Moyenne, sizeof(float), 1, f);
    }
}

//----------------------------------------------------prosuder scan-------------------------------------------------
void scan(struct Student x[], int y, FILE *f)
{

    int i;

    struct Student student;

    
    for (i = 1; i <= y; i++)
    {
        printf("\nEnter the name of student: ");
        scanf("%49s", student.name);

        printf("Enter the Lastname of student: ");
        scanf("%49s", student.Lastname);

        printf("Enter the Id of student: ");
        scanf("%d", &student.id);

        printf("Enter the TP algo note of student: ");
        scanf("%f", &student.M.Algo.TP);
        printf("Enter the TD algo note of student: ");
        scanf("%f", &student.M.Algo.TD);
        printf("Enter the Exam algo note of student: ");
        scanf("%f", &student.M.Algo.Exame);

        printf("Enter the TD algebra note of student: ");
        scanf("%f", &student.M.Algebra.TD);
        printf("Enter the Exam algebra note of student: ");
        scanf("%f", &student.M.Algebra.Exame);

        printf("Enter the TD analyse note of student: ");
        scanf("%f", &student.M.Analysis.TD);
        printf("Enter the Exam analyse note of student: ");
        scanf("%f", &student.M.Analysis.Exame);

        printf("Enter the TD STM note of student: ");
        scanf("%f", &student.M.STM.TD);
        printf("Enter the Exam STM note of student: ");
        scanf("%f", &student.M.STM.Exame);

        printf("Enter the Exam English note of student: ");
        scanf("%f", &student.M.English.Exame);
        
        fwrite(&student, sizeof(struct Student), 1, f);
    }

    printf("============================End scaning==============================\n");
}

//----------------------------------------------------prosuder print-------------------------------------------------
void print(FILE *f)
{

    struct Student student;

        
    printf("\n===========================Start printing===============================");
    printf("\n-------------------------------------------------------------------------");

    while (fread(&student, sizeof(struct Student), 1, f) == 1)
    {
        printf("\nThe name of student is: %s", student.name);
        printf("\nThe Lastname of student is: %s", student.Lastname);
        printf("\nThe Id of student is: %d", student.id);

        printf("\nThe TP algo note of student is: %.2f", student.M.Algo.TP);
        printf("\nThe TD algo note of student is: %.2f", student.M.Algo.TD);
        printf("\nThe Exam algo note of student is: %.2f", student.M.Algo.Exame);

        printf("\nThe TD algebra note of student is: %.2f", student.M.Algebra.TD);
        printf("\nThe Exam algebra note of student is: %.2f", student.M.Algebra.Exame);

        printf("\nThe TD analyse note of student is: %.2f", student.M.Analysis.TD);
        printf("\nThe Exam analyse note of student is: %.2f", student.M.Analysis.Exame);

        printf("\nThe TD STM note of student is: %.2f", student.M.STM.TD);
        printf("\nThe Exam STM note of student is: %.2f", student.M.STM.Exame);

        printf("\nThe Exam English note of student is: %.2f", student.M.English.Exame);

        printf("\nThe student's average is: %.2f", student.Moyenne);

        printf("\n--------------------------------------------------------------------------");
    }

    printf("\n============================End printing==============================\n");
}

//-------------------------------------------------prosuder sharche-------------------------------------------------

void sharche(FILE *f)
{

    int id, ans, Result = 1;
    char name[50];
    struct Student student;

        
    printf("\n===========================Start sharching===============================");

    do
    {

        id = 0;
        char name[50] = "";
        Result = 1;

        printf("\n1\\[🔍] Search by name\n2\\[🔍] Search by ID\n0\\[🔙] Exit\n>> ");
        scanf("%d", &ans);

        if (ans == 1)
        {
            printf("Enter the name you are searching for:\n>> ");
            scanf("%49s", name);
        }
        else if (ans == 2)
        {
            printf("\nEnter the ID you are searching for:\n>> ");
            scanf("%d", &id);
        }
        else if (ans == 0)
        {
            break;
        }
        while (fread(&student, sizeof(struct Student), 1, f) == 1)
        {
            if (student.id == id || !strcmp(student.name, name))
            {
                printf("\n--------------------------------------------------------------------------");
                printf("\nThe name of student is: %s", student.name);
                printf("\nThe Lastname of student is: %s", student.Lastname);
                printf("\nThe Id of student is: %d", student.id);

                printf("\nThe TP algo note of student is: %.2f", student.M.Algo.TP);
                printf("\nThe TD algo note of student is: %.2f", student.M.Algo.TD);
                printf("\nThe Exam algo note of student is: %.2f", student.M.Algo.Exame);

                printf("\nThe TD algebra note of student is: %.2f", student.M.Algebra.TD);
                printf("\nThe Exam algebra note of student is: %.2f", student.M.Algebra.Exame);

                printf("\nThe TD analyse note of student is: %.2f", student.M.Analysis.TD);
                printf("\nThe Exam analyse note of student is: %.2f", student.M.Analysis.Exame);

                printf("\nThe TD STM note of student is: %.2f", student.M.STM.TD);
                printf("\nThe Exam STM note of student is: %.2f", student.M.STM.Exame);

                printf("\nThe Exam English note of student is: %.2f", student.M.English.Exame);
                printf("\n--------------------------------------------------------------------------");
                Result = 0;
            }
        }
        if (Result)
        {
            printf("\nNo result found !!");
        }

        printf("\n============================End sharching==============================\n");
        fseek(f, 0, SEEK_SET);

    } while (ans != 0);
}

//-------------------------------------------------prosuder Delete-------------------------------------------------
void delete(FILE *f)
{

    FILE *temp;
    int ans, id, Result;
    struct Student student;

    printf("\n============================Beging delete==============================\n");
    do
    {
        Result = 0;

        printf("\n1\\[🗑] Delete by ID\n0\\[🔙] Exit\n>> ");
        scanf("%d", &ans);

        if (ans == 1)
        {
            printf("\nEnter the ID of the student you want to delete:\n>> ");
            scanf("%d", &id);

            temp = fopen("temp.bin", "wb");
            if (temp == NULL)
            {
                printf("\nError opening temporary file!");
                return;
            }

            fseek(f, 0, SEEK_SET);
            while (fread(&student, sizeof(struct Student), 1, f) == 1)
            {
                if (student.id != id)
                {
                    fwrite(&student, sizeof(struct Student), 1, temp);
                }
                else if (student.id == id)
                {
                    Result = 1;
                    continue;
                }
            }

            fclose(f);
            fclose(temp);

            remove("student_info.bin");

            rename("temp.bin", "student_info.bin");

            if (Result)
            {
                printf("Student with this ID <%d> has been deleted successfully [🎉].\n", id);
            }else{
                printf("Student with this ID <%d> it doesn't exist [🚫]!!\n", id);
            }
        }
        else if (ans == 0)
        {
            printf("\n============================End delete==============================\n");
            return;
        }

        fopen("student_info.bin", "rb");
        if (f == NULL)
                {
                    printf("Error opening file!");
                }
                
    } while (ans != 0);
    

}

//-------------------------------------------------prosuder modify-------------------------------------------------
void modify(FILE *f, int id)
{

    FILE *temp;
    int ans, ans2, Result;
    struct module new;
    struct Student student;

        
    fseek(f, 0, SEEK_SET);
    while (fread(&student, sizeof(struct Student), 1, f) == 1)
    {
        if (student.id == id)
        {
            new.Algo.TP = student.M.Algo.TP;
            new.Algo.TD = student.M.Algo.TD;
            new.Algo.Exame = student.M.Algo.Exame;

            new.Analysis.TD = student.M.Analysis.TD;
            new.Analysis.Exame = student.M.Analysis.Exame;

            new.Algebra.TD = student.M.Algebra.TD;
            new.Algebra.Exame = student.M.Algebra.Exame;

            new.STM.TD = student.M.STM.TD;
            new.STM.Exame = student.M.STM.Exame;

            new.English.Exame = student.M.English.Exame;
        }
    }

    do
    {
        printf("\n1\\[✍] Modify Algo note.\n2\\[✍] Modify Analysis note.\n3\\[✍] Modify Algebra note.\n4\\[✍] Modify STM note.\n5\\[✍] Modify English note.\n0\\[🔙] Exit\n>> ");
        scanf("%d", &ans);

        switch (ans)
        {
        case 1:
            do
            {
                printf("\n1\\[✍] Modify TP note.\n2\\[✍] Modify TD note.\n3\\[✍] Modify Exam note.\n0\\[🔙] Exit\n>> ");
                scanf("%d", &ans2);

                switch (ans2)
                {
                case 1:
                    printf("\nEnter the new TP note\n>> ");
                    scanf("%f", &new.Algo.TP);
                    break;

                case 2:
                    printf("\nEnter the new TD note\n>> ");
                    scanf("%f", &new.Algo.TD);
                    break;

                case 3:
                    printf("\nEnter the new Exam note\n>> ");
                    scanf("%f", &new.Algo.Exame);
                    break;

                case 0:
                    continue;
                    break;
                }
            } while (ans2 != 0);

            break;

        case 2:

            do
            {
                printf("\n1\\[✍] Modify TD note.\n2\\[✍] Modify Exam note.\n0\\[🔙] Exit\n>> ");
                scanf("%d", &ans2);

                switch (ans2)
                {
                case 1:
                    printf("\nEnter the new TD note\n>> ");
                    scanf("%f", &new.Analysis.TD);
                    break;

                case 2:
                    printf("\nEnter the new Exam note\n>> ");
                    scanf("%f", &new.Analysis.Exame);
                    break;

                case 0:
                    continue;
                    break;
                }
            } while (ans2 != 0);

            break;

        case 3:

            do
            {
                printf("\n1\\[✍] Modify TD note.\n2\\[✍] Modify Exam note.\n0\\[🔙] Exit\n>> ");
                scanf("%d", &ans2);

                switch (ans2)
                {
                case 1:
                    printf("\nEnter the new TD note\n>> ");
                    scanf("%f", &new.Algebra.TD);
                    break;

                case 2:
                    printf("\nEnter the new Exam note\n>> ");
                    scanf("%f", &new.Algebra.Exame);
                    break;

                case 0:
                    continue;
                    break;
                }
            } while (ans2 != 0);
            break;

        case 4:

            do
            {
                printf("\n1\\[✍] Modify TD note.\n2\\[✍] Modify Exam note.\n0\\[🔙] Exit\n>> ");
                scanf("%d", &ans2);

                switch (ans2)
                {
                case 1:
                    printf("\nEnter the new TD note\n>> ");
                    scanf("%f", &new.STM.TD);
                    break;
                case 2:

                    printf("\nEnter the new Exam note\n>> ");
                    scanf("%f", &new.STM.Exame);
                    break;
                case 0:

                    continue;
                    break;
                }
            } while (ans2 != 0);
            break;

        case 5:

            do
            {
                printf("\n1[✍] Modify Exam note.\n0\\[🔙] Exit\n>> ");
                scanf("%d", &ans2);

                switch (ans2)
                {
                case 1:

                    printf("\nEnter the new Exam note\n>> ");
                    scanf("%f", &new.English.Exame);
                    break;

                case 0:
                    continue;
                    break;
                }
            } while (ans2 != 0);
            break;
        default:
            break;
        }
    } while (ans != 0);

    temp = fopen("temp.bin", "wb");
    if (temp == NULL)
    {
        printf("\nError opening temporary file!");
        return;
    }

    fseek(f, 0, SEEK_SET);
    while (fread(&student, sizeof(struct Student), 1, f) == 1)
    {
        if (student.id == id)
        {
            student.M.Algo.TP = new.Algo.TP;
            student.M.Algo.TD = new.Algo.TD;
            student.M.Algo.Exame = new.Algo.Exame;

            student.M.Analysis.TD = new.Analysis.TD;
            student.M.Analysis.Exame = new.Analysis.Exame;

            student.M.Algebra.TD = new.Algebra.TD;
            student.M.Algebra.Exame = new.Algebra.Exame;

            student.M.STM.TD = new.STM.TD;
            student.M.STM.Exame = new.STM.Exame;

            student.M.English.Exame = new.English.Exame;
            Result = 1;
        }
        fwrite(&student, sizeof(struct Student), 1, temp);
    }

    fclose(f);
    fclose(temp);

    remove("student_info.bin");

    rename("temp.bin", "student_info.bin");

    if (Result)
    {
        printf("Student with this ID <%d> has been modify successfully[🎉].\n", id);
    }
    else
        printf("Student with this ID <%d> it doesn't exist[🚫]!!\n", id);

}

//-----------------------------------------------------int main-----------------------------------------------------
int main()
{

    SetConsoleOutputCP(CP_UTF8);
    
    FILE *file;
    long ST, st = 0;
    int ans;
    int Process;
    struct Student *First = NULL;

    loadingSpinner();

    Sleep(1000);
    printStudentInformationArt();
    Sleep(1000);

    if(login())
    {

    printf("\n Welcome to this program developed by Yasser Chellali and Imad Chalabi❤.\n");
    printf("\n This program allows you to freely deal with student information[📝].\n");

    do
    {
        printf("\n[💡] Please what is the process to be done: ");
        printf("\n1\\ [➕] Add New Student \n2\\ [📝] Update Student Information \n3\\ [🔎] Search Student (by ID or Name) \n4\\ [📄] Display All Students \n5\\ [ 🗑] Delete data\n0\\ [🔙] Exit\n>> ");
        scanf("%d", &Process);

        switch(Process){
            case 1:
                printf("\n1\\[💾] Scan info of student\n0\\[🔙] Exit\n>> ");
                scanf("%d", &ans);

                if (ans == 1)
                {
                                
                printf("===========================Start scaning===============================");
                    printf("\n[👨‍🎓] Enter how many students do you want to add:\n>> ");
                    scanf("%d", &ST);

                    st += ST;

                    First = (struct Student *)malloc(ST * sizeof(struct Student));
                    if (First == NULL)
                    {
                        printf("Memory allocation failed!\n");
                        return 1;
                    }

                    file = fopen("student_info.bin", "ab+");
                    if (file == NULL)
                    {
                        printf("Error opening file! [📁]");
                        free(First);
                        return 1;
                    }
                    scan(First + (st - ST), ST, file);

                    fclose(file);
                    free(First);
                    ans = 0;
                }
                else
                {
                    continue;
                }

                break;

            case 2:

                int id;
                    
                printf("===========================Start Update===============================");
                    printf("\n[💳] Enter the ID of the student you want to modify:\n>> ");
                    scanf("%d", &id);

                    First = (struct Student *)malloc(ST * sizeof(struct Student));
                    if (First == NULL)
                    {
                        printf("Memory allocation failed!\n");
                        return 1;
                    }

                    file = fopen("student_info.bin", "rb");
                    if (file == NULL)
                    {
                        printf("Error opening file!");
                        free(First);
                        return 1;
                    }

                    modify(file, id);

                    fopen("student_info.bin", "rb");
                    if (file == NULL)
                    {
                        printf("\nError opening temporary file!");
                    }

                    Moyenne_m(file);

                    fclose(file);
                    free(First);
                    printf("===========================End Update===============================");

                break;
                
            case 3:

                First = (struct Student *)malloc(ST * sizeof(struct Student));
                if (First == NULL)
                {
                    printf("Memory allocation failed!\n");
                    return 1;
                }

                file = fopen("student_info.bin", "rb");
                if (file == NULL)
                {
                    printf("Error opening file!");
                    free(First);
                    return 1;
                }

                sharche(file);
                fclose(file);
                free(First);

                break;

            case 4:

                printf("\n1\\[📃] print info of student\n0\\Exit\n>> ");
                scanf("%d", &ans);
                if (ans)
                {
                    file = fopen("student_info.bin", "rb");
                    if (file == NULL)
                    {
                        printf("Error opening file!");
                        printf("\nThere is no file containing student information[📁].\nTry entering some information[📋].\n");
                        continue;
                    }

                    Moyenne_m(file);

                    fopen("student_info.bin", "rb");
                    if (file == NULL)
                {
                    printf("\nError opening temporary file!");
                }
                    
                    print(file);

                    fclose(file);
                    ans = 0;
                }
                else
                    continue;

                break;

            case 5:

                First = (struct Student *)malloc(ST * sizeof(struct Student));
                if (First == NULL)
                {
                    printf("Memory allocation failed!\n");
                    return 1;
                }
                
                file = fopen("student_info.bin", "rb");
                if (file == NULL)
                {
                    printf("Error opening file!");
                    free(First);
                    return 1;
                }

                delete (file);
                fclose(file);
                free(First);

                break;
            
            case 0:
                break;
        }
        
    } while (Process != 0);

    char spinner[] = "-\\|/";
    printf("Thank you for the experience, We hope you liked it.\n");
    fflush(stdout);

    for (int i = 0; i < 21; i++) {
        printf("\rThe program is being stopped...%c", spinner[i % 4]);
        fflush(stdout);
        Sleep(250);
    }

    printf("\rThe program is being stopped...");
    printf("\nThank you ❤");

    return 0;
    }
}
