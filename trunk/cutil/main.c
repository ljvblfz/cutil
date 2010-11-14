#include    <stdio.h>
#include <time.h>

#include    "CUtil.h"

#define TEST_HASHTABLE                          0
#define TEST_HASHMAP                          0
#define TEST_ARRAYLIST                       0
#define TEST_QUEUE                              0
#define TEST_STACK                                0
#define TEST_STRING                               0
#define TEST_STRINGBUFFER                1
#define TEST_STRINGBUILDER              1
#define TEST_VECTOR                              0

#define TEST_LINKEDLIST                       0
#define TEST_LINKEDQUEUE                  0
#define TEST_LINKEDSTACK                  0
#define TEST_MEMORY                            0

#if TEST_MEMORY||USECMEMORY
#include    "CMemory.h"
#endif

#if TEST_HASHMAP
    #include    "HashMap.h"
#endif

#if TEST_HASHTABLE
    #include    "HashTable.h"  
#endif

#if TEST_ARRAYLIST
    #include    "ArrayList.h"
#endif

#if TEST_VECTOR
    #include    "Vector.h"
#endif

#if TEST_QUEUE
    #include    "Queue.h"
#endif

#if TEST_LINKEDQUEUE
#include    "LinkedQueue.h"
#endif

#if TEST_STACK
    #include    "Stack.h"
#endif

#if TEST_LINKEDSTACK
#include    "LinkedStack.h"
#endif

#if TEST_STRING
    #include    "CString.h"
#endif

#if TEST_STRINGBUFFER
    #include    "StringBuffer.h"
#endif

#if TEST_STRINGBUILDER
    #include    "StringBuilder.h"
#endif

#if TEST_LINKEDLIST
    #include    "LinkedList.h"
#endif


#if TEST_MEMORY
#define MEMORYLENGTH    15000

void testMemory()
{
    INT i = 0;
    BYTE* test[MEMORYLENGTH] = {NULL};
    clock_t start = 0;
    clock_t end = 0;

#if 0
    for (i=0; i<10; i++)
    {
        test[i] = get_ub(15);
        printf("get ub size: %d, address:%p\n", 15, test[i]);
    }


    for (i=0; i<10; i++)
    {
        printf("ret ub address:%p\n", test[i]);
        ret_ub(test[i]);
    }
#endif   
#if 1

    start = clock();
    for (i=0; i<MEMORYLENGTH; i++)
    {
        test[i] = balloc(16);
    }


    for (i=0; i<MEMORYLENGTH; i++)
    {
        bfree(test[i]);
    }
    end = clock();

    printf("memory pool used time:%ld\n", end-start);
#endif

#if 0

    start = clock();
    for (i=0; i<MEMORYLENGTH; i++)
    {
        test[i] = (BYTE*)malloc(16);
    }


    for (i=0; i<MEMORYLENGTH; i++)
    {
        free(test[i]);
    }
    end = clock();

    printf("malloc used time:%ld\n", end-start);
#endif

}
#endif


#if TEST_HASHMAP
void testHashMap()
{
    CHAR *testObject = "This is a object test.";
    HashMap map = newHashMap(8, 0);
    HashMap newMap = NULL;

    map->putByte(map, "byte", 20);
    map->putChar(map, "char", 'C');
    map->putShort(map, "short", 128);
    map->putInt(map, "int", -123);
    map->putUint(map, "uint", 234);
    map->putLong(map, "long", -12345);
    map->putUlong(map, "ulong", 34567);
    map->putFloat(map, "float", -123.34f);
    map->putDouble(map, "double", 545.23);
    map->putString(map, "string", "string test");
    map->putObject(map, "object", testObject);


    map->putString(map, "123ad12", "This is a test.");
    map->putString(map, "25622", "222 test.");
    map->putString(map, "38a7322", "333 test."); //conflict
    map->putString(map, "44094", "444 test.");
    map->putString(map, "5555", "555 test.");
    map->putString(map, "64566", "666 test.");


    printf("capacity: %d\n", map->getCapacity(map));
    printf("size: %d\n", map->getSize(map));

    printf("get byte: %d\n", *(BYTE *)map->get(map, "byte"));
    printf("get double: %f\n", *(DOUBLE *)map->get(map, "double"));
    printf("get null: %d\n", (map->get(map, "11") == NULL));
    printf("get object: %s\n", (CHAR *)map->get(map, "object"));
    printf("get 38a7322: %s\n", (char *)map->get(map, "38a7322"));
    printf("contains byte: %d\n", map->contains(map, "byte"));
    map->remove(map, "byte");
    printf("contains byte: %d\n", map->contains(map, "byte"));

    map->printByIndex(map, 10);
    map->print(map);

    newMap = map->clone(map);
    deleteHashMap(map);

    newMap->print(newMap);
    deleteHashMap(newMap);
}
#endif



