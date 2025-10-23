# 🏦 Bharati Bank Management System (C Project)

## 📘 Overview

The **Bharati Bank Management System** is a console-based project developed in **C language**.
It enables basic banking operations such as account creation, deposits, withdrawals, transfers, updates, and deletions using **file handling** for data storage.

This project is ideal for students learning **Data Structures**, **File Handling**, and **Modular Programming in C**.

---

## ⚙️ Features

* 🧾 **Create New Account** – Add new customer accounts with initial balance
* 💰 **Deposit Money** – Add money to an existing account
* 💸 **Withdraw Money** – Withdraw amount if sufficient balance is available
* 🔁 **Transfer Money** – Transfer funds between two accounts
* 🧍 **Update Account Info** – Modify account holder’s name
* ❌ **Delete Account** – Remove an existing account from the system
* 📋 **Display Account** – View details of a single account
* 📂 **Display All Accounts** – List all customer accounts with balances

---

## 🧩 Concepts Used

* **File Handling in C** (`fopen`, `fprintf`, `fscanf`, `remove`, `rename`)
* **Structures (`struct`)** for representing account data
* **String Handling** (`fgets`, `strcspn`, `strcpy`)
* **Input Validation & Buffer Clearing**
* **Menu-Driven Loops** using `switch` and `while`

---

## 🗂️ File Structure

```
📁 Bank_Management_System/
│
├── bank_management.c     # Main source code file
├── bank_records.txt      # Stores all account data
└── README.md             # Project documentation
```

---

## 🚀 How to Run

### 🪟 For Windows:

1. Open **Command Prompt** or any C IDE (e.g., Code::Blocks, Dev-C++, Turbo C, VS Code)
2. Compile the code:

   ```bash
   gcc bank_management.c -o bank
   ```
3. Run the executable:

   ```bash
   ./bank
   ```

### 🐧 For Linux / macOS:

1. Open the terminal
2. Compile the program:

   ```bash
   gcc bank_management.c -o bank
   ```
3. Run:

   ```bash
   ./bank
   ```

> ⚠️ Ensure the program has permission to read/write files in the same directory.

---

## 🧮 Sample Operations

```
======= Bharati BANK MANAGEMENT SYSTEM =======
1. Create New Account
2. Display Account Details
3. Deposit Money
4. Withdraw Money
5. Transfer Money
6. Update Account Info
7. Delete Account
8. Display All Accounts
9. Exit
```

---

## 💾 Data Storage Format

Each account record is stored in `bank_records.txt` as:

```
<AccountNumber> "AccountHolderName" <Balance>
```

Example:

```
1001 "Aamir Shaikh" 5000.00
1002 "Riya Patel"  7500.50
```

---

## 🧠 Learning Outcomes

* Understanding **persistent data management** using text files
* Implementing **real-world banking operations** with C logic
* Strengthening command over **structures, loops, and conditional logic**
* Gaining experience with **modular function-based design**

---

## 👨‍💻 Developed By

**Aamir Shaikh**
Bharati Vidyapeeth (Deemed to be University), College of Engineering, Pune
*Project-Based Learning (PBL) — Data Structures, Semester III (IT Branch)*
