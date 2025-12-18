#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//Declaring a struture student along with its member functions
struct Student
{
    int roll;
    char name[20];
    int age;
    float marks;
};

//Function used for login authentication to  protect the database
int login()
{
    char currentPass[20]="abc123";
    int attempts=3;
    char password[20];
    
    
    //Loop to provide 3 attempts to the user to enter the correct password
    while(attempts>0)
    {
        //comparing the entered password with the actual password
        printf("\nEnter the password (%d attempts left): ", attempts);
        scanf("%19s",password);
        if(strcmp(currentPass,password)==0)
        {
            printf("\nCorrect password!\n");
            return 1;
        }
        else
        {
            attempts--;
            if(attempts>0)
            printf("\nIncorrect password!Re-enter it\n");
            
        }
    }
    //If all attempts are used then it will exit the program
    printf("Too many incorrect attempts.Exiting the program\n");
    return 0;

}

//Declaring a array of strucure of size 100 globally
struct Student data[100] = {0}; //Initializing all the elements of the array as 0
int count = 0;//Initializing a global counter variable as 0. It points at the starting of the array

//Function to add the elements to the text file
void save_to_file()
{
    FILE *fp = fopen("Student.txt", "w");/*Using write mode instead of append mode because
    we want to overwrite the entire file every time we save data and append mode will just 
    add the data to the end of the file and hence it will not overwrite the previous data*/


    //If file is unable to access then this block will be executed
    if(fp == NULL)
    {
        perror("Error opening file!\n");
        return;
    }
    //Transversing throughout the entire array
    for(int i = 0; i < count; i++)
    {
        if(data[i].roll != 0)
        {
            fprintf(fp, "%d %s %d %.2f\n",
                    data[i].roll, data[i].name,
                    data[i].age, data[i].marks);
        }
        
    }
    fclose(fp);
}

//Function to retrieve the elements from the text file
void load_from_file()
{
    FILE *fp = fopen("Student.txt", "r");
    /*If file is unable to access then this block will be executed. Not using the perror function
    because for the very first time file is empty it will show the error line though the code is 
    used for the first time*/
    if(fp == NULL)
    {
        return;
    }
    count = 0;// Everytime the fuction is called it will start from the very first line of the file

    while(count < 100 && fscanf(fp, "%d %19s %d %f",
                 &data[count].roll,
                 data[count].name,
                 &data[count].age,
                 &data[count].marks) == 4)/*Used to check whether the count is not full and check
                 if the number returned is 4 by the function fscanf instead of EOF which will enter
                 infinite loop if any number is missing*/
    {
        count++;// move to the next position in the array after adding an element
    }
    fclose(fp);  //Closes the file
}

//Adds the new student to the array
void addStudent()
{
    if(count >= 100)// Check whether the database is full or not
    {
        printf("Database Full! Cannot add more students.\n");
        return;
    }
    int tempRoll;
    printf("Enter the roll no of student:\n");
    scanf("%d",&tempRoll);
    // Check for duplicate roll number
    for(int i = 0; i < count; i++) 
    {
        if(data[i].roll == tempRoll) {
            printf("Error: Roll Number %d already exists!\n", tempRoll);
            return;
        }
    }
    //If the roll number doesn't exist it will add the element to the array
    data[count].roll = tempRoll;
    printf("Enter Name: ");
    scanf("%19s", data[count].name);//%19s terminates the enter string upto 19th character

    printf("Enter Age: ");
    scanf("%d", &data[count].age);

    printf("Enter Marks: ");
    scanf("%f", &data[count].marks);

    count++;/* moving the counter to the next position inside the array so that when function is
    called again it will add the element to consecutive position*/
    save_to_file();             //Data added to the file
    printf("Student Added Successfully!\n\n");
}

//Modifies already existing roll number
void modifyStudent()
{
    printf("Enter Roll No of student to modify:\n");
    int rollNo, found2 = 0;
    scanf("%d",&rollNo);
    //Checks wheter the roll number exist or not
    //If it exists then it will modify the other members
    for(int i=0;i<count;i++)
    {
        if(data[i].roll==rollNo)
        {
            found2 =1;
            printf("Enter the modified name :\n");
            scanf("%19s",data[i].name);
            printf("Enter the modified age :\n");
            scanf("%d",&data[i].age);
            printf("Enter the modified marks :\n");
            scanf("%f",&data[i].marks);
            save_to_file();
        }
    }
    //if the entered roll is not found
    if(!found2)
    {
        printf("Student Not Found.\n");
        return;
    }
}

