#include "unity.h"
#include "logic.h"
#include "fileHandler.h"

void test_create_grid()
{
    int x = 0;
    int y = 0;
    int test = createGrid(x, y);
    TEST_ASSERT_MESSAGE(test == 2, "Failure");

    //Test edge cases
    x = 40;
    y = 10;
    test = createGrid(x, y);
    TEST_ASSERT_MESSAGE(test == 0, "Fails on edge cases!\n");

}

void test_set_next_state()
{

}

void test_set_initial_state()
{

}

void test_check_neighbours()
{

}

void test_write_grid()
{

}

void test_write_state()
{

}

void test_read_state()
{

}

void setUp()
{

}
void tearDown()
{

}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_create_grid);
    RUN_TEST(test_set_next_state);
    RUN_TEST(test_set_initial_state);
    RUN_TEST(test_check_neighbours);
    RUN_TEST(test_write_grid);
    RUN_TEST(test_write_state);
    RUN_TEST(test_read_state);
    return UNITY_END();
}