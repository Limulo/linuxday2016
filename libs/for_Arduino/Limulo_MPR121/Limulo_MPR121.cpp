/*************************************************** 
  This is a library for the MPR121 I2C 12-chan Capacitive Sensor

  Designed specifically to work with the MPR121 sensor from Adafruit
  ----> https://www.adafruit.com/products/1982

  These sensors use I2C to communicate, 2+ pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
  
  Modified by limulo.net (http://www.limulo.net)
 ****************************************************/

#include "Limulo_MPR121.h"


Limulo_MPR121::Limulo_MPR121() {
}

boolean Limulo_MPR121::begin(uint8_t i2caddr) {
  Wire.begin();
    
  _i2caddr = i2caddr;

  // soft reset
  writeRegister(MPR121_SOFTRESET, 0x63);
  delay(1);
  
  //printRegisters();

  uint8_t c = readRegister8(MPR121_CONFIG2); 
  if (c != 0x24) return false;

  reset();
  
  /*
  writeRegister(MPR121_ECR, 0xC0); // Stop Mode

  // Rising: filtered data greater than baseline values
  writeRegister(MPR121_MHDR, 0x01); // maximum half-delta (0 - 63) 
  writeRegister(MPR121_NHDR, 0x08);	// noise half-delta (0 - 63)
  writeRegister(MPR121_NCLR, 0x01);	// noise count limit
  writeRegister(MPR121_FDLR, 0x00);	// filter delay count

  // Falling: filtered data lower than baseline values
  writeRegister(MPR121_MHDF, 0x01); // (0 - 63)
  writeRegister(MPR121_NHDF, 0x01); // (0 - 63)
  writeRegister(MPR121_NCLF, 0x02); //
  writeRegister(MPR121_FDLF, 0x01); //
  
  // Touched: when electrode is in touch status 
  writeRegister(MPR121_NHDT, 0x00); // (0 - 63)
  writeRegister(MPR121_NCLT, 0x00); //
  writeRegister(MPR121_FDLT, 0x00); //
  
  writeRegister(MPR121_DEBOUNCE, 0x11); 	// 2 touch/release detections before Status changes (EFI x SFI x 2 (ms) delay)
      
  writeRegister(MPR121_AUTOCONFIG0, 0x9F);  // FFI (must match FFI in 0x5C) | RETRY enabled (2 times) | BVA (must match CL in 0x5E) | ARE enabled| ACE enabled
  writeRegister(MPR121_CONFIG1, 0x90); 		// FFI must match FFI in 0x7B
  
  writeRegister(MPR121_CONFIG2, 0x20); 		// 0.5uS encoding, 1ms period
  
  writeRegister(MPR121_UPLIMIT, 156);
  writeRegister(MPR121_TARGETLIMIT, 140); // should correspond to ~562 ADC
  writeRegister(MPR121_LOWLIMIT, 101);
  
  // preliminary setting for thresholds
  for (uint8_t i=0; i<12; i++) {
    writeRegister(MPR121_TOUCHTH_0 + 2*i, 12);
    writeRegister(MPR121_RELEASETH_0 + 2*i, 6);
  }
  
  // enable all electrodes (CL must match BVA in 0x7B)
  writeRegister(MPR121_ECR, 0xC2);  // start with first 10 bits of baseline tracking, only first 2 electrodes enabled, enter RUN MODE
 */
  return true;
}

void Limulo_MPR121::reset(void)
{

	writeRegister(MPR121_SOFTRESET, 0x63); //soft reset: all registers are set to default values
	delay(1);
	
	stopMode();
	
    /* Rising: filtered data greater than baseline values */
	writeRegister(MPR121_MHDR, 0x01); // maximum half-delta (0 - 63) 
	writeRegister(MPR121_NHDR, 0x08);	// noise half-delta (0 - 63)
    writeRegister(MPR121_NCLR, 0x01);	// noise count limit
  	writeRegister(MPR121_FDLR, 0x00);	// filter delay count

	/* Falling: filtered data lower than baseline values */
	writeRegister(MPR121_MHDF, 0x01); // (0 - 63)
    writeRegister(MPR121_NHDF, 0x01); // (0 - 63)
    writeRegister(MPR121_NCLF, 0x02); //
	writeRegister(MPR121_FDLF, 0x01); //
  
	/* Touched: when electrode is in touch status */
	writeRegister(MPR121_NHDT, 0x00); // (0 - 63)
	writeRegister(MPR121_NCLT, 0x00); //
	writeRegister(MPR121_FDLT, 0x00); //
  
	writeRegister(MPR121_DEBOUNCE, 0x11); 	// 2 touch/release detections before Status changes (EFI x SFI x 2 (ms) delay)
      
	writeRegister(MPR121_AUTOCONFIG0, 0x9F);  // FFI (must match FFI in 0x5C) | RETRY enabled (2 times) | BVA (must match CL in 0x5E) | ARE enabled| ACE enabled
	writeRegister(MPR121_CONFIG1, 0x90);	// FFI must match FFI in 0x7B
  
	writeRegister(MPR121_CONFIG2, 0x20);	// 0.5uS encoding, 1ms period
  
	writeRegister(MPR121_UPLIMIT, 156);
	writeRegister(MPR121_TARGETLIMIT, 140); // should correspond to ~562 ADC
	writeRegister(MPR121_LOWLIMIT, 101);
  
	// preliminary setting for thresholds
	for (uint8_t i=0; i<12; i++) {
		writeRegister(MPR121_TOUCHTH_0 + 2*i, 150);
		writeRegister(MPR121_RELEASETH_0 + 2*i, 50);
  	}
	delay(5);
	runMode();	
}

