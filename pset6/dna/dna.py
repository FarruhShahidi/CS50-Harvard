from sys import argv
import csv
import collections

# check the number of arguments
if len(argv) != 3:
    print("usage: python dna.py database sequence")

""" create a dict with keys as the name and with values as
pattern:count dict object.

"""
person_dna_count = dict()
# store the patterns in a list
patterns = []
#open the data file
with open(argv[1], "r") as data_file:
    datareader = csv.reader(data_file)
    patterns = list(next(datareader))[1:] #we do not need name
    for row in datareader:
        r = len(row)
        person_dna_count[row[0]] = {}
        for i in range(1, r):
            person_dna_count[row[0]][patterns[i - 1]] = row[i]
#print(person_dna_count)

#open the text file
sample = ""
with open(argv[2], "r") as text_file:
    textreader = csv.reader(text_file)
    # next returns(and moves to the next row) the first row as a string in a list of one element
    #to get that string we need to extract the first element
    sample += next(textreader)[0]
#print(sample)

def count_max_consec_occur(text, subs):
    t,s = len(text), len(subs)
    ans = 0
    for i in range(t - s):
        count = 0
        j = i
        while text[j: j + s] == subs:
            count += 1
            j += s
        ans = max(ans, count)
    return ans
#print(count_max_consec_occur(sample, 'AGATC'))
# store the frequences
sample_patterns = []
for i in range(len(patterns)):
    # the use of substring counting is better in here
    max_val = count_max_consec_occur(sample, patterns[i])
    sample_patterns.append(max_val)

#print(sample_patterns, patterns, person_dna_count)

# start searchin for the name
def get_name(person_dna_count, patterns, sample_patterns):

    for name in person_dna_count:
        freq = person_dna_count[name]
        for i in range(len(patterns)):
            if int(freq[patterns[i]]) != sample_patterns[i]:
                break
            if i == len(patterns) - 1:
                return name
    return "No match"


if __name__ == "__main__":
    print(get_name(person_dna_count, patterns, sample_patterns))



