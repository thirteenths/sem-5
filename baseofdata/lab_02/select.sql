
--1--/////////////////////////////////////////////////////////
--Инструкция SELECT, использующая предикат сравнения.
SELECT surname, name, middlename, bithday
FROM debtor
WHERE bithday > '1990.01.01'
ORDER BY bithday;

--2--////////////////////////////////////////////////////////
--Инструкция SELECT, использующая предикат BETWEEN
--Получить список коллекторов с опытом от 4 до 8
SELECT *
FROM collector
WHERE experience BETWEEN 4 AND 8;

--3--/////////////////////////////////////////////////////
--Инструкция SELECT, использующая предикат LIKE
--Получить всех должников живущих на улице
SELECT *
FROM adress join debtor d on d.id = adress.id_debtor
WHERE street  LIKE 'ул.%';

--4--/////////////////////////////////////////////////////////////
--Инструкция SELECT, использующая предикат IN с вложенным подзапросом
--Получить все долги где должники получали только смс
SELECT *
FROM debt
WHERE debt.id IN (SELECT id_debt
                            FROM visit
                            WHERE type = 'sms');


--5--/////////////////////////////////////////////////////////
--нструкция SELECT, использующая предикат EXISTS с вложенным подзапросом
--Вывести всех должников мужчин из России
SELECT surname, name, sex
FROM debtor
WHERE sex = 'м' AND EXISTS (SELECT id
                                FROM adress
                                WHERE country = 'Россия');

--6--////////////////////////////////////////////////////////////
--Инструкция SELECT, использующая предикат сравнения с квантором
--Получить всех должников, дата рождения которых раньше девушки рожденной в 2000
SELECT *
FROM debtor
WHERE bithday > ALL
      (SELECT bithday
          FROM debtor
          WHERE sex = 'ж' AND bithday > '2000.01.01');


--7--/////////////////////////////////////////////////////////
--Инструкция SELECT, использующая агрегатные функции в выражениях столбцов
--Получить колличество коллекторов с 3 звезлами
SELECT count(stars)
FROM collector
WHERE stars = 3;


--8--/////////////////////////////////////////////////
--Инструкция  SELECT, использующая скалярные подзапросы в выражениях столбцов
--Получить ФИО и дату рождения самого старого коллектора////////////////////////
SELECT surname, name, middlename, bithday,
       (SELECT MIN(bithday)
           FROM collector) AS GrandCollector
FROM collector;


--9--/////////////////////////////////////////////////////
--Инструкция SELECT, использующая простое выражение CASE
--Получить информацию о звездах коллекторов
--с доп. столбцом , в котором описаны звезды (лучший/средний/плохой)
SELECT id, surname, name, middlename, stars,
       CASE stars
WHEN
    (SELECT MAX(stars)
        FROM collector)
THEN 'лучший'
WHEN
    (SELECT MIN(stars)
        FROM collector)
THEN 'плохой'
ELSE 'средний'
END AS comment
FROM collector
ORDER BY stars;

--10--////////////////////////////////////////////////////
--Инструкция SELECT, использующая поисковое выражение CASE
--Получить информацию о коллекторах опыт которых
--выше среднего
SELECT id, surname, name, middlename, experience,
       CASE
WHEN experience >
    (SELECT AVG(experience)
        FROM collector)
THEN 'выше'
ELSE 'не выше'
END AS comment
FROM collector;


--11--///////////////////////////////////////////////////////////
--Создание новой временной локальной таблицы из результирующего набора
--данных инструкции SELECT
--создадим таблицу с ФИО должника - сумма долга
SELECT surname, name, middlename, fullsumma
INTO firstLocalTable
FROM debtor join debt d on debtor.id = d.id_debtor and debtor.id = d.id_debtor;
--WHERE id_debtor = d.id;
DROP TABLE firstLocalTable CASCADE ;

--12--/////////////////////////////////////////////////////////////
--нструкция SELECT, использующая вложенные коррелированные
--подзапросы в качестве производных таблиц в предложении FROM
--получить всех должников у которые из России
SELECT surname, name, middlename, country
FROM debtor
JOIN (SELECT *
    FROM adress
    WHERE country = 'Россия')
AS A ON debtor.id= id_debtor;


--13--////////////////////////////////////////////////////////////
--Инструкция SELECT, использующая вложенные подзапросы с уровнем
--вложенности 3
--вывести всех коллекторов
SELECT *
FROM collector
WHERE id IN
      (SELECT id_collector
        FROM debt
        WHERE id IN
              (SELECT id
                FROM debtor
                  WHERE id in
                  (
                      SELECT id
                      FROM adress
                      WHERE country = 'Россия'
                      )));

--14--///////////////////////////////////////////////////
--Инструкция  SELECT, консолидирующая данные с помощью предложения
--GROUP BY, но без предложения HAVING
--Для каждого должника получить максимальный долг и минимальный долг
SELECT surname, MAX(d.fullsumma), MIN(fullsumma)
FROM debtor join debt d on debtor.id = d.id_debtor
GROUP BY surname;

