
from faker import Faker
from random import randint, choice
import datetime
import time
import json

class Collector():
    id = int()
    surname = str()
    name = str()
    middlename = str()
    bithday = str()
    mobilephone = str()
    email = str()
    experience = int()
    star = float()

    def __init__(self, id, surname, name, middlename, bithday, mobilephone, email, experience, star):
        self.id = id
        self.surname = surname
        self.name = name

class Payment():
    id = int()
    summa = float()
    data = str()
    id_debt = int()

    def __init__(self, id, summa, data, id_debt):
        self.id = id
        self.summa = summa
        self.data = data
        self.id_debt = id_debt

    def get(self):
        return {'id':self.id, 'summa':self.summa, 'data':self.data, 'id_debt':self.id_debt}      

def main():
    facker = Faker()
    i = 0

    while True:
        obj = Payment(i, )


if __name__ == "__main__":
	main()