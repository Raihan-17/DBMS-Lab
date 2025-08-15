-- ====================================
-- 1. BANK DATABASE
-- ====================================
CREATE DATABASE BankDB;
USE BankDB;

-- Create tables
CREATE TABLE Branch (
    BranchName VARCHAR(20) PRIMARY KEY,
    BranchCity VARCHAR(20),
    Assets INT
);

CREATE TABLE Customer (
    CustomerID INT PRIMARY KEY,
    CustomerName VARCHAR(20),
    CustomerStreet VARCHAR(20),
    CustomerCity VARCHAR(20)
);

CREATE TABLE Account (
    AccountNumber INT PRIMARY KEY,
    BranchName VARCHAR(20),
    Balance INT,
    FOREIGN KEY (BranchName) REFERENCES Branch(BranchName)
);

CREATE TABLE Loan (
    LoanNumber INT PRIMARY KEY,
    BranchName VARCHAR(20),
    Amount INT,
    FOREIGN KEY (BranchName) REFERENCES Branch(BranchName)
);

CREATE TABLE Depositor (
    CustomerID INT,
    AccountNumber INT,
    PRIMARY KEY (CustomerID, AccountNumber),
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID),
    FOREIGN KEY (AccountNumber) REFERENCES Account(AccountNumber)
);

CREATE TABLE Borrower (
    CustomerID INT,
    LoanNumber INT,
    PRIMARY KEY (CustomerID, LoanNumber),
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID),
    FOREIGN KEY (LoanNumber) REFERENCES Loan(LoanNumber)
);

-- Insert values
INSERT INTO Branch VALUES
('B1', 'Dhaka', 1000000),
('B2', 'Chittagong', 800000);

INSERT INTO Customer VALUES
(1, 'Alice', 'Street1', 'Dhaka'),
(2, 'Bob', 'Street2', 'Chittagong'),
(3, 'Charlie', 'Street3', 'Dhaka');

INSERT INTO Account VALUES
(101, 'B1', 5000),
(102, 'B1', 7000),
(103, 'B2', 3000);

INSERT INTO Loan VALUES
(201, 'B1', 15000),
(202, 'B2', 20000);

INSERT INTO Depositor VALUES
(1, 101),
(2, 102);

INSERT INTO Borrower VALUES
(2, 201),
(3, 202);

-- Show database and tables
SHOW DATABASES;
SHOW TABLES;

-- Show data
SELECT * FROM Branch;
SELECT * FROM Customer;
SELECT * FROM Account;
SELECT * FROM Loan;
SELECT * FROM Depositor;
SELECT * FROM Borrower;

-- Exam Queries (BankDB)

-- I. Customers with account or loan
SELECT DISTINCT c.CustomerID, c.CustomerName
FROM Customer c
LEFT JOIN Depositor d ON c.CustomerID = d.CustomerID
LEFT JOIN Borrower b ON c.CustomerID = b.CustomerID
WHERE d.AccountNumber IS NOT NULL OR b.LoanNumber IS NOT NULL;

-- II. Branch with maximum accounts
SELECT BranchName
FROM Account
GROUP BY BranchName
ORDER BY COUNT(*) DESC
LIMIT 1;

-- III. Maximum loan amount in each branch
SELECT BranchName, MAX(Amount) AS MaxLoan
FROM Loan
GROUP BY BranchName;

-- IV. Customers whose names start with 'A'
SELECT CustomerID, CustomerName
FROM Customer
WHERE CustomerName LIKE 'A%';

-- ====================================
-- 2. EMPLOYEE DATABASE
-- ====================================
CREATE DATABASE EmployeeDB;
USE EmployeeDB;

-- Create tables
CREATE TABLE employee (
    EmployeeID INT PRIMARY KEY,
    EmployeeName VARCHAR(20),
    Street VARCHAR(20),
    City VARCHAR(20)
);

CREATE TABLE company (
    CompanyName VARCHAR(20) PRIMARY KEY,
    City VARCHAR(20)
);

CREATE TABLE works (
    EmployeeID INT,
    CompanyName VARCHAR(20),
    Salary INT,
    PRIMARY KEY (EmployeeID, CompanyName),
    FOREIGN KEY (EmployeeID) REFERENCES employee(EmployeeID),
    FOREIGN KEY (CompanyName) REFERENCES company(CompanyName)
);

CREATE TABLE manages (
    EmployeeID INT,
    ManagerID INT,
    PRIMARY KEY (EmployeeID, ManagerID),
    FOREIGN KEY (EmployeeID) REFERENCES employee(EmployeeID)
);

-- Insert values
INSERT INTO employee VALUES
(1, 'Eve', 'StreetA', 'Dhaka'),
(2, 'Frank', 'StreetB', 'Chittagong'),
(3, 'Grace', 'StreetC', 'Dhaka'),
(4, 'Heidi', 'StreetD', 'Khulna');

INSERT INTO company VALUES
('CompA', 'Dhaka'),
('CompB', 'Chittagong');

INSERT INTO works VALUES
(1, 'CompA', 50000),
(2, 'CompA', 60000),
(3, 'CompB', 55000),
(4, 'CompB', 70000);

INSERT INTO manages VALUES
(1, 2),   -- Eve managed by Frank
(3, 4);   -- Grace managed by Heidi

-- Show tables and data
SHOW TABLES;
SELECT * FROM employee;
SELECT * FROM company;
SELECT * FROM works;
SELECT * FROM manages;

-- Exam Queries (EmployeeDB)

-- I. Company with most employees
SELECT CompanyName
FROM works
GROUP BY CompanyName
ORDER BY COUNT(*) DESC
LIMIT 1;

-- II. Employees without a manager
SELECT e.EmployeeID, e.EmployeeName
FROM employee e
LEFT JOIN manages m ON e.EmployeeID = m.EmployeeID
WHERE m.ManagerID IS NULL;

-- III. Second highest salary
SELECT DISTINCT Salary
FROM works
ORDER BY Salary DESC
LIMIT 1 OFFSET 1;

-- IV. Employees in Dhaka but company not in Dhaka
SELECT e.EmployeeID, e.EmployeeName
FROM employee e
JOIN works w ON e.EmployeeID = w.EmployeeID
JOIN company c ON w.CompanyName = c.CompanyName
WHERE e.City = 'Dhaka' AND c.City <> 'Dhaka';
