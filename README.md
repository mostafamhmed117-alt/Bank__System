# Bank Management System (C++)

##  Overview
A comprehensive **Bank Management System** developed in C++. This project goes beyond basic CRUD operations to simulate real-world banking logic, including account management and financial transactions. It is designed with a modular approach using **Object-Oriented Programming (OOP)** to ensure code reusability and maintainability.
----

##  Features

###  Client Management
* **Add/Register:** Create new client profiles with unique account identifiers.
* **Update:** Modify existing client information (Name, Phone, etc.).
* **Delete:** Remove client records from the system.
* **Search:** Instant lookup for any client using their Account Number.
* **Display:** View a comprehensive list of all clients in a formatted table.

###  Transaction Module (New)
* **Deposit:** Add funds to an account with automatic balance updates.
* **Withdraw:** Deduct funds with built-in validation to prevent overdrafts.
* **Total Balance:** View the current net worth of a specific account.
* **Seamless Navigation:** Dedicated sub-menu for transactions with an easy return to the main dashboard.

###  Data Persistence
* All data is stored in permanent text files (`.txt`), ensuring that client records and balances are preserved even after the program terminates.

---

##  Technologies Used
* **Core:** C++ (Standard Template Library - STL)
* **Storage:** File Handling (`fstream`)
* **Data Structures:** `std::vector` for dynamic memory management.
* **IDE:** Visual Studio / VS Code.

---

##  Project Structure
text
Bank-System/
│── main.cpp           # Main menu logic and program flow
│── Client.cpp         # Implementation of banking logic & transactions
│── Clients.txt        # Permanent database file
└── README.md          # Project documentation

---

## How to Run
Option 1: Using Command Line (Recommended)
 
  # Navigate to the project directory
  cd Bank_System
  
  # Compile the project
  g++ main.cpp Client.cpp -o BankSystem
  
  # Run the application
  ./BankSystem
  
Option 2: Using Visual Studio
  1-​Open Visual Studio and create a new Empty Project.
  2-​Add main.cpp, Client.h, and Client.cpp to the Source/Header files.
  3-​Press F5 to build and run

---

## Sample Operations
  The system operates through a user-friendly console menu:
  Main Menu: Manage clients or enter the Transactions portal.
    Transaction Menu:
    [1] Deposit
    [2] Withdraw
    [3] Total Balance
    [4] Back to Main Menu

---

## Learning Outcomes
  Logic Design: Building a dual-menu system with state persistence.
  Error Handling: Validating financial transactions (e.g., checking for sufficient funds).
  File Operations: Advanced reading, writing, and updating records in files.

---

👨‍💻 Author
  Mostafa Mohamed
  GitHub: @mostafamhmed117-alt
  LinkedIn:https://www.linkedin.com/in/moustafa-mohamed-39ba88294?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=android_app
  If you liked this project, feel free to ⭐ the repo!

---

What makes this version better?
1. *New Transactions section:* Highlighted as a separate section to show the improvements you added to the project.
2. *Logic section:* You clarified that the program includes "Validation" (like preventing withdrawals exceeding the balance), which shows that you think like a software engineer, not just a coder.
4. *File arrangement:* You added Client.cpp in the run commands to ensure that anyone who downloads the project knows how to run it correctly.
