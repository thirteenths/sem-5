--• Четыре хранимых процедуры---------------------------------
--• Хранимую процедуру без параметров или с параметрами
--• Рекурсивную хранимую процедуру или хранимую процедур с рекурсивным ОТВ
--• Хранимую процедуру с курсором
--• Хранимую процедуру доступа к метаданным


--• Хранимую процедуру без параметров или с параметрами
--Добавить платеж
DROP PROCEDURE insert_payment(summ DOUBLE PRECISION, datepay date, d_id INT);
CREATE OR REPLACE PROCEDURE insert_payment(summ DOUBLE PRECISION, datepay date, d_id INT)
LANGUAGE sql
AS $$
    INSERT INTO payment(summa, date, id_debt) VALUES (summ, datepay, d_id);
    $$;

CALL insert_payment(10000, '2021.12.01', 15);


--• Рекурсивную хранимую процедуру или хранимую процедур с рекурсивным ОТВ


CREATE OR REPLACE PROCEDURE fib_proc
(
    res INOUT INT,
    max INT,
    first INT DEFAULT 1,
    second INT DEFAULT  1
)
AS '
DECLARE
    tmp INT;
BEGIN
    tmp = first + second;
    IF tmp <= max THEN
        res = tmp;
        CALL fib_proc(res, max, second, tmp);
    END IF;
END;
'LANGUAGE  plpgsql;

CALL fib_proc(0, 100);

--• Хранимую процедуру с курсором
--Все долгт одного коллектора передать другому(id коллекторв переданы в качестве параметров)

SELECT d.id, fullsumma, datecreate, procent, remainder, id_debtor, id_collector
FROM collector join debt d on collector.id = d.id_collector
WHERE d.id_collector = 5;

SELECT *
INTO tmp_cursor
FROM debt;

DROP TABLE tmp_cursor;

CREATE OR REPLACE PROCEDURE proc_update_cursor
(
    old_collector_id INT,
    new_collector_id INT
)
AS '
DECLARE
    upCursor CURSOR FOR
        SELECT d.id, fullsumma, datecreate, procent, remainder, id_debtor, id_collector
        FROM collector join debt d on collector.id = d.id_collector
        WHERE d.id_collector = old_collector_id;
    tmp tmp_cursor;
BEGIN
    OPEN upCursor;

    LOOP
        FETCH upCursor
        INTO tmp;

        EXIT WHEN NOT FOUND;

        UPDATE tmp_cursor
        SET id_collector = new_collector_id
        WHERE tmp_cursor.id = tmp.id;
        RAISE NOTICE ''Elem =  %'', tmp;

    END LOOP;

    CLOSE upCursor;

END;
' LANGUAGE plpgsql;

CALL proc_update_cursor(5, 1);


--• Хранимую процедуру доступа к метаданным
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


SELECT * FROM pg_stat_activity;