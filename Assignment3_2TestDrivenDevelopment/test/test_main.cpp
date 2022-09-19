
#include <avr/delay.h>
#include <unity.h>

#include <fifo3.h>

void test_normal_flow(void)
{
    // 1 Setup
    Fifo f;
    f.put(1);
    f.put(2);
    f.get();
    f.put(3);

    // 2-3 Execute and validate
    TEST_ASSERT_EQUAL(2, f.get());
    TEST_ASSERT_EQUAL(3, f.get());

    f.put(1);
    f.put(2);
    f.put(3);
    f.put(4);
    f.put(5);
    f.get();

    // 4 Cleanup
}

void test_underflow(void)

{
    // 1 Setup
    Fifo f;
    f.put(1);
    f.put(2);
    f.get();
    f.get();

    // 2-3 Execute and validate
    TEST_ASSERT_TRUE(f.is_empty());

    // 4 Cleanup
}

void test_reset(void)
{
    Fifo f;
    f.put(1);
    f.put(3);
    TEST_ASSERT_FALSE(f.is_empty());
    f.reset();
    TEST_ASSERT_TRUE(f.is_empty());
}

void test_overwrite()
{
    Fifo f;
    for (int i = 0; i<FIFO_SIZE; i++)
    {
        f.put(i+1);
    }
    TEST_ASSERT_TRUE(f.is_full());
    // buffer = [1, 2, 3, 4, 5]
    // now the queue is full so putting one more should result in the oldest one (1) popping out
    f.put(100);
//     // thus the oldest member is now 2
    // f.get();
    TEST_ASSERT_EQUAL(2, f.get());
}

void test_overflow()
{
    Fifo f;
    TEST_ASSERT_FALSE(f.is_full());
    for (int i = 0; i<FIFO_SIZE; i++)
    {
        f.put(i);
    }
    TEST_ASSERT_TRUE(f.is_full());
}

void basic()
{

    TEST_ASSERT_TRUE(false);
}

int main()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    _delay_ms(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!count==FIFO_SIZE;

    RUN_TEST(test_normal_flow);
    RUN_TEST(test_underflow);
    RUN_TEST(test_reset);
    RUN_TEST(test_overflow);
    RUN_TEST(test_overwrite);
    // RUN_TEST(basic);

    UNITY_END(); // stop unit testing
}
