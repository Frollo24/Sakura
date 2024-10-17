#pragma once

#define SKR_BIT(x) (1 << x)

#define SKR_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define SKR_DEFINE_ENUM_FLAG_OPERATORS(enumtype) \
extern "C++" { \
inline constexpr enumtype operator | (enumtype a, enumtype b) noexcept { return enumtype(((int)a) | ((int)b)); } \
inline enumtype &operator |= (enumtype &a, enumtype b) noexcept { return (enumtype &)(((int &)a) |= ((int)b)); } \
inline constexpr enumtype operator & (enumtype a, enumtype b) noexcept { return enumtype(((int)a) & ((int)b)); } \
inline enumtype &operator &= (enumtype &a, enumtype b) noexcept { return (enumtype &)(((int &)a) &= ((int)b)); } \
inline constexpr enumtype operator ^ (enumtype a, enumtype b) noexcept { return enumtype(((int)a) ^ ((int)b)); } \
inline enumtype &operator ^= (enumtype &a, enumtype b) noexcept { return (enumtype &)(((int &)a) ^= ((int)b)); } \
inline constexpr enumtype operator ~ (enumtype a) noexcept { return enumtype(~((int)a)); } \
}
