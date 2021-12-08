#include <map>
#include <vector>

#include "player.h"

class LedgeFilter
{
public:
    // Default constructor that can take in values for yob, category, and regStat filtering. Leave variable as 0 to have the filter not be set.
    LedgeFilter(int birth_year = 0, int category = 0, bool registration = 0): yob(birth_year), cat(category), reg(registration) {};

    // enum for using the filters.
    enum Filter { birth_year, category, registration };

    // returns the value of the given filter.
    int getFilter(Filter filter);

    // takes in a filter to set and a value to set it to.
    void setFilter(Filter filter, int new_val);

    // returns the value of the given filter.
    int & operator [](Filter filter);

    // returns a vector of the current filters that have a value set for them (have a filter set to 0 is the equivalent of the filter being off).
    std::vector<Filter> getCurrentFiltersInUse();

private:
    int yob, cat, reg;
    std::map<Filter, int> currentFilters
    {
        {birth_year, yob},
        {category, cat},
        {registration, reg}
    };
};
