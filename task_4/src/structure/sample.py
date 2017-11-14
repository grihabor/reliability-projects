from xml.etree import ElementTree
from .module import Module


def sample_to_xml(sample):
    sample_xml = ElementTree.Element('sample')
    for module in sample.modules:
        sample_xml.append(module.to_xml())
    return sample_xml


def sample_from_xml(xml_obj):
    sample = Sample([])
    for module_xml in xml_obj:
        sample.modules.append(Module.from_xml(module_xml))
    return sample


class Sample:
    def __init__(self, modules):
        self.modules = modules

    def to_xml(self):
        return sample_to_xml(self)

    @classmethod
    def from_xml(cls, xml_obj: ElementTree.Element):
        return sample_from_xml(xml_obj)