def some_test():
	return

def test_for_password():
	assert some_test() == "1234567890"

def test_for_password_length():
	assert len(some_test()) == 10

def test_for_password_type():
	assert isinstance(some_test(), str)

def test_for_password_complexity():
	assert len(some_test()) >= 10