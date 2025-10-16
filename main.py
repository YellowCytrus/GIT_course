import os
import random
import string

print("Hello world!")

def generate_password(length: int):
	return "".join(random.choices(string.ascii_letters + string.digits, k=length))

print(generate_password(10))

vredonosnaya komanda kotoraya ne rabotaet # Команда, которая ломает программу, но я надеюсь что ты не прочитаешь этого комментария и просто замёржишь ветку
# Функционала не будет


def generate_krypton_password(length: int):
	return "".join(random.choices(string.ascii_letters + string.digits + string.punctuation, k=length))

print(generate_krypton_password(11))
