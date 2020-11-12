#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IKeypad.h>
#include <ILatch.h>
#include <lockcontroller.h>

using namespace testing;

struct MockKeypad : IKeypad {
    MOCK_METHOD(
        bool,
        isActive,
        (),
        (override)
    );

    MOCK_METHOD(
        void,
        wait,
        (),
        (override)
    );

    MOCK_METHOD(
        PasswordResponse,
        requestPassword,
        (),
        (override)
    );
};

struct MockLatch : ILatch {
    MOCK_METHOD(
        bool,
        isActive,
        (),
        (override)
    );

    MOCK_METHOD(
        DoorStatus,
        open,
        (),
        (override)
    );

    MOCK_METHOD(
        DoorStatus,
        close,
        (),
        (override)
    );

    MOCK_METHOD(
        DoorStatus,
        getDoorStatus,
        (),
        (override)
    );

};

struct LockControllerFixture : public testing::Test {
    MockKeypad keypad;
    MockLatch latch;
    LockController* lc;

    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {
        lc = new LockController(&keypad, &latch);
    }
    void TearDown() override {
        delete lc;
    };
};

// 1
TEST_F(LockControllerFixture, CallingWait) {
    // Arrange
    EXPECT_CALL(keypad, wait())
            .Times(1)
            .WillOnce(Return());

    // Act
    lc->wait();

    // Assert
}

// 2
TEST_F(LockControllerFixture, IsDoorOpenWhenDoorIsClosed) {
    // Arrange
    EXPECT_CALL(latch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));


    // Act
    bool result = lc->isDoorOpen();

    // Assert
    ASSERT_FALSE(result);
}

// 3
TEST_F(LockControllerFixture, IsDoorOpenWhenDoorIsOpen) {
    // Arrange
    EXPECT_CALL(latch, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));


    // Act
    bool result = lc->isDoorOpen();

    // Assert
    ASSERT_TRUE(result);
}


// 4
TEST_F(LockControllerFixture, Opening) {
    // Arrange
    EXPECT_CALL(latch, open())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));

    // Act
    DoorStatus result = lc->unlockDoor();

    // Assert
    ASSERT_EQ(result, DoorStatus::OPEN);
}

// 5
TEST_F(LockControllerFixture, Closing) {
    // Arrange
    EXPECT_CALL(latch, close())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));

    // Act
    DoorStatus result = lc->lockDoor();

    // Assert
    ASSERT_EQ(result, DoorStatus::CLOSE);
}

// 6
TEST_F(LockControllerFixture, HardwareIsFine) {
    // Arrange
    EXPECT_CALL(keypad, isActive())
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(latch, isActive())
            .Times(1)
            .WillOnce(Return(true));

    // Act
    HardWareStatus result = lc->hardWareCheck();

    // Assert
    ASSERT_EQ(result, HardWareStatus::OK);
}

// 7
TEST_F(LockControllerFixture, HardwareIsNotOkay) {
    // Arrange
    delete lc;
    lc = new LockController(nullptr, &latch);

    EXPECT_CALL(keypad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));
    EXPECT_CALL(latch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    // Act
    HardWareStatus result = lc->hardWareCheck();

    // Assert
    ASSERT_EQ(result, HardWareStatus::ERROR);
}

// 8
TEST_F(LockControllerFixture, LatchIsNotActive) {
    // Arrange

    EXPECT_CALL(keypad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));
    EXPECT_CALL(latch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(false));

    // Act
    HardWareStatus result = lc->hardWareCheck();

    // Assert
    ASSERT_EQ(result, HardWareStatus::ERROR);
}

// 9
TEST_F(LockControllerFixture, CorrectPassword) {
    // Arrange
    PasswordResponse resp;
    resp.status = PasswordResponse::Status::OK;
    resp.password = "0000";
    EXPECT_CALL(keypad, requestPassword())
            .Times(1)
            .WillOnce(Return(resp));

    // Act
    bool result = lc->isCorrectPassword();

    // Assert
    ASSERT_TRUE(result);
}

// 10
TEST_F(LockControllerFixture, IncorrectPassword) {
    // Arrange
    PasswordResponse resp;
    resp.status = PasswordResponse::Status::OK;
    resp.password = "1234";
    EXPECT_CALL(keypad, requestPassword())
            .Times(1)
            .WillOnce(Return(resp));

    // Act
    bool result = lc->isCorrectPassword();

    // Assert
    ASSERT_FALSE(result);
}

// 11
TEST_F(LockControllerFixture, CorrectPasswordChange) {
    // Arrange
    PasswordResponse resp1;
    resp1.status = PasswordResponse::Status::OK;
    resp1.password = "0000";

    PasswordResponse resp2;
    resp2.status = PasswordResponse::Status::OK;
    resp2.password = "9876";

    PasswordResponse resp3;
    resp3.status = PasswordResponse::Status::OK;
    resp3.password = "9876";

    EXPECT_CALL(keypad, requestPassword())
            .Times(3)
            .WillOnce(Return(resp1))
            .WillOnce(Return(resp2))
            .WillOnce(Return(resp3));

    lc->resetPassword();

    // Act
    bool result = lc->isCorrectPassword();

    // Assert
    ASSERT_TRUE(result);
}

// 12
TEST_F(LockControllerFixture, CorrectPasswordChange2) {
    // Arrange
    PasswordResponse resp1;
    resp1.status = PasswordResponse::Status::OK;
    resp1.password = "0000";

    PasswordResponse resp2;
    resp2.status = PasswordResponse::Status::OK;
    resp2.password = "9876";

    PasswordResponse resp3;
    resp3.status = PasswordResponse::Status::OK;
    resp3.password = "9876";

    PasswordResponse resp4;
    resp4.status = PasswordResponse::Status::OK;
    resp4.password = "1234";

    PasswordResponse resp5;
    resp5.status = PasswordResponse::Status::OK;
    resp5.password = "1234";


    EXPECT_CALL(keypad, requestPassword())
            .Times(5)
            .WillOnce(Return(resp1))
            .WillOnce(Return(resp2))
            .WillOnce(Return(resp3))
            .WillOnce(Return(resp4))
            .WillOnce(Return(resp5));

    lc->resetPassword();
    lc->resetPassword();


    // Act
    bool result = lc->isCorrectPassword();

    // Assert
    ASSERT_TRUE(result);
}


#endif // TST_TESTDIVISIONBYZERO_H
