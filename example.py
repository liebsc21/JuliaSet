#!/usr/bin/env python

""" example implementation of Julia set
Code based on:
"High Performance Python" by Miche Gorelick, Ian Ozsvald. O'Reilly 2014
"""

import sys
import logging
import argparse
import time
import csv
import math
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


def produce_grid(desired_width, max_iterations, steps_angle, exponent, radius):
    """ Create a list of complex coordinates (zs) and complex parameters (cs),
    build Julia set, and display
    based on:
    "High Performance Python" by Miche Gorelick, Ian Ozsvald. O'Reilly 2014
    """
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
        output = calculate_z_serial(max_iterations, zs, cs, exponent)
        if not len(output) == (desired_width) * (desired_width):
            logging.error("output length = {}, with desired_width = {}"
                          .format(len(output), desired_width))
            Exception("unkown dimension")
        chunked = chunks(output, int(math.sqrt(1.0 * len(output))))
        outfile = "output_{}.csv".format(str(i_angle).zfill(3))
        with open(outfile, "wb") as outputfile:
            wr = csv.writer(outputfile)
            for row in chunked:
                wr.writerow(row)

        end_time = time.time()
        secs = end_time - start_time
        logging.debug("{:4.0f}th step took {:4.1f}seconds"
                      .format(i_angle, secs))


def calculate_z_serial(maxiter, zs, cs, exponent):
    """Calculate output list using Julia update rule
    based on:
    "High Performance Python" by Miche Gorelick, Ian Ozsvald. O'Reilly 2014
    """
    output = [0] * len(zs)
    for i in range(len(zs)):
        n = 0
        z = zs[i]
        c = cs[i]
        while abs(z) < 2 and n < maxiter:
            z = z ** exponent + c
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
    parser.add_argument("-e", '--exponent',
                        default=2., type=float,
                        help='exponent of z in julia update rule')
    parser.add_argument("-g", '--gridwidth',
                        default=100, type=int,
                        help='number of steps in x and y')
    parser.add_argument("-N", '--Nsteps',
                        default=200, type=int,
                        help='number of steps in angle')
    parser.add_argument("-r", '--radius',
                        default=0.7563447119534848, type=float,
                        help='absolute value of c')

    parser.add_argument("inputs", nargs="*",
                        help="further input")
    args = parser.parse_args(argv)

    if args.debug:
        logging.basicConfig(level=logging.DEBUG)
        logging.debug("Set log level to DEBUG")
    else:
        logging.basicConfig(level=logging.INFO)
        logging.debug("Set log level to INFO")

    start = time.time()
    produce_grid(desired_width=args.gridwidth,
                 max_iterations=300,
                 steps_angle=args.Nsteps,
                 exponent=args.exponent,
                 radius=args.radius)
    end = time.time()
    logging.info("Total execution took: {:4.1f}s.".format(end - start))


if __name__ == "__main__":
    main(sys.argv[1:])
