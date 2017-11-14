from xml.etree import ElementTree
from utils import FILE_INPUT_XML
from structure import Sample


def _increment_state(state, modules, module_index):
    if module_index < 0:
        return False

    module = modules[module_index]

    if state[module_index] + 1 < len(module.variants):
        state[module_index] += 1
        return True

    state[module_index] = 0
    return _increment_state(state, modules, module_index - 1)


def _calc_cost(state, modules, max_cost):
    cost = 0
    reliability = 0.
    for i, (variant_index, module) in enumerate(zip(state, modules)):
        cost += module.variants[variant_index].cost
        reliability += module.variants[variant_index].reliability
        if cost > max_cost:
            return dict(cost=None, index=i)
    return dict(cost=cost, reliability=reliability)


def find_best_solution(sample: Sample):
    modules = sample.modules
    reduce_count = 0

    # List of variant indices
    state = [0 for _ in sample.modules]
    best_state = dict(
        state=list(state),
        reliability=0,
    )

    while True:
        result = _calc_cost(state, modules, sample.max_cost)
        if result['cost'] is None:
            reduce_count += 1
            index = result['index']
            ok = _increment_state(state, modules, index)
            if not ok:
                break
            continue

        reliability = result['reliability']
        if reliability > best_state['reliability']:
            best_state = dict(
                state=list(state),
                reliability=reliability,
            )

        ok = _increment_state(state, modules, len(modules) - 1)
        if not ok:
            break

    print(f'Reduce count: {reduce_count}')
    return best_state


def main():
    sample_xml = ElementTree.parse(FILE_INPUT_XML).getroot()
    sample = Sample.from_xml(sample_xml)
    print(find_best_solution(sample))


if __name__ == '__main__':
    main()
