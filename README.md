# Shopping-and-Inventory-Management-System-Cpp-Fundamentals-Project
Programming Fundamentals Project: Complete shopping system in C++. Features admin portal, customer interface, and file I/O operations. 

Mughal Online Mart: Dual-role C++ system with inventory management, multi-currency support, discount system, and file persistence.
# 🛒 Mughal Online Mart - Shopping & Inventory Management System

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Education](https://img.shields.io/badge/Educational_Project-Programming_Fundamentals-blue?style=for-the-badge)

A comprehensive **C++ console-based application** demonstrating core programming concepts through a fully-functional shopping system with dual interfaces for administration and customers.

## 🎯 Project Overview

**Mughal Online Mart** is a complete shopping and inventory management system built in C++ as a Programming Fundamentals project. The system features:

- **Dual Interface System**: Separate admin and customer portals
- **File-based Data Persistence**: All data stored in organized text files
- **Real-time Inventory Management**: Automatic stock tracking and updates
- **Multi-currency Support**: USD, EURO, and PKR with live conversion
- **Smart Discount System**: Admin-controlled promotions with customer rewards

## ✨ Key Features

### 🛠️ **Admin Module**
- ✅ Product CRUD operations (Add, Remove, Update, View)
- ✅ Automatic low-stock detection across 10 categories
- ✅ Sales report generation and viewing
- ✅ Discount/promo code management
- ✅ Secure 3-factor authentication

### 🛍️ **Customer Module**
- ✅ User registration & login with unique username enforcement
- ✅ Category-based product browsing (10 categories)
- ✅ Shopping cart with quantity management (max 50 items)
- ✅ Multi-currency price display and conversion
- ✅ Discount application at checkout
- ✅ Automatic receipt generation and file storage

### 🔧 **Technical Features**
- ✅ File I/O operations with multiple file types
- ✅ Real-time data synchronization
- ✅ Input validation and error handling
- ✅ Structured data using C++ structs and vectors
- ✅ Modular function-based architecture

## 📁 Project File Structure

<pre>
📦 Mughal-Online-Mart/
│
├── 📂 Project Related Files/
│   ├── 📂 Categories/
│   │   ├── Computer and Electronics.txt
│   │   ├── Beverages.txt
│   │   ├── Kitchen Accessories.txt
│   │   ├── DIY and Hardware.txt
│   │   ├── Sports and Outdoors.txt
│   │   ├── Bedroom Equipment.txt
│   │   ├── Stationery and Books.txt
│   │   ├── Bathroom Equipment.txt
│   │   ├── Beauty and Personal Care.txt
│   │   └── Perfumes and Fragrances.txt
│   │
│   ├── 📂 Logins/
│   │   ├── Admin Login.txt
│   │   └── Customer Login.txt
│   │
│   ├── 📂 Sales Reports/
│   │   └── Sales.txt
│   │
│   ├── 📂 Discount Codes/
│   │   └── Discount & promo Codes.txt
│   │
│   └── 📂 Purchase Reports/
│       └── {Username}.txt  (Generated per customer)
│
├── 📄 Shopping_System_and_Inventory_Management_System.cpp
├── 📄 README.md
└── 📄 LICENSE
</pre>

## 🏗️ System Architecture

**Main Application** → Mughal Online Mart

### 🔐 Authentication Layer
- **Admin**: 3-factor login (Name + Password + Auth Key)
- **Customer**: Login/Signup with unique username

### 🛠️ Admin Module
- Product Management (Add/Remove/Update/View)
- Inventory Monitoring (Auto low-stock alerts)
- Sales Reporting (Transaction history)
- Discount Management (Create promo codes)

### 🛍️ Customer Module
- Shopping Interface (Browse 10 categories)
- Cart System (Max 50 items, quantity management)
- Checkout Process (Discounts, receipts)
- Account Settings (Password/Auth updates)

### 💾 Data Storage Layer
- **Categories**: 10 product category files
- **Logins**: Admin & customer credentials
- **Sales**: Transaction records
- **Discounts**: Promotional codes with usage limits
- **Receipts**: Customer purchase records


## 🚀 Getting Started

### Prerequisites
- C++ Compiler (GCC, MinGW, or MSVC)
- Basic file system access for data storage

### Installation & Compilation
```bash
# Clone the repository
git clone https://github.com/yourusername/mughal-online-mart.git

# Compile the program
g++ Shopping_System_and_Inventory_Management_System.cpp -o Shopping_System_and_Inventory_Management_System.exe

# Run the program
./Shopping_System_and_Inventory_Management_System
```

## 🎓 Educational Purpose
Note: This project was developed as part of Programming Fundamentals coursework to demonstrate:

- File handling and data persistence

- Data structures (structs, vectors)

- Control structures and functions

- User interface design for console applications

- Error handling and input validation


![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

**Educational Use Notice**: This project was created for educational purposes as part of Programming Fundamentals coursework. While the MIT License permits reuse and modification, please:
- Do not submit this as your own academic work
- Credit the original author if using significant portions
- Use primarily as a learning resource

## 👤 Author
Abdullah Mughal

GitHub: @mughal-scri

Project for: Programming Fundamentals Course


---

c-plus-plus cpp-project programming-fundamentals
inventory-management shopping-system console-application
file-handling data-persistence student-project
educational-project cpp-learning

