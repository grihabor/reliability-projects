from .variant import Variant
from xml.etree import ElementTree


def module_to_xml(module):
    attrib = dict(
        id=str(module.id),
    )
    module_xml = ElementTree.Element('module', attrib)
    for variant in module.variants:
        variant_xml = variant.to_xml()
        module_xml.append(variant_xml)

    return module_xml


def module_from_xml(xml_obj):
    module = Module(xml_obj.attrib['id'], [])
    for variant_xml in xml_obj:
        module.variants.append(Variant.from_xml(variant_xml))
    return module


class Module:
    def __init__(self, module_id, variants):
        self.id = module_id
        self.variants = variants

    def to_xml(self):
        return module_to_xml(self)

    @classmethod
    def from_xml(cls, xml_obj):
        return module_from_xml(xml_obj)

