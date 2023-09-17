COPY collector (surname,name, middlename, bithday, mobilephone, email, experience, stars)
FROM '/baseofdata/generation/collector.csv' DELIMITER '|'

COPY debtor (surname, name, middlename, bithday, sex, mobilephone, email)
FROM '/baseofdata/generation/debtor.csv' DELIMITER '|'

COPY visit (type, datevisit, success, id_debt)
FROM '/baseofdata/generation/visit.csv' DELIMITER '|'

COPY debt (fullsumma, datecreate, procent, remainder, id_debtor, id_collector)
FROM '/baseofdata/generation/debt.csv' DELIMITER '|'

COPY adress (country, city, street, house, flat, id_debtor)
FROM '/baseofdata/generation/adress.csv' DELIMITER  '|'

COPY payment (summa, date, id_debt)
FROM '/baseofdata/generation/payment.csv' DELIMITER '|'