#if TEST_HASHTABLE
void testHashTable()
{
    CHAR *testObject = "This is a object test.";
    HashTable map = newHashTable(8, 0);
    HashTable newMap = NULL;

    map->putByte(map, "byte", 20);
    map->putChar(map, "char", 'C');
    map->putShort(map, "short", 128);
    map->putInt(map, "int", -123);
    map->putUint(map, "uint", 234);
    map->putLong(map, "long", -12345);
    map->putUlong(map, "ulong", 34567);
    map->putFloat(map, "float", -123.34f);
    map->putDouble(map, "double", 545.23);
    map->putString(map, "string", "string test");
    map->putObject(map, "object", testObject);


    map->putString(map, "123ad12", "This is a test.");
    map->putString(map, "25622", "222 test.");
    map->putString(map, "38a7322", "333 test."); //conflict
    map->putString(map, "44094", "444 test.");
    map->putString(map, "5555", "555 test.");
    map->putString(map, "64566", "666 test.");


    printf("capacity: %d\n", map->getCapacity(map));
    printf("size: %d\n", map->getSize(map));

    printf("get byte: %d\n", *(BYTE *)map->get(map, "byte"));
    printf("get double: %f\n", *(DOUBLE *)map->get(map, "double"));
    printf("get null: %d\n", (map->get(map, "11") == NULL));
    printf("get object: %s\n", (CHAR *)map->get(map, "object"));
    printf("get 38a7322: %s\n", (char *)map->get(map, "38a7322"));
    printf("contains byte: %d\n", map->contains(map, "byte"));
    map->remove(map, "byte");
    printf("contains byte: %d\n", map->contains(map, "byte"));

    map->printByIndex(map, 10);
    map->print(map);

    newMap = map->clone(map);
    deleteHashTable(map);

    newMap->print(newMap);
    deleteHashTable(newMap);
}
#endif


#if TEST_ARRAYLIST
void testArrayList()
{
    clock_t start = 0;
    clock_t end = 0;
    ArrayList newList = NULL;

    int i = 0;

    ArrayList list = newArrayList(5);
    OBJECT obj = "Object method test.";
    INT      testInt = -123;
    
    start = clock();

    for (i=0; i<10000; i++)
    {
        list->addByte(list, 128);
        list->addChar(list, 'C');
        list->addInt(list, -123);
        list->addUint(list, 123);
        list->addLong(list, -123456);
        list->addUlong(list, 123456);
        list->addFloat(list, 123.456f);
        list->addDouble(list, 123456.789);
        list->addString(list, "addString test.");
        list->addObject(list, obj);
    }
    list->insert(list, 0, "insert 0", TYPE_STRING);
    list->insert(list, 5, "insert 5", TYPE_STRING);
    list->insert(list, 11, "insert 11", TYPE_STRING);
    list->insert(list, list->size, "insert last", TYPE_STRING);
#if 0
    list->print(list);

    printf("get 11: %s\n", (CHAR *)list->get(list, 11));

    printf("setByIndex 11, old value:%s\n", (char *)(list->setByIndex(list, 11, "setByIndex method.", TYPE_STRING)));
    printf("get 11: %s\n", (CHAR *)list->get(list, 11));

    list->print(list);

    printf("lastIndexOf -123 : %d\n", list->lastIndexOf(list, (OBJECT)&testInt, TYPE_INT));
    printf("lastIndexOf obj : %d\n",   list->lastIndexOf(list, obj, TYPE_OBJECT));

    printf("indexOf -123 : %d\n", list->indexOf(list, (OBJECT)&testInt, TYPE_INT));
    printf("indexOf obj : %d\n", testInt = list->indexOf(list, obj, TYPE_OBJECT));
    printf("getObject : %s\n", (CHAR *)list->get(list, testInt));

    list->remove(list, 2);
    list->print(list);
#endif

    deleteArrayList(list);

    end = clock();

    printf("************  ArrayList used time : %ld\n", end-start);
}
#endif


