/********************************************************
 * CANAL INTERNET E COISAS
 * Função hold
 * 04/2025 - Andre Michelon
 */

void hold(unsigned long ms) {
  uint32_t start = millis();
  while ((millis() - start) < ms) {
    yield();
  }
}