void Limulo_MPR121::stopMode( void )
{
	writeRegister(MPR121_ECR, 0xC0); // enter STOP MODE
}

void Limulo_MPR121::runMode( void )
{
	//writeRegister(MPR121_ECR, 0xC2); // exit STOP MODE, enter RUN MODE - only 2 electrode working
	writeRegister(MPR121_ECR, 0xC9); // exit STOP MODE, enter RUN MODE - 9 are electrode working
}


void Limulo_MPR121::setFFI(uint8_t ffi)
{
	uint8_t _ffi = ffi & 0x03;
	_ffi = _ffi << 6;
	uint8_t cdc = readRegister8( MPR121_CONFIG1 );
	cdc = cdc & 0x3F;
	
	stopMode();
	writeRegister(MPR121_CONFIG1, _ffi | cdc );
	runMode();
}

void Limulo_MPR121::setESI(uint8_t esi)
{
	uint8_t _esi = esi & 0x07;
	_esi = _esi << 0;
	uint8_t cdt_sfi = readRegister8( MPR121_CONFIG2 );
	cdt_sfi = cdt_sfi & 0xF8;
	
	stopMode();
	writeRegister(MPR121_CONFIG2, cdt_sfi | _esi );
	runMode();
}

void Limulo_MPR121::setSFI(uint8_t sfi)
{
	uint8_t _sfi = sfi & 0x03;
	_sfi = _sfi << 3;
	uint8_t cdt_esi = readRegister8( MPR121_CONFIG2 );
	cdt_esi = cdt_esi & 0xE7;
	
	stopMode();
	writeRegister(MPR121_CONFIG2, cdt_esi | _sfi );
	runMode();
}

void Limulo_MPR121::setCDC(uint8_t cdc)
{
	uint8_t _cdc = cdc & 0x3F;
	_cdc = _cdc << 0;
	uint8_t ffi = readRegister8( MPR121_CONFIG1 );
	ffi = ffi & 0xC0;
	
	stopMode();
	writeRegister(MPR121_CONFIG1, ffi | _cdc );
	runMode();
}

void Limulo_MPR121::setCDT(uint8_t cdt)
{
	uint8_t _cdt = cdt & 0x07;
	_cdt = _cdt << 5;
	uint8_t sfi_esi = readRegister8( MPR121_CONFIG2 );
	sfi_esi = sfi_esi & 0x1F;
	
	stopMode();
	writeRegister(MPR121_CONFIG2, sfi_esi | _cdt );
	runMode();
}

/* SET DEBOUNCE
* Set how many additional readings must be 
* perceived before detecting a touch or release
*/
void Limulo_MPR121::setDebounces(uint8_t touch, uint8_t release)
{
	uint8_t _touch = touch & 0x07;
	_touch = _touch << 0;
	
	uint8_t _release = release & 0x07;
	_release = _release << 4;
	
	stopMode();
	writeRegister( MPR121_DEBOUNCE, (_release | _touch) );
	runMode();
	
} 

/* Rising scenario 
* when filtered data greater than baseline values 
*/
void Limulo_MPR121::setRising(uint8_t mhd, uint8_t nhd, uint8_t ncl, uint8_t fdl)
{
	uint8_t _mhd = mhd & 0x3F;
	uint8_t _nhd = nhd & 0x3F;
	
	stopMode();
  	writeRegister(MPR121_MHDR, _mhd); 	// maximum half-delta (0 - 63) 
  	writeRegister(MPR121_NHDR, _nhd);	// noise half-delta (0 - 63)
  	writeRegister(MPR121_NCLR, ncl);	// noise count limit
  	writeRegister(MPR121_FDLR, fdl);	// filter delay count
	runMode();	
}

/* Falling scenario 
* when filtered data are lower than baseline values 
*/
void Limulo_MPR121::setFalling(uint8_t mhd, uint8_t nhd, uint8_t ncl, uint8_t fdl)
{
	uint8_t _mhd = mhd & 0x3F;
	uint8_t _nhd = nhd & 0x3F;
	
	stopMode();
  	writeRegister(MPR121_MHDF, _mhd); 	// maximum half-delta (0 - 63) 
  	writeRegister(MPR121_NHDF, _nhd);	// noise half-delta (0 - 63)
  	writeRegister(MPR121_NCLF, ncl);	// noise count limit
  	writeRegister(MPR121_FDLF, fdl);	// filter delay count
	runMode();	
}

