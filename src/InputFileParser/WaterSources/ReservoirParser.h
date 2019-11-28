//
// Created by bernardo on 11/21/19.
//

#ifndef TRIANGLEMODEL_RESERVOIRPARSER_H
#define TRIANGLEMODEL_RESERVOIRPARSER_H


#include "../Base/WaterSourceParser.h"
#include "../CatchmentParser.h"
#include "../EvaporationSeriesParser.h"


class ReservoirParser : public WaterSourceParser {
protected:
    ReservoirParser(string tag_name);

    unsigned long BLOCK_LEN_EXISTING_RESERVOIR = 7;
    unsigned long BLOCK_LEN_NON_EXISTING_RESERVOIR = 10;

    CatchmentParser catchment_parser;
    EvaporationSeriesParser evaporation_series_parser;
    EvaporationSeries evaporation_series;

    double storage_area = NON_INITIALIZED;
    bool variable_area = false;

    vector<Catchment *> catchments;
    DataSeries storage_vs_area_curves;

public:
    ReservoirParser();

    void parseVariables(vector<vector<string>> &block, int n_realizations,
                        int n_weeks) override;

    WaterSource *
    generateSource(int id, vector<vector<string>> &block, int line_no,
                   int n_realizations, int n_weeks,
                   const map<string, int> &ws_name_to_id,
                   const map<string, int> &utility_name_to_id) override;

    void checkMissingOrExtraParams(int line_no,
                                   vector<vector<string>> &block) override;


};


#endif //TRIANGLEMODEL_RESERVOIRPARSER_H