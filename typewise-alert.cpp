#include "typewise-alert.h"
#include <stdio.h>


/*get temp range based on cooling type*/
TemperatureRange getTemperatureRange(CoolingType coolingType) {
    TemperatureRange ranges[] = {
    {0, 35}, /*passive cooling*/
    {0, 45}, /*high active cooling*/
    {0, 40}  /*mid active cooling*/
  };
  return ranges[coolingType];
}

/* infer breach type based on value and limits*/
BreachType inferBreach(double value, TemperatureRange range) {
  if (value < range.lowerLimit) {
    return TOO_LOW;
  }
  if (value > range.upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

// differentiate temp breach based on cooling type and temp
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  TemperatureRange range = getTemperatureRange(coolingType);
  return inferBreach(temperatureInC, range);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}
void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if (breachType == TOO_LOW) {
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too low\n");
  } else if (breachType == TOO_HIGH) {
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too high\n");
  }
}
