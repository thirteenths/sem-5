--Разработать и тестировать 10 модулей

--• Четыре функции--------------------------------------------
--• Скалярную функцию
--• Подставляемую табличную функцию
--• Многооператорную табличную функцию
--• Рекурсивную функцию или функцию с рекурсивным ОТВ

--• Четыре хранимых процедуры---------------------------------
--• Хранимую процедуру без параметров или с параметрами
--• Рекурсивную хранимую процедуру или хранимую процедур с рекурсивным ОТВ
--• Хранимую процедуру с курсором
--• Хранимую процедуру доступа к метаданным

--• Два DML триггера------------------------------------------
--• Триггер AFTER
--• Триггер INSTEAD OF

--Скалярная функция
--
DROP FUNCTION IF EXISTS AvgDebtor();
CREATE FUNCTION AvgDebtor()
RETURNS NUMERIC
AS $$
BEGIN
    RETURN
    (
        SELECT sum(summa)
        FROM payment
        WHERE id_debt = 11
        );
END;
$$
LANGUAGE plpgsql;

SELECT AvgDebtor();



--Подставляемая табличная функция
--Вывести
DROP FUNCTION get_info_debt(d_id INT);
CREATE OR REPLACE FUNCTION get_info_debt(d_id INT = 0)
RETURNS SETOF debt
AS $$
    BEGIN
    RETURN QUERY (
        SELECT *
        FROM debt
        WHERE id = d_id
    );
    END;
$$
LANGUAGE plpgsql;

SELECT *
FROM get_info_debt(100);

--• Многооператорную табличную функцию
DROP FUNCTION country_debtor(cont VARCHAR);
CREATE OR REPLACE FUNCTION country_debtor(cont VARCHAR)
RETURNS TABLE
(
    out_id          int ,
  out_surname     varchar(20) ,
  out_name        varchar(20) ,
  out_middlename  varchar(20) ,
  out_bithday     date        ,
  out_sex         char        ,
  out_mobilephone varchar(20) ,
  out_email       varchar(40) ,
  out_country     varchar(40)
)
AS $$
BEGIN
    RETURN QUERY
    SELECT debtor.id, surname, name, middlename, bithday, sex, mobilephone, email, country
    FROM debtor join adress a on debtor.id = a.id_debtor
    WHERE country = cont;
END;
$$
LANGUAGE plpgsql;

SELECT *
FROM country_debtor('Россия');


--• Рекурсивную функцию или функцию с рекурсивным ОТВ


CREATE OR REPLACE FUNCTION date_create(d_id int)
RETURNS TABLE()
    AS $$
    BEGIN
WITH RECURSIVE REC(id, surname, datacreate) AS
    (
        SELECT d.id, surname, datecreate
        FROM debt join debtor d on d.id = debt.id_debtor
        WHERE id_debtor = 10

        UNION

        SELECT d2.id, d2.surname ,debt.datecreate
        FROM debt join debtor d2 on d2.id = debt.id_debtor join REC ON REC.id = debt.id_debtor
    )
END ;
    $$
LANGUAGE plpgsql;

--Увеличить опыт всем коллекторам которые имеют более N должников на delta

CREATE OR REPLACE PROCEDURE get_me
(
    count_debtor INT,
    delta_ex INT DEFAULT 1
)
AS '
BEGIN
    FOR elem IN
        SELECT *
        FROM collector join debt d on collector.id = d.id_collector join debtor d2 on d2.id = d.id_debtor
        WHERE
END;
'LANGUAGE plpgsql;

--Хранимую процедуру без параметров или с параметрами
--Добавить платеж
DROP PROCEDURE insert_payment(summ DOUBLE PRECISION, datepay date, d_id INT);
CREATE OR REPLACE PROCEDURE insert_payment(summ DOUBLE PRECISION, datepay date, d_id INT)
LANGUAGE sql
AS $$
    INSERT INTO payment(summa, date, id_debt) VALUES (summ, datepay, d_id);
    $$;

CALL insert_payment(10000, '2021.12.01', 15);


--• Хранимую процедуру с курсором

--Хранимую процедуру доступа к метаданным

CREATE OR REPLACE PROCEDURE ShowSize(nameTable VARCHAR)
AS $$
    DECLARE myCursor CURSOR
        FOR
        SELECT column_name, size
            FROM
                 (
                     SELECT column_name, pg_column_size(cast(column_name as varchar)) as size
                     FROM information_schema.columns
                     WHERE table_name = nameTable
                     ) AS sizeInfo;
        param RECORD;
BEGIN
        OPEN myCursor;
        LOOP
            FETCH myCursor INTO param;
            EXIT WHEN NOT FOUND;

            RAISE INFO 'column: %   size: %', param.column_name, param.size;
        end LOOP ;
        CLOSE myCursor;
END
$$
LANGUAGE plpgsql;

CALL ShowSize('debt');



-- Триггер AFTER
--
DROP TRIGGER myTrigger;
CREATE OR REPLACE FUNCTION trigger_update()
RETURNS TRIGGER
AS $$
BEGIN
    RAISE INFO 'Запись в таблице payment изменена.';
    RETURN NULL;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER myTrigger
    AFTER UPDATE ON payment
    FOR EACH STATEMENT
    EXECUTE PROCEDURE trigger_update();


UPDATE payment
SET date = '2021.12.02'
WHERE id = 154;


--Триггер INSTEAD OF

CREATE OR REPLACE FUNCTION name()
RETURNS TRIGGER
AS'
BEGIN

END;'
LANGUAGE plpgsql;


CREATE TRIGGER