--• Два DML триггера------------------------------------------
--• Триггер AFTER
--• Триггер INSTEAD OF

--AFTER/BEFORE.
--Триггеры этого класса исполняются после действия,
-- вызвавшего срабатывание триггера.
-- Они считаются классом триггеров по умолчанию.

CREATE OR REPLACE FUNCTION trigger_update_payment()
RETURNS TRIGGER
AS $$
BEGIN
    RAISE INFO 'Запись в таблице payment изменена.';
    RETURN NULL;
END;
$$
LANGUAGE plpgsql;

CREATE TRIGGER up_pay
    AFTER UPDATE ON payment
    FOR EACH STATEMENT
    EXECUTE PROCEDURE trigger_update_payment();

UPDATE payment
SET date = '2021.12.02'
WHERE id = 154;



--INSTEAD  OF.
-- Триггеры этого класса выполняются в обход действий,
-- вызывавших их срабатывание, заменяя эти действия.
-- Например, обновление таблицы, в которой есть триггер INSTEAD OF,
-- вызовет срабатывание этого триггера. В результате вместо оператора
-- обновления выполняется код триггера. Это позволяет размешать в
-- триггере сложные операторы обработки, которые дополняют действия
-- оператора, модифицирующего таблицу.

--Вместотого что бы удалить долг долг -- none

CREATE VIEW debt_new AS
    SELECT *
FROM debt
WHERE id < 100;

CREATE OR REPLACE FUNCTION del_debt()
RETURNS TRIGGER
AS '
BEGIN
    RAISE NOTICE ''kek''   ;

    UPDATE debt_new
    SET remainder = 0
    WHERE debt_new.id = old.id;

    RETURN new;
END;
'LANGUAGE plpgsql;

CREATE TRIGGER del_debt_trigger
    INSTEAD OF DELETE ON debt_new
    FOR EACH ROW
    EXECUTE PROCEDURE del_debt();

DELETE FROM debt_new
WHERE id = 20;



--придобовавление долга уведомление

DROP FUNCTION trigger_add_debt() CASCADE;
CREATE OR REPLACE FUNCTION trigger_add_debt()
RETURNS TRIGGER
AS $$
BEGIN
    RAISE INFO 'Коллектор вышел по вашу душу';

    INSERT INTO visit(type, datevisit, success, id_debt) VALUES ('звонок', now(), false, (SELECT MAX(id)  FROM debt));
    RETURN NULL;
END;
$$
LANGUAGE plpgsql;


DROP TRIGGER add_debt ON debt CASCADE ;
CREATE TRIGGER add_debt
    AFTER INSERT ON debt
    FOR EACH STATEMENT
    EXECUTE PROCEDURE trigger_add_debt();

INSERT INTO debt(fullsumma, datecreate, procent, remainder, id_debtor, id_collector) VALUES (10000, now(), 0.1, 10000, 2, 8);

SELECT *
FROM visit
WHERE id = (SELECT MAX(id) FROM visit);