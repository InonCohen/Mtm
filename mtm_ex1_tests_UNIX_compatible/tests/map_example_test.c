#include "../test_utilities.h"
#include <stdlib.h>
#include "../mtm_map/map.h"

static long NumTestsPassed = 0;

static void red () {
  printf("\033[1;31m");
  fflush(stdout);
}

static void green() {
  printf("\033[0;32m");
  fflush(stdout);
}

static void purple() {
  printf("\033[0;35m");
}

static void yellow () {
  printf("\033[0;33m");
  fflush(stdout);
}

static void reset () {
  printf("\033[0m");
  fflush(stdout);
}

static void printIfSuccess(long num_tests)
{
    if (0 == NumTestsPassed)
    {
        red();
    }
    if (num_tests == NumTestsPassed)
    {
        green();
    }
    else
    {
        yellow();
    }
    
    printf("####  Summary: Passed %ld out of %ld ####\n" ,NumTestsPassed, num_tests);
    reset();
}


#define RUN_COLORFULL_TEST(test, name, id)                  \
    do {                                 \
purple();      printf("Running test# %ld %s ... ", id + 1, name);  reset(); \
      fflush(stdout); \
        if (test()) {                    \
            green();\
            printf("[OK]\n");            \
            reset();\
            ++NumTestsPassed;   \
        } else {    \
            red();\
            printf("[Failed]\n");        \
            reset();\
        }                                \
    } while (0)

/*************************************************************************/



/** Function to be used for copying an int as a key to the map */
static MapKeyElement copyKeyInt(MapKeyElement n) {
    if (!n) {
        return NULL;
    }
    int *copy = (int*)malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    *copy = *(int *) n;
    return copy;
}

/** Function to be used for copying a char as a data to the map */
static MapDataElement copyDataChar(MapDataElement n) {
    if (!n) {
        return NULL;
    }
    char *copy = (char*)malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }
    *copy = *(char *) n;
    return (MapDataElement) copy;
}

/** Function to be used by the map for freeing elements */
static void freeInt(MapKeyElement n) {
    free(n);
}

/** Function to be used by the map for freeing elements */
static void freeChar(MapDataElement n) {
    free(n);
}

/** Function to be used by the map for comparing elements */
static int compareInts(MapKeyElement n1, MapKeyElement n2) {
    return (*(int *) n1 - *(int *) n2);
}

static bool isMapSorted(Map map)
{
    bool answer = true;
   
    MapKeyElement current =  mapGetFirst(map);
    if(NULL == current)
    {
        return true; //empty map
    }
    MapKeyElement next =  mapGetNext(map);
    if (NULL == next)
    {
        freeInt(current);
        return true; //only one element == sorted
    }
    
    while (next)
    {
        if ( 0 <= compareInts(current, next))
        {
            answer = false;
            break;
        }
        freeInt(current);
        current = next;
        next = mapGetNext(map);
    }
    freeInt(current);
    freeInt(next);

    return answer;
}

/*************************************************************************/

bool testCreateNulls(){

    Map map1 = mapCreate(NULL, copyKeyInt, freeChar, freeInt, compareInts);
    ASSERT_TEST(map1 == NULL);
    Map map2 = mapCreate(copyDataChar, NULL, freeChar, freeInt, compareInts);
    ASSERT_TEST(map2 == NULL);
    Map map3 = mapCreate(copyDataChar, copyKeyInt, NULL, freeInt, compareInts);
    ASSERT_TEST(map3 == NULL);
    Map map4 = mapCreate(copyDataChar, copyKeyInt, freeChar, NULL, compareInts);
    ASSERT_TEST(map4 == NULL);
    Map map5 = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt, NULL);    
    ASSERT_TEST(map5 == NULL);

    return true;
}


bool testMapCreateDestroy() {
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    ASSERT_TEST(map != NULL);
    ASSERT_TEST(mapGetSize(map) == 0);
    ASSERT_TEST(mapGetFirst(map) == NULL);
    mapDestroy(map);
    return true;

}

bool testMapAddAndSize() {
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
        ASSERT_TEST(mapGetSize(map) == i);
    }
    mapDestroy(map);
    return true;
}

bool testMapGet() {
    int key_junk = 15;
    ASSERT_TEST(mapGet(NULL, &key_junk) == NULL);
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
        ASSERT_TEST(mapGetSize(map) == i);
    }

    ASSERT_TEST(mapGet(map, NULL) == NULL);
    key_junk = -99999;
    ASSERT_TEST(mapGet(map, &key_junk) == NULL);

    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        char *getVal = (char *) mapGet(map, &i);
        ASSERT_TEST(*getVal == j);
    }
    int i = 0;
    ASSERT_TEST(mapGet(map, &i) == NULL);
    i = 1000;
    ASSERT_TEST(mapGet(map, &i) == NULL);
    mapDestroy(map);
    return true;
}

