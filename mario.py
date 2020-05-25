from cs50 import get_int

def main():
    #
    i = get_positive_1_to_8_int()
    for a in range (i):
        for b in range (1*i-a-1):
            print(" ", end ="")
        for b in range (1*a+1):
            print("#", end ="")
        print("  ", end ="")
        for b in range (1*a+1):
            print("#", end ="")
        print()

def get_positive_1_to_8_int():
    while True:
        n = get_int ("Height: ")
        if n > 0 and n < 9:
            break
    return n

main()
