// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the BUILD_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// BUILD_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef BUILD_EXPORTS
#define BUILD_API __declspec(dllexport)
#else
#define BUILD_API __declspec(dllimport)
#endif

// This class is exported from the dll
class BUILD_API Cbuild {
public:
	Cbuild(void);
	// TODO: add your methods here.
};

extern BUILD_API int nbuild;

BUILD_API int fnbuild(void);
