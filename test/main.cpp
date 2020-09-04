#include "mylib.h"
#include "gtest/gtest.h"
#include <stdio.h>

TEST(testAdd, pcemucpp) { EXPECT_EQ(1, 1); }

int
main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    CPU cpu;
    printf("FUCKFUCCK\n");
    return RUN_ALL_TESTS();
}
