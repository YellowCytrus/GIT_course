import os
import random
import string

print("Hello world!")

def generate_password(length: int):
	return "".join(random.choices(string.ascii_letters + string.digits, k=length))

print(generate_password(10))


def generate_krypton_password(length: int):
	return "".join(random.choices(string.ascii_letters + string.digits + string.punctuation, k=length))

print(generate_krypton_password(10))