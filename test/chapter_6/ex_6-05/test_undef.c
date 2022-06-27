#ifdef TEST

#include "unity.h"
#include "string.h"

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
    char *definition = "test_definition";
    install("test", definition);

    // when
    struct table_entry *entry = lookup("test");

    // then
    TEST_ASSERT_EQUAL(entry->definition != NULL, 1);
    TEST_ASSERT_EQUAL(entry->name != NULL, 1);
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
