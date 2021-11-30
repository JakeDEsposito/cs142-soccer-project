#include <map>
#include <vector>

#include "player.h"

class LedgeFilter
{
public:
    LedgeFilter(int birth_year = 0, int category = 0, bool registration = 0): yob(birth_year), cat(category), reg(registration) {};
    enum Filter { birth_year, category, registration };

    int getFilter(Filter filter);
    void setFilter(Filter filter, int new_val);

    int & operator [](Filter filter);

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