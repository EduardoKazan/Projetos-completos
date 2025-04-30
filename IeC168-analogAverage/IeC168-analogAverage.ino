/********************************************************
 * CANAL INTERNET E COISAS
 * Função analogAverage
 * 04/2025 - Andre Michelon
 */

uint16_t analogAverage(const uint8_t &a) {
  // Average analog read
  uint32_t l = 0;
  for (uint8_t b = 0; b < 100; b++) {
    l += analogRead(a);
    yield();
  }
  return l / 100;
}
