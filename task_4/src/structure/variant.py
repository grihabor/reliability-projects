from xml.etree import ElementTree


def variant_to_xml(variant):
    attrib = dict(
        id=str(variant.id),
        cost=str(variant.cost),
        reliability=str(variant.reliability),
    )
    return ElementTree.Element('variant', attrib)


def variant_from_xml(xml_obj):
    return Variant(
        variant_id=int(xml_obj.attrib['id']),
        cost=int(xml_obj.attrib['cost']),
        reliability=float(xml_obj.attrib['reliability']),
    )


class Variant:
    def __init__(self, variant_id, reliability, cost):
        self.id = variant_id
        self.reliability = reliability
        self.cost = cost

    def to_xml(self):
        return variant_to_xml(self)

    @classmethod
    def from_xml(cls, xml_obj):
        return variant_from_xml(xml_obj)