bool testIterator() {
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);

    for (int i = 1; i < 400; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
    }
    ASSERT_TEST(mapGetSize(map) == 399);

    for (int i = 800; i >= 400; --i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
    }
    ASSERT_TEST(mapGetSize(map) == 800);

    for (int i = 801; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
    }
    ASSERT_TEST(mapGetSize(map) == 999);

    int i = 1;
    MAP_FOREACH(int *, iter, map) {
      ASSERT_TEST(*iter == i);
      freeInt(iter);
      i++;
    }

    mapDestroy(map);
    return true;
}

bool testCopy()
{
    ASSERT_TEST(mapCopy(NULL) == NULL);
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    
    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
        ASSERT_TEST(mapGetSize(map) == i);
    }

    Map map_copied = mapCopy(map);
    ASSERT_TEST(map_copied != NULL);
    mapDestroy(map);

    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        char *getVal = (char *) mapGet(map_copied, &i);
        ASSERT_TEST(*getVal == j);
    }

    mapDestroy(map_copied);
    return true;    
}


bool testRemove()
{   
    int key_junk = 15;
    ASSERT_TEST(mapRemove(NULL, &key_junk) == MAP_NULL_ARGUMENT); // fail
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);

    ASSERT_TEST(map != NULL);
    ASSERT_TEST(mapRemove(map, NULL) == MAP_NULL_ARGUMENT); //fail
    ASSERT_TEST(mapGetSize(map) == 0);
    int count = 15;
    const int diff = 111;
    int num = diff;

    char data = 0;
    for (int i = 0; i < count; i++)
    {
        ASSERT_TEST(mapPut(map, &num, &data) == MAP_SUCCESS);
        ASSERT_TEST(mapGetSize(map) == i+1);
        ++data;
        num += diff;
    }

    num -= diff;
    for (int i = 0; i < 6; i++)
    {
        ASSERT_TEST(mapContains(map, &num) == true);
        ASSERT_TEST(mapRemove(map,&num) == MAP_SUCCESS);
        ASSERT_TEST(mapRemove(map,&num) == MAP_ITEM_DOES_NOT_EXIST); //returns MAP_ITEM_ALREADY_EXISTS      
        ASSERT_TEST(mapContains(map, &num) == false);
        ASSERT_TEST(mapGetSize(map) == (--count));
        num -= (diff*2);
    }
    mapDestroy(map);
    return true;
}


bool testClear()
{
    ASSERT_TEST(mapClear(NULL) == MAP_NULL_ARGUMENT); //returns something else    
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    ASSERT_TEST(mapClear(map) == MAP_SUCCESS);
    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapPut(map, &i, &j) == MAP_SUCCESS);
        ASSERT_TEST(mapContains(map, &i) == true);
        ASSERT_TEST(mapGetSize(map) == i);
    }

    ASSERT_TEST(mapClear(map) == MAP_SUCCESS);
    ASSERT_TEST(mapGetSize(map) == 0);

    for (int i = 1; i < 1000; ++i) {
        char j = (char) i;
        ++j;
        ASSERT_TEST(mapContains(map, &i) == false);
        char *getVal = (char *) mapGet(map, &i);
        ASSERT_TEST(getVal == NULL);
    }
    mapDestroy(map);
    return true;
}

bool testGetFirstGetNext()
{
    ASSERT_TEST(mapGetFirst(NULL) == NULL);
    ASSERT_TEST(mapGetNext(NULL) == NULL);
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);

    int key[] = { 5,4,6,2,1,3};
    char data[] = "Shimon";
    for (size_t i = 0; i < sizeof(key) / sizeof(*key); i++)
    {
        ASSERT_TEST(mapPut(map, &(key[i]), &(data[i])) == MAP_SUCCESS);
    }
    
    int size = mapGetSize(map);
    ASSERT_TEST(sizeof(key) / sizeof(*key) == size);
    MapKeyElement current_key = mapGetFirst(map);
    for (int i = 0; i < size; i++)
    {
        ASSERT_TEST(current_key != NULL);
        ASSERT_TEST(*(int*)current_key ==i+1);
        freeInt(current_key);
        current_key = mapGetNext(map);
    }
    ASSERT_TEST(current_key == NULL);

    mapDestroy(map);

    return true;
}

