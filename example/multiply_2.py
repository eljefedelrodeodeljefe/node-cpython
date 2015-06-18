
import sys
print "this functions sees your arguments %s" % sys.argv


def fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib(n-1) + fib(n-2)


print "Let's talk about Fibonnaci number of 10: %d." % fib(10)
