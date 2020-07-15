from cs50 import get_int
# get a default int
n = -1
# get the int
while n < 1 or n > 8:
    n = get_int("Enter a number: ")
# start printing
for i in range(1, n + 1):
    print(' ' * (n - i) + '#' * i + '  ' + '#' * i )

