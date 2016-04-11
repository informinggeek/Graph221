#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>

////////////////////////////////////////////////////////////////////////////////
/// A stopwatch-like wrapper around chrono's high-resolution clock. The
/// durations are measured in nanoseconds.
////////////////////////////////////////////////////////////////////////////////
class timer {

  ///\name Local Types
  ///@{

  typedef std::chrono::high_resolution_clock           clock;
  typedef std::chrono::duration<double, std::nano>     nano_seconds;
  typedef std::chrono::time_point<clock, nano_seconds> time_stamp;

  ///@}
  ///\name Internal State
  ///@{

  time_stamp   last;           ///< The last measured time point.
  nano_seconds total;          ///< The total measured duration.
  bool         running{false}; ///< Is the timer running?

  public:

    ///@}
    ///\name Construction
    ///@{

    timer();
    ~timer() = default;

    ///@}
    ///\name Interface
    ///@{

    void start() noexcept;   ///< Start the timer.
    void stop() noexcept;    ///< Pause the timer and update total duration.
    void reset() noexcept;   ///< Reset to initial state.
    void restart() noexcept; ///< Reset and start the timer.

    double elapsed() const noexcept;  ///< Get the total elapsed time in ns.

    ///@}
};

#endif
