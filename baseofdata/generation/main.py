from math import remainder
from faker import Faker
from random import choice
from datetime import datetime


MAX_COUNT = 1000
sex =  ['ж', 'м']
DEBTOR = [i+1 for i in range(MAX_COUNT)]

type_visit = [ 'звонок', 'sms', 'встреча' ]
succ = [0, 1]
type_country = ['Россия','Украина','Белорусь']

id_debt = []
id_debtor = []

def generationDebtor():
    fake_ru = Faker('ru_Ru')

    f = open('debtor.csv', 'w', encoding='utf-8')

    for i in range(MAX_COUNT):
        sex_p = choice(sex)
        if sex_p == 'м':
            surname = fake_ru.last_name_male()
            name = fake_ru.first_name_male()
            middle_name = fake_ru.middle_name_male()
        else:
            surname = fake_ru.last_name_female()
            name = fake_ru.first_name_female()
            middle_name = fake_ru.middle_name_female()

        date_of_brth = fake_ru.date_of_birth(None, 21, 80)
        #address = fake_ru.address()
        phone = fake_ru.phone_number()
        email = fake_ru.email()
        line = "{0}|{1}|{2}|{3}|{4}|{5}|{6}\n".format(
            surname,
            name,
            middle_name,
            date_of_brth,
            sex_p,
            phone,
            email
        )

        f.write(line)
    f.close()     

def generationCollector():
    fake_ru = Faker('ru_Ru')

    f = open('collector.csv', 'w', encoding='utf-8')

    for i in range(MAX_COUNT):
        sex_p = choice(sex)
        if sex_p == 'м':
            surname = fake_ru.last_name_male()
            name = fake_ru.first_name_male()
            middle_name = fake_ru.middle_name_male()
        else:
            surname = fake_ru.last_name_female()
            name = fake_ru.first_name_female()
            middle_name = fake_ru.middle_name_female()

        date_of_brth = fake_ru.date_of_birth(None, 21, 80)
        phone = fake_ru.phone_number()
        email = fake_ru.email()
        experience = choice(range(1, 10))
        stars = choice(range(1, 50))/10
        line = "{0}|{1}|{2}|{3}|{4}|{5}|{6}|{7}\n".format(
            
            surname,
            name,
            middle_name,
            date_of_brth,
            phone,
            email,
            experience,
            stars
        )

        f.write(line)
    f.close()     

def generationDebt():
    fake_ru = Faker('ru_Ru')

    f = open('debt.csv', 'w', encoding='utf-8')
    for i in range(MAX_COUNT):
        fullsumma = choice(range(100000,10000000,50000))
        
        dataCreate = fake_ru.date_between_dates(date_start = datetime(2018,1,1), date_end = datetime(2020,1,1))
        procent = choice(range(1, 20, 5)) / 100
        remainder = choice(range(10000,fullsumma,10000))
        id_debtor = choice(range(1,1000))
        id_collector = choice(range(1, 1000))
        line = "{0}|{1}|{2}|{3}|{4}|{5}\n".format(
            fullsumma,
            dataCreate,
            procent,
            remainder,
            id_debtor,
            id_collector
        )
        f.write(line)


    f.close() 

def generationVisit():
    fake_ru = Faker('ru_Ru')

    f = open('visit.csv', 'w', encoding='utf-8')

    for i in range(MAX_COUNT):

        typeVisit = choice(type_visit)
        dataVisit = fake_ru.date_between_dates(date_start = datetime(2020,1,1))
        success = choice(succ)
        id_debt = choice(range(1, 1000))

        line = "{0}|{1}|{2}|{3}\n".format(
            typeVisit,
            dataVisit,
            success,
            id_debt
        )
        f.write(line)

    f.close() 

def generationAdress():
    fake_ru = Faker('ru_Ru')

    f = open('adress.csv', 'w', encoding='utf-8')

    for i in range(MAX_COUNT):
        
        for j in range(choice(range(1, 4))):
            country = choice(type_country)
            city = fake_ru.city()
            street = fake_ru.street_name()
            house = choice(range(1,20))
            flat = choice(range(1,200))
            id_debtor = i + 1

            line = "{0}|{1}|{2}|{3}|{4}|{5}\n".format(
                country,
                city,
                street,
                house,
                flat,
                id_debtor
            )
            f.write(line)

    f.close()    

def generationPayment():
    fake_ru = Faker('ru_Ru')

    f = open('payment.csv', 'w', encoding='utf-8')

    for i in range(MAX_COUNT):

        for j in range(choice(range(0, 5))):
            summa = choice(range(5000, 100000, 10000))
            date = fake_ru.date_between_dates(date_start = datetime(2020,1,1))
            id_debt = i + 1

            line = "{0}|{1}|{2}\n".format(
                summa,
                date, 
                id_debt
            )
            f.write(line)

    f.close() 

if __name__ == "__main__":
    #generationDebtor()
    #generationCollector()
    generationDebt()
    #generationVisit()
    #generationAdress()
    #generationPayment()