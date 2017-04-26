from distutils.core import setup, Extension
import numpy as np

setup(
    ext_modules=[Extension("_nw", ["_nw.c", "nw.c"])]
)	
