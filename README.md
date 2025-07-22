# 📘 Student Management System (C++ | File Handling | OOP)

A menu-driven student management system developed in **C++**, focusing on **file handling**, **data validation**, and **modular design** using **object-oriented principles**. This system stores, edits, views, and searches student data across dynamically chosen or created CSV files. Ideal for learning how real-world C++ applications interact with files and data formats.

---

## ✅ Features

- Add single or multiple student records to a CSV file
- Choose to create a **new file** or use an **existing one**
- Input validation for:
  - Roll number (positive & unique)
  - Name (letters + spaces only)
  - Marks (0 to 100 float)
- View records from any selected file
  - Records are **auto-sorted by Roll Number** before display
- Edit marks of a student by roll number
- Search student by roll number
- All data stored in `.csv` format under the `/data` folder
---

## 🛠 How to Run

### 🔧 Requirements
- C++ Compiler (e.g., g++, MinGW, MSVC)
- A terminal or command line
- Basic knowledge of how to compile C++ programs

### 📂 Project Structure
Student_management_system/
│
├── data/ # Contains CSV data files per class or section
├── student.h # Header file for student class
├── student.cpp # Implementation of student class methods
├── main.cpp # Contains menu and program flow
└── README.md # This file

### ▶️ Compile & Run
```bash
g++ main.cpp student.cpp -o student_mgmt
./student_mgmt
```
Make sure the data folder exists (empty is fine). It is auto-used by the program to store files.

🧠 What I Learned
This project helped me apply foundational C++ knowledge in a real-world-like scenario. Specifically:
1. File Handling in C++
   - Reading from and writing to CSV files
   - Dynamic file selection based on user input
2. OOP Principles
   - Class design, encapsulation, and method responsibilities
3. Input Validation
   - Robust checks for type and logical correctness
4. Code Modularization
   - Separating declaration and definitions into header/source files
5. Version Control
   - Git & GitHub for version tracking and collaboration

🏁 Future Scope
- Implement Qt GUI for visual interface
- Add user authentication
- Import/export bulk student data
- Advanced sorting/searching algorithms

🧑‍💻 Author
Saikat Samanta
GitHub: NeoTox419