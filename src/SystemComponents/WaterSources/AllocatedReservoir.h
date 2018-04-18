//
// Created by bernardoct on 7/9/17.
//

#ifndef TRIANGLEMODEL_ALLOCATEDRESERVOIR_H
#define TRIANGLEMODEL_ALLOCATEDRESERVOIR_H


#include "Reservoir.h"
#include "../../Controls/AllocationModifier.h"

class AllocatedReservoir : public Reservoir {
protected:

    AllocationModifier *allocation_modifier;
    bool modified_allocations;
    const bool has_water_quality_pool;

public:
    AllocatedReservoir(
            const char *name, const int id,
            const vector<Catchment *> &catchments, const double capacity,
            const double max_treatment_capacity,
            EvaporationSeries &evaporation_series,
            DataSeries *storage_area_curve,
            vector<int> *utilities_with_allocations,
            vector<double> *allocated_fractions, vector<double>
            *allocated_treatment_fractions);

    AllocatedReservoir(const char *name, const int id, const vector<Catchment *> &catchments,
                           const double capacity, const double max_treatment_capacity,
                           EvaporationSeries &evaporation_series, DataSeries *storage_area_curve,
                           const vector<double> &construction_time_range, double construction_cost,
                           vector<int> *utilities_with_allocations, vector<double> *allocated_fractions,
                           vector<double> *allocated_treatment_fractions);

    AllocatedReservoir(
            const char *name, const int id,
            const vector<Catchment *> &catchments, const double capacity,
            const double max_treatment_capacity,
            EvaporationSeries &evaporation_series, double storage_area,
            vector<int> *utilities_with_allocations,
            vector<double> *allocated_fractions, vector<double>
            *allocated_treatment_fractions);

    AllocatedReservoir(const char *name, const int id, const vector<Catchment *> &catchments,
                           const double capacity, const double max_treatment_capacity,
                           EvaporationSeries &evaporation_series, double storage_area,
                           const vector<double> &construction_time_range, double construction_cost,
                           vector<int> *utilities_with_allocations, vector<double> *allocated_fractions,
                           vector<double> *allocated_treatment_fractions);
    AllocatedReservoir(
            const char *name,
            const int id,
            const vector<Catchment *> &catchments,
            const double capacity,
            const double max_treatment_capacity,
            EvaporationSeries &evaporation_series,
            double storage_area,
            vector<int> *utilities_with_allocations,
            vector<double> *allocated_fractions,
            vector<double> *allocated_treatment_fractions,
            AllocationModifier *allocation_modifier);

    AllocatedReservoir(
            const char *name, const int id,
            const vector<Catchment *> &catchments, const double capacity,
            const double max_treatment_capacity,
            EvaporationSeries &evaporation_series, DataSeries *storage_area_curve,
            const vector<double> &construction_time_range,
            double construction_cost,
            vector<int> *utilities_with_allocations,
            vector<double> *allocated_fractions, vector<double>
            *allocated_treatment_fractions,
            AllocationModifier *allocation_modifier);

    AllocatedReservoir &operator=(
            const AllocatedReservoir
            &allocated_reservoir);

    AllocatedReservoir(const AllocatedReservoir &allocated_reservoir);

    ~AllocatedReservoir();

    void applyContinuity(int week, double upstream_source_inflow,
                             double wastewater_inflow,
                             vector<double> &demand_outflow) override;

    void setFull() override;

    double getAvailableAllocatedVolume(int utility_id) override;

    void removeWater(int allocation_id, double volume) override;

    void addWater(int allocation_id, double volume) override;

    double getAllocatedCapacity(int utility_id) override;

    double getAllocatedFraction(int utility_id) override;

    void addCapacity(double capacity) override;

    void addTreatmentCapacity(const double added_plant_treatment_capacity, int utility_id)
    override;

    double getAllocatedTreatmentCapacity(int utility_id) const override;

    double getSupplyAllocatedFraction(int utility_id) override;

    void updateTreatmentAndCapacityAllocations(int week) override;

    bool
    mass_balance_with_wq_pool(double net_inflow, vector<double> &demand_outflow);

    bool
    mass_balance_without_wq_pool(double net_inflow, vector<double> &demand_outflow);

    void addAllocatedTreatmentCapacity(const double added_allocated_treatment_capacity, int utility_id) override;
};


#endif //TRIANGLEMODEL_ALLOCATEDRESERVOIR_H
