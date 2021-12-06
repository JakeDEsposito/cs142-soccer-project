#include "ledgefilter.h"

int LedgeFilter::getFilter(Filter filter)
{
    return currentFilters[filter];
};

void LedgeFilter::setFilter(Filter filter, int new_val)
{
    currentFilters[filter] = new_val;
};

int & LedgeFilter::operator [](Filter filter)
{
    return currentFilters[filter];
};

std::vector<LedgeFilter::Filter> LedgeFilter::getCurrentFiltersInUse()
{
    std::vector<Filter> result;
    for(auto i = currentFilters.begin(); i != currentFilters.end(); i++)
        if(i->second)
            result.push_back(i->first);
    return result;
};