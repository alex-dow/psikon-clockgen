"""
Call pioasm
"""
from os.path import join, exists
import subprocess
import glob
import sys
Import("env")

platform = env.PioPlatform();
srcDir   = env['PROJECT_SRC_DIR']
pioFiles = glob.glob(join(srcDir, '*.pio'), recursive=True)

if pioFiles:
    frameworkDir = platform.get_package_dir("framework-arduinopico")
    picoSDKDir = join(frameworkDir, 'pico-sdk')
    pioasmDir = join(picoSDKDir, 'tools', 'pioasm')
    pioasmExec = join(pioasmDir, 'pioasm')

    if not exists(frameworkDir):
        print("Error: framework-arduinopico not installed")
        sys.exit()
    if not exists(pioasmExec):

        print("Error: no pioasm executable found at %s" % pioasmExec)
        subprocess.call(['cmake','.'], cwd=pioasmDir)
        subprocess.call(['make'], cwd=pioasmDir)
        if not exists(pioasmExec):
            print("Error: no pioasm executable found at %s" % pioasmExec)

    for filename in pioFiles:
        subprocess.call([pioasmExec, '-o', 'c-sdk', filename, filename + '.h'])

