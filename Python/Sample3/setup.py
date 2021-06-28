from distutils.core import setup, Extension

setup(name = 'plistModule', version = '1.0.0',  \
   ext_modules = [Extension('plistModule', ['py_param_list.c'])])