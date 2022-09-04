/************************************************************************
 * Parable, a little smalltalk
 *
 * This code is gifted to the public domain. Share freely.
 ************************************************************************/
/*
	New object creation routines built on top of memory allocation, these
 	routines handle the creation of various kinds of objects
 */

#include <stdio.h>
#include "env.h"
#include "memory.h"
#include "names.h"

static object arrayClass = nilobj; /* the class Array */
static object intClass = nilobj; /* the class Integer */
static object stringClass = nilobj; /* the class String */
static object symbolClass = nilobj; /* the class Symbol */

void ncopy(char *p,char *q, int n) { /* ncopy - copy exactly n bytes from place to place */
	for (; n > 0; n--)
		*p++ = *q++;
}

object getClass(object obj) { /* getClass - get the class of an object */

	if (isInteger(obj)) {
		if (intClass == nilobj)
			intClass = globalSymbol("Integer");

		return (intClass);
	}
	
	return (classField(obj));
}

object newArray( int size) {

	object newObj;
	newObj = allocObject(size);

	if (arrayClass == nilobj)
		arrayClass = globalSymbol("Array");

	setClass(newObj, arrayClass);
	return newObj;
}

object newBlock() {

	object newObj;
	newObj = allocObject(blockSize);
	setClass(newObj, globalSymbol("Block"));
	return newObj;
}

object newByteArray(int size) {

	object newobj;
	newobj = allocByte(size);
	setClass(newobj, globalSymbol("ByteArray"));
	return newobj;
}

object newChar(int value) {

	object newobj;
	newobj = allocObject(1);
	basicAtPut(newobj, 1, newInteger(value));
	setClass(newobj, globalSymbol("Char"));
	return (newobj);
}

object newClass(char *name) {

	object newObj, nameObj;
	newObj = allocObject(classSize);
	setClass(newObj, globalSymbol("Class"));

	/* now make name */
	nameObj = newSymbol(name);
	basicAtPut(newObj, nameInClass, nameObj);

	/* now put in global symbols table */
	nameTableInsert(symbols, strHash(name), nameObj, newObj);
	return newObj;
}

object copyFrom(object obj,int start,int size) {

	object newObj;
	int i;
	newObj = newArray(size);

	for (i = 1; i <= size; i++) {
		basicAtPut(newObj, i, basicAt(obj, start));
		start++;
	}

	return newObj;
}

object newContext(int link,object method,object args,object temp) {

	object newObj;
	newObj = allocObject(contextSize);
	setClass(newObj, globalSymbol("Context"));
	basicAtPut(newObj, linkPtrInContext, newInteger(link));
	basicAtPut(newObj, methodInContext, method);
	basicAtPut(newObj, argumentsInContext, args);
	basicAtPut(newObj, temporariesInContext, temp);
	return newObj;
}

object newDictionary(int size) {

	object newObj;
	newObj = allocObject(1);
	setClass(newObj, globalSymbol("Dictionary"));
	basicAtPut(newObj, 1, newArray(size));
	return newObj;
}

object newFloat(double d) {

	object newObj;
	newObj = allocByte((int)sizeof(double));
	ncopy(charPtr(newObj), (char *)&d, (int)sizeof(double));
	setClass(newObj, globalSymbol("Float"));
	return newObj;
}

double floatValue(object o) {

	double d;
	ncopy((char *)&d, charPtr(o), (int)sizeof(double));
	return d;
}

object newLink(object key, object value) {

	object newObj;
	newObj = allocObject(3);
	setClass(newObj, globalSymbol("Link"));
	basicAtPut(newObj, 1, key);
	basicAtPut(newObj, 2, value);
	return newObj;
}

object newMethod() {
	object newObj;
	newObj = allocObject(methodSize);
	setClass(newObj, globalSymbol("Method"));
	return newObj;
}

object newStString(char *value) {

	object newObj;
	newObj = allocStr(value);

	if (stringClass == nilobj)
		stringClass = globalSymbol("String");

	setClass(newObj, stringClass);
	return (newObj);
}

object newSymbol(char *str) {

	object newObj;

	/* first see if it is already there */
	newObj = globalKey(str);

	if (newObj)
		return newObj;

	/* not found, must make */
	newObj = allocStr(str);

	if (symbolClass == nilobj){
		symbolClass = globalSymbol("Symbol");
	}

	setClass(newObj, symbolClass);
	nameTableInsert(symbols, strHash(str), newObj, nilobj);
	return newObj;
}
