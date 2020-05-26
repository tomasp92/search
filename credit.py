from cs50 import get_int

def main():
    # Ask a positive credit card i
    i = get_positive_int()

    suma = 0

    #extract all the digits into an array and make a sum 

    for a in range (16):
        if a == 0:
            digits = i % 10
            
            suma = digits

        # every other digit is multiplied by 2 and then its digits are sumed
        elif a % 2 != 0:
            digits = (i%10**(1+a)-i%10**a)/10**a
            other_digits = digits*2 % 10
            other_digitss = (digits*2 % 100 - other_digits)/10

            suma = suma + other_digits + other_digitss
            
        else:
            digits = (i%10**(1+a)-i%10**a)/10**a
            suma = suma + digits

    suma = suma % 2
    
    if suma > 0:
        print("INVALID\n", end="")

    #check out if its a valid VISA
    elif 3999999999999 < i and 5000000000000 > i:
        print("VISA\n", end="")

    elif 3999999999999999 < i and 5000000000000000 > i:
        print("VISA\n", end="")

    #check out if its a valid Master Mard
    elif 5099999999999999 < i and 5600000000000000 > i:
        print("MASTERCARD\n", end="")

    #checkout if its a valid American Express
    elif 339999999999999 < i and 350000000000000 > i:
        print("AMEX\n", end="")

    elif 369999999999999 < i and 380000000000000 > i:
        print("AMEX\n", end="")

    # If neither of the option is correct then:
    else:
        print("INVALID\n", end="")




#get positive int from user
def get_positive_int():
    while True:
        n = get_int ("number: ")
        if n > 0:
            break
    return n

main()