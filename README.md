# Zephyr Workqueue LED Demo

This project is a minimal Zephyr application that toggles the board LED using a timer-driven workqueue.

## Overview

The application:

- configures the LED connected to the `led0` alias
- starts a periodic timer
- submits a `k_work` item from the timer callback
- toggles the LED in the work handler

This is a simple example of using `k_timer` and `k_work` together in Zephyr.

## Project files

- `CMakeLists.txt` — Zephyr application configuration
- `prj.conf` — project configuration, including timer interval
- `src/main.c` — main application logic
- `build_dk/` — generated build directory for the Nordic nrf54l15dk target

## Configuration

The timer interval is set in `prj.conf`:

```conf
CONFIG_TIMER_INTERVAL=1000
```

That value is interpreted as milliseconds, so the LED toggles once per second.

## Requirements

This project expects a Zephyr/NCS environment, including:

- Zephyr / Nordic Connect SDK
- `west`
- a compatible board target such as `nrf54l15dk/nrf54l15/cpuapp`

## Build

From the project root:

```bash
west build -p always -b nrf54l15dk/nrf54l15/cpuapp .
```

If you are using the generated build directory already present in this workspace, the configuration is under `build_dk/`.

## Flash

```bash
west flash
```

## Expected behavior

After flashing the firmware, the LED connected to the `led0` alias should blink at a 1-second interval.

## Notes

- The application uses `GPIO_DT_SPEC_GET` with the `led0` devicetree alias.
- The timer callback does not toggle the LED directly; it submits work to be executed asynchronously by the system workqueue.
