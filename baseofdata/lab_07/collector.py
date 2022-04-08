
class collector():
    id = int()
    surname = str()
    name = str()
    middlename = str()
    bithday = str()
    mobilephone = str()
    email = str()
    experiene = int()
    stars = float()


    def __init__(self, id, surname, name, middlename, bithday, mobilephone, email, experiene, stars):
        self.id = id
        self.surname = surname
        self.name = name
        self.middlename = middlename
        self.bithday = bithday
        self.mobilephone = mobilephone
        self.email = email
        self.experiene = experiene
        self.stars = stars