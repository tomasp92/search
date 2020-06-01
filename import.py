from sys import argv, exit
from cs50 import SQL
import csv

def main():

    # Check correct Usage
    if len(argv) != 2:
        print("Usage: python dna.py [].csv")
        exit(1)

    # Generete an SQL db to use
    db = SQL ("sqlite:///students.db")

    # Open csv file
    with open(argv[1], "r") as file:
        
        # Divide file in lineas
        lines = file.read().splitlines()
        # Pop Header
        lines.pop(0)
        
       # Loop in lines and split them
        for l in lines:
            n = 0
            line = l.split(",")
            for a in line:
                
                # Loop in fields and split them
                campo = a.split(",")
                b = a.split()
                l = 0
                
                # Extract values in fields and divide name field in first middle and last
                for c in b:
                    
                    # Deal with name
                    if n == 0:
                        
                        # First name
                        if l == 0:
                            h = c
                        
                        # Last name 
                        if l == 1:
                            e = c
                            d = None
                            
                        # Last name and middle
                        elif l == 2:
                            d = e
                            e = c 
                    
                    # House
                    elif n == 1:
                        f = c
                    
                    # Year    
                    elif n == 2:
                        g = c
                    
                    
                    l += 1        
                                    
                n += 1
            
            #Copy to database
            db.execute("INSERT INTO 'students' ('first', 'middle', 'last', 'house', 'birth') VALUES(?,?,?,?,?)", h, d, e, f, g)

main()