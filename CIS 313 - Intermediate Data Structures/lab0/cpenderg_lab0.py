"""
Fibonacci Number Calculator

AUTHOR: Cole Pendergraft

This program prompts a user for numerical input, and outputs the Fibonacci sequence term associated with the input.
I.e. if provided with 3, the program will output "The 3rd Fibonacci number is 1".

Summary of my process:

I used Binet's formula in order to compute my Fibonacci values. I ran into an interesting problem using this formula,
I found that my code was only accurate up to the 72nd Fibonacci number, and the 73rd was off by 1. Every following value
is off by greater and greater values. I spent a long time bug testing and trying to determine what I had done wrong, but
eventually realized that my error was coming from my calculation of phi, the Golden Ratio. Since Python has to round
floats in order to keep them from getting too large, my approximation for the Golden Ratio was actually pretty bad
given that typically the GR is an infinite value, and I just didn't see that until we got to high n values. This was an
interesting experience for me in learning about the limitations of programming. I had thought my method was foolproof,
as Binet's formula is known to be exact, but that just goes to show that there are a whole host of considerations to
make when trying to move a theoretical function from paper to program, and that just because something should be exact
in the physical world, it won't always be exact when coded out.
"""


class FibSequence:
    """
    A FibSequence object contains all the methods required to compute the Fibonacci value at some input value by
    passing that input value into two methods: compute and display.
    """
    def __init__(self):
        None

    def compute(self, n):
        """
        This method of the FibSequence class handles the actual computation of the Fibonacci number at position n. It
        takes the input value n and passes it into Binet's formula, which is used to compute the Fibonacci number at
        some position.
        """
        phi = ((5 ** 0.5) + 1)/2
        # Phi is commonly used as the variable name for the Golden Ratio.
        # The golden ratio is equivalent to (sqrt(5) + 1)/2
        # This is the calculation that I believe produces the round-off errors at n > 72 that I mentioned in my
        # docstring. Python can only compute the sqrt of 5 accurately up to a certain decimal position

        m = int(n) - 1
        # The reason I do this is because the Binet formula indexes the Fibonacci sequence at 1, whereas we want the
        # sequence to be indexed at zero. If we subtract 1 from our input then we are adjusting the index of the Binet
        # formula to be zero, which matches the indices we want. This further means that I have to include a check in
        # my main to ensure the user doesn't ask for the 0th fibonacci number, as then we would have m = -1 which would
        # return an incorrect answer.

        num = (phi**m - (-phi**(-m)))/(5 ** 0.5)
        # This is known as Binet's Formula for the nth Fibonacci number. The name pretty much says it all.

        return int(num)
        # num is naturally a float, so here we want to declare it as an int which will perform floor division to give us
        # an integer.

    def display(self, step, num):
        """
        This method handles displaying the nth Fibonacci number to the console in a way that is easily understood.
        Multiple lines account for the multiple potential suffixes depending on the step passed. Step is expected to be
        the string first passed in by the user, and num is the calculated value produced from FibSequence.compute().
        """
        # I used the str.endswith() method in order to determine the appropriate suffix for the step.
        # I also had to account for the fact that we don't say '11st', '12nd', and '13rd'.
        if step.endswith('1') and step != '11':
            print("The %sst Fibonacci number is %s" % (step, num))
        elif step.endswith('2') and step != '12':
            print("The %snd Fibonacci number is %s" % (step, num))
        elif step.endswith('3') and step != '13':
            print("The %srd Fibonacci number is %s" % (step, num))
        else:
            print("The %sth Fibonacci number is %s" % (step, num))


def n_check_function(n):
    """
    This function is used to check that the user input matches what the program expects. This means that there is no
    extra whitespace, and no Alphanumeric characters other that 'q' to exit the program and 0-9 for entering values.
    """
    # After some experimenting, I found that writing a dedicated check function was the best way to make sure that the
    # user input matched what we wanted. I don't love that I had to use a list of allowed values to make this work as it
    # feels somewhat brute-force-y and inelegant, but ultimately it works reliably and prevents the user from inputting
    # any letters other than 'q' or weird characters like !, *, or ?.
    allowed = ['q', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    check = 1
    for i in range(0, len(n)):
        if n[i] not in allowed:
            check = 0

        if n == '0':
            check = 0
        # I include this here because if the user is searching for the first fibonacci number (F_0) then we want them
        # to input 1, not 0. This prevents 0 from being entered as the input, which prevents my function from executing
        # with m = -1
    return check


def main():
    """
    This is my main function that executes all the code above and prompts the user for input. It also handles checking
    the output from the n_check_function and printing any messages notifying the user of invalid input.
    """
    n = input("Enter a digit or press 'q' to quit:")

    while n != 'q':
        if n_check_function(n) != 0:
            x = FibSequence()
            num = x.compute(int(n))
            x.display(n, num)
            # This if statement checks that the user input something that fits our input parameters, and then executes
            # the calculations making use of the FibSequence class.

        else:
            if n == '0':
                print(
                    "For this program we do not have a 0th entry. If you want the first entry of the sequence (F_0), "
                    "please enter '1'")
            else:
                print("You've entered an invalid character! Only positive digits or 'q' please!")
            # This statement executes if the n_check_function returns 0. It informs the user that they have entered an
            # incorrect input and refuses to preform any calculations.

        n = input("Enter a digit or press 'q' to quit:")
        # This line will execute regardless of the return from the check function. This way, the user is prompted for
        # new input even if their previous input is invalid.

    else:
        print("Goodbye! Thanks for using my program!")
        # Ends the program with a farewell message if n == 'q'.


if __name__ == '__main__':
    main()
