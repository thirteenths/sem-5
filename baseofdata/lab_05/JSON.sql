--Из таблиц базы данных, созданной в первой лабораторной работе, извлечь
--данные в XML (MSSQL) или JSON(Oracle, Postgres). Для выгрузки в XML
--проверить все режимы конструкции FOR XML


SELECT row_to_json(a) result FROM adress a;
SELECT row_to_json(c) result FROM collector c;
SELECT row_to_json(d) result FROM debt d;
SELECT row_to_json(d) result FROM debtor d;
SELECT row_to_json(p) result FROM payment p;
SELECT row_to_json(v) result FROM visit v;

--Выполнить загрузку и сохранение XML или JSON файла в таблицу.
--Созданная таблица после всех манипуляций должна соответствовать таблице
--базы данных, созданной в первой лабораторной работе.

CREATE TABLE IF NOT EXISTS  Collector_copy
(
  id          SERIAL PRIMARY KEY ,
  surname     varchar(20)      NOT NULL,
  name        varchar(20)      NOT NULL ,
  middlename  varchar(20)      NOT NULL,
  bithday     date             NOT NULL,
  mobilephone varchar(20)      NOT NULL,
  email       varchar(40)      NOT NULL,
  experience  int              NOT NULL,
  stars       double precision NOT NULL DEFAULT 0
);


COPY
(   SELECT row_to_json(c) result
    FROM collector c)
TO '/baseofdata/lab_05/collector.json' ;


CREATE TABLE IF NOT EXISTS collector_import(doc json);

COPY collector_import FROM '/baseofdata/lab_05/collector.json' ;

SELECT * FROM collector_import, json_populate_record(null::collector_copy, doc);

SELECT * FROM collector_import, json_populate_record(CAST(null AS collector_copy), doc);

INSERT INTO Collector_copy
SELECT id, surname, name, middlename, bithday, mobilephone, email, experience, stars
FROM collector_import, json_populate_record(null::collector_copy, doc);


--Создать таблицу, в которой будет атрибут(-ы) с типом XML или JSON, или
--добавить атрибут с типом XML или JSON к уже существующей таблице.
--Заполнить атрибут правдоподобными данными с помощью команд INSERT
--или UPDATE.


CREATE TABLE IF NOT EXISTS debt_is_gone
(
    data json
);

INSERT INTO debt_is_gone
SELECT * FROM json_object('{debtor_id, debt_id, collector_id}', '{1, 1, 1}');


--Выполнить следующие действия:
--1. Извлечь XML/JSON фрагмент из XML/JSON документа

CREATE TABLE IF NOT EXISTS collector_id_surname(
    id INT,
    surname varchar
);

SELECT * FROM collector_import, json_populate_record(null::collector_id_surname, doc);



--2. Извлечь значения конкретных узлов или атрибутов XML/JSON документа

DROP TABLE inventory CASCADE ;
CREATE TABLE inventory(doc jsonb);


INSERT INTO inventory VALUES ('{"id":0, "weapon": {"firearms":"pistol", "hand_weapon":"knife"}}');
INSERT INTO inventory VALUES ('{"id":1, "weapon": {"firearms":"machine gun", "hand_weapon":"none"}}');

SELECT * FROM inventory;


SELECT doc->'id' AS id, doc->'weapon'->'firearms' AS firearms
FROM inventory;


--3. Выполнить проверку существования узла или атрибута




CREATE OR REPLACE FUNCTION get_inventory(u_id jsonb)
RETURNS VARCHAR AS '
    SELECT CASE
               WHEN count.cnt > 0
                   THEN ''true''
               ELSE ''false''
               END AS comment
    FROM (
             SELECT COUNT(doc -> ''id'') cnt
             FROM inventory
             WHERE doc -> ''id'' @> u_id
         ) AS count;
' LANGUAGE sql;

SELECT * FROM inventory;

SELECT get_inventory('1');

--4. Изменить XML/JSON документ


INSERT INTO inventory VALUES ('{"id":3, "weapon": {"firearms":"machine gun", "hand_weapon":"none"}}');

SELECT * FROM inventory;

UPDATE inventory
SET doc = doc || '{"id": 33}'::jsonb
WHERE (doc->'id')::INT = 3;



SELECT * FROM inventory;


--5. Разделить XML/JSON документ на несколько строк по узлам


CREATE TABLE IF NOT EXISTS passed_debt(doc JSON);

INSERT INTO passed_debt VALUES ('[{"debtor_id": 0, "debt_id": 1},
  {"debtor_id": 2, "debt_id": 2}, {"debtor_id": 3, "debt_id": 1}]');

SELECT * FROM passed_debt;

-- jsonb_array_elements - Разворачивает массив JSON в набор значений JSON.
SELECT jsonb_array_elements(doc::jsonb)
FROM passed_debt;