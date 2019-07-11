#################################################
#                                               #
#    Name:       Ren Gibbons                    #
#    Date:       December 14, 2016              #
#    Course:     CME211                         #
#    Submission: Final Project                  #
#    File:       postprocess.py                 #
#                                               #
#    See despription in writeup.pdf             #
#                                               #
#################################################


"""Import modules."""
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import math
import numpy as np
import sys


def computeDomain(length, width, h, Tc, Th, soln_file, input_file):
    """Compute the 2D array of nodal temperatures on the domain."""
    # Open solution file and read each line to a list.
    x = []
    with open(soln_file, 'r') as fso:
        # Header contains input file used to create solution.
        # This must match the input file provided in the command line.
        input_file_compare = fso.readline().strip('\n')
        if input_file != input_file_compare:
            raise RuntimeError('ERROR: Provided input file does not'
                               ' match input file used to create solution file.')
            exit(0)

        # Read each solution temperature.
        for line in fso:
            x.append(float(line))

    # Compute number of rows and columns and initialize domain 2D array.
    nrows = int(width / h + 1)
    ncols = int(length / h + 1)
    domain = np.zeros((nrows, ncols))

    # Set the fixed temperature of the top row.
    domain[nrows - 1] = Th

    # Set the temperatures for the middle rows.
    coinc_node_num = 0
    count = 0
    for ii in range(nrows - 2, 0, -1):
        # Loop over the middle rows.
        for jj in range(ncols - 1):
            # Loop over columns.
            domain[ii][jj] = x[count]
            count += 1
            if jj == (ncols - 2):
                # On right side of domain. Set coincident node temperature.
                domain[ii][jj + 1] = x[coinc_node_num]
                coinc_node_num = count

    # Set the fixed temperatures of the bottom row.
    for jj in range(ncols):
        x_location = jj * h
        T = -Tc * (math.exp(-10 * pow(x_location - length / 2, 2)) - 2)
        domain[0][jj] = T
    return domain, nrows, ncols


if __name__ == "__main__":
    """Post process data."""
    # Check for appropriate command line arguments.
    if len(sys.argv) != 3:
        print('Usage:')
        print('    python3 {} <input_file> <soln_file>'.format(sys.argv[0]))
        sys.exit(0)

    # Store the input and solution file names.
    input_file = str(sys.argv[1])
    soln_file = str(sys.argv[2])

    # Open input file, read, and store data.
    with open(input_file, 'r') as fin:
        data = fin.readlines()
        length, width, h = data[0].split()
        Tc, Th = data[1].split()

    # Convert inputs to float variables.
    length = float(length)
    width = float(width)
    h = float(h)
    Tc = float(Tc)
    Th = float(Th)

    # Get the domain 2D array.
    domain, nrows, ncols = computeDomain(length, width, h, Tc, Th, soln_file, input_file)
    x_grid, y_grid = np.mgrid[slice(0, length + h, h), slice(0, width + h, h)]

    # Compute mean temperature isoline data.
    mean_temp = np.mean(domain)
    iso_temp = []
    x_val = []
    for ii in range(ncols):
         x_val.append(ii * h)
         # Find the isoline using linear interpolation.
         iso_temp.append(width / (domain[nrows - 1][ii] - domain[0][ii]) * \
                         (mean_temp - domain[0][ii]))

    # Plot pseudocolor plot.
    plt.pcolor(x_grid, y_grid, domain.T)

    # Plot mean temperature isoline.
    plt.plot(x_val, iso_temp)

    # Format plot.
    plt.title('2D heat equation solution')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.axis([x_grid.min(), x_grid.max(), y_grid.min(), y_grid.max()])
    plt.axis('equal')
    plt.colorbar()
    plt.show()
    plt.savefig('solution.png')

    # Print to console.
    print('Input file processed: {}'.format(input_file))
    print('Mean Temperature: {:.5f}'.format(mean_temp))