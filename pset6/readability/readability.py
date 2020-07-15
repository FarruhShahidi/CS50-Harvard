
from cs50 import get_string
text = get_string("Enter a text:\n")


letters, words,sentences = 0,1,0
for ch in text:
    if ch.isalpha():
        letters += 1
    if ch == " ":
        words += 1
    if ch in ["?", "!", "."]:
        sentences += 1


L = (letters / words) * 100
S = (sentences / words) * 100

ind = round(0.0588 * L - 0.296 * S - 15.8)

if ind >=16:
    print("Grade 16+\n")

elif ind < 1:
    print("Before Grade 1\n")
else:
    print("Grade : {}".format(ind))
#print(L,S, letters, sentences, words, ind)

