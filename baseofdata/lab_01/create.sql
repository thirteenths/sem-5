
CREATE TABLE IF NOT EXISTS  Collector
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


CREATE TABLE IF NOT EXISTS  Debt
(
  id           serial,
  fullSumma    double precision NOT NULL,
  dateCreate   date             NOT NULL,
  procent      double precision NOT NULL,
  remainder    double precision ,
  id_debtor    int  REFERENCES   debtor(id)        ,
  id_collector int  REFERENCES collector(id)        ,
  PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS Debtor
(
  id          serial ,
  surname     varchar(20) NOT NULL,
  name        varchar(20) NOT NULL,
  middlename  varchar(20) NOT NULL,
  bithday     date        NOT NULL,
  sex         char        NOT NULL,
  mobilephone varchar(20) NOT NULL,
  email       varchar(40) NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS  Visit
(
  id           serial,
  type         varchar(10) NOT NULL,
  dateVisit    date        NOT NULL,
  success      bool        NOT NULL,
  id_debt   int         ,
  PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS Adress
(
    id          serial,
    country     varchar(20),
    city        varchar(40),
    street      varchar(40),
    house       int,
    flat        int,
    id_debtor   int,
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS Payment
(
    id          serial,
    summa       double precision,
    date        date,
    id_debt     int,
    PRIMARY KEY (id)
);

ALTER TABLE Debt
  ADD CONSTRAINT FK_Debtor_TO_Debt
    FOREIGN KEY (id_debtor)
    REFERENCES Debtor (id);

ALTER TABLE Debt
  ADD CONSTRAINT FK_Collector_TO_Debt
    FOREIGN KEY (id_collector)
    REFERENCES Collector (id);

ALTER TABLE Visit
  ADD CONSTRAINT FK_Debt_TO_Visit
    FOREIGN KEY (id_debt)
    REFERENCES Debt (id);

ALTER TABLE Adress
  ADD CONSTRAINT FK_Debtor_TO_Adress
    FOREIGN KEY (id_debtor)
    REFERENCES Debtor (id);


ALTER TABLE Payment
  ADD CONSTRAINT FK_Debt_TO_Payment
    FOREIGN KEY (id_debt)
    REFERENCES Debt (id);




