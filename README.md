# Zephyr Workqueue LED Sample

This project demonstrates a simple Zephyr pattern: a periodic timer schedules a work item, and the actual LED state change happens in the workqueue callback.

## Overview

The sample application:

- gets the `led0` alias from the board devicetree
- configures it as a GPIO output
- starts a repeating `k_timer`
- submits a `k_work` item from the timer callback
- toggles the LED inside the work handler

This is useful when the work must run outside the timer callback context, which is typically safer and more predictable in embedded systems.

## Files in this project

- `CMakeLists.txt` — Zephyr app definition
- `prj.conf` — build-time and runtime configuration
- `src/main.c` — LED and timer logic
- `build_dk/` — generated build output for the current target

## Target board

This sample is configured for the Nordic Semiconductor nRF54L15 DK:

- board target: `nrf54l15dk/nrf54l15/cpuapp`
- LED alias: `led0`

## Configuration

The blink interval is set in `prj.conf`:

```conf
CONFIG_TIMER_INTERVAL=1000
```

The value is in milliseconds, so the LED toggles once every second.

## Prerequisites

Before building, make sure you have:

- a working Zephyr / Nordic Connect SDK installation
- `west` installed and available on your PATH
- the correct board support files for the nRF54L15 DK
- a connected board or debug probe

## Build

From the project root, run:

```bash
west build -p always -b nrf54l15dk/nrf54l15/cpuapp .
```

This workspace already includes a generated build directory at `build_dk/` for the matching board configuration.

## Flash

```bash
west flash
```

## Expected result

After flashing the firmware, the LED connected to the `led0` alias should blink continuously at a 1-second interval.

## Implementation notes

- `GPIO_DT_SPEC_GET` is used to access the LED from the device tree.
- `K_TIMER_DEFINE` creates the periodic timer.
- `K_WORK_DEFINE` creates the deferred work item.
- The LED state change happens in `work_handler()`, not directly in the timer callback.

## Related Zephyr APIs

- `k_timer`
- `k_work`
- `gpio_pin_toggle_dt()`
- device tree aliases (`led0`)
