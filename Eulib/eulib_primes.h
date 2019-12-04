#pragma once

#include <vector>
#include <functional>

namespace eulib {
	std::vector<int64_t> getPrimes(std::function<bool(const std::vector<int64_t>&)> stopCondition);
}