from distutils.core import setup, Extension

setup(name = 'listpModule', version = '1.0.0',  \
   ext_modules = [Extension('listpModule', ['py_list_param.c'])])