#include "map.h"
#include "test_utilities.h"
#include <stdlib.h>

#define NUMBER_TESTS 12

static MapKeyElement copyKeyInt(MapKeyElement n);
static MapDataElement copyDataChar(MapDataElement n);
static void freeInt(MapKeyElement n);
static void freeChar(MapDataElement n);
static int compareInts(MapKeyElement n1, MapKeyElement n2);
static bool testMapCreateDestroy();
static bool testMapAddAndSize();
static bool testMapGet();
static bool testIterator();

/** Function to be used for copying an int as a key to the map */
static MapKeyElement copyKeyInt(MapKeyElement n)
{
	if (!n)
	{
		return NULL;
	}
	int* copy = malloc(sizeof(*copy));
	if (!copy)
	{
		return NULL;
	}
	*copy = *(int*)n;
	return copy;
}

static MapKeyElement badCopyKeyInt(MapKeyElement n)
{
	(void)n;
	return NULL;
}

/** Function to be used for copying a char as a data to the map */
static MapDataElement copyDataChar(MapDataElement n)
{
	if (!n)
	{
		return NULL;
	}
	char* copy = malloc(sizeof(*copy));
	if (!copy)
	{
		return NULL;
	}
	*copy = *(char*)n;
	return (MapDataElement)copy;
}

static MapDataElement badCopyDataChar(MapDataElement n)
{
	(void)n;
	return NULL;
}

/** Function to be used by the map for freeing elements */
static void freeInt(MapKeyElement n)
{
	free(n);
}

/** Function to be used by the map for freeing elements */
static void freeChar(MapDataElement n)
{
	free(n);
}

/** Function to be used by the map for comparing elements */
static int compareInts(MapKeyElement n1, MapKeyElement n2)
{
	int x = *(int*)n1;
	int y = *(int*)n2;
	return x - y;
}

bool testMapCreateDestroy()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	ASSERT_TEST(map != NULL);
	ASSERT_TEST(mapGetSize(map) == 0);
	ASSERT_TEST(mapGetFirst(map) == NULL);

	mapDestroy(map);

	return true;
}

bool testMapAddAndSize()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	for (int key = 1; key < 1000; ++key)
	{
		char val = (char)key;
		++val;

		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
		ASSERT_TEST(mapGetSize(map) == key);
	}

	mapDestroy(map);

	return true;
}

bool testNoMemory()
{
	Map map = mapCreate(copyDataChar, badCopyKeyInt, freeChar, freeInt, compareInts);

	for (int key = 1; key < 100; ++key)
	{
		char val = (char)key;
		++val;

		ASSERT_TEST(mapPut(map, &key, &val) == MAP_OUT_OF_MEMORY);
		ASSERT_TEST(mapGetSize(map) == 0);
	}

	mapDestroy(map);

	map = mapCreate(badCopyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	for (int key = 1; key < 100; ++key)
	{
		char val = (char)key;
		++val;

		ASSERT_TEST(mapPut(map, &key, &val) == MAP_OUT_OF_MEMORY);
		ASSERT_TEST(mapGetSize(map) == 0);
	}

	mapDestroy(map);

	return true;
}

bool testMapGet()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	for (int key = 1; key < 1000; ++key)
	{
		char val = (char)key;
		++val;

		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
		ASSERT_TEST(mapGetSize(map) == key);
	}

	for (int i = 1; i < 1000; ++i)
	{
		char j = (char)i;
		++j;
		char* getVal = (char*)mapGet(map, &i);
		ASSERT_TEST(*getVal == j);
	}

	int i = 0;
	ASSERT_TEST(mapGet(map, &i) == NULL);

	i = 1000;
	ASSERT_TEST(mapGet(map, &i) == NULL);

	mapDestroy(map);

	return true;
}

