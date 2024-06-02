#pragma once 
#if defined(SHARED)
#define TP_EXPORT __declspec(dllexport)
#else
#define TP_EXPORT __declspec(dllimport)
#endif
