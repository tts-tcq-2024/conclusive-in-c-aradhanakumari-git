#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToLow) {
  TemperatureRange range = {0, 35};  
  EXPECT_EQ(inferBreach(-1, range), TOO_LOW);
}

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToHIGH) {
  TemperatureRange range = {0, 35}; 
  EXPECT_EQ(inferBreach(36, range), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToNormal) {
  TemperatureRange range = {0, 35};
  EXPECT_EQ(inferBreach(20, range), NORMAL);
}
TEST(TypewiseAlertTest, ClassifyTemperatureBreachPassiveCooling) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, -1), TOO_LOW);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 35), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
}

TEST(TypewiseAlertTest, ClassifyTemperatureBreachHiActiveCooling) {
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1), TOO_LOW);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
}

TEST(TypewiseAlertTest, ClassifyTemperatureBreachMedActiveCooling) {
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1), TOO_LOW);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, SendsLowTemperatureEmail) {
    testing::internal::CaptureStdout();
    sendToEmail(TOO_LOW);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n");
}
