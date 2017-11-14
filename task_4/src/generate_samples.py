import sys
from xml.etree.ElementTree import ElementTree

from sample_generation import generate_sample, Args
from utils import FILE_INPUT_XML


def print_usage():
    print(f'Usage: python3 {sys.argv[0]} xml_path [module_count [variant_count]]')


def initialize_args(default: Args):
    try:
        default.xml_path = sys.argv[1]
        default.module_count = int(sys.argv[2])
        default.variant_count = int(sys.argv[3])
    except ValueError as e:
        print(e)
        print_usage()
        sys.exit(0)
    except IndexError:
        pass

    return default


def main():
    args = initialize_args(default=Args(
        xml_path=FILE_INPUT_XML,
        module_count=8,
        variant_count=5,
    ))
    sample = generate_sample(args.module_count, args.variant_count)
    xml_obj = sample.to_xml()
    et = ElementTree(xml_obj)
    et.write(args.xml_path)


if __name__ == '__main__':		
    main()

