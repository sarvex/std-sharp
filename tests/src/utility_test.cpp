#include "utility_test.h"
#include "utility/utility.h"

namespace blurringshadow::test::utility
{
    boost::ut::suite& utility_test()
    {
        static boost::ut::suite suite{[] {}};
        return suite;
    }
}
