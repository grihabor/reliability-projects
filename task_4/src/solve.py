from xml.etree import ElementTree
from utils import FILE_INPUT_XML
from structure import Sample


def _increment_state(state, modules, module_index, zero_tail=True):
    if module_index < 0:
        return False

    if zero_tail:
        for index in range(module_index + 1, len(state)):
            state[index] = 0

    module = modules[module_index]

    if state[module_index] + 1 < len(module.variants):
        state[module_index] += 1
        return True

    state[module_index] = 0
    return _increment_state(state, modules, module_index - 1, zero_tail=False)


def _calc_cost(state, modules, max_cost, max_reliability):
    cost = 0
    reliability = 1.
    for i, (variant_index, module) in enumerate(zip(state, modules)):
        cost += module.variants[variant_index].cost
        reliability *= module.variants[variant_index].reliability
        if cost > max_cost:
            return dict(cost=None, index=i)
        if reliability < max_reliability:
            return dict(cost=None, index=i)
    return dict(cost=cost, reliability=reliability)


def find_best_solution(sample: Sample):
    modules = sample.modules
    reduce_count = 0

    # List of variant indices
    state = [0 for _ in sample.modules]
    best_state = dict(
        state=list(state),
        reliability=0.,
        cost=None,
    )

    while True:
        result = _calc_cost(state, modules, sample.max_cost, best_state['reliability'])
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
                cost=result['cost']
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
