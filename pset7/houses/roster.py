import sys
from cs50 import SQL



if len(sys.argv) != 2:
    print("error\n")
    sys.exit(1)
h = sys.argv[1]

db = SQL("sqlite:///students.db")

house_list  = db.execute("SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first", h)
#print(len(house_list))
for line in house_list:

    if line["middle"] == None:
        print(line["first"] + " " +  line["last"] + ", born" + str(line["birth"]))
    else:
        print(line["first"] + " " + line["middle"] + " " +  line["last"] + ", born " + str(line["birth"]))


