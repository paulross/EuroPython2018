# Taken from: http://docs.cython.org/en/latest/src/tutorial/cython_tutorial.html
# and modified to add an unoptimised version.
#
# Example timeit:
# >>> timeit.timeit('primes.primes(10)', 'import primes')
# 0.5585061359452084
# >>> timeit.timeit('primes.primes_nopt(10)', 'import primes')
# 10.349789578001946
#
# Or from the command line:
# $ python -m timeit -s 'import primes' 'primes.primes(200)'
# 10000 loops, best of 3: 100 usec per loop
# $ python -m timeit -s 'import primes' 'primes.primes_nopt(200)'
# 1000 loops, best of 3: 1.15 msec per loop


def primes(int nb_primes):
    cdef int n, i, len_p
    cdef int p[1000]
    if nb_primes > 1000:
        nb_primes = 1000
    len_p = 0  # The current number of elements in p.
    n = 2
    while len_p < nb_primes:
        # Is n prime?
        for i in p[:len_p]:
            if n % i == 0:
                break
        # If no break occurred in the loop, we have a prime.
        else:
            p[len_p] = n
            len_p += 1
        n += 1
    # Let's return the result in a python list:
    result_as_list  = [prime for prime in p[:len_p]]
    return result_as_list


def primes_nopt(nb_primes):
    if nb_primes > 1000:
        nb_primes = 1000
    p = [0] * 1000
    len_p = 0  # The current number of elements in p.
    n = 2
    while len_p < nb_primes:
        # Is n prime?
        for i in p[:len_p]:
            if n % i == 0:
                break
        # If no break occurred in the loop, we have a prime.
        else:
            p[len_p] = n
            len_p += 1
        n += 1
    return p[:len_p]
