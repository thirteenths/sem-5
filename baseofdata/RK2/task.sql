

CREATE TABLE IF NOT EXISTS Преподователи
(
    id serial,
    ФИО varchar(50),
    Степень int,
    Должность varchar(20),
    id_Кафедра int references Кафедра(id),
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS Кафедра
(
    id serial,
    Название varchar(15),
    Описание text,
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS Предмет
(
    id serial,
    Название varchar(15),
    Количество_часов int,
    Семестр int,
    Рейтинг double precision,
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS Преподаватель_Предмет
(
    id serial,
    id_Преподаватель int references Преподователи(id),
    id_Предмет int references Предмет(id),
    PRIMARY KEY (id)
);

