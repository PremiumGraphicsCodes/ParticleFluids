from distutils.core import setup, Extension

setup(name = 'multiplyList', version = '1.0.0',  \
   ext_modules = [Extension('multiplyList', ['py_list_list.c'])])