#ifndef _PSEUDOOOP_H_
#define _PSEUDOOOP_H_

#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

struct class_object_t;
struct class_type_t;
DLLIMPORT typedef struct class_object_t Object;
DLLIMPORT typedef struct class_type_t Type;

DLLIMPORT Type* typeof_Object();
DLLIMPORT Type* typeof_Type();

DLLIMPORT Type*		Object_GetType(Object* object);
DLLIMPORT Object*	Object_new();
DLLIMPORT void 		Object_Dispose(Object* object);
DLLIMPORT int		Object_Is(Object* object, Type* type);

//use only in static constructors!!
DLLIMPORT Type* Type_new();
DLLIMPORT Type* Type_GetBaseType(Type* type);


#endif
