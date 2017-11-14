from xml.etree.ElementTree import ElementTree, Element

from .args import Args


def _generate_variants(variant_count):
    for variant_index in range(variant_count):
        attrib = dict(
            id=str(variant_index),
            cost='0',
            reliability='0',
        )
        variant = Element('variant', attrib)
        yield variant


def _generate_modules(module_count, variant_count):
    for module_index in range(module_count):
        module = Element('module', dict(id=str(module_index)))
        for variant in _generate_variants(variant_count):
            module.append(variant)
        yield module


def generate_xml(args: Args):
    data = Element('data')
    for module in _generate_modules(args.module_count, args.variant_count):
        data.append(module)

    et = ElementTree(element=data)
    et.write(args.xml_path)

