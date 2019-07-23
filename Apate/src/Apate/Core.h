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