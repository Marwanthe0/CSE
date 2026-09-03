# CSE Undergraduate Coursework and Academic Archive

A structured repository containing academic coursework, lab implementations, semester projects, and study materials from my Bachelor of Science in Computer Science and Engineering (CSE).

The primary purpose of this repository is personal version control, reference, and tracking academic progression from foundational mathematics and programming up to advanced systems and software engineering.

---

## Repository Structure

```
CSE/
├── First Year/
│   ├── 1-1/                          # Discrete Math, Calculus, Basic EEE, Chemistry, Bangladesh Studies
│   └── 1-2/                          # Data Structures & Algorithms, Calculus, DLD, Physics, Engineering Drawing
│
├── Second Year/
│   ├── 2_1/                          # Algorithms, OOP (Java), Computer Architecture, Numerical Analysis
│   └── 2_2/                          # DBMS, Software Dev Lab, Data Comm & Networking, Linear Algebra, Statistics
│
├── Third Year/
│   ├── 3-1/                          # Microprocessor (8086), Operating Systems, Software Engineering, Web Dev Lab
│   └── 3-2/                          # AI & ML, Compiler Design, Software Engineering Project, Simulation, IoT
│
├── Documents/                        # Academic records, certificates, marksheets, and higher study references
│   ├── Admit Card/
│   ├── Certificates/
│   ├── Marksheets/
│   ├── Semster Fees/
│   └── University list For Masters.xlsx
│
└── CSE_Curriculum.pdf                # Official department syllabus and course outline
```

---

## Coursework by Semester

### First Year

#### Semester 1-1
- **Discrete Mathematics**: Logic, set theory, relations, combinatorics, and graph theory fundamentals.
- **Calculus**: Differential calculus, limits, continuity, and basic integration.
- **Electrical & Electronic Engineering (EEE)**: Basic circuit theory, Ohm's law, Kirchhoff's laws, and network theorems.
- **Basic Chemistry & Bangladesh Studies**: Allied foundational courses.
- Course archives include question papers from 2019 to 2022.

#### Semester 1-2
- **Data Structures and Algorithms**: Arrays, linked lists, stacks, queues, recursion, and introductory sorting/searching.
- **Differential and Integral Calculus**: Multivariable calculus, series, and integration techniques.
- **Digital Logic Design (DLD)**: Boolean algebra, logic gates, combinational and sequential circuit design, flip-flops, registers.
- **Physics & Engineering Drawing**: Foundational engineering sciences and CAD/drawing practices.

---

### Second Year

#### Semester 2_1
- **Algorithm Design and Analysis**:
  - Graph traversal: Depth-First Search (DFS), Breadth-First Search (BFS)
  - Disjoint Set Union (DSU) and cycle detection
  - Greedy strategies: Activity Selection Problem
  - Dynamic programming and recursive problems (Fibonacci, optimization)
  - C++ lab implementations and problem sets
- **Object-Oriented Programming (Java)**:
  - OOP pillars: Encapsulation, inheritance, polymorphism, abstraction
  - Exception handling, Java collections, and file I/O
  - Lab implementation: Console-based ATM banking system
- **Computer Architecture**: Instruction set architecture, CPU datapath, pipelining, and memory hierarchy.
- **Numerical Analysis & Linear Algebra**: Matrix operations, numerical methods for equation solving and interpolation.

#### Semester 2_2
- **Database Management Systems (DBMS)**:
  - Relational model, Entity-Relationship (ER) modeling, normalization (1NF through BCNF)
  - SQL querying, indexing techniques, B+ tree indexing
  - Semester lab reports and database design project
- **Software Development Project Lab**:
  - Multi-tier employee and payroll management system implemented in Java and C++
  - Class hierarchies for Teachers, Officers, and Staff with salary calculation logic
- **Data Communications and Networking**: Layered network architectures, signal encoding, data link protocols.
- **Digital System Design**: Advanced digital circuits, HDL fundamentals, and state machine design.
- **Probability and Statistics**: Distributions, hypothesis testing, and statistical analysis for computing.

---

### Third Year

#### Semester 3-1
- **Software Engineering**:
  - System analysis, architectural patterns (Service, Repository, DTO), and UML modeling
  - Course project: [University Payroll Management System](Third%20Year/3-1/Software%20Engineering/LAB_REPORT.md)
  - Tech stack: Python, FastAPI backend, Streamlit UI, SQLite
- **Operating Systems**:
  - Process scheduling algorithms: Shortest Job First (SJF), First-Come First-Served (FCFS)
  - Process synchronization, deadlock handling, paging, and page fault handling mechanisms
  - C/C++ lab implementations and question solutions
- **Microprocessor and Interfacing**:
  - Intel 8086 architecture, registers, segment-offset addressing, and interrupt handling
  - 8086 Assembly programs: Arithmetic routines, factorial calculation, memory array operations
  - Embedded systems introduction: Modules covering architecture, interfacing, and system design
