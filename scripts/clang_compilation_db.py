import os

Import("env")

# Ensure output directory exists
if not os.path.exists(".pio/build/esp32dev"):
    os.makedirs(".pio/build/esp32dev")

# Enable compilation database
env.SetDefault(
    CCFLAGS=["--compilation-database=.pio/build/esp32dev/compile_commands.json"]
)


# Alternative: Generate compilation db at completion
def generate_compilation_database(target, source, env):
    env.Execute("pio run -t compiledb")


# Uncomment to use this method instead
# env.AddPostAction("$BUILD_DIR/${PROGNAME}.elf", generate_compilation_database)