/* Touched scenario 
* when electrodes are in touch status 
*/
void Limulo_MPR121::setTouched(uint8_t nhd, uint8_t ncl, uint8_t fdl)
{
	uint8_t _nhd = nhd & 0x3F;
	
	stopMode();
  	writeRegister(MPR121_NHDT, _nhd);	// noise half-delta (0 - 63)
  	writeRegister(MPR121_NCLT, ncl);	// noise count limit
  	writeRegister(MPR121_FDLT, fdl);	// filter delay count
	runMode();	
}

void Limulo_MPR121::setMHD(uint8_t rising, uint8_t falling) 
{
	stopMode();
  	writeRegister(MPR121_MHDR, rising); 
  	writeRegister(MPR121_MHDF, falling);
	runMode();
}

void Limulo_MPR121::setNHD(uint8_t rising, uint8_t falling, uint8_t touched) 
{
	stopMode();
  	writeRegister(MPR121_NHDR, rising); 
  	writeRegister(MPR121_NHDF, falling); 
  	writeRegister(MPR121_NHDT, touched); 
	runMode();
}

void Limulo_MPR121::setNCL(uint8_t rising, uint8_t falling, uint8_t touched) 
{
	stopMode();
  	writeRegister(MPR121_NCLR, rising); 
  	writeRegister(MPR121_NCLF, falling); 
  	writeRegister(MPR121_NCLT, touched); 
	runMode();
}

void Limulo_MPR121::setFDL(uint8_t rising, uint8_t falling, uint8_t touched) 
{
	stopMode();
  	writeRegister(MPR121_FDLR, rising); 
  	writeRegister(MPR121_FDLF, falling); 
  	writeRegister(MPR121_FDLT, touched); 
	runMode();
}



/* SET THR ///////////////////////////////////////////////////////////////////////////////
* TOUCH TH and RELEASE TH are values comprised between 0 and 255.
* These values are used to detect a touch and a release according to these formulae:
*
* 		Touch condition = (Baseline - Filtered Data) > Touch Th
*		Release condition = (Baseline - Filtered Data) < Release Th
*
* These values affect register between 0x41 - 0x5A.
* See Technical Note AN3892 for more details.
*/

void Limulo_MPR121::setThresholds(uint8_t touch, uint8_t release) {
  stopMode();
  for (uint8_t i=0; i<12; i++) {
    writeRegister(MPR121_TOUCHTH_0 + 2*i, touch);
    writeRegister(MPR121_RELEASETH_0 + 2*i, release);
  }
  runMode();  
}


uint16_t  Limulo_MPR121::filteredData(uint8_t t) {
  if (t > 12) return 0;
  return readRegister16(MPR121_FILTDATA_0L + t*2);
}

uint16_t  Limulo_MPR121::baselineData(uint8_t t) {
  if (t > 12) return 0;
  uint16_t bl = readRegister8(MPR121_BASELINE_0 + t);
  return (bl << 2);
}

uint16_t  Limulo_MPR121::touched(void) {
  uint16_t t = readRegister16(MPR121_TOUCHSTATUS_L);
  return t & 0x0FFF;
}

// READ REGISTER ////////////////////////////////////////////////////////////////////////
uint8_t Limulo_MPR121::readRegister8(uint8_t reg) {
    Wire.beginTransmission(_i2caddr);
    Wire.write(reg);
    Wire.endTransmission(false);
    while (Wire.requestFrom(_i2caddr, 1) != 1);
    return ( Wire.read());
}

uint16_t Limulo_MPR121::readRegister16(uint8_t reg) {
    Wire.beginTransmission(_i2caddr);
    Wire.write(reg);
    Wire.endTransmission(false);
    while (Wire.requestFrom(_i2caddr, 2) != 2);
    uint16_t v = Wire.read();
    v |=  ((uint16_t) Wire.read()) << 8;
    return v;
}

// WRITE REGISTER ///////////////////////////////////////////////////////////////////////
// Writes 8-bits to the specified destination register
void Limulo_MPR121::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.write((uint8_t)(value));
    Wire.endTransmission();
}

// PRINT REGISTERS //////////////////////////////////////////////////////////////////////
// print all registers for debug purposes
void Limulo_MPR121::printRegisters( void )
{
  for (uint8_t i=0; i<0x80; i++) {
    Serial.print("$"); Serial.print(i, HEX); 
    Serial.print(": 0x"); Serial.println( readRegister8(i), HEX );
  }
}

void Limulo_MPR121::printRegister( uint8_t reg )
{
	Serial.print("$"); Serial.print(reg, HEX); 
    Serial.print(": 0x"); Serial.println( readRegister8( reg ), HEX );
}


// print CDC / CDT
// print CDC and CDT in a more readable way
void Limulo_MPR121::printCDC( void )
{
	uint8_t cdc = readRegister8( MPR121_CONFIG1 ) & 0x3F;
	Serial.print("CDC: ");
	Serial.print( cdc, DEC);
	Serial.println(" uA;");
}


void Limulo_MPR121::printCDT( void )
{
	uint8_t cdt = readRegister8( MPR121_CONFIG2 ) & 0xE0;
	cdt = cdt >> 5;
	signed int exp = cdt - 2;
	float time = (float) pow( 2, exp );
	Serial.print("CDT: ");
	Serial.print( time, DEC);
	Serial.println(" uS;");
}
