# ESP32 QEMU Test Project

This is a minimal ESP-IDF project created to debug and test issues with the qemu-esp-xtensa emulator from Espressif. The goal is to create a controlled testing environment to identify potential conflicts or bugs when running ESP32 firmware in the emulator.

## Building the Project

```bash
# Build the firmware
pio run

# Generate compile_commands.json (for code analysis tools)
pio run -t compiledb
```

## Testing with QEMU

```bash
# Using Espressif's qemu-esp-xtensa
qemu-esp-xtensa [options] -kernel <path-to-built-firmware>
```

## Testing Strategy

This project serves as a baseline for adding components incrementally to identify which elements cause issues with the qemu-esp-xtensa emulator. The testing approach follows these steps:

1. Start with minimal ESP-IDF code
2. Add FreeRTOS tasks and features
3. Introduce peripheral initializations
4. Add framework components
5. Gradually incorporate custom code until the issue is reproduced

## Debug Notes

- Console output is set to verbose (CORE_DEBUG_LEVEL=5)
- The firmware will restart after a 10-second countdown
- Each test iteration should be documented to track what changes cause failures