#if TEST_VECTOR
void testVector()
{
    clock_t start = 0;
    clock_t end = 0;

    int i = 0;

    Vector newList = NULL;
    Vector list = newVector(5);
    OBJECT obj = "Object method test.";
    INT      testInt = -123;

    start = clock();

    for (i=0; i<10000; i++)
    {
        list->addByte(list, 128);
        list->addChar(list, 'C');
        list->addInt(list, -123);
        list->addUint(list, 123);
        list->addLong(list, -123456);
        list->addUlong(list, 123456);
        list->addFloat(list, 123.456f);
        list->addDouble(list, 123456.789);
        list->addString(list, "addString test.");
        list->addObject(list, obj);
    }
    list->insert(list, 0, "insert 0", TYPE_STRING);
    list->insert(list, 5, "insert 5", TYPE_STRING);
    list->insert(list, 11, "insert 11", TYPE_STRING);
    list->insert(list, list->size, "insert last", TYPE_STRING);
#if 0
    list->print(list);

    printf("get 11: %s\n", (CHAR *)list->get(list, 11));

    printf("setByIndex 11, old value:%s\n", (char *)(list->setByIndex(list, 11, "setByIndex method.", TYPE_STRING)));
    printf("get 11: %s\n", (CHAR *)list->get(list, 11));

    list->print(list);

    printf("lastIndexOf -123 : %d\n", list->lastIndexOf(list, (OBJECT)&testInt, TYPE_INT));
    printf("lastIndexOf obj : %d\n",   list->lastIndexOf(list, obj, TYPE_OBJECT));

    printf("indexOf -123 : %d\n", list->indexOf(list, (OBJECT)&testInt, TYPE_INT));
    printf("indexOf obj : %d\n", testInt = list->indexOf(list, obj, TYPE_OBJECT));
    printf("getObject : %s\n", (CHAR *)list->get(list, testInt));

    list->remove(list, 2);
    list->print(list);
#endif
    deleteVector(list);
    end = clock();

    printf("**************  Vector used time : %ld\n", end-start);
}
#endif

#if TEST_QUEUE
void testQueue()
{
    char* test = "Object test OK!";
    Queue queue = newQueue(0);
    queue->addChar(queue, 'C');
    queue->addInt(queue, 123);
    queue->addDouble(queue, 12.3);
    queue->addFloat(queue, 1.23f);
    queue->addString(queue, "this is a queue test.");
    queue->addObject(queue, test);

    queue->print(queue);
    printf("peek :%c\n",  *(CHAR *)queue->peek(queue)); 

    printf("empty:%d\n", queue->isEmpty(queue));
    printf("size:%d\n", queue->getSize(queue));
    printf("remove :%c\n",  *(CHAR *)queue->remove(queue)); 
    printf("remove :%d\n",  *(INT *)queue->remove(queue));
    printf("remove :%3.2f\n",  *(DOUBLE *)queue->remove(queue));
    printf("remove :%3.2f\n",  *(FLOAT *)queue->remove(queue));
    printf("remove :%s\n",  (CHAR *)queue->remove(queue));
    printf("size:%d\n", queue->getSize(queue));
    printf("remove :%s\n",  (CHAR *)queue->remove(queue));
}
#endif

