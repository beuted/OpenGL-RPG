// Source : http://frouin.me/recherche-de-fuites-memoire-en-cpp/

#ifdef LEAKS
 
#ifndef _LEAK_DETECTOR_H_
#define _LEAK_DETECTOR_H_
 
#include "memory_manager.h"
 
/*extern */CMemoryManager g_mm;

/*!
 * @brief new operator surcharge
 */
inline void* operator new(std::size_t Size, const char* File, int Line)
{
  return g_mm.Allocate(Size, File, Line, false);
}
 
/*!
 * @brief new[] operator surcharge
 */
inline void* operator new[](std::size_t Size, const char* File, int Line)
{
  return g_mm.Allocate(Size, File, Line, true);
}
 
/*!
 * @brief delete operator surcharge
 */
inline void operator delete(void* Ptr) throw ()
{
  g_mm.Free(Ptr, false);
}
 
/*!
 * @brief delete[] operator surcharge
 */
inline void operator delete(void* Ptr, const char* File, int Line)
{
  g_mm.NextDelete(File, Line);
  g_mm.Free(Ptr, false);
}
 
inline void operator delete[](void* Ptr) throw ()
{
  g_mm.Free(Ptr, true);
}
 
inline void operator delete[](void* Ptr, const char* File, int Line)
{
  g_mm.NextDelete(File, Line);
  g_mm.Free(Ptr, true);
}
#endif // _LEAK_DETECTOR_H__

#undef delete
 
#ifndef new
#define new    new(__FILE__, __LINE__)
#define delete g_mm.NextDelete(__FILE__, __LINE__), delete
#endif

#endif // LEAKS

