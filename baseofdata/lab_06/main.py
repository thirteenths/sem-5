import psycopg2
import getpass


def print_menu():
    print()
    print('-' * 35 + " MENU " + '-' * 35)
    print(" 1 Получить общее количество должников\n"
          "\t--> Выполнить скалярный запрос")

    print(" 2 Вывести фамилии охотников, у которых есть ружья конкретной марки, марку и тип\n"
          "\t--> Выполнить запрос с несколькими соединениями (JOIN)")

    print(" 3 Вывести для каждого должника MAX долг\n"
          "\t--> Выполнить запрос с ОТВ(CTE) и оконными функциями")

    print(" 4 Вывести таблицы базы данных и их размер в байтах\n"
          "\t--> Выполнить запрос к метаданным")

    print(" 5 Получить сумму платяжей должника\n"
          "\t--> Вызвать скалярную функцию")

    print(" 6 Вывести информацию о должниках из определенной страны\n"
          "\t--> Вызвать многооператорную или табличную функцию")

    print(" 7 Вывести размер введенной таблицы\n"
          "\t--> Вызвать хранимую процедуру")
    print(" 8 Вывести название текущей базы данных, порт соединения и время запуска сервера\n"
          "\t--> Вызвать системную функцию или процедуру")

    print(" 9 Создать таблицу lolkek с полями kek, lol\n"
          "\t--> Создать таблицу в базе данных, соответствующую тематике БД")

    print(" 10 Вставить данные в талицу temp_dogs\n"
          "\t--> Выполнить вставку данных в созданную таблицу с использованием инструкции INSERT или COPY")
    print(" 0 Выход\n")

class DataBase:
    connection = None
    cursor = None

    def __init__(self, pwd):
        try:
            self.connection = psycopg2.connect(dbname='mainDB', user = 'verendaya', password= 'password', host='localhost', port= '5433')
            self.cursor = self.connection.cursor()
        except:
            print("ОШИБКА: соединения")
            self.connection = None
            self.cursor = None

    def __del__(self):
        if self.connection != None:
            self.connection.close()
        if self.cursor != None:
            self.cursor.close()

    def is_close(self):
        if self.connection == None or self.cursor == None:
            return True
        return False

    def get_result(self):
        res = self.cursor.fetchall()
        if res is not None:
            for name in self.cursor.description:
                print('{:^20}'.format(name.name), end="|")
            print()

            for row in res:
                for item in row:
                    print('{:<20}'.format(str(item)), end="|")
                print()
        else:
            print("Result is empty!")

    def get_number_debtor(self):
        self.cursor.execute("SELECT COUNT(*) AS number FROM debtor")

    def get_debtor_fullsumma(self):
        self.cursor.execute("SELECT surname, name, middlename, fullsumma "
                            "FROM debtor JOIN debt on debtor.id = debt.id_debtor;"
                            )

    def get_debtor_max_debt(self):
        self.cursor.execute("SELECT id_debtor, surname, max(fullsumma) "
                            " over (PARTITION BY d.id_debtor)"
                            "FROM debtor join debt d on debtor.id = d.id_debtor;")

    def get_tables_with_size(self):
        self.cursor.execute("SELECT table_name, pg_relation_size(cast(table_name as varchar)) as size "
                            "FROM information_schema.tables "
                            "WHERE table_schema not in ('information_schema','pg_catalog')")

    def get_summa_payment(self, id):
        self.cursor.execute("SELECT summPay(%d)" %id)

    def get_debtor_info_in_country(self, kind):
        self.cursor.execute("SELECT * FROM country_debtor('%s')" %kind)

    def get_size_table(self, name):
        self.cursor.execute("CALL ShowSize('%s')" %name)

    def call_systems_call(self):
        self.cursor.execute("SELECT * "
                            "FROM current_database(), inet_server_port(), pg_postmaster_start_time()")

    def create_table(self):
        try:
            self.cursor.execute("CREATE TABLE IF NOT EXISTS lolkek ("
                                "id     SERIAL PRIMARY KEY,"
                                "lol   TEXT NOT NULL,"
                                "kek  TEXT NOT NULL);")
            self.connection.commit()
            print("Таблица успешно создана")
        except:
            print("ОШИБКА: не удалось создать таблицу")

    def insert_data(self, lol, kek):
        try:
            self.cursor.execute("INSERT INTO lolkek(lol, kek) "
                                "VALUES ('%s', '%s');" % (lol, kek))
            self.connection.commit()
            print("Запись успешно добавлена")
        except:
            print("ОШИБКА: не удалось добавить данные в таблицу")

def menu():
    pwd = getpass.getpass("Введите пароль для работы с базой данных: ")
    my_db = DataBase(pwd)
    if my_db.is_close():
        return

    while True:
        print_menu()
        choice = int(input(">> Ваш выбор: "))

        if choice == 1:
            my_db.get_number_debtor()
            my_db.get_result()
        elif choice == 2:
            #kind = input("Введите марку (полностью или часть, например, МР-18М%) ружья: ")
            my_db.get_debtor_fullsumma()
            my_db.get_result()
        elif choice == 3:
            my_db.get_debtor_max_debt()
            my_db.get_result()
        elif choice == 4:
            my_db.get_tables_with_size()
            my_db.get_result()
        elif choice == 5:
            id = int(input("Введите номер долга: "))
            my_db.get_summa_payment(id)
            my_db.get_result()
        elif choice == 6:
            kind = input("Введите название страны: ")
            my_db.get_debtor_info_in_country(kind)
            my_db.get_result()
        elif choice == 7:
            print("Введите: ")
            name = input()
            

            my_db.get_size_table(name)
        elif choice == 8:
            my_db.call_systems_call()
            my_db.get_result()
        elif choice == 9:
            my_db.create_table()
        elif choice == 10:
            print("Введите: ")
            lol = input("- lol: ")
            if lol == "":
                print("ОШИБКА: неверный ввод имени")
                continue

            kek = input("- kek: ")
            if kek == "":
                print("ОШИБКА: неверный ввод названия породы")
                continue

            my_db.insert_data(lol, kek)
        elif choice == 0:
            break
        else:
            print("ОШИБКА: неверный ввод")

if __name__ == '__main__':
    menu()