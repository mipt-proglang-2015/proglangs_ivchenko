__author__ = 'velkerr'

import random
import string
import argparse as asp

import repeating_count as rc

MAX_LENGTH = 250
MIN_LENGTH = 10

def string_generator():
    """
    String generator. All pritnable symbols (except whitespaces) may be a part of string.
    :return: generated string.
    :rtype: str
    """
    return ''.join(random.SystemRandom().choice(string.printable.rstrip()) for _ in range(random.randint(MIN_LENGTH, MAX_LENGTH)))

def setup_parser():
    """
    Configuring argparser.
    :return: argparser with all necessary parameters filled.
    :rtype: asp.ArgumentParser
    """
    parser = asp.ArgumentParser(
        'Searching max k-repeatings in strings',
        description='This program runs k-repeatings searching for string (or list with several strings). '
                    'The algorithm was written in C++.',
        epilog='This algorithm was proposed as task 1.4 in 2nd semester SHAD.')
    parser.add_argument('count', nargs='?', default=1, help='Quantity of strings', type=int)
    parser.add_argument('-s', '--strings', nargs='*', help='One or more strings for analysis. '
                                                           'If this argument was ignored, strings will be generated.')
    parser.add_argument('--single', action='store_true', help='Input data as a single string. '
                                                              'If more than one string was inputted, '
                                                              'only one string will be processed.')
    parser.add_argument('-v', '--version', action='version', version='%(prog)s 1.0')
    return parser

if __name__ == "__main__":
    args = setup_parser().parse_args()

    strings = [string_generator() for _ in range(args.count)] if args.strings is None else args.strings[:args.count]

    if args.single:
        print('STRING= ', strings[0], '\nRESULT= ', rc.count_rep_single(strings[0]))
    else:
        results = rc.count_rep_list(strings)
        [print('\nSTRING= ', s, '\nRESULT= ', res) for s, res in zip(strings, results)]
