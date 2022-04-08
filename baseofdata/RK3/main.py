
from peewee import *
from datetime import *
from request import *

# Создаем соединение с базой данных
con = PostgresqlDatabase(
    database='postgres',
    user='verendaya',
    password='password',
    host='127.0.0.1',
    port="5432"
)

class BaseModel(Model):
    class Meta:
        database = con


class Worker(BaseModel):
    id_worker = IntegerField(column_name='id_worker')
    fnp = CharField(column_name='fnp')
    brht = DateField(column_name='brht')
    department = CharField(column_name='department')

    class Meta:
        table_name = 'workers'

class in_out(BaseModel):
    #id_worker = IntegerField(column_name='id_worker')
    id_worker  = ForeignKeyField(Worker, backref='id_worker ')
    cur_date	 = DateField(column_name='cur_date')
    cur_day	 =  CharField(column_name='cur_day')
    cur_time = TimeField(column_name='cur_time')
    cur_type = IntegerField(column_name='cur_type')

    class Meta:
        table_name = 'in_out'

def Task1():
    global con

    cur = con.cursor()

    cur.execute(FirstQ)
    print("Запрос 1:\n")
    rows = cur.fetchall()
    for row in rows:
        print(*row)

    cur.execute(SecondQ)
    print("\nЗапрос 2:\n")
    rows = cur.fetchall()
    for row in rows:
        print(*row)

    cur.execute(ThirdQ)
    print("\nЗапрос 3:\n")
    rows = cur.fetchall()
    for row in rows:
        print(*row)

    cur.close()

def Task2():
    global con

    cur = con.cursor()
	
    print("1. Найти самого старшего сотрудника в бухгалтерии")
    query = Worker.select(Worker.id_worker, Worker.fnp, Worker.brht).where(Worker.department == 'Бухгалтерия' and Worker.select(min(Worker.brht).where(Worker.department == 'Бухгалтерия')))
    for q in query.dicts().execute():
        print(q)

    print("2. Найти сотрудников, выходивших больше 3-х раз с рабочего места")
    query = in_out.select(in_out.id_worker, fn.count(in_out)).where(in_out.cur_type == 2).group_by(in_out.id_worker, in_out.cur_time).having(fn.count(in_out) > 4)


    for q in query.dicts().execute():
        print(q)
        
    print("3. Найти сотрудника, который пришел сегодня последним")

    query = Worker.select(Worker.id_worker).join(in_out).where(in_out.cur_date == fn.now() and in_out.cur_tipy == 1 and in_out.cur_time.in_(in_out.select(max(in_out.cur_time).where(in_out.cur_type == 1))))
    for q in query.dicts().execute():
        print(q)

    cur.close()
	




if __name__ == "__main__":
	Task1()
	Task2()

	con.close()