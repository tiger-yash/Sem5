SELECT CURRENT_ROLE();

GRANT INSERT ON lab6.* TO 'C'@'localhost';

GRANT SELECT ON TABLE student TO 'B'@'localhost';

USE lab6;

create table student(
	Reg_No int auto_increment not null,
	full_name varchar(40),
	primary key(Reg_No)
);


REVOKE INSERT ON lab6.* FROM 'C'@'localhost';

REVOKE SELECT ON TABLE student FROM 'B'@'localhost';