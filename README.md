# Banking Management System

A console-based Banking Management System built in C using structured programming principles. This project simulates core banking operations such as account creation, deposits, withdrawals, and balance tracking with persistent file-based storage and robust error handling.

---

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Compilation](#compilation)
  - [Running the Program](#running-the-program)
- [Usage](#usage)
- [Core Concepts Used](#core-concepts-used)
- [File Handling](#file-handling)
- [Error Handling](#error-handling)
- [Future Improvements](#future-improvements)
- [Author](#author)

---

## About the Project

This project is a simulation of a basic banking system implemented in C. It is designed to perform fundamental banking operations through a terminal interface, with all account data stored in a file for persistence across sessions.

The goal of this project was to strengthen understanding of structured programming in C, particularly around control flow, file I/O, and data management using structs. It also focuses on writing reliable software by preventing invalid operations through proper error handling.

---

## Features

- Create a new bank account with a unique account number and holder name
- Deposit money into an existing account
- Withdraw money with overdraft prevention
- Check account balance
- View all existing accounts and their details
- Delete an account
- Persistent file-based storage — all account data is saved between sessions
- Duplicate account number prevention
- Input validation at every step

---

## Tech Stack

| Component        | Technology         |
|------------------|--------------------|
| Language         | C                  |
| Paradigm         | Structured Programming |
| Storage          | File I/O (binary files using `fread`/`fwrite`) |
| Interface        | Console / Terminal |
| Build Tool       | gcc / any C compiler |

---

## Project Structure

```
BankingManagementSystem/
│
├── main.c            # Entry point, menu loop and program flow
├── account.h         # Account struct and function declarations
├── account.c         # Core banking operation implementations
├── filehandler.h     # File utility function declarations
├── filehandler.c     # File read/write/search logic
├── accounts.dat      # Data file (auto-generated on first run)
└── README.md         # Project documentation
```

---

## Getting Started

### Prerequisites

You need a C compiler installed on your system.

- **Linux/macOS:** GCC is usually pre-installed. Check with:
  ```bash
  gcc --version
  ```
- **Windows:** Install [MinGW](https://www.mingw-w64.org/) or use an IDE like [Code::Blocks](https://www.codeblocks.org/) or [Dev-C++](https://www.bloodshed.net/).

---

### Installation

Clone the repository to your local machine:

```bash
git clone https://github.com/bhavay-sharma/banking-management-system.git
cd banking-management-system
```

---

### Compilation

Compile all source files using gcc:

```bash
gcc main.c account.c filehandler.c -o banking_system
```

Or compile a single-file version if applicable:

```bash
gcc main.c -o banking_system
```

---

### Running the Program

**Linux/macOS:**
```bash
./banking_system
```

**Windows:**
```bash
banking_system.exe
```

---

## Usage

Once the program starts, you will see a menu like this:

```
========================================
       BANKING MANAGEMENT SYSTEM
========================================
 1. Create New Account
 2. Deposit Money
 3. Withdraw Money
 4. Check Balance
 5. View All Accounts
 6. Delete Account
 7. Exit
========================================
Enter your choice:
```

- Enter the number corresponding to the operation you want to perform.
- Follow the on-screen prompts to enter account details or transaction amounts.
- The system will confirm every successful operation and display appropriate error messages for invalid inputs.
- All data is automatically saved to `accounts.dat` and reloaded the next time the program runs.

### Example Transaction Flow

```
Enter your choice: 2
Enter Account Number: 1001
Enter Deposit Amount: 5000
Success: Rs. 5000 deposited. New Balance: Rs. 15000

Enter your choice: 3
Enter Account Number: 1001
Enter Withdrawal Amount: 20000
Error: Insufficient funds. Available Balance: Rs. 15000
```

---

## Core Concepts Used

This project demonstrates the following structured programming and C language concepts:

| Concept                   | How It Is Applied |
|---------------------------|-------------------|
| Structs                   | `Account` struct holds account number, holder name, and balance |
| Functions                 | Each operation (deposit, withdraw, etc.) is a separate function |
| File I/O                  | `fread` and `fwrite` used for binary file operations |
| Pointers                  | Used for passing structs by reference to functions |
| Control Flow              | Switch-case for menu navigation, loops for record traversal |
| Error Handling            | Conditional checks prevent overdrafts and duplicate accounts |

---

## File Handling

Account records are stored persistently using binary file operations in C (`fopen`, `fread`, `fwrite`, `fclose`). The approach works as follows:

- On program start, existing records are loaded from `accounts.dat`
- Every create, update, or delete operation writes the changes back to the file immediately
- Binary storage is used for efficiency and to preserve the exact structure of the `Account` struct
- If the data file does not exist on first run, the program creates it automatically

This simulates a basic flat-file database without requiring any third-party libraries.

---

## Error Handling

The system includes multiple layers of error handling to ensure reliability:

| Scenario                        | Handling                                              |
|---------------------------------|-------------------------------------------------------|
| Withdrawal exceeds balance      | Operation blocked, current balance displayed          |
| Duplicate account number        | Account creation rejected with an error message       |
| Account not found               | Informative message shown, no changes made            |
| Invalid menu input              | User prompted to re-enter a valid choice              |
| Empty name or zero/negative amount | Input rejected with a validation message           |

---

## Future Improvements

- Add interest calculation for savings accounts
- Implement transaction history with timestamps
- Add PIN-based authentication for each account
- Support multiple account types (savings, current, fixed deposit)
- Export account statements to a text or CSV file
- Build a simple GUI using a library like GTK or Qt

---

## Author

**Bhavay Sharma**
B.E. Computer Science and Engineering, Dayananda Sagar College of Engineering (2024–2028)

- GitHub: [github.com/bhavay-sharma](https://github.com/bhavay-sharma)
- LinkedIn: [linkedin.com/in/bhavay-sharma-i9](https://linkedin.com/in/bhavay-sharma-i9)
- Email: bhavay17s@gmail.com

---

*This project was developed as part of learning the C programming language and structured programming concepts.*
