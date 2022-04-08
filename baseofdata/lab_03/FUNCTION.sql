--Скалярная функция
--

CREATE OR REPLACE FUNCTION summPay(debt_id INT)
RETURNS NUMERIC
AS $$
BEGIN
    RETURN
    (
        SELECT sum(summa)
        FROM payment
        WHERE id_debt = debt_id
        );
END;
$$
LANGUAGE plpgsql;

SELECT summPay(9);


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


-- Фибоначи. Аргументы:
-- Два числа последовательности
-- И предел (до какого числа нужно идти).
-- RETURN QUERY добавляет результат выполнения запроса к результату функции.
CREATE OR REPLACE FUNCTION fib(first INT, second INT,max INT)
RETURNS TABLE (fibonacci INT)
AS '
BEGIN
    RETURN QUERY
    SELECT first;
    IF second <= max THEN
        RETURN QUERY
        SELECT *
        FROM fib(second, first + second, max);
    END IF;
END' LANGUAGE plpgsql;

SELECT *
FROM fib(1,1, 13);