bool testIterator()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	for (int key = 1; key < 400; ++key)
	{
		char val = (char)key;
		++val;
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	for (int key = 800; key >= 400; --key)
	{
		char val = (char)key;
		++val;
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	for (int key = 801; key < 1000; ++key)
	{
		char val = (char)key;
		++val;
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	int i = 1;
	MAP_FOREACH(int*, iter, map)
	{
		ASSERT_TEST(*iter == i);
		i++;
		freeInt(iter);
	}

	i = 1;
	MAP_FOREACH(int*, iter, map)
	{
		ASSERT_TEST(*iter == i);
		i++;
		freeInt(iter);
	}

	mapDestroy(map);
	return true;
}

bool testDuplicates()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	for (int key = 0; key < 400; key++)
	{
		char val = (char)key;
		++val;
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	for (int key = 399; key >= 0; key--)
	{
		char val = (char)key;
		++val;
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	ASSERT_TEST(mapGetSize(map) == 400);

	mapDestroy(map);

	return true;
}

bool testElemVals()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	for (int key = 0; key < 400; key++)
	{
		char val = (char)(key + 1);
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	ASSERT_TEST(mapGetSize(map) == 400);

	int i = 0;
	MAP_FOREACH(int*, iter, map)
	{
		ASSERT_TEST(*(char*)mapGet(map, iter) == (char)(i + 1));
		i++;
		freeInt(iter);
	}

	for (int key = 0; key < 400; key++)
	{
		char val = (char)key;
		val += 10;
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	ASSERT_TEST(mapGetSize(map) == 400);

	i = 0;
	MAP_FOREACH(int*, iter, map)
	{
		ASSERT_TEST(*(char*)mapGet(map, iter) == (char)(i + 10));
		i++;
		freeInt(iter);
	}

	mapDestroy(map);

	return true;
}

bool testRemove()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	for (int key = 0; key < 400; key++)
	{
		char val = (char)(key + 1);
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	ASSERT_TEST(mapGetSize(map) == 400);

	for (int key = 0; key < 200; key++)
	{
		ASSERT_TEST(mapRemove(map, &key) == MAP_SUCCESS);
	}

	for (int key = 0; key < 200; key++)
	{
		ASSERT_TEST(mapRemove(map, &key) == MAP_ITEM_DOES_NOT_EXIST);
	}

	ASSERT_TEST(mapGetSize(map) == 200);

	int i = 200;
	MAP_FOREACH(int*, iter, map)
	{
		ASSERT_TEST(*(char*)mapGet(map, iter) == (char)(i + 1));
		i++;
		freeInt(iter);
	}

	mapDestroy(map);

	return true;
}

bool testClear()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	ASSERT_TEST(mapGetSize(map) == 0);

	for (int key = 0; key < 400; key++)
	{
		char val = (char)(key + 1);
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	ASSERT_TEST(mapGetSize(map) == 400);

	MAP_FOREACH(int*, iter, map)
	{
		freeInt(iter);
	}

	mapClear(map);

	ASSERT_TEST(mapGetSize(map) == 0);

	for (int key = 0; key < 300; key++)
	{
		char val = (char)(key + 1);
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	ASSERT_TEST(mapGetSize(map) == 300);

	int i = 0;
	MAP_FOREACH(int*, iter, map)
	{
		ASSERT_TEST(*(char*)mapGet(map, iter) == (char)(i + 1));
		i++;
		freeInt(iter);
	}

	mapClear(map);

	ASSERT_TEST(mapGetSize(map) == 0);

	mapDestroy(map);

	return true;
}

bool testCopy()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	for (int key = 0; key < 400; key++)
	{
		char val = (char)(key + 1);
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	ASSERT_TEST(mapGetSize(map) == 400);

	Map copy = mapCopy(map);

	ASSERT_TEST(copy != NULL);

	ASSERT_TEST(mapGetSize(copy) == 400);

	mapDestroy(map);

	int i = 0;
	MAP_FOREACH(int*, iter, copy)
	{
		ASSERT_TEST(*(char*)mapGet(copy, iter) == (char)(i + 1));
		i++;
		freeInt(iter);
	}

	Map copy2 = mapCopy(copy);

	ASSERT_TEST(copy2 != NULL);

	ASSERT_TEST(mapGetSize(copy2) == 400);

	mapDestroy(copy2);

	i = 0;
	MAP_FOREACH(int*, iter, copy)
	{
		ASSERT_TEST(*(char*)mapGet(copy, iter) == (char)(i + 1));
		i++;
		freeInt(iter);
	}

	mapDestroy(copy);

	return true;
}

bool testContains()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	for (int key = 0; key < 400; key++)
	{
		char val = (char)(key + 1);
		ASSERT_TEST(mapPut(map, &key, &val) == MAP_SUCCESS);
	}

	ASSERT_TEST(mapGetSize(map) == 400);

	for (int i = 0; i < 400; i++)
	{
		ASSERT_TEST(mapContains(map, &i) == true);
	}

	for (int i = 500; i < 600; i++)
	{
		ASSERT_TEST(mapContains(map, &i) == false);
	}

	mapDestroy(map);

	return true;
}

bool nullTests()
{
	Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, compareInts);

	int val = 1;

	ASSERT_TEST(mapCopy(NULL) == NULL);

	ASSERT_TEST(mapGetSize(NULL) == -1);

	ASSERT_TEST(mapGetSize(map) == 0);

	ASSERT_TEST(mapContains(NULL, &val) == false);

	ASSERT_TEST(mapContains(map, NULL) == false);

	ASSERT_TEST(mapPut(NULL, &val, &val) == MAP_NULL_ARGUMENT);

	ASSERT_TEST(mapPut(map, NULL, &val) == MAP_NULL_ARGUMENT);

	ASSERT_TEST(mapPut(map, &val, NULL) == MAP_NULL_ARGUMENT);

	ASSERT_TEST(mapGet(NULL, &val) == NULL);

	ASSERT_TEST(mapGet(map, NULL) == NULL);

	ASSERT_TEST(mapRemove(NULL, &val) == MAP_NULL_ARGUMENT);

	ASSERT_TEST(mapRemove(map, NULL) == MAP_NULL_ARGUMENT);

	ASSERT_TEST(mapGetFirst(NULL) == NULL);

	ASSERT_TEST(mapGetFirst(map) == NULL);

	ASSERT_TEST(mapGetNext(NULL) == NULL);

	ASSERT_TEST(mapGetNext(map) == NULL);

	ASSERT_TEST(mapClear(NULL) == MAP_NULL_ARGUMENT);

	mapDestroy(map);

	return true;
}

/*The functions for the test should be added here*/
bool (*tests[])(void) =
	{
		testMapCreateDestroy,
		testNoMemory,
		testMapAddAndSize,
		testMapGet,
		testIterator,
		testDuplicates,
		testElemVals,
		testRemove,
		testClear,
		testCopy,
		testContains,
		nullTests,
};

/*The names of the test functions should be added here*/
const char* testNames[] =
	{
		"testMapCreateDestroy",
		"testNoMemory",
		"testMapAddAndSize",
		"testMapGet",
		"testIterator",
		"testDuplicates",
		"testElemVals",
		"testRemove",
		"testClear",
		"testCopy",
		"testContains",
		"nullTests",
};

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		for (int test_idx = 0; test_idx < NUMBER_TESTS; test_idx++)
		{
			RUN_TEST(tests[test_idx], testNames[test_idx]);
		}
		return 0;
	}
	if (argc != 2)
	{
		fprintf(stdout, "Usage: <your_executable_file_name> <test index>\n");
		return 0;
	}

	int test_idx = strtol(argv[1], NULL, 10);
	if (test_idx < 1 || test_idx > NUMBER_TESTS)
	{
		fprintf(stderr, "Invalid test index %d\n", test_idx);
		return 0;
	}

	RUN_TEST(tests[test_idx - 1], testNames[test_idx - 1]);
	return 0;
}
