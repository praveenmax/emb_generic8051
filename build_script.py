Import("env")
import os
import subprocess

def build_program(*args, **kwargs):
    # Access environment variable
    include_path = os.getenv("SDCC_INCLUDE_PATH", "")

    # Define your source and output paths
    src_file = "src/main.c"
    output_file = ".pio/build/at89c51/main.hex"
    
    # Call the sdcc compiler with desired flags
    subprocess.call(["sdcc",
                      "-mmcs51",
                      f"-I{include_path}",
                       "-o", output_file, 
                       src_file])

# Register the build function
env.AddPreAction("buildprog", build_program)