#if TEST_STACK
void testStack()
{
    char* test = "Object test OK!";
    Stack stack = newStack(0);
    stack->pushChar(stack, 'C');
    stack->pushInt(stack, 123);
    stack->pushDouble(stack, 12.3);
    stack->pushFloat(stack, 1.23f);
    stack->pushString(stack, "this is a stack test.");
    stack->pushObject(stack, test);

    stack->print(stack);

    printf("peek :%s\n",  (CHAR *)stack->peek(stack));

    printf("empty:%d\n", stack->isEmpty(stack));
    printf("size:%d\n", stack->getSize(stack));
    printf("pop :%s\n",  (CHAR *)stack->pop(stack));
    printf("pop :%s\n",  (CHAR *)stack->pop(stack));
    printf("pop :%3.2f\n",  *(FLOAT *)stack->pop(stack));
    printf("pop :%3.2f\n",  *(DOUBLE *)stack->pop(stack));
    printf("pop :%d\n",  *(INT *)stack->pop(stack));

    printf("size:%d\n", stack->getSize(stack));

    printf("pop :%c\n",  *(CHAR *)stack->pop(stack)); 
}
#endif


#if TEST_LINKEDQUEUE
void testLinkedQueue()
{
    char* test = "Object test OK!";
    LinkedQueue queue = newLinkedQueue();
    queue->addChar(queue, 'C');
    queue->addInt(queue, 123);
    queue->addDouble(queue, 12.3);
    queue->addFloat(queue, 1.23f);
    queue->addString(queue, "this is a queue test.");
    queue->addObject(queue, test);

    printf("addChar :%c\n",  'C'); 
    printf("addInt :%d\n", 123);
    printf("addDouble :%3.2f\n", 12.3);
    printf("addFloat :%3.2f\n",  1.23f);
    printf("addString :%s\n", "this is a queue test.");
    printf("addObject :%s\n", test);
    printf("empty:%d\n", queue->isEmpty(queue));
    printf("size:%d\n", queue->getSize(queue));

    queue->print(queue);

    printf("remove :%c\n",  *(CHAR *)queue->remove(queue)); 
    printf("remove :%d\n",  *(INT *)queue->remove(queue));
    printf("remove :%3.2f\n",  *(DOUBLE *)queue->remove(queue));
    printf("remove :%3.2f\n",  *(FLOAT *)queue->remove(queue));
    printf("remove :%s\n",  (CHAR *)queue->remove(queue));
    printf("size:%d\n", queue->getSize(queue));
    printf("remove :%s\n",  (CHAR *)queue->remove(queue));
}
#endif

#if TEST_LINKEDSTACK
void testLinkedStack()
{
    char* test = "Object test OK!";
    LinkedStack stack = newLinkedStack();
    stack->pushChar(stack, 'C');
    stack->pushInt(stack, 123);
    stack->pushDouble(stack, 12.3);
    stack->pushFloat(stack, 1.23f);
    stack->pushString(stack, "this is a stack test.");
    stack->pushObject(stack, test);

    printf("pushChar :%c\n",  'C'); 
    printf("pushInt :%d\n", 123);
    printf("pushDouble :%3.2f\n", 12.3);
    printf("pushFloat :%3.2f\n",  1.23f);
    printf("pushString :%s\n", "this is a stack test.");
    printf("pushObject :%s\n", test);
    printf("empty:%d\n", stack->isEmpty(stack));
    printf("size:%d\n", stack->getSize(stack));

    stack->print(stack);

    printf("pop :%s\n",  (CHAR *)stack->pop(stack));
    printf("pop :%s\n",  (CHAR *)stack->pop(stack));
    printf("pop :%3.2f\n",  *(FLOAT *)stack->pop(stack));
    printf("pop :%3.2f\n",  *(DOUBLE *)stack->pop(stack));
    printf("pop :%d\n",  *(INT *)stack->pop(stack));

    printf("size:%d\n", stack->getSize(stack));

    printf("pop :%c\n",  *(CHAR *)stack->pop(stack)); 
}
#endif

