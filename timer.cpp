#include "timer.h"


timer::
timer() {
  reset();
}


void
timer::
start() noexcept {
  if(running) return;
  running = true;
  last = clock::now();
}


void
timer::
stop() noexcept {
  if(!running) return;
  running = false;
  total += clock::now() - last;
}


void
timer::
reset() noexcept {
  running = false;
  total = nano_seconds(0);
}


void
timer::
restart() noexcept {
  reset();
  start();
}


double
timer::
elapsed() const noexcept {
  return running ? ((clock::now() - last) + total).count() : total.count();
}
