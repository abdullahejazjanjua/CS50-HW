from cs50 import get_int

credit_Answer = int(input("Number: "))

lenght = len(str(credit_Answer))
sumOfTwice = 0
sumOnce = 0

for i in range(len(str(credit_Answer)) - 2, -1, -2):
    product = int(str(credit_Answer)[i]) * 2
    while product > 0:
        sumOfTwice += product % 10
        product //= 10

for i in range(len(str(credit_Answer)) - 1, -1, -2):
    sumOnce += int(str(credit_Answer)[i])


checkSum = sumOfTwice + sumOnce
if (lenght == 15 and (str(credit_Answer)[:2] == '34' or str(credit_Answer)[:2] == '37')):
    if (checkSum % 10 == 0):
        print("AMEX")
    else:
        print("INVALID")
elif (lenght == 16 and (str(credit_Answer)[:2] == '51' or str(credit_Answer)[:2] == '52' or str(credit_Answer)[:2] == '53' or str(credit_Answer)[:2] == '54' or str(credit_Answer)[:2] == '55')):
    if (checkSum % 10 == 0):
        print("MASTERCARD")
    else:
        print("INVALID")
elif ((lenght == 16 or lenght == 13) and (str(credit_Answer)[:2] == '13' or str(credit_Answer)[:2] == '16' or str(credit_Answer)[0] == '4')):
    if (checkSum % 10 == 0):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
