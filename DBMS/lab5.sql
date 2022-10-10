CREATE DATABASE LAB5;

USE LAB5;
create table student(
	Reg_No int auto_increment not null,
	full_name varchar(40),
	Marks1 int,
	Marks2 int,
	Marks3 int,
	Marks4 int,
	Marks5 int,
	primary key(Reg_No)
);

create table employee(
	Emp_id int auto_increment not null,
	full_name varchar(40),
	salary int,
	primary key(Emp_id)
);

create table restricted(
	num int not null
);

INSERT INTO student VALUES (1,'Yash Raj',97,95,92,87,99), (2,'Alok',91,75,97,89,100),(3,'Abhinav',87,95,98,77,89);
INSERT INTO employee VALUES (1,'Yash Raj',125000), (2,'Mayank',110000),(3,'Aditya',200000);

DROP PROCEDURE IF EXISTS tot_marks;
DELIMITER //
create procedure tot_marks(
    reg int
)
begin 
    select Reg_No, full_name, Marks1 + Marks2 + Marks3 + Marks4 + Marks5 as total_marks 
    from student
    where Reg_No=reg; 
end//
DELIMITER ;


call tot_marks(1);

DROP PROCEDURE IF EXISTS update_salary;
DELIMITER //
create procedure update_salary(
    ID int,
    current_salary int,
    percent_raise int,
    OUT cnt int
)
begin 
    update employee
    set
    	salary = current_salary + current_salary*(percent_raise/100)
    where
    	Emp_ID = ID;
	SELECT COUNT(*) into cnt FROM employee;
end//
DELIMITER ;

UPDATE employee SET salary = 100000 WHERE Emp_ID=1;
call update_salary(1,100000,25);

DELIMITER //
drop trigger if exists test_trigger_insert //
create trigger test_trigger_insert before insert on restricted
for each row
begin
    declare msg varchar(128);
    set msg = 'Error: Trying to insert value in Restricted Table';
    signal sqlstate '45000' set message_text = msg;
end//

drop trigger if exists test_trigger_delete //
create trigger trg_trigger_test_ins before delete on restricted
for each row
begin
    declare msg varchar(128);
    set msg = 'Error: Trying to delete a value in Restricted Table';
    signal sqlstate '45000' set message_text = msg;
end//

DELIMITER ;



INSERT INTO restricted VALUES (6);
DELETE FROM restricted WHERE num=5;

select * from employee;
select * from student;
select * from restricted;