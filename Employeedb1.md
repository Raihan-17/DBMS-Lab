====================================
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