--15--///////////////////////////////////////////////////////
--Инструкция  SELECT, консолидирующая данные с помощью предложения
--GROUP BY и предложения HAVING.
--Получить должников максимальный долг которых меньше 1000000
SELECT surname, MAX(d.fullsumma)
FROM debtor join debt d on debtor.id = d.id_debtor
GROUP BY surname
HAVING MAX(d.fullsumma) < 1000000;

--16--//////////////////////////////////////////////////////////
--Однострочная инструкция  INSERT, выполняющая вставку в таблицу одной
--строки значений
--Добавте платеж
INSERT INTO payment( summa, date, id_debt)
VALUES (10000, '2020.01.23', 27);

--17--//////////////////////////////////////////////////////////
--Многострочная инструкция INSERT, выполняющая вставку в таблицу
--результирующего набора данных вложенного подзапроса.

INSERT INTO visit(type, datevisit, success, id_debt)
SELECT 'встреча',
       (
           SELECT MAX(datevisit)
           FROM visit
           WHERE id_debt = 128
           ), true,
       128
FROM visit
WHERE id_debt = 128
       ;

--18--/////////////////////////////////////////////////////
--Простая инструкция UPDATE.
UPDATE collector
SET stars = 5
WHERE id = 10;

--19--////////////////////////////////////////////////////////
-- Инструкция UPDATE со скалярным подзапросом в предложении SET
--Получить остаток по долгу для каждого долга

SELECT p.id_debt, SUM(summa)
FROM debt join payment p on debt.id = p.id_debt
GROUP BY p.id_debt
    ;

UPDATE debt
SET remainder = (SELECT SUM(summa)
    FROM debt join payment p on debt.id = p.id_debt
    WHERE id_debt = 2)
WHERE id = 2 ;

--20--////////////////////////////////////////////
--Простая инструкция DELETE
DELETE FROM payment WHERE id = 101;

--21--
--нструкция DELETE с вложенным коррелированным подзапросом в
--предложении WHERE.
--Удалить людей без долгов


DELETE FROM visit
WHERE id in  (SELECT id_debt
                    FROM visit
                WHERE success = false AND datevisit = '2020.01.01'
    );

--22--/////////////////////////////////////////////////////////
--нструкция SELECT, использующая простое обобщенное табличное выражение
--Получить всю инфо о должниках которые имеют 1 адресс

SELECT id_debtor, count(id_debtor)
        FROM debtor join adress a on debtor.id = a.id_debtor
        GROUP BY id_debtor;

WITH debtor_adr(debtor, cnt) AS
    (
        SELECT id_debtor, count(id_debtor)
        FROM debtor join adress a on debtor.id = a.id_debtor
        GROUP BY id_debtor
    )
SELECT *
FROM debtor_adr DA join debtor D ON DA.debtor = D.id
WHERE cnt = 1;

--23--////////////////////////////////////////////////
--Инструкция  SELECT, использующая рекурсивное обобщенное табличное
--выражение.
--Вывести все даты создания долга должника id = 10
WITH RECURSIVE REC(id, surname, datacreate) AS
    (
        SELECT d.id, surname, datecreate
        FROM debt join debtor d on d.id = debt.id_debtor
        WHERE id_debtor = 10

        UNION

        SELECT d2.id, d2.surname ,debt.datecreate
        FROM debt join debtor d2 on d2.id = debt.id_debtor join REC ON REC.id = debt.id_debtor
    )
    SELECT *
FROM REC;

--24--//////////////////////////////////////////////////////////////////
--Оконные функции. Использование конструкций MIN/MAX/AVG OVER()
--Для каждого должника вывести min max avg долг
SELECT id_debtor, surname, max(fullsumma) over (PARTITION BY d.id_debtor)
FROM debtor join debt d on debtor.id = d.id_debtor;

--25--//////////////////////////////////////////////////////////////////////
--Оконные фнкции для устранения дублей
WITH max_debt(id_debtor, surname, fullsumma, cnt) AS
         (
             SELECT id_debtor,
                    surname,
                    max(fullsumma) over (PARTITION BY d.id_debtor),
                    row_number() over (partition by d.id_debtor)
             FROM debtor
                      join debt d on debtor.id = d.id_debtor
         )
SELECT id_debtor, surname, fullsumma, cnt
FROM max_debt
WHERE cnt  = 1;


--сколько в России встреч звонков или смс


select *
from (SELECT count(type) as meet
      FROM visit join debt d on d.id = visit.id_debt
      WHERE d.id in (SELECT id
                     FROM adress
                     WHERE country = 'Россия')
      GROUP BY type
      HAVING type = 'встреча') as a,
     (SELECT count(type) as sms
            FROM visit join debt d on d.id = visit.id_debt
        WHERE d.id in (
        SELECT id
        FROM adress
        WHERE country = 'Россия'
    )
        GROUP BY type
        HAVING type = 'sms') as b,
     (
     SELECT count(type) as call
            FROM visit join debt d on d.id = visit.id_debt
        WHERE d.id in (
        SELECT id
        FROM adress
        WHERE country = 'Россия'
    )
        GROUP BY type
        HAVING type = 'звонок'
         ) as c;