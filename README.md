Student Database Management System
A robust, console-based application written in C designed to manage student records efficiently. This project utilizes File Handling to ensure data persistence, allowing records to be saved and retrieved even after the program terminates.

🚀 Features
🔒 Secure Authentication: Includes a login system with a 3-attempt limit to protect the database.

📂 Persistent Storage: Automatically saves and loads data from Student.txt using file handling.

📝 CRUD Operations:

Add Student: Input details (Roll No, Name, Age, Marks) with duplicate roll number validation.

Display: View all student records currently in the database.

Search: Find specific student details using their Roll Number.

Modify: Update details for existing students.

Delete: Remove records and automatically rearrange the database.

📊 Data Analysis:

Sort: Organize records based on marks (descending order).

Highest Marks: Instantly find the top-performing student.

🛠️ Tech Stack
Language: C

Concepts Used: Structures (struct), File I/O, Pointers, Arrays, String Handling, Sorting Algorithms.

⚙️ How to Run
Clone the repository:

Bash

git clone https://github.com/your-username/your-repo-name.git

Compile the code:

Bash

gcc data_base_2.c -o student_db

Run the application:

Windows:

Bash

student_db.exe

Mac/Linux:

Bash

./student_db

🔑 Login Credentials
To access the system, use the default password hardcoded in the source file:

Password: abc123

(Note: You can change this password by modifying the currentPass variable in the login() function inside data_base_2.c)

📂 Project Structure
data_base_2.c: The main source code containing all logic and functions.

Student.txt: The text file where student records are stored (automatically created upon first run).

🔮 Future Improvements
Implement password hashing for better security.

Add input validation for names (to prevent numbers in names).

Expand the database limit (currently set to 100 students) using dynamic memory allocation (malloc).

👨‍💻 Author
Adesh Singh

LinkedIn: https://www.linkedin.com/in/adesh-singh-73aba8375/

GitHub: https://github.com/adesh-singh596
