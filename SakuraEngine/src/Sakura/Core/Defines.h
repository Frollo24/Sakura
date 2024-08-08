#pragma once

#define SKR_BIT(x) (1 << x)

#define SKR_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }