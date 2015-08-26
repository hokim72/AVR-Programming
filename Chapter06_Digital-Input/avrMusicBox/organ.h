// Plays a note for the given duration. None of these times are
// calibrated to actual notes or tempi. It's all relative to TIMEBASE.
void playNote(uint16_t wavelength, uint16_t duration);

// Does nothing for time equal to the passed duration.
void rest(uint16_t duration);
