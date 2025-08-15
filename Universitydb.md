-- ====================================
-- UNIVERSITY DATABASE
-- ====================================
CREATE DATABASE UniversityDB;
USE UniversityDB;

-- Create tables
CREATE TABLE Department (
    DepartmentID INT PRIMARY KEY,
    DepartmentName VARCHAR(50),
    HeadOfDept VARCHAR(50),
    FacultyCount INT
);

CREATE TABLE Student (
    StudentID INT PRIMARY KEY,
    StudentName VARCHAR(50),
    DOB DATE,
    Gender CHAR(1),
    Address VARCHAR(100),
    Phone VARCHAR(15),
    Email VARCHAR(50),
    DepartmentID INT,
    FOREIGN KEY (DepartmentID) REFERENCES Department(DepartmentID)
);

CREATE TABLE Course (
    CourseID INT PRIMARY KEY,
    CourseName VARCHAR(50),
    Credits INT,
    DepartmentID INT,
    FOREIGN KEY (DepartmentID) REFERENCES Department(DepartmentID)
);

CREATE TABLE Faculty (
    FacultyID INT PRIMARY KEY,
    FacultyMemberName VARCHAR(50),
    Designation VARCHAR(50),
    Email VARCHAR(50),
    Phone VARCHAR(15),
    DepartmentID INT,
    FOREIGN KEY (DepartmentID) REFERENCES Department(DepartmentID)
);

CREATE TABLE Enrollment (
    EnrollmentID INT PRIMARY KEY,
    StudentID INT,
    CourseID INT,
    Semester VARCHAR(10),
    Grade CHAR(2),
    FOREIGN KEY (StudentID) REFERENCES Student(StudentID),
    FOREIGN KEY (CourseID) REFERENCES Course(CourseID)
);

CREATE TABLE Classroom (
    RoomNumber INT PRIMARY KEY,
    Building VARCHAR(50),
    Capacity INT
);

-- Insert Departments
INSERT INTO Department VALUES
(1, 'Computer Science', 'Dr. Smith', 10),
(2, 'Mathematics', 'Dr. Jones', 8);

-- Insert Students
INSERT INTO Student VALUES
(1, 'Alice', '2000-05-10', 'F', 'Street1', '1111111111', 'alice@example.com', 1),
(2, 'Bob', '1999-08-15', 'M', 'Street2', '2222222222', 'bob@example.com', 1),
(3, 'Charlie', '2001-02-20', 'M', 'Street3', '3333333333', 'charlie@example.com', 2),
(4, 'Diana', '2000-12-12', 'F', 'Street4', '4444444444', 'diana@example.com', 1);

-- Insert Courses
INSERT INTO Course VALUES
(101, 'DBMS', 3, 1),
(102, 'Algorithms', 4, 1),
(103, 'Data Structures', 3, 1),
(104, 'Calculus', 3, 2),
(105, 'Statistics', 3, 2);

-- Insert Faculty
INSERT INTO Faculty VALUES
(1, 'Dr. Smith', 'Professor', 'smith@example.com', '5551111111', 1),
(2, 'Dr. Jones', 'Professor', 'jones@example.com', '5552222222', 2);

-- Insert Enrollment
-- Alice takes 4 courses (>3 courses requirement)
INSERT INTO Enrollment VALUES
(1, 1, 101, 'Fall', 'A'),
(2, 1, 102, 'Fall', 'B'),
(3, 1, 103, 'Fall', 'C'),
(4, 1, 104, 'Fall', 'B');

-- Bob takes 2 courses
INSERT INTO Enrollment VALUES
(5, 2, 101, 'Fall', 'A'),
(6, 2, 105, 'Fall', 'F'); -- Bob got F

-- Charlie takes 1 course
INSERT INTO Enrollment VALUES
(7, 3, 104, 'Fall', 'B');

-- Diana takes 1 course
INSERT INTO Enrollment VALUES
(8, 4, 103, 'Fall', 'B');

-- Insert Classrooms
INSERT INTO Classroom VALUES
(201, 'Building A', 40),
(202, 'Building B', 35);

-- ====================================
-- QUERIES
-- ====================================

-- I. Department with highest number of students
SELECT DepartmentID, COUNT(*) AS StudentCount
FROM Student
GROUP BY DepartmentID
ORDER BY StudentCount DESC
LIMIT 1;

-- II. Students who have taken more than 3 courses
SELECT StudentID, COUNT(*) AS CourseCount
FROM Enrollment
GROUP BY StudentID
HAVING COUNT(*) > 3;

-- III. Students with at least one 'F'
SELECT DISTINCT s.StudentID, s.StudentName
FROM Student s
JOIN Enrollment e ON s.StudentID = e.StudentID
WHERE e.Grade = 'F';

-- IV. Total number of students enrolled in each course
SELECT CourseID, COUNT(*) AS TotalStudents
FROM Enrollment
GROUP BY CourseID;