#if TEST_STRING
void testString()
{
    String str1 = newString("中文测试，This is a test for String, the String test.");
    String str2 = newString("This is a test for String, the String test.");
    String str3 = NULL;
    String* strArray = NULL;
    UINT count = 0;
    UINT i = 0;

    printf("str1 length: %d\n", str1->getLength(str1));
    printf("equals: %d\n", str1->equals(str1, str2));
    printf("compareTo: %d\n", str1->compareTo(str1, str2));
    printf("indexOf 'S' : %d\n", str1->indexOf(str1, 'S', 0));
    printf("lastIndexOf 'S' : %d\n", str1->lastIndexOf(str1, 'S', 0));
    printf("charAt 0 : %d\n", str1->charAt(str1, 0));
    printf("startWith 'This' : %d\n", str1->startWith(str1, "This"));
    printf("endWith 'est.'  : %d\n", str1->endWith(str1, "est."));

    str1->toUpperCase(&str1);
    str1->print(str1);

    str2->toUpperCase(&str2);
    str2->print(str2);
    str2->toLowerCase(&str2);
    str2->print(str2);

    str3 = str1->subString(str1, 10, 30);

    printf("toCharArray : %s\n", str3->toCharArray(str3));

    strArray = str1->split(str1, ' ', &count);
    for (i=0; i<count; i++)
    {
        strArray[i]->print(strArray[i]);
    }

    for (i=0; i<count; i++)
    {
        deleteString(strArray[i]);
    }
    deleteString(str3);
    deleteString(str2);
    deleteString(str1);

    printf("test String OK!\n");
}
#endif

#if TEST_STRINGBUFFER
void testStringBuffer()
{
    String str = NULL;
    StringBuffer sbuf = newStringBuffer(0);
#if 0
    printf("length :%d\n", sbuf->getLength(sbuf));
    printf("capacity :%d\n", sbuf->getLength(sbuf));

    sbuf->appendChar(sbuf, 'C');
    sbuf->appendCharArray(sbuf, " char array");
    sbuf->appendSubCharArray(sbuf, "array test char", 5, 10);
    sbuf->appendInt(sbuf, 123);
    sbuf->appendChar(sbuf, ' ');
    sbuf->appendLong(sbuf, 456);
    sbuf->appendChar(sbuf, ' ');
    sbuf->appendFloat(sbuf, 12.3f);
    sbuf->appendChar(sbuf, ' ');
    sbuf->appendDouble(sbuf, 4.56);
    sbuf->appendChar(sbuf, ' ');

    str = sbuf->toString(sbuf);
    sbuf->appendString(sbuf, str);

    sbuf->appendStringBuffer(sbuf, sbuf);


    printf("charAt(20): %c\n", sbuf->charAt(sbuf, 20));
    sbuf->setCharAt(sbuf, 20, 'A');
    sbuf->print(sbuf);

    sbuf->deleteCharAt(sbuf, 20);
    sbuf->print(sbuf);

    sbuf->deleteValue(sbuf, 20, 30);
    sbuf->print(sbuf);

    printf("indexOf C :%d\n", sbuf->indexOf(sbuf, 'C', 0));
    printf("Offset 10, indexOf C :%d\n", sbuf->indexOf(sbuf, 'C', 10));
    printf("lastIndexOf C :%d\n", sbuf->lastIndexOf(sbuf, 'C', 0));

    sbuf->insertChar(sbuf, 10, 'D');

    sbuf->insertCharArray(sbuf, 10, " char array");
    sbuf->insertSubCharArray(sbuf, 10, "array test char", 5, 10);
    sbuf->insertInt(sbuf, 10, 789);
    sbuf->insertChar(sbuf, 10, ' ');
    sbuf->insertLong(sbuf, 10, 631);
    sbuf->insertChar(sbuf, 10, ' ');
    sbuf->insertFloat(sbuf, 10, 98.7f);
    sbuf->insertChar(sbuf, 10, ' ');
    sbuf->insertDouble(sbuf, 10, 7.23);
    sbuf->insertChar(sbuf, 10, ' ');
    deleteString(str);
    str = NULL;

    str = sbuf->subString(sbuf, 10, 30);
    sbuf->insertString(sbuf, 10, str);
    deleteString(str);

    sbuf->print(sbuf);

    sbuf->reverse(sbuf);
    sbuf->print(sbuf);
#endif

    /* 效率测试 */
#if 1
    int i = 0;
    int count = 10000;

    clock_t start, end;

    start = clock();
    for (i=0; i<count; i++)
    {
        sbuf->appendChar(sbuf, 'C');
    }

    for (i=0; i<count; i++)
    {
        sbuf->insertChar(sbuf, 10, 'C');
    }

    end = clock();

    printf("StringBuffer used time: %ld\n", end-start);
#endif

    deleteStringBuffer(sbuf);
}
#endif

