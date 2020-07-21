import sys
from cs50 import SQL
import csv





if len(sys.argv) != 2:
    print("error\n")
    sys.exit(1)

db = SQL("sqlite:///students.db")
with open(sys.argv[1], "r") as file:
    filereader = csv.reader(file)
    next(filereader)
    for row in filereader:

        fullname, house , birth = row[0], row[1], row[2]
        middle = None
        if fullname.count(" ") == 1:
            first,last = fullname.split(" ")
        else:
            first,middle,last = fullname.split(" ")
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)", first, middle, last, house, birth)