- **Web Development Lab**: Frontend and backend fundamentals, client-server communication.
- **Engineering Ethics**: Professional ethics, intellectual property, and computing code of conduct.

#### Semester 3-2
- **Compiler Design**:
  - Lexical analysis using Flex / Lex (`lexer.l`, `lex.yy.c`)
  - Syntax analysis and parsing using Bison / Yacc (`parser.y`, grammar definitions)
  - Tokenization, regular expression evaluation, and parse tree construction
- **Artificial Intelligence and Machine Learning**:
  - Search strategies: Uninformed search (BFS, DFS) and informed search (A*, heuristic search)
  - Constraint Satisfaction Problems (CSPs)
  - Supervised learning basics: Linear models, Gradient Descent, Artificial Neural Networks (ANN)
  - Jupyter notebook lab tasks and evaluation reports
- **Simulation and Modeling**:
  - Stochastic modeling and probabilistic simulations
  - Monte Carlo simulation with visualization (`monte_carlo.py`)
  - Single-server queuing model simulation (`single_server.py`)
  - Inventory systems simulation
- **Software Engineering Capstone / Project**:
  - [Hotel Management System](Third%20Year/3-2/Software%20Engineering/HotelManagement/): Full-stack enterprise application built with ASP.NET Core and Clean Architecture
  - WebApp1: Minimal API prototype demonstrating DTO patterns and EF Core integration
- **Internet of Things (IoT)**: Sensor interfacing, microcontroller workflows, and hardware communication.

---

## Highlighted Projects

### 1. Hotel Management System (.NET / Clean Architecture)
- **Path**: [`Third Year/3-2/Software Engineering/HotelManagement`](Third%20Year/3-2/Software%20Engineering/HotelManagement/)
- **Stack**: ASP.NET Core, Entity Framework Core, C#, SQL Server, React
- **Architecture**: Clean Architecture split across distinct layers:
  - `HotelManagement.Domain`: Core business models (Room, Booking, Customer)
  - `HotelManagement.Application`: Service contracts, DTOs, and validation logic
  - `HotelManagement.Infrastructure`: Data persistence, EF Core configurations, and external services
  - `HotelManagement.API`: RESTful endpoints, middleware, and dependency injection configuration
- **Capabilities**: Room inventory tracking, booking management, customer records, and status transitions.

### 2. University Payroll Management System
- **Path**: [`Third Year/3-1/Software Engineering/LAB_REPORT.md`](Third%20Year/3-1/Software%20Engineering/LAB_REPORT.md)
- **Stack**: Python, FastAPI, Streamlit, SQLite
- **Architecture**: Three-tier architecture decoupling presentation, service logic, and database operations.
- **Capabilities**: Automated payroll generation for faculty, administrative officers, and support staff; calculation of house rent allowances, medical benefits, and tax deductions; payslip generation.

### 3. Compiler Lexer and Parser Suite
- **Path**: [`Third Year/3-2/Compiler Design`](Third%20Year/3-2/Compiler%20Design/)
- **Stack**: C, Flex, Bison
- **Capabilities**: Custom token generator and grammar parser handling language constructs, operator precedence, syntax verification, and error detection.

### 4. Microprocessor 8086 Assembly Suite
- **Path**: [`Third Year/3-1/Microprocessor`](Third%20Year/3-1/Microprocessor/)
- **Stack**: 8086 Assembly, EMU8086
- **Capabilities**: Assembly subroutines covering register arithmetic, looping constructs, memory addressing modes, and modular subroutines.

---

## Primary Technologies and Tooling

- **Programming Languages**: C, C++, Java, C#, Python, x86 Assembly (8086), SQL
- **Frameworks & Libraries**: ASP.NET Core, Entity Framework Core, FastAPI, Streamlit, NumPy, Matplotlib
- **Systems & Compilers**: GCC/G++, Flex, Bison, EMU8086, DOSBox
- **Databases**: SQLite, SQL Server, MySQL
- **Developer Tools**: Visual Studio, VS Code, Git

---

## Academic Reference Documents

The [`Documents/`](Documents/) directory stores administrative records, certifications, and reference lists:
- Academic documents: Transcripts, admit cards, and semester fee records
- Curriculum: [`CSE_Curriculum.pdf`](CSE_Curriculum.pdf) contains the full 4-year undergraduate syllabus
- Higher study planning: [`Documents/University list For Masters.xlsx`](Documents/University%20list%20For%20Masters.xlsx)

---

## Notes on Academic Integrity

This repository is maintained as an archive of my undergraduate coursework and personal learning progress. If you are a student taking similar courses, feel free to use these materials for conceptual understanding and study. Please do not directly copy assignment solutions or lab submissions for your own graded coursework.
