--Создать, развернуть и протестировать 6 объектов SQL CLR:
--• Определяемую пользователем скалярную функцию CLR,
--• Пользовательскую агрегатную функцию CLR,
--• Определяемую пользователем табличную функцию CLR,
--• Хранимую процедуру CLR,
--• Триггер CLR,
--• Определяемый пользователем тип данных CLR.


select * from pg_language;

create extension plpython3u;

--Определяемую пользователем скалярную функцию CLR

--Получить должника по id
CREATE OR REPLACE FUNCTION get_debtor_name(debtor_id INT)
RETURNS varchar
AS $$
    res = plpy.execute(f"SELECT * FROM debtor WHERE id = {debtor_id};" )
    if res:
        return res[0]['surname']

$$LANGUAGE plpython3u;

SELECT get_debtor_name(10);


--• Пользовательскую агрегатную функцию CLR,
--Получить кол-во долгов по id должника
CREATE OR REPLACE FUNCTION count_debt(debtor_id INT)
RETURNS INT
AS $$
    count = 0
    #res = plpy.execute("SELECT * FROM debt")

    for elem in plpy.execute("SELECT * FROM debt"):
        if int(elem["id_debtor"]) == debtor_id:
            count += 1

    return count
$$LANGUAGE plpython3u;

SELECT count_debt(13);


--• Определяемую пользователем табличную функцию CLR
-- Вывести всех должников из определенного города
DROP TYPE result_search_debtor CASCADE ;
CREATE TYPE result_search_debtor AS
(
    out_id          int ,
    surname     varchar(20) ,
    name        varchar(20) ,
    middlename  varchar(20) ,
    bithday     date        ,
    sex         char        ,
    mobilephone varchar(20) ,
    email       varchar(40) ,
    country     varchar(40),
    city        varchar(40)
);

DROP  FUNCTION  Show_debtor_in_the_city(in_city varchar(40));
CREATE OR REPLACE FUNCTION Show_debtor_in_the_city(in_city varchar(40))
RETURNS TABLE
(
    out_id          int ,
    surname     varchar(20) ,
    name        varchar(20) ,
    middlename  varchar(20) ,
    bithday     date        ,
    sex         char        ,
    mobilephone varchar(20) ,
    email       varchar(40) ,
    country     varchar(40),
    city        varchar(40)
)
AS $$
    temp_res = []

    for elem in plpy.execute("SELECT DISTINCT  debtor.id as out_id, surname, name, middlename, bithday, sex, mobilephone, email, country, city \
    FROM debtor join adress a on debtor.id = a.id_debtor"):
        if elem["city"] == in_city:
            #print(elem)
            temp_res.append(elem)

    return temp_res

    $$ LANGUAGE plpython3u;

SELECT * FROM Show_debtor_in_the_city('п. Пятигорск');


SELECT DISTINCT  debtor.id as out_id, surname, name, middlename, bithday, sex, mobilephone, email, country, city
    FROM debtor join adress a on debtor.id = a.id_debtor
WHERE city = 'п. Пятигорск' ;


--• Хранимую процедуру CLR,
--Добавим нового коллектора
CREATE OR REPLACE PROCEDURE add_collector
    (
 id          int,
  surname     varchar(20)     ,
  name        varchar(20)     ,
ision
    ) AS $$  middlename  varchar(20)     ,
  bithday     date            ,
  mobilephone varchar(20)     ,
  email       varchar(40)     ,
  experience  int             ,
  stars       double prec

    plan = plpy.prepare("INSERT INTO collector VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9)", ["INT", "VARCHAR","VARCHAR", "VARCHAR",  "DATE", "VARCHAR", "VARCHAR", "INT", "double precision"])
    rv = plpy.execute(plan, [id, surname, name, middlename, bithday, mobilephone, email, experience, stars])


    $$LANGUAGE plpython3u;

CALL add_collector('1001', 'Петров', 'Петр', 'Петрович', '1990-01-01', '+7 985 467 33 22', 'ppp@example.com', 0, 0.0);

--• Триггер CLR,

CREATE VIEW debt_new AS
    SELECT *
FROM debt
WHERE id < 100;

CREATE OR REPLACE FUNCTION del_debt()
RETURNS TRIGGER
AS $$
    old_id = TD["old"]["id"]
    rv = plpy.execute(f"\
    UPDATE debt_new \
    SET remainder = 0 \
    WHERE debt_new.id = {old_id}")

    return TD["new"]
$$
LANGUAGE plpython3u;

DROP TRIGGER del_debt_trigger ON debt_new CASCADE ;
CREATE TRIGGER del_debt_trigger
    INSTEAD OF DELETE ON debt_new
    FOR EACH ROW
    EXECUTE PROCEDURE del_debt();

DELETE FROM debt_new
WHERE id = 20;


--• Определяемый пользователем тип данных CLR.
DROP TYPE count_debt_collect;
CREATE TYPE count_debt_collect AS
(
    id INT,
    surname VARCHAR(40),
    name VARCHAR(40),
    middlename VARCHAR(40),
    count_debt INT
);

DROP FUNCTION get_count_debt_collect();
CREATE OR REPLACE FUNCTION get_count_debt_collect()
RETURNS SETOF count_debt_collect
AS
    $$
    rv = plpy.execute("SELECT collector.id  as id, surname, name, middlename, count(*) as count_debt\
                        FROM collector join debt d on collector.id = d.id_collector \
                        GROUP BY collector.id, surname, name, middlename ")

    for i in range(rv.nrows()):
        return rv
$$ LANGUAGE plpython3u;

SELECT * FROM get_count_debt_collect();

SELECT collector.id, surname, name, middlename, count(*)
FROM collector join debt d on collector.id = d.id_collector
GROUP BY collector.id, surname, name, middlename;

SELECT *
FROM collector join debt d on collector.id = d.id_collector
WHERE id_collector = 652;

---------------------------------------------------------------------

DROP FUNCTION trigger_add_debt_py() CASCADE;
CREATE OR REPLACE FUNCTION trigger_add_debt_py()
RETURNS TRIGGER
AS $$
BEGIN
    RAISE INFO 'Коллектор вышел по вашу душу';

    INSERT INTO visit(type, datevisit, success, id_debt) VALUES ('звонок', now(), false, (SELECT MAX(id)  FROM debt));
    RETURN NULL;
END;
$$
LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION trigger_add_debt_py()
RETURNS TRIGGER
AS $$

    rv = plpy.execute(f"\
     INSERT INTO visit(type, datevisit, success, id_debt)\
    VALUES ('звонок', now(), false, (SELECT MAX(id)  FROM debt)) \
    ")


$$
LANGUAGE plpython3u;

CREATE TRIGGER add_debt_py
    AFTER INSERT ON debt
    FOR EACH STATEMENT
    EXECUTE PROCEDURE trigger_add_debt_py();


INSERT INTO debt(fullsumma, datecreate, procent, remainder, id_debtor, id_collector) VALUES (10000, now(), 0.1, 10000, 2, 8);

SELECT *
FROM visit
WHERE id = (SELECT MAX(id) FROM visit);