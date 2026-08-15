# BSc in Computer Science & Engineering (4-Year Course)

A comprehensive repository containing all academic materials, study resources, coursework, projects, and documentation for a 4-year Bachelor of Science degree in Computer Science & Engineering.

## 📚 Repository Overview

This repository serves as a centralized hub for organizing and preserving all learning materials, assignments, lab work, projects, and study notes throughout the entire CSE degree program. It includes lecture slides, PDFs, notes, code implementations, projects, and other resources organized by academic year and semester.

### Key Features:
- **Organized by Academic Year**: Structured folders for Year 1, 2, 3, and 4
- **Semester-wise Organization**: Each year is divided into semesters (2_1, 2_2, etc.)
- **Course-specific Materials**: Dedicated folders for each course with subdivisions for lectures, labs, and assignments
- **Multiple File Types**: Jupyter notebooks, C++/Java source code, PDFs, documentation, and project reports
- **Project Portfolio**: Complete projects with source code, documentation, and lab reports
- **Curriculum Reference**: Official BSc CSE curriculum document

---

## 📂 Directory Structure

```
CSE/
├── First Year/              # Year 1 - Foundational Concepts
│   ├── 1_1/                # First Semester
│   │   ├── Course folders (with notes, assignments, labs, projects)
│   │   └── Study materials
│   └── 1_2/                # Second Semester
│
├── Second Year/            # Year 2 - Core CSE Concepts
│   ├── 2_1/               # Third Semester
│   │   ├── Algorithm/      # Algorithm Design & Analysis
│   │   │   ├── Lab/       # Lab assignments (C++ implementations)
│   │   │   └── Lectures/  # Lecture notes and slides
│   │   ├── Object Oriented Programming/
│   │   │   ├── Lab/       # Java implementations (ATM system, inheritance, polymorphism)
│   │   │   └── OOP/       # Object-oriented concepts
│   │   └── [Other courses]
│   │
│   └── 2_2/               # Fourth Semester
│       ├── Database Management System/
│       │   ├── Project/   # Complete database project with lab reports
│       │   ├── Lab/       # Database lab work
│       │   └── Theory/    # DBMS concepts and documentation
│       ├── Software Development Project Lab/
│       │   └── Payroll system/ # Employee payroll management system
│       └── [Other courses]
│
├── Third Year/            # Year 3 - Advanced Topics
│   ├── 3_1/              # Fifth Semester
│   │   ├── Microprocessor/
│   │   │   ├── Lab Final/  # 8086 Assembly language programs (factorial.asm)
│   │   │   ├── 8086.txt   # 8086 Microprocessor notes and architecture
│   │   │   └── Theory/    # Microprocessor concepts
│   │   ├── Operating System/
│   │   │   ├── Lab_03/    # Scheduling algorithms (SJF, etc.)
│   │   │   └── Concepts/  # OS theory and notes
│   │   ├── Software Engineering/
│   │   │   ├── LAB_REPORT.md  # University Payroll Management System (FastAPI + Streamlit)
│   │   │   └── Documentation
│   │   └── [Other courses]
│   │
│   └── 3_2/              # Sixth Semester
│       ├── Simulation/
│       │   ├── monte_carlo.py  # Monte Carlo simulation with visualization
│       │   └── Stochastic modeling
│       ├── Compiler Design/
│       │   ├── Lab_01/    # Lexical analysis (lex.yy.c)
│       │   ├── Lab_03/    # Syntax parsing (lexer.l, parser.y, parser.tab.h)
│       │   └── Theory/    # Compiler concepts
│       ├── Software Engineering Project/
│       │   ├── WebApp1/   # C# web application with DTOs and architecture
│       │   └── Documentation
│       └── [Other courses]
│
├── Documents/             # General Documentation
│   ├── Assignments/
│   ├── Exams/
│   ├── General Notes/
│   └── Resources/
│
├── Semster Fees/          # Administrative & Financial Documents
│   └── Fee receipts, payment records
│
├── CSE_Curriculum.pdf     # Official BSc CSE 4-Year Curriculum
├── University list For Masters.xlsx  # Post-graduation university options
└── hotel/                 # .NET Hotel Management System Project
    ├── src/
    │   ├── HotelManagement.API/      # ASP.NET Core API
    │   ├── HotelManagement.Application/ # Business logic & interfaces
    │   ├── HotelManagement.Domain/   # Entity models (Room, Booking, Customer)
    │   └── HotelManagement.Infrastructure/ # Data access & EF Core
    ├── HotelManagement.slnx         # Solution file
    └── README/                       # Project documentation
```

---

## 🎓 Course Organization by Year

### **First Year (1st & 2nd Semester)**
Foundational programming, mathematics, and computer science basics
- Introduction to Programming
- Discrete Mathematics
- Web Development Basics
- Software Fundamentals
- *[See folders for complete course list]*

