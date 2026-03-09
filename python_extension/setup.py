from distutils.core import setup, Extension

module = Extension('stats_c', sources=['stats_module.c'])

setup(name='stats_c',
      version='1.0',
      description='C extension for fast statistics',
      ext_modules=[module])
      