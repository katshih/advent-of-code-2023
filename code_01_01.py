input_file = './Inputs/input_01.txt'

with open(input_file) as f:
    dat = f.read()

sum = 0
first_digit = None
last_digit = None

for c in dat:
    if(c == '\n'):
        sum += first_digit*10 + last_digit
        first_digit = None
        last_digit = None
    elif(c.isdigit()):
        last_digit = int(c)
        if(first_digit is None):
            first_digit = int(c)

print(sum)