bool testContains()
{
    int key_junk = 15;
    ASSERT_TEST(mapContains(NULL, &key_junk) == false);
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    ASSERT_TEST(map!=NULL);
    ASSERT_TEST(mapContains(map, NULL) == false);
    int key1 = 9999;
    int key2 = 1111;
    char data = 'a';
    ASSERT_TEST(mapGetSize(map) == 0);
    ASSERT_TEST(mapPut(map, &key1, &data) == MAP_SUCCESS);

    ASSERT_TEST(mapContains(NULL, &key1) == false);
    ASSERT_TEST(mapContains(map, &key1) == true);
    ASSERT_TEST(mapContains(map, &key2) == false);
    ASSERT_TEST(mapContains(map, &key1) == true);
    ASSERT_TEST(mapGetSize(map) == 1);
    ASSERT_TEST(mapPut(map, &key2, &data) == MAP_SUCCESS);
    
    ASSERT_TEST(mapPut(map, &key1, &data) == MAP_SUCCESS);

    ASSERT_TEST(mapContains(map, &key2) == true);
    ASSERT_TEST(mapContains(map, &key1) == true);
    ASSERT_TEST(mapGetSize(map) == 2);


    mapDestroy(map);
    return true;
}
static bool testArray(Map map, int *array, int size)
{
    int i=0;
    char data = 'a';
    for(i=0; i < size; ++i)
    {
        ASSERT_TEST(mapPut(map, &array[i], &data) == MAP_SUCCESS);
        ASSERT_TEST(isMapSorted(map));
        ASSERT_TEST(mapGetSize(map) == i+1);
    }

    for(int j=0; j < size; ++j)
    {    
        ASSERT_TEST(mapGetSize(map) == (i--));
        ASSERT_TEST(mapRemove(map, &array[j]) == MAP_SUCCESS);
        ASSERT_TEST(isMapSorted(map));
        if(j%2 == 0)
        {
            ASSERT_TEST(mapRemove(map, &array[j]) == MAP_ITEM_DOES_NOT_EXIST);
            ASSERT_TEST(isMapSorted(map));
        }
    }
    ASSERT_TEST(mapGetSize(map) == 0);

    return true;
}

static bool testSorting()
{
    Map map = mapCreate(copyDataChar, copyKeyInt, freeChar, freeInt,
                        compareInts);
    ASSERT_TEST(map != NULL);

    ASSERT_TEST(isMapSorted(map));
    ASSERT_TEST(mapGetSize(map) == 0);
    int array[] = {59851,	233929,	50239,	150537,	58116,	125686,	21076,
    	-19695,	82012,	-95805,	113199,	280062,	154924,	-123570,	54332,
        	250160,	-132003,162055,	148045,	-101495,	219050,	212345,	20051,
            	287858,	-11299,	198464,	-83981,	293604,	-12157,	69071,	-99592};

    int array2[] ={524,	43,	54,	151,	810	,195,	-90,	773,	
            108, 11	,411,	60,	893,	842,	880,	543,	
            -33,	246,	370,	863,	818,	663,	839	,-26};

    int array3[] ={-751603,	-205814,	-529717,	-656686,
    	-403893,	-813204,	-598182,	-215233,	-764703,	-17568,
        	-301040,	-355594,	-499273,	-47162,	-472360,	-96429,	-83309,	-110612,};

    int array4[] ={ 12207,	63338,	5015,	81022,	88005,	
            81506,	12845,	65456,	4710,	80526,	95625,	90617,	-260400};


    ASSERT_TEST(testArray(map, array, (int)(sizeof(array)/sizeof(array[0]))));
    ASSERT_TEST(testArray(map, array2, (int)(sizeof(array2)/sizeof(array2[0]))));
    ASSERT_TEST(testArray(map, array3, (int)(sizeof(array3)/sizeof(array3[0]))));
    ASSERT_TEST(testArray(map, array4, (int)(sizeof(array4)/sizeof(array4[0]))));

    mapDestroy(map);
    return true;
}

/*The functions for the tests should be added here*/
bool (*tests[]) (void) = {
        testCreateNulls,
        testMapCreateDestroy,
        testMapAddAndSize,
        testMapGet,
        testIterator,
        testCopy,
        testRemove,
        testClear,
        testGetFirstGetNext,
        testContains,
        testSorting,
};

#define NUMBER_TESTS ((long)(sizeof(tests)/sizeof(*tests)))

/*The names of the test functions should be added here*/

const char* testNames[NUMBER_TESTS] = {
        "testCreateNulls",
        "testMapCreateDestroy",
        "testMapAddAndSize",
        "testMapGet",
        "testIterator",
        "testCopy",
        "testRemove",
        "testClear",
        "testGetFirstGetNext",
        "testContains",
        "testSorting",
};



int main(int argc, char *argv[]) 
{
    if (argc == 1)
    {
        fprintf(stdout, "Running %ld tests:\n", NUMBER_TESTS);
        for (long test_idx = 0; test_idx < NUMBER_TESTS; test_idx++)
        {
            RUN_COLORFULL_TEST(tests[test_idx], testNames[test_idx], test_idx);
        }
        printIfSuccess(NUMBER_TESTS);
        return 0;
    }

    if (argc != 2) 
    {
        fprintf(stdout, "Usage: chessSystem <test index>\n");
        return 0;
    }

    long test_idx = strtol(argv[1], NULL, 10);
    if (test_idx < 1 || test_idx > NUMBER_TESTS) 
    {
        fprintf(stderr, "Invalid test index %ld\n", test_idx);
        return 0;
    }

    RUN_COLORFULL_TEST(tests[test_idx - 1], testNames[test_idx - 1], test_idx - 1);
    return 0;
}