//Display the entire list of elements
void displayStudent()
{
    //Transverse through the entire array
    for(int i = 0; i < count; i++)
    {
        //If student found it will print the details of the student
        if(data[i].roll != 0)
        {
            printf("\nRoll: %d\n", data[i].roll);
            printf("Name: %s\n", data[i].name);
            printf("Age: %d\n", data[i].age);
            printf("Marks: %.2f\n", data[i].marks);
        }
    }
}

//Searchs for the student based on roll number
void searchStudent()
{
    int id, found = 0;

    //Accepting the roll number of the student
    printf("Enter Roll No to search: ");
    scanf("%d", &id);

    //Transversing through entire array to check if the element found or not
    for(int i = 0; i < count; i++)
    {
        //Prints the entire details of the student if found
        if(data[i].roll == id)
        {
            found = 1;
            printf("\nStudent Found!\n");
            printf("Roll: %d\n", data[i].roll);
            printf("Name: %s\n", data[i].name);
            printf("Age: %d\n", data[i].age);
            printf("Marks: %.2f\n\n", data[i].marks);
            break;
        }
    }

    //If not found......
    if(!found)
        printf("Student Not Found.\n");
}

//Delete the record of a student by shifting all the elements after it to the left
void DeleteStudent()
{
    int id, found = 0;

    printf("Enter Roll No to delete: ");
    scanf("%d", &id);

    for(int i = 0; i < count; i++)
    {
        if(data[i].roll == id)
        {
            found = 1;
            // Shift all remaining records
            for(int j = i; j < count - 1; j++)
            {
                data[j] = data[j + 1];
            }
            count--;//Reduces the size of the student database
            break;
        }
    }

    if(found)
    {
        save_to_file();
        printf("Student Deleted Successfully.\n");
    }
    else
    {
        printf("Student Not Found.\n");
    }
}

//Sort the entire student database based on marks
void sortMarks()
{
    for(int i = 0; i < count; i++)
    {
        for(int j = i + 1; j < count; j++)
        {
            if(data[i].marks > data[j].marks)
            {
                struct Student temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
    save_to_file();
    printf("Sorted by Marks.\n");
}

//Returns the student with highest marks
void Highestmarks()
{
    if(count == 0)
    {
        printf("No Student Records.\n");
        return;
    }

    int index = 0;
    float highest = data[0].marks;

    for(int i = 0; i < count; i++)
    {
        if(data[i].marks > highest)
        {
            highest = data[i].marks;
            index = i;
        }
    }

    printf("\nHighest Marks: %.2f by Roll No: %d\n\n",
           highest, data[index].roll);
}

int main()
{
    //This block will ask for login authentication before accessing the database
    if(!login())
    {
        return 0;
    }

    //Access the content of the file in read mode
    load_from_file();
    int choice, n = 0;

    do
    {
        //Giving choices to the user
        printf("\n<Student Database Management>\n");
        printf("1 → Add Student\n");
        printf("2 → Display Students\n");
        printf("3 → Search Student\n");
        printf("4 → Delete Student\n");
        printf("5 → Sort by Marks\n");
        printf("6 → Highest Marks\n");
        printf("7 → Modify Student\n");
        printf("Enter Choice: ");
        scanf("%d",&choice);          //Accepting the choice from the user

        switch(choice)                //Passing the choice provided by the user
        {
            //Required function with the case match is called
            case 1: addStudent(); break;
            case 2: displayStudent(); break;
            case 3: searchStudent(); break;
            case 4: DeleteStudent(); break;
            case 5: sortMarks(); break;
            case 6: Highestmarks(); break;
            case 7: modifyStudent(); break;
            default: printf("Invalid Choice.\n");   //If no case matches default will be executed
        }
        //After completing the task once compiler will ask the user whether to continue or not
        printf("\nEnter 1 to continue, 0 to exit: ");
        scanf("%d", &n);        //Accepting the choice to continue or not
        if(n!=0 && n!=1)  //If anything other than 0 or 1 is pressed compiler will treat it as 0
        {
            n=0;
        }

    } while(n);                 //Based on the choice the while loop will run accordingly

    return 0;
}