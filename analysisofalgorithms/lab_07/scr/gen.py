from math import remainder
from faker import Faker
from random import choice
from datetime import datetime

sex =  ['ж', 'м']

def generation():
    fake_ru = Faker('ru_Ru')

    f = open('data.txt', 'w', encoding='utf-8')

    for i in range(2000):
        sex_p = choice(sex)
        if sex_p == 'м':
            surname = fake_ru.last_name_male()
            name = fake_ru.first_name_male()
            middle_name = fake_ru.middle_name_male()
        else:
            surname = fake_ru.last_name_female()
            name = fake_ru.first_name_female()
            middle_name = fake_ru.middle_name_female()
        oms = ''    

        for i in range(16):
            oms += str(choice(range(10)))
        #oms = '1234567890123456'    

        line = "{0} {1} {2} {3}\n".format(
            oms,
            surname,
            name,
            middle_name
        )

        f.write(line)
    f.close()  




if __name__ == "__main__":
    generation()