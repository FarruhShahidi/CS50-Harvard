from cs50 import get_int, get_string


st = get_string(" Enter a number:\n")
n = len(st)

luhn = 0
for i in range(n - 2, -1, -2):
    temp = int(st[i]) * 2
    luhn += temp % 10 + (temp //10)
for i in range(n - 1, -1, -2):
    luhn += int(st[i])
luhn %= 10

if (st[0] == '4') and (not luhn) and (n == 13 or n == 16):
    print("VISA\n")
elif (50 < int(st[:2]) < 56) and (not luhn) and (n == 16):
    print("MASTERCARD\n")

elif (st[:2] == "34" or st[:2] == "37") and (not luhn) and (n == 15):
    print("AMEX\n")
else:
    print("INVALID\n")

