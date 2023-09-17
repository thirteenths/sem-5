DROP TABLE workers CASCADE;
DROP TABLE in_out CASCADE;

CREATE TABLE IF NOT EXISTS workers (
	id_worker	SERIAL PRIMARY KEY,
	fnp			TEXT,
	brth		DATE,
	department	TEXT
);

CREATE TABLE IF NOT EXISTS in_out (
	id_worker	INTEGER REFERENCES workers,
	cur_date	DATE,
	cur_day		TEXT,
	cur_time	TIME,
	cur_type	INTEGER
);



INSERT INTO workers(fnp, brth, department) VALUES('Иванов Иван Иванович', '1990-09-25', 'ИТ');
INSERT INTO workers(fnp, brth, department) VALUES('Петров Петр Петрович', '1987-11-12', 'Бухгалтерия');

INSERT INTO in_out(id_worker, cur_date, cur_day, cur_time, cur_type) VALUES(1, '2018-12-14', 'Суббота', '9:00', 1);
INSERT INTO in_out(id_worker, cur_date, cur_day, cur_time, cur_type) VALUES(1, '2018-12-14', 'Суббота', '9:20', 2);
INSERT INTO in_out(id_worker, cur_date, cur_day, cur_time, cur_type) VALUES(1, '2018-12-14', 'Суббота', '9:25', 1);
INSERT INTO in_out(id_worker, cur_date, cur_day, cur_time, cur_type) VALUES(1, '2018-12-14', 'Суббота', '9:45', 2);
INSERT INTO in_out(id_worker, cur_date, cur_day, cur_time, cur_type) VALUES(2, '2018-12-14', 'Суббота', '9:05', 1);
INSERT INTO in_out(id_worker, cur_date, cur_day, cur_time, cur_type) VALUES(2, '2018-12-14', 'Суббота', '19:05', 2);


---------------------------------------------------------------------------------------------------------------------
--Написать скалярную функцию, возвращающую минимальный возраст сотрудника,
--опоздавшего более чем на 10 минут

-- Минимальный возраст == максимальная дата рождения.
CREATE OR REPLACE FUNCTION get_latecomer()
RETURNS INT
AS
$$
    SELECT date_part('year',age(MAX(workers.brth)))
    FROM workers JOIN in_out io on workers.id_worker = io.id_worker
    WHERE io.cur_type = 1 AND io.cur_time > '09:10:00'
$$LANGUAGE SQL;

SELECT * FROM get_latecomer();

--Найти самого старшего сотрудника в бухгалтерии

SELECT id_worker, fnp, brth
FROM workers
WHERE department = 'Бухгалтерия' AND brth =
                                     (
                                         SELECT MIN(brth)
                                            FROM workers
                                            WHERE department = 'Бухгалтерия'
                                         );


--Найти сотрудников, выходивших больше 3-х раз с рабочего места
SELECT DISTINCT id_worker, COUNT(*)
FROM in_out
WHERE cur_type = 2
GROUP BY id_worker, cur_type
HAVING COUNT(*) > 4;


--Найти сотрудника, который пришел сегодня последним
SELECT workers.id_worker
FROM workers join in_out io on workers.id_worker = io.id_worker
WHERE io.cur_date = now() AND io.cur_type = 1 AND io.cur_time IN
(
    SELECT MAX(cur_time)
    FROM in_out
    WHERE io.cur_type = 1
    );

SELECT * FROM workers;
SELECT * FROM in_out;


create extension plpython3u;






------------------------------------------3---------------------------------------------------
----------------------------------------------------------------------------------------------









