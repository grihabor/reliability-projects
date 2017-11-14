import csv
from xml.etree import ElementTree

from solve import find_best_solution
from structure import Sample
from utils import FILE_INPUT_XML, FILE_RESULTS_CSV
from generate_samples import initialize_args
from sample_generation import generate_sample, Args


def _generate_xml(path, module_count, variant_count):
    args = initialize_args(default=Args(
        xml_path=path,
        module_count=module_count,
        variant_count=variant_count,
    ))
    sample = generate_sample(args.module_count, args.variant_count)
    xml_obj = sample.to_xml()
    et = ElementTree.ElementTree(xml_obj)
    et.write(args.xml_path)


def _find_solution(path):
    sample_xml = ElementTree.parse(path).getroot()
    sample = Sample.from_xml(sample_xml)
    solution = find_best_solution(sample)
    return solution


def run():
    path = FILE_INPUT_XML
    for i in range(10, 11):
        for _ in range(1000):
            module_count = i + 1
            variant_count = i
            _generate_xml(
                path,
                module_count,
                variant_count
            )
            yield dict(
                solution=_find_solution(path),
                module_count=module_count,
                variant_count=variant_count,
            )


def main():
    with open(FILE_RESULTS_CSV, 'w') as f:
        writer = csv.writer(f)
        writer.writerow([
            'module_count',
            'variant_count',
            'cost',
            'reliability',
        ])
        for results in run():
            solution = results['solution']
            writer.writerow([
                results['module_count'],
                results['variant_count'],
                solution['cost'],
                solution['reliability'],
            ])
            f.flush()


if __name__ == '__main__':
    main()
