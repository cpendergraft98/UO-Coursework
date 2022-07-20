'''
CIS 210 Project 5-2 Parity Bits

Author: Cole Pendergraft
Credits: None

'''
def parity(bitrep):
    '''
    (string) -> string
    
    Calculates an even parity bit for a given binary code. By even parity, I 
    mean that if there is an even number of ones in the binary string, then the
    parity bit will be 0, but if there is an odd number of ones in the binary
    string then the parity bit will be 1.
    
    >>> parity('1100011')
    '0'
    
    >>> parity('1110110')
    '1'
    '''
    total = 0
    for i in bitrep:
        total += int(i)
        
    if total % 2 == 0:
        parity_bit = '0'
        
    elif total % 2 != 0:
        parity_bit = '1'
        
    return str(parity_bit)
        
def encode(letter):
    '''
    (string) -> string
    
    Converts characters to their binary ascii equivalent with an included parity
    bit.
    
    >>> encode('c')
    '01100011'
    
    >>> encode('v')
    '11110110'
    '''
    ascii_value = ord(letter)
    binary_value = '{:b}'.format(ascii_value)
    
    parity_bit = parity(binary_value)
    
    new_binary = parity_bit + binary_value
 
    return new_binary

def decode(binary):
    '''
    (string) -> string
    
    Takes binary strings along with a parity bit and converts it back into 
    the orignal character that created the binary string.
    
    >>> decode('01100011')
    'c'
    
    >>> decode('11110110')
    'v'
    '''
    binary = binary[1:]
    
    base_ten = int(binary, 2)
    
    decoded_string = chr(base_ten)
    
    return decoded_string
    
def main():
    '''
    Executes encode and decode for a mult-character string.
    '''
    word = 'cat'
    for letter in word:
        print(decode(encode(letter)))
    print()
    return None

if __name__ == '__main__':
    main()