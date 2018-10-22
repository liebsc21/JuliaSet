#!/usr/bin/env python

""" example implementation of CPU-bound problem
"""

# import os
import sys
import logging
import argparse
import time
import csv
import math
# import pprint
try:
    import colorer
    colorer.__name__
except ImportError:
    pass

# area of complex space to investigate
x1, x2, y1, y2 = -1.8, 1.8, -1.8, 1.8


def chunks(l, n):
    """returns successive n-sized chunks from l."""
    result = []
    for i in range(0, len(l), n):
        result.append(l[i:i + n])
    return result


def calc_pure_python(desired_width, max_iterations, steps_angle):
    """ Create a list of complex coordinates (zs) and complex parameters (cs),
    build Julia set, and display """
    x_step = (float(x2 - x1) / float(desired_width))
    y_step = (float(y1 - y2) / float(desired_width))
    x = []
    y = []
    ycoord = y2
    while ycoord > y1:
        y.append(ycoord)
        ycoord += y_step
    xcoord = x1
    while xcoord < x2:
        x.append(xcoord)
        xcoord += x_step

    for i_angle in range(steps_angle):
        this_angle = 2.0 * math.pi * i_angle / steps_angle
        radius = 0.7563447119534848
        this_c_real = radius * math.sin(this_angle)
        this_c_imag = radius * math.cos(this_angle)

        # Build a list of coordinates and the initial condition for each cell.
        # Note that our initial condition is a constant and could easily
        # be removed;
        # we use it to simulate a real-world scenario with several inputs to
        # our function.
        zs = []
        cs = []
        for ycoord in y:
            for xcoord in x:
                zs.append(complex(xcoord, ycoord))
                cs.append(complex(this_c_real, this_c_imag))

        start_time = time.time()
        output = calculate_z_serial_purepython(max_iterations, zs, cs)
        if not len(output) == (desired_width) * (desired_width):
            logging.error("output lendth = {}, with desired_width = {}"
                          .format(len(output), desired_width))
            Exception("unkown dimension")
        chunked = chunks(output, int(math.sqrt(1.0 * len(output))) )
        with open("output_{}.csv".format(str(i_angle).zfill(3)), "wb") as outputfile:
            wr = csv.writer(outputfile)
            for row in chunked:
                wr.writerow(row)

        end_time = time.time()
        secs = end_time - start_time
        print "{:4.0f}th step took".format(i_angle), secs, "seconds"


def calculate_z_serial_purepython(maxiter, zs, cs):
    """Calculate output list using Julia update rule"""
    output = [0] * len(zs)
    for i in range(len(zs)):
        n = 0
        z = zs[i]
        c = cs[i]
        while abs(z) < 2 and n < maxiter:
            z = z * z + c
            n += 1
        output[i] = n
    return output


def main(argv):
    parser = argparse.ArgumentParser(
        description='template for generic python script',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("-d", '--debug',
                        default=False, action='store_true',
                        help='print in debug output')
    parser.add_argument("-N", '--Ntimes',
                        default=1, type=int,
                        help='print multiple times')
    parser.add_argument("inputs", nargs="*",
                        help="further input")
    args = parser.parse_args(argv)

    if args.debug:
        logging.basicConfig(level=logging.DEBUG)
        logging.debug("Set log level to DEBUG")
    else:
        logging.basicConfig(level=logging.INFO)
        logging.debug("Set log level to INFO")

    calc_pure_python(desired_width=1000, max_iterations=300, steps_angle=200)


if __name__ == "__main__":
    main(sys.argv[1:])
