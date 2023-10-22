#pragma once

// Virtual function invoker lifted from https://github.com/komashchenko/MiniVIP
template <typename T, int index, typename ...Args>
constexpr T CallVFunc(void* pThis, Args... args) noexcept
{
	return reinterpret_cast<T(*)(void*, Args...)> (reinterpret_cast<void***>(pThis)[0][index])(pThis, args...);
}

#include <sstream>
#include <string>

inline std::string AddrToString(void* address) {
	std::stringstream ss;
	ss << address;
	return ss.str();
}

#include <memory>

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> NewRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}