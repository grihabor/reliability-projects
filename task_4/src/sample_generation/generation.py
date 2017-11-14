from structure import Module, Variant, Sample


def _generate_variant(variant_id):
    return Variant(
        variant_id=variant_id,
        reliability=0.,
        cost=0.,
    )


def _generate_module(module_id, variant_count):
    module = Module(module_id, [])

    for variant_id in range(variant_count):
        module.variants.append(_generate_variant(variant_id))

    return module


def generate_sample(module_count, variant_count):
    sample = Sample([])

    for module_id in range(module_count):
        sample.modules.append(_generate_module(module_id, variant_count))

    return sample