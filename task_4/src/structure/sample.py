from typing import List
from xml.etree import ElementTree
from .module import Module


def sample_to_xml(sample):
    attrib = dict(max_cost=str(sample.max_cost))
    sample_xml = ElementTree.Element('sample', attrib)
    for module in sample.modules:
        sample_xml.append(module.to_xml())
    return sample_xml


def sample_from_xml(xml_obj):
    sample = Sample(int(xml_obj.attrib['max_cost']), [])
    for module_xml in xml_obj:
        sample.modules.append(Module.from_xml(module_xml))
    return sample


class Sample:
    def __init__(self, max_cost, modules):
        self.max_cost = max_cost  # type: int
        self.modules = modules  # type: List[Module]

    def to_xml(self):
        return sample_to_xml(self)

    @classmethod
    def from_xml(cls, xml_obj: ElementTree.Element):
        return sample_from_xml(xml_obj)