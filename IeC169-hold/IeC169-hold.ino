/********************************************************
 * Função hold
 * 04/2025 
 */






void hold(unsigned long ms) {
  uint32_t start = millis();
  while ((millis() - start) < ms) {
    yield();
  }
}








