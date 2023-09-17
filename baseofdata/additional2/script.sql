DROP TABLE EmplVisits CASCADE ;

CREATE TABLE IF NOT EXISTS EmplVisits
(
    Department varchar(16),
    FIO varchar(30),
    Date date,
    Status varchar(30)
);

COPY EmplVisits (department, fio, date, status) FROM '/baseofdata/additional2/data.csv' DELIMITER ',';

--Вывести интервалы непрерывного нахождения сотрудника в определенном статусе.

SELECT Status
FROM EmplVisits
GROUP BY Status;