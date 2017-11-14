import sys
from xml.etree.ElementTree import ElementTree

from sample_generation import generate_sample, Args
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
    sample = generate_sample(args.module_count, args.variant_count)
    xml_obj = sample.to_xml()
    et = ElementTree(xml_obj)
    et.write(args.xml_path)


if __name__ == '__main__':		
    main()

