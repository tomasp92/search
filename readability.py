from cs50 import get_string

def main ():

    # Get a text from usser
    text = get_string("Text: ")

    # Count number of letters
    let = count_letters(text)

    # Count number of words
    wor = count_words(text)

    # Count number of sentences
    sent = count_sentences(text)

    l = 100 * let / wor
    s =  100 * sent / wor

    colemanliaau = 0.0588 * l - 0.296 * s - 15.8


    if colemanliaau < 1:
        print(f"Before Grade 1")
    elif colemanliaau > 16:
        print(f"Grade 16+")
    else:
        print(f"Grade {round(colemanliaau)}")

def count_letters(text):
    letters = 0

    # Loop that counts number of words (not other characters)
    for x in text:
        if x.isalpha():
            letters += 1



    return letters

def count_words(text):
    l = 0
    words = 0
    # Loop that counts number of words
    for x in text:
        if x.isalpha():
            l += 1
        elif x == " ":
            words += 1
    if l > 0:
        words += 1

    return words

def count_sentences(text):
    let = 0
    w = 0
    sentences = 0

    # Loop that counts number of sentences
    for x in text:
        if x in [".","!","?"]:
            sentences += 1

    return sentences
main()