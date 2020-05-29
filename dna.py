from sys import argv, exit
import csv

def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Open dna database
    database = open(argv[1],"r")
    reader = csv.reader(database, delimiter=',')

    # Extract header to use the STR variable
    header = next(reader)
    header.pop(0)

     # Open sequence file sequence
    sequence = open(argv[2],"r")

    # read sequence file
    readsequence = sequence.read()

    # Declare a dictionary of STR
    STR = list()

    # Look for each that STR (st) a person has in sequence file
    o = 0
    for st in header:
        n = 0

        STR.insert(o, 0)
        # Once it finds a particular st in that file start counting how many consecutive st of that type there are
        while n < len(readsequence):
            if readsequence[n:n +len(st)] == st:

                # Creates a count of consecutive st
                temp_consecutive_st = 0

                # starts counting in (temp_consecutive_st) how many we have
                while readsequence[n:n+len(st)]== st:
                    n = n + len(st)
                    temp_consecutive_st += 1

                # Extracts the bigger count of current consecutive st
                current_consecutive_st = STR [o]

                # Compares the actual count with the stored one and stays with bigger number
                if temp_consecutive_st > current_consecutive_st:
                    STR [o] = temp_consecutive_st

            n += 1
        o += 1
        
    # Look for matches
    for row in reader:
        a = 0
        b = 0
        count = 0
        for v in row:
            if a != 0:
                if int(v) == STR [b]:
                    count += 1
                b += 1
            a += 1
        if count == len(STR):
            print(row[0])
            exit(0)
    
    # If no match is found:
    print ("No match")
    

    sequence.close()
    database.close()

    

main()