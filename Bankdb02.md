CREATE DATABASE BankDB_Q4;
USE BankDB_Q4;

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

CREATE TABLE SavingAccount (
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
    FOREIGN KEY (AccountNumber) REFERENCES SavingAccount(AccountNumber)
);

CREATE TABLE Borrower (
    CustomerID INT,
    LoanNumber INT,
    PRIMARY KEY (CustomerID, LoanNumber),
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID),
    FOREIGN KEY (LoanNumber) REFERENCES Loan(LoanNumber)
);

-- Insert Branches
INSERT INTO Branch VALUES
('B1', 'Dhaka', 1000000),
('B2', 'Chittagong', 800000),
('B3', 'Sylhet', 600000);

-- Insert Customers
INSERT INTO Customer VALUES
(1, 'Alice', 'Street1', 'Dhaka'),
(2, 'Bob', 'Street2', 'Chittagong'),
(3, 'Charlie', 'Street3', 'Dhaka'),
(4, 'David', 'Street4', 'Sylhet');

-- Insert Saving Accounts (balances in ranges for conditions)
INSERT INTO SavingAccount VALUES
(101, 'B1', 10000),
(102, 'B1', 70000),
(103, 'B2', 3000),
(104, 'B3', 20000);

-- Insert Loans (amounts for between 5000-15000 and >50000 conditions)
INSERT INTO Loan VALUES
(201, 'B1', 10000),    -- between range
(202, 'B1', 60000),    -- big loan
(203, 'B2', 8000),     -- between range
(204, 'B3', 70000);    -- big loan

-- Depositor mapping
INSERT INTO Depositor VALUES
(1, 101),
(2, 102),
(3, 103),
(4, 104);

-- Borrower mapping (for 3% vs 5% service charge)
INSERT INTO Borrower VALUES
(1, 201), -- Alice has both
(2, 202), -- Bob has both
(3, 203), -- Charlie loan only
(4, 204); -- David has both



Queries:

-- I. Delete loans between 5000 and 15000
DELETE FROM Loan
WHERE Amount BETWEEN 5000 AND 15000;

-- II. Branches with no accounts
SELECT b.BranchName
FROM Branch b
LEFT JOIN SavingAccount s ON b.BranchName = s.BranchName
WHERE s.AccountNumber IS NULL;

-- III. Branches where total loan amount > 50000
SELECT BranchName, SUM(Amount) AS TotalLoan
FROM Loan
GROUP BY BranchName
HAVING SUM(Amount) > 50000;

-- IV. Deduct service charge: 3% if both loan & savings, else 5%
UPDATE SavingAccount sa
JOIN Depositor d ON sa.AccountNumber = d.AccountNumber
JOIN Customer c ON d.CustomerID = c.CustomerID
LEFT JOIN Borrower b ON c.CustomerID = b.CustomerID
SET sa.Balance = sa.Balance * (CASE WHEN b.LoanNumber IS NOT NULL THEN 0.97 ELSE 0.95 END);
