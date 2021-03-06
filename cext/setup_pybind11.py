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

class get_pybind_include(object):
    """Helper class to determine the pybind11 include path

    The purpose of this class is to postpone importing pybind11
    until it is actually installed, so that the ``get_include()``
    method can be invoked. """

    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)


# As of Python 3.6, CCompiler has a `has_flag` method.
# cf http://bugs.python.org/issue26689
def has_flag(compiler, flagname):
    """Return a boolean indicating whether a flag name is supported on
    the specified compiler.
    """
    import tempfile
    with tempfile.NamedTemporaryFile('w', suffix='.cpp') as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        try:
            compiler.compile([f.name], extra_postargs=[flagname])
        except setuptools.distutils.errors.CompileError:
            return False
    return True


def cpp_flag(compiler):
    """Return the -std=c++[11/14] compiler flag.

    The c++14 is preferred over c++11 (when it is available).
    """
    # Hack, won't build on mac os x otherwise
    return '-std=c++11'
    if has_flag(compiler, '-std=c++14'):
        return '-std=c++14'
    elif has_flag(compiler, '-std=c++11'):
        return '-std=c++11'
    else:
        raise RuntimeError('Unsupported compiler -- at least C++11 support '
                           'is needed!')


class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    c_opts = {
        'msvc': ['/EHsc'],
        'unix': [],
    }

    if sys.platform == 'darwin':
        c_opts['unix'] += ['-stdlib=libc++', '-mmacosx-version-min=10.7']

    def build_extensions(self):
        ct = self.compiler.compiler_type
        opts = self.c_opts.get(ct, [])
        if ct == 'unix':
            opts.append('-DVERSION_INFO="%s"' % self.distribution.get_version())
            opts.append(cpp_flag(self.compiler))
            if has_flag(self.compiler, '-fvisibility=hidden'):
                opts.append('-fvisibility=hidden')
        elif ct == 'msvc':
            opts.append('/DVERSION_INFO=\\"%s\\"' % self.distribution.get_version())
        for ext in self.extensions:
            ext.extra_compile_args = opts + EXTRA_COMPILE_ARGS
        build_ext.build_extensions(self)

test_requirements = [
]


ext_modules = [
    # pybind11
    Extension(
        "pbPerson",
        sources=[
            'pybind11/pyb_Person.cpp',
            'pybind11/Person.cpp',
        ],
        include_dirs=[
            'pybind11/',
            # Path to pybind11 headers
            get_pybind_include(),
            get_pybind_include(user=True)
        ],
        language='c++'
    ),
]

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
    cmdclass={'build_ext': BuildExt},
)

