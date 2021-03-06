//
// Created by grihabor on 08.10.17.
//

#include "../../header/run.h"
#include "../../header/init/code.h"
#include "../../header/init/code_with_state.h"

CodeWithState get_f_code_with_state() {
    return CodeWithState(get_f_code(), 0);
}

CodeWithState get_g_code_with_state(int b) {
    return CodeWithState(get_g_code(b), 0);
}

CodeWithState get_f_code_with_state_h_only() {
    return CodeWithState(get_f_code_h_only(), 0);
}

CodeWithState get_g_code_with_state_h_only(int b) {
    return CodeWithState(get_g_code_h_only(b), 0);
}
