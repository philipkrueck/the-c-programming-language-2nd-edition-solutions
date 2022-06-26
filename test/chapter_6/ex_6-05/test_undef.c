#ifdef TEST

#include "unity.h"

#include "undef.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_lookup_not_inserted(void)
{
    TEST_ASSERT_EQUAL_PTR(NULL, lookup("test"));
}

void test_lookup_inserted(void)
{
    // given
    char *definition = "test";
    install("test", definition);

    // when
    struct table_entry *entry = lookup("test");

    // then
    TEST_ASSERT_EQUAL_PTR("test", entry->definition);
    TEST_ASSERT_EQUAL_PTR("test", entry->name);
}

void test_undef(void)
{
    // given
    char *definition = "test";
    install("test", definition);

    // when
    undef("test");
    struct table_entry *entry = lookup("test");

    // then
    TEST_ASSERT_EQUAL_PTR(NULL, entry);
}

#endif // TEST
