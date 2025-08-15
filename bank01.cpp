-- 1. Create database and use it
CREATE DATABASE BankDB;
USE BankDB;

-- 2. Create tables
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

-- 3. Insert values
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

-- 4. Show database and tables
SHOW DATABASES;
SHOW TABLES;

-- 5. Show data from each table
SELECT * FROM Branch;
SELECT * FROM Customer;
SELECT * FROM Account;
SELECT * FROM Loan;
SELECT * FROM Depositor;
SELECT * FROM Borrower;

-- 6. Queries from exam

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
