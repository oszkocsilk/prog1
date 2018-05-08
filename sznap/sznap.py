import datetime

def zero():
    return "Vasárnap"

def one():
    return "Hetfo"

def two():
    return "Kedd"

def three():
    return "Szerda"

def four():
    return "Csütörtök"

def five():
    return "Péntek"

def six():
    return "Szombat"

def numberToDay(arg):
    switcher = {
        0: zero,
        1: one,
        2: two,
        3: three,
        4: four,
        5: five,
        6: six
    }

    func = switcher.get(arg, lambda: "Érvénytelen hónap")

    print func()

def addyear(y, d):
    dd = d
    year = y
    while year < 3000:
        year += 1
        if( ((year%4) == 0) and (((year%100) != 0) or ((year%400) == 0))):
            dd = (dd+2)%7
        else:
            dd = (dd+1)%7
    return dd

year = input("Év: ")
month = input("Hónap: ")
day = input("Nap: ")
mydate = datetime.date(year, month, day)
wd = addyear(year, int(mydate.strftime("%w")))

print "A születésnapod 3000-ben erre a napra esik: "

number_to_day(wd)

