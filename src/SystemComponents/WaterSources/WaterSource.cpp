//
// Created by bernardo on 1/22/17.
//

#include <iostream>
#include "WaterSource.h"

using namespace std;

/**
 * Constructor for when water source is built and operational.
 * @param source_name
 * @param id
 * @param min_environmental_outflow
 * @param catchments
 * @param capacity
 * @param max_treatment_capacity
 * @param source_type
 */
WaterSource::WaterSource(const string &source_name, const int id, const double min_environmental_outflow,
                         const vector<Catchment *> &catchments, const double capacity,
                         const double max_treatment_capacity, const int source_type)
        : name(source_name), capacity(capacity), min_environmental_outflow(min_environmental_outflow),
          total_outflow(min_environmental_outflow), catchments(catchments), online(ONLINE), available_volume(capacity),
          id(id), max_treatment_capacity(max_treatment_capacity), source_type(source_type),
          construction_rof(NON_INITIALIZED), construction_time(NON_INITIALIZED), construction_price(NON_INITIALIZED) {}

/**
 * Constructor for when water source does not exist in the beginning of the simulation.
 * @param source_name
 * @param id
 * @param min_environmental_outflow
 * @param catchments
 * @param capacity
 * @param max_treatment_capacity
 * @param source_type
 * @param construction_rof
 * @param construction_time_range
 * @param construction_price
 */
WaterSource::WaterSource(const string &source_name, const int id, const double min_environmental_outflow,
                         const vector<Catchment *> &catchments, const double capacity,
                         const double max_treatment_capacity, const int source_type, const double construction_rof,
                         const vector<double> construction_time_range, double construction_price)
        : name(source_name), capacity(capacity), min_environmental_outflow(min_environmental_outflow),
          total_outflow(min_environmental_outflow), catchments(catchments), online(OFFLINE), available_volume(capacity),
          id(id), max_treatment_capacity(max_treatment_capacity), source_type(source_type),
          construction_rof(construction_rof),
          construction_time(construction_time_range[0] * WEEKS_IN_YEAR +
                                    construction_time_range[0] * (rand() % (int) WEEKS_IN_YEAR)),
          construction_price(construction_price) {}

/**
 * Copy constructor.
 * @param water_source
 */
WaterSource::WaterSource(const WaterSource &water_source) : capacity(water_source.capacity),
                                                            name(water_source.name),
                                                            min_environmental_outflow(
                                                                    water_source.min_environmental_outflow),
                                                            id(water_source.id),
                                                            available_volume(water_source.available_volume),
                                                            total_outflow(water_source.total_outflow),
                                                            online(water_source.online),
                                                            source_type(water_source.source_type),
                                                            upstream_min_env_inflow(
                                                                    water_source.upstream_min_env_inflow),
                                                            upstream_catchment_inflow(
                                                                    water_source.upstream_catchment_inflow),
                                                            max_treatment_capacity(
                                                                    water_source.max_treatment_capacity),
                                                            construction_rof(water_source.construction_rof),
                                                            construction_time(
                                                                    water_source.construction_time),
                                                            construction_price(water_source.construction_price) {
    catchments.clear();
    for (Catchment *c : water_source.catchments) {
        catchments.push_back(new Catchment(*c));
    }
}

/**
 * Destructor.
 */
WaterSource::~WaterSource() {
//    catchments.clear();
}

/**
 * Copy assignment operator.
 * @param water_source
 * @return
 */
WaterSource &WaterSource::operator=(const WaterSource &water_source) {

    catchments.clear();
    for (Catchment *c : water_source.catchments) {
        catchments.push_back(new Catchment(*c));
    }

    return *this;
}

/**
 * Sorting by id compare operator.
 * @param other
 * @return
 */
bool WaterSource::operator<(const WaterSource *other) {
    return id < other->id;
}

/**
 * Applies continuity to the water source.
 * @param week
 * @param upstream_source_inflow Total inflow released from the upstream water source, excluding water for the
 * catchment between both water sources.
 * @param demand_outflow demand from utility.
 */
void WaterSource::continuityWaterSource(int week, double upstream_source_inflow, double demand_outflow) {
    if (online)
        applyContinuity(week, upstream_source_inflow, demand_outflow);
    else
        bypass(week, upstream_source_inflow);
}

/**
 * Does not apply continuity to the water source, by instead just treats it as non existing,
 * i.e. outflow = inflow + catchment_flow
 * @param week
 * @param upstream_source_inflow Total inflow released from the upstream water source, excluding water for the
 * catchment between both water sources.
 */
void WaterSource::bypass(int week, double upstream_source_inflow) {

    upstream_catchment_inflow = 0;
    for (Catchment *c : catchments) {
        upstream_catchment_inflow += c->getStreamflow((week));
    }

    demand = NONE;
    available_volume = NONE;
    total_outflow = upstream_catchment_inflow + upstream_source_inflow;
    this->upstream_source_inflow = upstream_source_inflow;
}

double WaterSource::getAvailable_volume() const {
    return available_volume;
}

bool WaterSource::isOnline() const {
    return online;
}

void WaterSource::setAvailable_volume(double available_volume) {
    WaterSource::available_volume = available_volume;
}

void WaterSource::setOutflow_previous_week(double outflow_previous_week) {
    WaterSource::total_outflow = outflow_previous_week;
}

void WaterSource::setOnline() {
    online = ONLINE;
}

double WaterSource::getTotal_outflow() const {
    return total_outflow;
}

double WaterSource::getCapacity() {
    return capacity;
}

double WaterSource::getDemand() const {
    return demand;
}

double WaterSource::getUpstream_source_inflow() const {
    return upstream_source_inflow;
}

double WaterSource::getCatchment_upstream_catchment_inflow() const {
    return upstream_catchment_inflow;
}
