-- CREATE DATABASE INFO;
-- show global variables like 'local_infile';
-- set global local_infile=true;
-- tee /home/tiger/Desktop/College/DBMS/SQL/data.txt;

USE INFO;

DROP TABLE IF EXISTS lab_3;
CREATE TABLE lab_3(
    first_name varchar(30),
    last_name varchar(30),
    roll_no int not null primary key,
    gender char(1),
    age int
);

INSERT INTO lab_3 VALUES ('Yash','Raj',20075098,'M',20);

LOAD DATA LOCAL infile "/home/tiger/Desktop/College/DBMS/SQL/lab2.csv" into table lab_3 FIELDS TERMINATED BY ',' LINES TERMINATED BY '\n';

INSERT INTO lab_3 VALUES ('Abhinav','Verma',20075058,'F',21),('Shreya','Sharma',20075051,'F',19),('Dhruv','Rathi',20075049,'M',18);

ALTER TABLE lab_3 ADD CONSTRAINT name_unique UNIQUE (first_name,last_name);

ALTER TABLE lab_3 DROP INDEX name_unique;

ALTER TABLE lab_3 MODIFY COLUMN gender char(1) not null default 'M';

ALTER TABLE TAB_2 add constraint age CHECK (age>=18);

DESCRIBE lab_3;

SELECT * FROM lab_3 WHERE NOT gender='F' ORDER BY first_name DESC;
SELECT COUNT(first_name), first_name FROM lab_3 GROUP BY first_name ORDER BY COUNT(first_name) DESC;
SELECT * FROM lab_3 WHERE last_name LIKE '_e%' AND first_name NOT LIKE 	BINARY 'A%';

update lab_3 set gender='M' where first_name='Alok';

delete from lab_3 where first_name='Yash';

SELECT * FROM lab_3;