/* Replace "dll.h" with the name of your header */
#include "pseudooop.h"
#include <stdio.h>
#include <windows.h>
#include <memory.h>

typedef struct class_object_t
{
	Type*(*GetType)(Object* object);
	void (*Dispose)(Object* object);
} Object;

typedef struct class_type_t
{
	Object Base;
	long Identifier;
	Type*(*GetBaseType)(Type* type);
	long BaseTypeID;
} Type;

Type* TypeofObject;
Object* StaticObject;
Type* TypeofType;

Type* typeof_Object()
{
	return TypeofObject;
}

Type* typeof_Type()
{
	return TypeofType;
}

Type* Object_GetType(Object* object)
{
	return object->GetType(object);
}

Type* object_GetType(Object* object)
{
	return TypeofObject;
}

void object_Dispose(Object* object)
{
	free(object);
}

Type* type_GetType(Object* object)
{
	return TypeofType;
}

void Object_sctor()
{
	static BOOL inited = FALSE;
	if (!inited)
	{
		inited = TRUE;
		TypeofObject = Type_new();
		TypeofType = Type_new();
		StaticObject = Object_new();
	}
}

int static_type_ident = 1;

Type* Type_new()
{
	Type* ret = calloc(1, sizeof(Type));
	ret->Identifier = static_type_ident++;
	ret->Base.GetType = &type_GetType;
	ret->BaseTypeID = 1;
	return ret;
}

Object*	Object_new()
{
	Object_sctor();
	Object* ret = calloc(1, sizeof(Object));
	ret->GetType = &object_GetType;
	ret->Dispose = &object_Dispose;
	return ret;
}

void Object_Dispose(Object* object)
{
	object->Dispose(object);
}

int Object_Is(Object* object, Type* type)
{
	Type* t = Object_GetType(object);
	int cur = t->Identifier;
	if (cur == type->Identifier) return TRUE;
	while (cur != 1)
	{
		t = t->GetBaseType(t);
		cur = t->Identifier;
		if (cur == type->Identifier) return TRUE;
	}
	return FALSE;
}

/* class T */

typedef struct T_t
{
	Object Base;
	int intfield;
} T;

Type* TypeofT;

void T_sctor()
{
	static BOOL inited = FALSE;
	if (!inited)
	{
		inited = TRUE;
		TypeofT = Type_new();
		TypeofT->BaseTypeID = TypeofObject->Identifier;
		TypeofT->GetBaseType = &object_GetType;
	}
}

Type* t_GetType(Object* object)
{
	return TypeofT;
}

T* T_new()
{
	T_sctor();
	T* ret = calloc(1, sizeof(T));
	ret->Base.GetType = &t_GetType;
	ret->Base.Dispose = &object_Dispose;
	return ret;
}

void main()
{
	Object* o = Object_new();
	T* t = T_new();
	printf("%i ", Object_Is(o, t_GetType(t)));
}
























