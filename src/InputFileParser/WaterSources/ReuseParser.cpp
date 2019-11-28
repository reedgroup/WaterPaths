//
// Created by Bernardo on 11/19/2019.
//

#include "ReuseParser.h"
#include "../MasterSystemInputFileParser.h"


void
ReuseParser::parseVariables(vector<vector<string>> &block, int n_realizations,
                            int n_weeks) {
    WaterSourceParser::parseVariables(block, n_realizations, n_weeks);
}

WaterSource *
ReuseParser::generateSource(int id, vector<vector<string>> &block, int line_no,
                            int n_realizations,
                            int n_weeks,
                            const map<string, int> &ws_name_to_id,
                            const map<string, int> &utility_name_to_id) {
    parseVariables(block, n_realizations, n_weeks);

    checkMissingOrExtraParams(line_no, block);

    if (existing_infrastructure) {
        return new WaterReuse(name, id, capacity);
    } else {
        return new WaterReuse(name, id, treatment_capacity, construction_time,
                              permitting_time, *bonds[0]);
    }
}

void ReuseParser::checkMissingOrExtraParams(int line_no,
                                            vector<vector<string>> &block) {
    WaterSourceParser::checkMissingOrExtraParams(line_no, block);
}

ReuseParser::ReuseParser() : WaterSourceParser("[WATER REUSE]") {
    capacity = 0;
}