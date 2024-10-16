CREATE TABLE `foreign_names` (
	`id` INT NOT NULL,
	`name` VARCHAR(25) NOT NULL,
	`meaning` VARCHAR(1000) NOT NULL,
	`gender` VARCHAR(6) NOT NULL,
	`origin` VARCHAR(24) NOT NULL,
	`PeoplesCount` INT NULL,
	`WhenPeoplesCount` DATETIME NULL,
	`Source` NVARCHAR(10) NOT NULL
);

CREATE TABLE `russian_names` (
	`ID` INT NOT NULL,
	`Name` NVARCHAR(100) NOT NULL,
	`Sex` NVARCHAR(1) NULL,
	`PeoplesCount` INT NULL,
	`WhenPeoplesCount` DATETIME NULL,
	`Source` VARCHAR(10) NULL
);

CREATE TABLE `russian_surnames` (
	`ID` INT NOT NULL,
	`Surname` NVARCHAR(100) NOT NULL,
	`Sex` NVARCHAR(1) NULL,
	`PeoplesCount` INT NULL,
	`WhenPeoplesCount` DATETIME NULL,
	`Source` VARCHAR(50) NULL
);

