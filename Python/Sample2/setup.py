from distutils.core import setup, Extension

setup(name = 'addModule', version = '1.0.0',  \
   ext_modules = [Extension('addModule', ['py_add.c'])])