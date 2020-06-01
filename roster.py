from sys import argv, exit
from cs50 import SQL

def main():

    # Check correct Usage
    if len(argv) != 2:
        print("Usage: python dna.py [House]")
        exit(1)
    
    # Generete an SQL db to use
    db = SQL ("sqlite:///students.db")
    
    selected_house = argv[1]
    
    
    #Copy to database
    students = db.execute("SELECT students.first, students.middle, students.last, students.birth FROM students WHERE house = ? ORDER BY students.last, students.first;", selected_house)
    
    for lines in students:
        for a, b in lines.items():
            
            if b is None:
                continue
            print (f"{b}", end=" ") 
        print()
   
main()