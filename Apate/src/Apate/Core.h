#pragma once

#define AP_DYNAMIC_LINK 0

#ifdef AP_PLATFORM_WINDOWS
	#if (AP_DYNAMIC_LINK == 1)
		#ifdef AP_BUILD_DLL
			#define APATE_API __declspec(dllexport)
		#else
			#define APATE_API __declspec(dllimport)
		#endif
	#else
		#define APATE_API
	#endif
#else
	#error APATE only support Windows!
#endif

#ifdef AP_DEBUG
	#define AP_ENABLE_ASSERT
#endif

#ifdef AP_ENABLE_ASSERT
	#define AP_ASSERT(x, ...) {if(!(x)) {AP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define AP_CORE_ASSERT(x, ...) {if(!(x)) {AP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define AP_ASSERT(x, ...) 
	#define AP_CORE_ASSERT(x, ...)
#endif // AP_ENABLE_ASSERT

#define BIT(x) (1 << x)

#define AP_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
