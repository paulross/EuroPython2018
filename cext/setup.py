from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools

__version__ = '0.0.1'

# Building: MACOSX_DEPLOYMENT_TARGET=10.9 python setup.py build_ext -f --inplace
# Testing: PYTHONPATH=. pytest --benchmark-name=long --benchmark-sort=name --benchmark-save=benchmark_00 --benchmark-warmup=on tests/unit/
# --benchmark-warmup=on is slow as it does about 10000 warmup iterations.
# Benchmark data in .benchmarks

# from setuptools import setup, find_packages
DEBUG = False

EXTRA_COMPILE_ARGS = [
    '-Wall',
    '-Wextra',
#     '-Werror',
#     '-Wfatal-errors',
#     '-pedantic',
]
if DEBUG:
    # Pybind11 in debug mode #if !defined(NDEBUG)
    EXTRA_COMPILE_ARGS += ['-DDEBUG', '-O0', '-g', '-UNDEBUG']


test_requirements = []


from Cython.Build import cythonize

ext_modules = [
    # CPython modules
    Extension("spam", ["cpython/spammodule.c"]),
    Extension("cp_demo", ["cpython/cp_demo.c"]),
]

# Cythonise and add Cython modules
ext_modules += cythonize("cython/cy_hello.pyx")
ext_modules += cythonize("cython/fib.pyx")
ext_modules += cythonize("cython/primes.pyx")
ext_modules += cythonize("cython/rect.pyx")

setup(
    name="ep2018cext",
    version="1.0",
    author='Paul Ross',
    author_email='apaulross@gmail.com',
    url='https://github.com/paulross/EuroPython2018',
    description='Helpdesk code during EuroPython2018. C extensions, Cython and pybind11.',
    ext_modules=ext_modules,
    install_requires = ['pybind11>=2.2'],
    tests_require = test_requirements,
)

