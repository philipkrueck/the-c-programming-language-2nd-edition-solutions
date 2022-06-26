#include "src/chapter_6/ex_6-05/undef.h"
#include "/Library/Ruby/Gems/2.6.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








void setUp(void)

{

}



void tearDown(void)

{

}



void test_lookup_not_inserted(void)

{

    UnityAssertEqualNumber((UNITY_INT64)((((void*)0))), (UNITY_INT64)((lookup("test"))), (((void*)0)), (UNITY_UINT)(17), UNITY_DISPLAY_STYLE_HEX64);

}



void test_lookup_inserted(void)

{



    char *definition = "test";

    install("test", definition);





    struct table_entry *entry = lookup("test");





    UnityAssertEqualNumber((UNITY_INT64)(("test")), (UNITY_INT64)((entry->definition)), (((void*)0)), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_HEX64);

    UnityAssertEqualNumber((UNITY_INT64)(("test")), (UNITY_INT64)((entry->name)), (((void*)0)), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_HEX64);

}



void test_undef(void)

{



    char *definition = "test";

    install("test", definition);





    undef("test");

    struct table_entry *entry = lookup("test");





    UnityAssertEqualNumber((UNITY_INT64)((((void*)0))), (UNITY_INT64)((entry)), (((void*)0)), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_HEX64);

}