#if TEST_STRINGBUILDER
void testStringBuilder()
{
    String str = NULL;
    StringBuilder sbuf = newStringBuilder(0);
#if 0
    printf("length :%d\n", sbuf->getLength(sbuf));
    printf("capacity :%d\n", sbuf->getLength(sbuf));

    sbuf->appendChar(sbuf, 'C');
    sbuf->appendCharArray(sbuf, " char array");
    sbuf->appendSubCharArray(sbuf, "array test char", 5, 10);
    sbuf->appendInt(sbuf, 123);
    sbuf->appendChar(sbuf, ' ');
    sbuf->appendLong(sbuf, 456);
    sbuf->appendChar(sbuf, ' ');
    sbuf->appendFloat(sbuf, 12.3f);
    sbuf->appendChar(sbuf, ' ');
    sbuf->appendDouble(sbuf, 4.56);
    sbuf->appendChar(sbuf, ' ');

    str = sbuf->toString(sbuf);
    sbuf->appendString(sbuf, str);

    sbuf->appendStringBuilder(sbuf, sbuf);

    printStringBuilder(sbuf);

    printf("charAt(20): %c\n", sbuf->charAt(sbuf, 20));
    sbuf->setCharAt(sbuf, 20, 'A');
    printStringBuilder(sbuf);

    sbuf->deleteCharAt(sbuf, 20);
    printStringBuilder(sbuf);

    sbuf->deleteValue(sbuf, 20, 30);
    printStringBuilder(sbuf);

    printf("indexOf C :%d\n", sbuf->indexOf(sbuf, 'C', 0));
    printf("Offset 10, indexOf C :%d\n", sbuf->indexOf(sbuf, 'C', 10));
    printf("lastIndexOf C :%d\n", sbuf->lastIndexOf(sbuf, 'C', 0));

    sbuf->insertChar(sbuf, 10, 'D');

    sbuf->insertCharArray(sbuf, 10, " char array");
    sbuf->insertSubCharArray(sbuf, 10, "array test char", 5, 10);
    sbuf->insertInt(sbuf, 10, 789);
    sbuf->insertChar(sbuf, 10, ' ');
    sbuf->insertLong(sbuf, 10, 631);
    sbuf->insertChar(sbuf, 10, ' ');
    sbuf->insertFloat(sbuf, 10, 98.7f);
    sbuf->insertChar(sbuf, 10, ' ');
    sbuf->insertDouble(sbuf, 10, 7.23);
    sbuf->insertChar(sbuf, 10, ' ');
    deleteString(str);
    str = NULL;

    str = sbuf->subString(sbuf, 10, 30);
    sbuf->insertString(sbuf, 10, str);
    deleteString(str);

    printStringBuilder(sbuf);

    sbuf->reverse(sbuf);
    printStringBuilder(sbuf);
#endif

    /* 效率测试 */
#if 1
    int i = 0;
    int count = 10000;

    clock_t start, end;

    start = clock();
    for (i=0; i<count; i++)
    {
        sbuf->appendChar(sbuf, 'C');
    }

    for (i=0; i<count; i++)
    {
        sbuf->insertChar(sbuf, 10, 'C');
    }

    end = clock();

    printf("StringBuilder used time: %ld\n", end-start);
#endif

    deleteStringBuilder(sbuf);
}
#endif