### **Second Year (3rd & 4th Semester)**
Core computer science concepts and software development
- **Algorithm Design & Analysis**: DFS, graph traversal, cycle detection, activity selection
- **Object Oriented Programming**: Inheritance, polymorphism, encapsulation (Java)
- **Database Management Systems**: Database design, SQL, ER diagrams, relational models
- **Software Development Project Lab**: Payroll system development
- Data Structures
- Web Development
- *[See folders for complete course list]*

### **Third Year (5th & 6th Semester)**
Advanced topics and specializations
- **Microprocessor Architecture**: 8086 assembly language, instruction sets, addressing modes
- **Operating Systems**: Process scheduling (SJF, FCFS), process synchronization
- **Software Engineering**: Full-stack project development (FastAPI + Streamlit + SQLite)
- **Compiler Design**: Lexical analysis, syntax parsing using Lex & Yacc
- **Simulation**: Stochastic modeling, Monte Carlo methods
- **Advanced Web Development**: ASP.NET Core, C#, Entity Framework
- *[See folders for complete course list]*

### **Fourth Year (7th & 8th Semester)**
Specialization, capstone projects, and emerging technologies
- *[Add when Year 4 materials are added]*

---

## 💻 Notable Projects & Implementations

### **1. University Payroll Management System** (Third Year - Software Engineering)
- **Location**: `Third Year/3-1/Software Engineering/`
- **Tech Stack**: FastAPI (Backend), Streamlit (Frontend), SQLite, Python
- **Architecture**: Three-tier (Presentation → Business Logic → Data Access)
- **Features**:
  - Employee management (Faculty, Officers, Staff)
  - Automated salary calculation
  - Allowances: HRA (20%), TA (10%), Medical (₹2,000)
  - Deductions: Tax (5%), PF (3%)
  - Salary receipts & payroll reports
  - Data integrity constraints
- **Patterns Used**: Service, Repository, DTO, Factory patterns
- **[View Full Report](Third%20Year/3-1/Software%20Engineering/LAB_REPORT.md)**

### **2. Hotel Management System** (.NET Project)
- **Location**: `hotel/`
- **Tech Stack**: ASP.NET Core, Entity Framework Core, C#, SQL Server
- **Architecture**: Clean architecture with Domain, Application, and Infrastructure layers
- **Entities**: Room, Booking, Customer
- **Features**:
  - Room management and availability
  - Booking system
  - Customer management
  - RESTful API endpoints

### **3. ATM Machine System** (Second Year - OOP)
- **Location**: `Second Year/2_1/Object Oriented Programming/Lab/ATM_MACHINE/`
- **Language**: Java
- **Demonstrates**: Bank account operations, deposit, withdrawal, transaction history

### **4. Compiler Parser** (Third Year - Compiler Design)
- **Location**: `Third Year/3-2/Compiler Design/`
- **Tools**: Lex, Yacc
- **Components**:
  - Lexer (lexer.l) - Tokenization
  - Parser (parser.y) - Syntax tree generation
  - Regular expression support

### **5. Microprocessor Programs** (Third Year)
- **Location**: `Third Year/3-1/Microprocessor/`
- **Language**: 8086 Assembly
- **Programs**: Factorial calculation, loop operations
- **Concepts**: Registers, addressing modes, instruction execution

### **6. Algorithm Implementations** (Second Year)
- **DFS/BFS**: Graph traversal (C++)
- **DSU (Disjoint Set Union)**: Cycle detection in graphs
- **Activity Selection**: Greedy algorithm implementation
- **Fibonacci**: Recursive implementations

### **7. Operating System Simulations** (Third Year)
- **SJF Scheduling**: Non-preemptive CPU scheduling with wait time calculations
- **Process Management**: Arrival time, burst time, completion time analysis

### **8. Monte Carlo Simulation** (Third Year)
- **Location**: `Third Year/3-2/Simulation/monte_carlo.py`
- **Features**: Stochastic modeling, probability visualization, matplotlib graphics

---

## 📝 File Types & Content

| File Type | Description | Examples |
|-----------|-------------|----------|
| **.cpp / .c** | C/C++ lab implementations | Algorithm labs, OS scheduling, microprocessor programs |
| **.java** | Java OOP projects | ATM system, inheritance examples, polymorphism demos |
| **.cs** | C# backend projects | Hotel Management API, DTOs, business logic |
| **.py** | Python scripts & notebooks | Simulations, data analysis, utilities |
| **.asm** | 8086 Assembly language | Microprocessor programs |
| **.l / .y** | Lex/Yacc compiler tools | Lexer and parser definitions |
| **.md** | Markdown documentation | Lab reports, system documentation |
| **.pdf** | Lecture slides & documents | Notes, curriculum, reference materials |
| **.xlsx** | Spreadsheets | University list, schedules, grades |
| **.drawio** | Diagrams | ER diagrams, architecture diagrams |
| **.txt** | Text notes | Study notes, concept summaries |

