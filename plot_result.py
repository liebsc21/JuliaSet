#!/usr/bin/env python

""" reads result from csv and plots output to canvas
"""

import os
import sys
import logging
import argparse
import csv
import numpy
import math
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pprint
try:
    import colorer
    colorer.__name__
except ImportError:
    pass


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

    fig = plt.figure()
    plt.axis('off')
    files = [f for f in os.listdir(".") if f.startswith("output") and f.endswith(".csv")]
    files.sort()
#    pprint.pprint(files)

    steps = []

    for i, f in enumerate(files):
        logging.info("Now at: " + str(i))
        r = csv.reader(open(f, "r"))
        result = []
        while True:
            try:
                line = r.next()
            except StopIteration:
                break
            result.append([math.log(int(x) + 1) for x in line])
        result = numpy.array(result)

        im = plt.imshow(result, cmap="Greens")

        im.axes.get_xaxis().set_visible(False)
        im.axes.get_yaxis().set_visible(False)
        steps.append([im])
        plt.savefig('test_{}.png'.format(i), bbox_inches='tight')

    ani = animation.ArtistAnimation(fig, steps, interval=50, blit=True)
    ani.save('animation.mp4', bitrate=100000)
    plt.show()


if __name__ == "__main__":
    main(sys.argv[1:])
