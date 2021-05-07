#include "unity.h"
#include "logic.h"
#include "fileHandler.h"

int x = 0;
int y = 0;
int test = 0;

void test_create_grid()
{
    test = createGrid(x, y);
    TEST_ASSERT_MESSAGE(test == 2, "Failure on invalid parameters!");

    //Test edge cases
    x = 40;
    y = 10;
    test = createGrid(x, y);
    TEST_ASSERT_MESSAGE(test == 0, "Fails on edge cases!");

    x = 100;
    y = 50;
    test = createGrid(x, y);
    TEST_ASSERT_MESSAGE(test == 0, "Fails on edge 232 cases!");
    destroyGrid();
}

void test_set_next_state()
{
    createGrid(50, 50);
    x = -1;
    y = -1;
    test = setNextState(x, y);
    TEST_ASSERT_MESSAGE(test == 1, "Failure on invalid parameters!");

    x = (int) grid.width;
    y = (int) grid.height;
    test = setNextState(x, y);
    TEST_ASSERT_MESSAGE(test == 1, "Failure on invalid parameters!");

    x = (int) grid.width - 1;
    y = (int) grid.height - 1;
    test = setNextState(x, y);
    TEST_ASSERT_MESSAGE(test == 0, "Failure on edge cases!");

    x = 0;
    y = 0;
    test = setNextState(x, y);
    TEST_ASSERT_MESSAGE(test == 0, "Failure on edge cases!");
    destroyGrid();
}

void test_set_initial_state()
{
    createGrid(50, 50);
    x = -1;
    y = -1;
    test = setInitialState(x, y, false);
    TEST_ASSERT_MESSAGE(test == 1, "Failure on invalid parameters!");

    x = (int) grid.width;
    y = (int) grid.height;
    test = setInitialState(x, y, true);
    TEST_ASSERT_MESSAGE(test == 1, "Failure on invalid parameters!");

    x = (int) grid.width - 1;
    y = (int) grid.height - 1;
    test = setInitialState(x, y, false);
    TEST_ASSERT_MESSAGE(test == 0, "Failure on edge cases!");

    x = 0;
    y = 0;
    test = setInitialState(x, y, true);
    TEST_ASSERT_MESSAGE(test == 0, "Failure on edge cases!");
    destroyGrid();
}

void test_check_neighbours()
{
    createGrid(50, 50);
    x = -1;
    y = -1;
    test = (int) checkNeighbours(x, y);
    TEST_ASSERT_MESSAGE(test == 1, "Failure on invalid parameters!");

    x = (int) grid.width;
    y = (int) grid.height;
    test = (int) checkNeighbours(x, y);
    TEST_ASSERT_MESSAGE(test == 1, "Failure on invalid parameters!");

    x = (int) grid.width - 1;
    y = (int) grid.height - 1;
    test = (int) checkNeighbours(x, y);
    TEST_ASSERT_MESSAGE(test == 0, "Failure on edge cases!");

    x = 0;
    y = 0;
    test = (int) checkNeighbours(x, y);
    TEST_ASSERT_MESSAGE(test == 0, "Failure on edge cases!");
    destroyGrid();
}

void test_write_grid()
{
    createGrid(50, 50);
    FILE *file = NULL;
    test = writeGrid(file);
    TEST_ASSERT_MESSAGE(test == 1, "Failure on open file check!");
    file = fopen("../testWriteGrid.txt", "w");
    test = writeGrid(file);
    TEST_ASSERT_MESSAGE(test == 0, "Failure on writing to file!");
    destroyGrid();
}

void test_write_state()
{
    createGrid(50, 50);
    FILE *file = NULL;
    test = writeState(file);
    TEST_ASSERT_MESSAGE(test == 1, "Failure on open file check!");
    file = fopen("../testWriteGrid.txt", "w");
    test = writeState(file);
    TEST_ASSERT_MESSAGE(test == 0, "Failure on writing to file!");
    destroyGrid();
}

void test_read_state()
{
    FILE *file = NULL;
    test = readState(file);
    TEST_ASSERT_MESSAGE(test == 1, "Failure on open file check!");
    file = fopen("../testReadGrid.txt", "r");
    test = writeGrid(file);
    TEST_ASSERT_MESSAGE(test == 0, "Failure on reading from file!");
    destroyGrid();
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