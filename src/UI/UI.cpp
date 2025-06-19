#include "UI.hpp"

int main() {

    run_container();
    if (!container_num) {
        delete tree;
        delete set;
        delete queue;
        return 0;
    }

    run_method();
    if (!method) {
        return 0;
    }
}