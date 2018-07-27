# Taken from: http://docs.cython.org/en/latest/src/tutorial/cython_tutorial.html
# and modified to add optimised version.
from __future__ import print_function

def fib(n):
    """Print the Fibonacci series up to n."""
    a, b = 0, 1
    while b < n:
        print(b, end=' ')
        a, b = b, a + b
    print()
