#include <exception>

#include "utility_test.h"
#include "algorithm_test.h"
#include "traits/value_sequence_test.h"

using namespace blurringshadow::test::utility;

int main()
{
    algorithm_test();
    traits::sequence_test();
}