---

## 🛠️ Technologies & Languages Used

### Programming Languages
- **C/C++**: Algorithms, Data Structures, Systems Programming
- **Java**: Object-Oriented Programming, Design Patterns
- **Python**: Simulation, Scripts, Data Analysis
- **C#**: ASP.NET Core, Web Development
- **8086 Assembly**: Microprocessor & Architecture
- **SQL**: Database Management
- **HTML/CSS/JavaScript**: Web Development

### Frameworks & Tools
- **Backend**: FastAPI, ASP.NET Core, Express.js
- **Frontend**: Streamlit, React
- **Database**: SQLite, SQL Server, MySQL
- **ORM**: Entity Framework Core, SQLAlchemy
- **Compiler Tools**: Lex, Yacc, Bison
- **Version Control**: Git
- **Development**: VS Code, Visual Studio, PyCharm

### Concepts & Topics Covered
- Data Structures & Algorithms
- Object-Oriented Programming
- Database Design & Management
- Web Application Development
- Software Engineering Principles
- Operating Systems
- Microprocessor Architecture
- Compiler Design
- Software Testing
- System Design
- Simulation & Modeling

---

## 📖 How to Use This Repository

1. **Browse by Year**: Navigate to your specific year folder (First Year, Second Year, etc.)
2. **Find Course Materials**: Look within each year's semester folders
3. **View Implementations**: Open `.cpp`, `.java`, or `.py` files to study code
4. **Read Documentation**: Check `.md` files and lab reports for detailed explanations
5. **Reference Curriculum**: See `CSE_Curriculum.pdf` for course structure

### For Study:
- Review lecture notes and PDFs
- Study implementations of algorithms and concepts
- Follow lab reports for practical applications
- Use projects as references for system design

### For Projects:
- Study full-stack project implementations
- Review architecture patterns used
- Understand design decisions and trade-offs
- Check documentation for setup and usage

---

## 📊 Academic Statistics

- **Total Academic Years**: 4 years (with Year 3 and Year 4 materials included)
- **Semesters Covered**: Up to 6+ semesters documented
- **Courses**: 20+ core courses with materials
- **Projects**: Multiple full-stack projects
- **Programming Languages**: 6+ languages
- **Lines of Code**: Thousands of lines across various implementations
- **Documentation**: Lab reports, README files, inline comments

---

## 🎯 Learning Outcomes

Through this repository, the following competencies have been developed:

✅ **Programming Proficiency**: C, C++, Java, Python, C#  
✅ **Data Structures & Algorithms**: Implementation and optimization  
✅ **Database Design**: ER modeling, normalization, SQL  
✅ **Web Development**: Full-stack applications, RESTful APIs  
✅ **Software Engineering**: Design patterns, architecture, best practices  
✅ **Operating Systems**: Process scheduling, synchronization  
✅ **Microprocessors**: Assembly language, hardware fundamentals  
✅ **Compilers**: Lexical and syntax analysis  
✅ **Project Management**: Multi-layer architecture, documentation  

---

## 📚 Additional Resources

- **Curriculum**: [CSE_Curriculum.pdf](CSE_Curriculum.pdf) - Official 4-year program structure
- **Higher Studies**: [University list For Masters.xlsx](University%20list%20For%20Masters.xlsx) - Post-graduation options
- **Lab Reports**: Available in individual course folders with detailed analysis

---

## 📝 Notes

- This repository is continually updated with new materials as semesters progress
- All code follows industry best practices and uses proper naming conventions
- Projects demonstrate real-world application of theoretical concepts
- Documentation is comprehensive to facilitate learning and reference

---

## 👤 Author

**Marwanthe0** - CSE Student  
*Maintaining comprehensive academic documentation and project portfolio*

---

## 📄 License

These materials are personal academic work. If you use any code or content, please provide appropriate attribution.

---

## 🔗 Quick Links

- [First Year Materials](First%20Year/)
- [Second Year Materials](Second%20Year/)
- [Third Year Materials](Third%20Year/)
- [Payroll System Documentation](Third%20Year/3-1/Software%20Engineering/LAB_REPORT.md)
- [Hotel Management Project](hotel/)
- [Official Curriculum](CSE_Curriculum.pdf)

---

**Last Updated**: August 2026  
**Repository Size**: ~866 MB  
**Topics**: `cse` `computer-science` `coursework` `jupyter-notebook` `python` `machine-learning` `data-science` `artificial-intelligence` `software-engineering`

---

*For questions or suggestions about this repository, please reach out!*