#if TEST_LINKEDLIST
void testLinkedList()
{
    OBJECT obj = "Object method test.";
    INT      testInt = -123;

    LinkedList list = newLinkedList();
    LinkedList newList = NULL;

    list->add(list, "add method test.", TYPE_STRING);

    list->addByte(list, 128);
    list->addChar(list, 'C');
    list->addInt(list, -123);
    list->addUint(list, 123);
    list->addLong(list, -123456);
    list->addUlong(list, 123456);
    list->addFloat(list, 123.456f);
    list->addDouble(list, 123456.789);
    list->addString(list, "addString test.");
    list->addObject(list, obj);

    list->addFirst(list, "addFirst method.", TYPE_STRING);
    list->addLast(list, "addLast method.", TYPE_STRING);

    list->addByIndex(list, "addByIndex method.", TYPE_STRING, 5);
    printf("get 5: %s\n", (CHAR *)list->get(list, 5));

    list->setByIndex(list, "setByIndex method.", TYPE_STRING, 5);
    printf("get 5: %s\n", (CHAR *)list->get(list, 5));

    list->print(list);

    printf("getFirst : %s\n", (CHAR *)list->getFirst(list));
    printf("getLast : %s\n", (CHAR *)list->getLast(list));  


    printf("lastIndexOf -123 : %ld\n", list->lastIndexOf(list, (OBJECT)&testInt, TYPE_INT));
    printf("lastIndexOf obj : %ld\n",   list->lastIndexOf(list, obj, TYPE_OBJECT));

    printf("indexOf -123 : %ld\n", list->indexOf(list, (OBJECT)&testInt, TYPE_INT));
    printf("indexOf obj : %d\n", testInt = list->indexOf(list, obj, TYPE_OBJECT));
    printf("getObject : %s\n", (CHAR *)list->get(list, testInt));

    list->removeByIndex(list, testInt);
    list->removeFirst(list);
    list->removeLast(list);
    list->removeByIndex(list, 5);
    list->print(list);

    printf("test clone method.\n");
    newList = list->clone(list);
    deleteLinkedList(list);

    newList->print(newList);
    deleteLinkedList(newList);
}
#endif



int main(int argc, char** argv)
{
    int i = 0;
#if   USECMEMORY
    initMemoryPool();
#endif

#if TEST_HASHMAP
    printf("\n*******************  Test for HashMap  *******************\n");
    testHashMap();
#endif

#if TEST_HASHTABLE
    printf("\n*******************  Test for HashTable  *******************\n");
    testHashTable();
#endif

#if TEST_ARRAYLIST
    printf("\n*******************  Test for ArrayList  *******************\n");
    for (i=0; i<10; i++)
    {
        testArrayList();
    }
#endif

#if TEST_VECTOR
    printf("\n*******************  Test for Vector  *******************\n");
    for (i=0; i<10; i++)
    {
        testVector();
    }
#endif

#if TEST_QUEUE
    printf("\n*******************  Test for Queue  *******************\n");
    testQueue();
#endif

#if TEST_STACK
    printf("\n*******************  Test for Stack  *******************\n");
    testStack();
#endif

#if TEST_LINKEDQUEUE
    printf("\n*******************  Test for LinkedQueue  *******************\n");
    testLinkedQueue();
#endif

#if TEST_LINKEDSTACK
    printf("\n*******************  Test for LinkedStack  *******************\n");
    testLinkedStack();
#endif

#if TEST_STRING
    printf("\n*******************  Test for String  *******************\n");
    testString();
#endif

#if TEST_STRINGBUFFER
    printf("\n*******************  Test for StringBuffer  *******************\n");
    testStringBuffer();
#endif

#if TEST_STRINGBUILDER
    printf("\n*******************  Test for StringBuilder  *******************\n");
    testStringBuilder();
#endif

#if TEST_LINKEDLIST
    printf("\n*******************  Test for LinkedList  *******************\n");
    testLinkedList();
#endif

#if TEST_MEMORY
    printf("\n*******************  Test for CMemory  *******************\n");
    testMemory();
#endif

#if   USECMEMORY
    destroyMemoryPool();
#endif

    return 0;
}

