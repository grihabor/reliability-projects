import sys

from sample_generation import generate_xml, Args
from utils import FILE_INPUT_XML


def print_usage():
    print(f'Usage: python3 {sys.argv[0]} xml_path [module_count [variant_count]]')


def initialize_args():
    args = Args(
        xml_path=FILE_INPUT_XML,
        module_count=5,
        variant_count=3,
    )
    try:
        args.path = sys.argv[1]
        args.module_count = int(sys.argv[2])
        args.variant_count = int(sys.argv[3])
    except ValueError as e:
        print(e)
        print_usage()
        sys.exit(0)
    except IndexError as e:
        print(e)

    return args


def main():
    args = initialize_args()
    generate_xml(args)


if __name__ == '__main__':		
    main()

