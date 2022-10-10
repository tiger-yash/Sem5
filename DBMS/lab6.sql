CREATE DATABASE lab6;

CREATE USER 'A'@'localhost' IDENTIFIED BY 'Newuser123a!';
CREATE USER 'B'@'localhost' IDENTIFIED BY 'Newuser123b!';
CREATE USER 'C'@'localhost' IDENTIFIED BY 'Newuser123c!';

USE mysql;  
select user from user;

DROP ROLE IF EXISTS 'Student','Faculty','Dean';
CREATE ROLE 'Student', 'Faculty', 'Dean';

GRANT create ON lab6.* TO 'Faculty';
GRANT select ON lab6.* TO 'Student';
GRANT ALL PRIVILEGES ON lab6.* TO 'Dean';

GRANT GRANT OPTION ON lab6.* to 'A'@'localhost';

GRANT 'Dean' TO 'A'@'localhost';
FLUSH PRIVILEGES;

show grants for 'Dean'@'%';
show grants for 'A'@'localhost';
show grants for 'A'@'localhost' USING 'Dean';

SELECT CURRENT_ROLE();
SET DEFAULT ROLE ALL TO 'A'@'localhost', 'B'@'localhost', 'C'@'localhost';