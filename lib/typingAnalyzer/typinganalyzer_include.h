#pragma once 
#if(SHARED)
#define TP_EXPORT  Q_DECL_EXPORT
#else
#define TP_EXPORT  Q_DECL_IMPORT
#endif
