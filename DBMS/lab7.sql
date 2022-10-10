CREATE DATABASE COLLEGE;

USE COLLEGE;

DROP TABLE IF EXISTS students;
CREATE TABLE students(
    srn int,
 fname varchar(200),
 lname varchar(200),
 age int,
 gender varchar(1),
 phone_no varchar(10),
 primary key(srn)
);
LOAD DATA LOCAL INFILE '/home/tiger/Desktop/College/DBMS/SQL/Children.csv'
INTO TABLE students
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(fname,lname,srn,age,gender,phone_no);

SELECT * FROM students WHERE fname='Ryf' LIMIT 0,100000;
-- SELECT * FROM students FORCE INDEX(finder) LIMIT 0,100000; 

CREATE INDEX finder ON students (fname);
ALTER TABLE students DROP INDEX finder;








































































DROP TABLE IF EXISTS courses;
CREATE TABLE courses(
    Cid int,
  Cname varchar(200),
  Department varchar(200),
  primary key(Cid)
);
 LOAD DATA LOCAL INFILE '/home/tiger/Desktop/College/DBMS/SQL/Courses.csv'
INTO TABLE courses
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(Cid,Cname,Department);

DROP TABLE IF EXISTS enrollment;
CREATE TABLE enrollment(
    rollNo int,
    Cid int,
    Grade varchar(1),
    Semester varchar(4),
    primary key(rollNo, Cid),
    foreign key (rollNo) references students(srn),
   foreign key (Cid) references courses(Cid) 
);
 LOAD DATA LOCAL INFILE '/home/tiger/Desktop/College/DBMS/SQL/Enrollment.csv'
INTO TABLE enrollment
FIELDS TERMINATED BY ','
OPTIONALLY ENCLOSED BY '\"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS
(rollNo,Cid,Grade,Semester);