//
// Created by Felix Sittenauer on 13.10.16.
//

#ifndef BERRYCOPTER_MEASUREFILTER_H
#define BERRYCOPTER_MEASUREFILTER_H

class MeasureFilter {
public:
    MeasureFilter();
    virtual ~MeasureFilter() {}

    virtual void applyFilter(double measuredValue, double dt) {}
};

#endif //BERRYCOPTER_MEASUREFILTER_H
