'''
CIS 210 Project 5-1 Calender

Author: Cole Pendergraft
Credits: None

Write a function that takes two parameters and generates a calender using
these parameters
'''
import datetime

def calender_month(month):
    '''
    (int) -> string
    
    Determines the month associated with the given integer value and returns 
    mnth_hdr (month header) that will then be used to produce a calender
    
    >>> calender_month(1)
    'January'
    
    >>> calender_month(13)
    Months can only be values ranging between and including 1 and 12.
    This message means you have entered an invalid month.
    '''
    if month == 1:
        mnth_hdr = 'January'
        
    elif month == 2:
        mnth_hdr = 'February'
        
    elif month == 3:
        mnth_hdr = 'March'
        
    elif month == 4:
        mnth_hdr = 'April'
        
    elif month == 5:
        mnth_hdr = 'May'
        
    elif month == 6:
        mnth_hdr = 'June'
        
    elif month == 7:
        mnth_hdr = 'July'
        
    elif month == 8:
        mnth_hdr = 'August'
        
    elif month == 9:
        mnth_hdr = 'September'
        
    elif month == 10:
        mnth_hdr = 'October'
        
    elif month == 11:
        mnth_hdr = 'November'
        
    elif month == 12:
        mnth_hdr = 'December'
        
    else:
        print('Months can only be values ranging between and including 1 and 12.')
        print('This message means you have entered an invalid month.')
        return None
    
    days = 0
    if month == 1:
        days = 31
    elif month == 2:
        days = 28
    elif month == 3:
        days = 31
    elif month == 4:
        days = 30
    elif month == 5:
        days = 31
    elif month == 6:
        days = 30
    elif month == 7:
        days = 31
    elif month == 8:
        days = 31
    elif month == 9:
        days = 30
    elif month == 10:
        days = 31
    elif month == 11:
        days = 30
    elif month == 12:
        days = 31

        
    return (mnth_hdr, days)
    
def calender(month, year):
    '''
    (int, int) -> None
    
    Creates a calender for the given month in the given year.
    
    CALLS: calender_month
    '''
    mnth_hdr, num_days = calender_month(month)
    
    adate = datetime.date(year, month, 1)
    
    offset = adate.isoweekday()
    
    if adate.isoweekday() == 7:
        offset = 0
        
    week = []
    
    for i in range(0, offset):
        week.append('  ')
    for i in range(9):
        week.append('0'+str(i+1))
    for i in range(10, num_days):
        week.append(i+1)
    for i in range(10):
        week.append('      ')
    
    print(mnth_hdr, year)
    print(f'{"SU": ^1} {"MO": ^1} {"TU": ^1} {"WE": ^1} {"TH": ^1} {"FR": ^1} {"SA": ^1}')
    print(f'{week[0]: ^1} {week[1]: ^1} {week[2]: ^1} {week[3]: ^1} {week[4]: ^1} {week[5]: ^1} {week[6]: ^1}')
    print(f'{week[7]: ^1} {week[8]: ^1} {week[9]: ^1} {week[10]: ^1} {week[11]: ^1} {week[12]: ^1} {week[13]: ^1}')
    print(f'{week[14]: ^1} {week[15]: ^1} {week[16]: ^1} {week[17]: ^1} {week[18]: ^1} {week[19]: ^1} {week[20]: ^1}')
    print(f'{week[21]: ^1} {week[22]: ^1} {week[23]: ^1} {week[24]: ^1} {week[25]: ^1} {week[26]: ^1} {week[27]: ^1}')
    print(f'{week[28]: ^1} {week[29]: ^1} {week[30]: ^1} {week[31]: ^1} {week[32]: ^1} {week[33]: ^1} {week[34]: ^1}')
    
    return None

def main():
    '''
    Runs the calender function 12 times, once for each month in the year, to
    display efficacy of the function.
    '''
    print(calender(1, 2020))
    print()
    print(calender(2, 2020))
    print()
    print(calender(3, 2020))
    print()
    print(calender(4, 2020))
    print()
    print(calender(5, 2020))
    print()
    print(calender(6, 2020))
    print()
    print(calender(7, 2020))
    print()
    print(calender(8, 2020))
    print()
    print(calender(9, 2020))
    print()
    print(calender(10, 2020))
    print()
    print(calender(11, 2020))
    print()
    print(calender(12, 2020))
    
    return None

main()