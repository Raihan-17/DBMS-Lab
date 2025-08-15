CREATE DATABASE EmployeeDB_Q5;
USE EmployeeDB_Q5;

CREATE TABLE employee (
    EmployeeID INT PRIMARY KEY,
    EmployeeName VARCHAR(20),
    Street VARCHAR(20),
    City VARCHAR(20)
);

CREATE TABLE company (
    CompanyName VARCHAR(30) PRIMARY KEY,
    City VARCHAR(20)
);

CREATE TABLE works (
    EmployeeID INT,
    CompanyName VARCHAR(30),
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

-- Insert companies
INSERT INTO company VALUES
('First Bank Corporation', 'Dhaka'),
('TechCorp', 'Chittagong');

-- Insert employees
INSERT INTO employee VALUES
(1, 'Eve', 'StreetA', 'Dhaka'),
(2, 'Frank', 'StreetB', 'Dhaka'),
(3, 'Grace', 'StreetC', 'Dhaka'),
(4, 'Heidi', 'StreetD', 'Dhaka'),
(5, 'Ivan', 'StreetE', 'Dhaka'),
(6, 'Judy', 'StreetF', 'Dhaka'),
(7, 'Karl', 'StreetG', 'Chittagong');

-- Works mapping (6 employees in First Bank Corporation to meet >5 condition)
INSERT INTO works VALUES
(1, 'First Bank Corporation', 50000),
(2, 'First Bank Corporation', 52000),
(3, 'First Bank Corporation', 55000),
(4, 'First Bank Corporation', 60000),
(5, 'First Bank Corporation', 62000),
(6, 'First Bank Corporation', 58000),
(7, 'TechCorp', 70000);

-- Manages mapping (leave some without managers)
INSERT INTO manages VALUES
(1, 2), -- Eve managed by Frank
(3, 4); -- Grace managed by Heidi


Queries:

-- I. Companies with more than 5 employees
SELECT CompanyName
FROM works
GROUP BY CompanyName
HAVING COUNT(*) > 5;

-- II. 20% raise for First Bank Corporation employees
UPDATE works
SET Salary = Salary * 1.20
WHERE CompanyName = 'First Bank Corporation';

-- III. Delete employees with no manager
DELETE FROM employee
WHERE EmployeeID NOT IN (SELECT EmployeeID FROM manages);

-- IV. Assign a new manager (e.g., ManagerID = 2) to employees with no manager
INSERT INTO manages (EmployeeID, ManagerID)
SELECT e.EmployeeID, 2
FROM employee e
LEFT JOIN manages m ON e.EmployeeID = m.EmployeeID
WHERE m.EmployeeID IS NULL;
