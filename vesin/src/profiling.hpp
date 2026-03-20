#ifndef VESIN_PROFILING_HPP
#define VESIN_PROFILING_HPP

#ifdef VESIN_TORCH_PROFILER
#include <ATen/record_function.h>
#endif

namespace vesin::profiling {

class UserScope {
public:
    explicit UserScope(const char* name) {
#ifdef VESIN_TORCH_PROFILER
        guard_.before(name);
#else
        (void)name;
#endif
    }

private:
#ifdef VESIN_TORCH_PROFILER
    at::RecordFunction guard_{at::RecordScope::USER_SCOPE};
#endif
};

} // namespace vesin::profiling

#define VESIN_PROFILE_CONCAT_IMPL(a, b) a##b
#define VESIN_PROFILE_CONCAT(a, b) VESIN_PROFILE_CONCAT_IMPL(a, b)
#define VESIN_PROFILE_SCOPE(name) \
    ::vesin::profiling::UserScope VESIN_PROFILE_CONCAT(vesin_profile_scope_, __LINE__)(name)

#endif
