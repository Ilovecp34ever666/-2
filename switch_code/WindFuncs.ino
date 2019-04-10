//==========================================================================
void printWindDetails()
{
  Serial.print("  TMP volts ");
  Serial.print(TMP_Therm_ADunits * 0.0048828125);
  Serial.print(" RV volts ");
  Serial.print((float)RV_Wind_Volts);
  Serial.print("\t  TempC*100 ");
  Serial.print(TempCtimes100 );
  Serial.print("   ZeroWind volts ");
  Serial.print(zeroWind_volts);
  Serial.print("   WindSpeed MPH ");
  Serial.print((float)WindSpeed_MPH);
  Serial.print("   WindSpeed2 MPH ");
  Serial.println((float)WindSpeed_MPH2);
}

//==========================================================================

void calculateWindSpeeds(unsigned long currentTime)
{
  if (currentTime - lastMillis > windReadInterval)
  {
    TMP_Therm_ADunits = analogRead(analogPinForTMP);
    RV_Wind_ADunits = analogRead(analogPinForRV);
    RV_Wind_ADunits2 = analogRead(analogPinForRV2);
    RV_Wind_Volts = (RV_Wind_ADunits *  0.0048828125);
    RV_Wind_Volts2 = (RV_Wind_ADunits2 *  0.0048828125);

    TempCtimes100 = (0.005 * ((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits)) - (16.862 * (float)TMP_Therm_ADunits) + 9075.4;
    zeroWind_ADunits = -0.0006 * ((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits) + 1.0727 * (float)TMP_Therm_ADunits + 47.172; //  13.0C  553  482.39
    zeroWind_volts = (zeroWind_ADunits * 0.0048828125) - zeroWindAdjustment;
    WindSpeed_MPH =  pow(((RV_Wind_Volts - zeroWind_volts) / .2300) , 2.7265);
    WindSpeed_MPH2 =  pow(((RV_Wind_Volts2 - zeroWind_volts) / .2300) , 2.7265);

    printWindDetails();
    lastMillis = currentTime;
  }
}
