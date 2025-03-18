#!/bin/bash

# Path definitions
flash_image=".pio/build/esp32dev/flash_image.bin"
bootloader=".pio/build/esp32dev/bootloader.bin"
partition_table=".pio/build/esp32dev/partitions.bin"
app=".pio/build/esp32dev/firmware.bin"

# Check if files exist
if [ ! -f "$bootloader" ] || [ ! -f "$partition_table" ] || [ ! -f "$app" ]; then
  echo "Error: Required files not found:"
  ls -la "$bootloader" "$partition_table" "$app" 2>/dev/null
  echo "Please build the project first with: pio run"
  exit 1
fi

# Create flash image by merging bootloader, partition table and application
echo "Creating flash image..."
esptool.py --chip esp32 merge_bin -o "${flash_image}" --flash_mode dio --flash_freq 40m --flash_size 4MB \
  0x1000 "${bootloader}" \
  0x8000 "${partition_table}" \
  0x10000 "${app}" --fill-flash-size 4MB

# Check if flash image was created successfully
if [ ! -f "$flash_image" ]; then
  echo "Failed to create flash image"
  exit 1
fi

echo "Starting QEMU..."
qemu-esp-xtensa -nographic -machine esp32 -smp 1 -serial mon:stdio \
  -drive file="${flash_image}",if=mtd,format=raw
