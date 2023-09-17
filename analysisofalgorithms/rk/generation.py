import random
import string


def generate_random_string(length):
    letters = string.ascii_lowercase
    rand_string = ''.join(random.choice(letters) for i in range(length))
    #print("Random string of length", length, "is:", rand_string)
    return rand_string

def generation_file():
    f = open('data.txt', 'w', encoding='utf-8')

    for i in range(100):
        f.write(generate_random_string(random.choice(range(5, 20, 2))))
        f.write(' ')

    f.close()  


generation_file()