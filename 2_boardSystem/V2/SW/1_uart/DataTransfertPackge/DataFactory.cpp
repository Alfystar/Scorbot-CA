//
// Created by alfyhack on 15/10/19.
//

#include "DataFactory.h"
namespace dataFactory {

    SPIPACK &makeSPIPACK() {
        SPIPACK *p = (SPIPACK *) malloc(sizeof(SPIPACK));
        memset(p, 0, sizeof(SPIPACK));
        return *p;
    }

    void freeSPIPACK(SPIPACK *p) {
        free(p);
    }

};