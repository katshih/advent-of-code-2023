input_file = './Inputs/input_01.txt'
with open(input_file) as f:
    dat = f.read()

sum = 0
first_digit = None
last_digit = None
digit_str = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
line = ""

for c in dat:
    if(c == '\n'):
        sum += first_digit*10 + last_digit
        first_digit = None
        last_digit = None
        line = ""
    elif(c.isdigit()):
        last_digit = int(c)
        if(first_digit is None):
            first_digit = int(c)
    else:
        line += c
        for i, d in enumerate(digit_str):
            if(d in line):
                last_digit = i + 1
                if(first_digit is None):
                    first_digit = i + 1
                line = c
                break

print(sum)