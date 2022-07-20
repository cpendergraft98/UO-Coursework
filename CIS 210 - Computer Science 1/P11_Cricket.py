'''
CIS 210 Project 1-1 Hello-Cricket
[Author]: Cole Pendergraft
[Credits]: N/A
Determine temperature based on cricket chirps
'''

def chirps_to_celsius(chirp_number_25s):
    '''
    (int) -> float
    This function converts the number of chirps given off by a cricket
    in 25 seconds into a celsius temperature by dividing by 3 and
    adding 4. It then returns this celsius temp.
    
    >>>chirps_to_celsius(21)
    11.0
    
    >>>chirps_to_celsius(15)
    9.0
    '''
    c_temp = (chirp_number_25s / 3) + 4
    return c_temp

print(chirps_to_celsius(21), 'degrees celsius')

def chirps_to_fahrenheit(chirp_number_14s):
    '''
    (int) -> int
    This function converts the number of chirps given off by a cricket
    in 14 seconds into a fahrenheit temperature by adding 40. It then
    returns this fahrenheit temp.
    
    >>>chirps_to_fahrenheit(30)
    70
    
    >>>chirps_to_fahrenheit(80)
    120
    '''
    f_temp = chirp_number_14s + 40
    return f_temp

print(chirps_to_fahrenheit(30), 'degrees fahrenheit')
