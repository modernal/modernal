from setuptools import Extension, setup

ext = Extension(
    name='modernal',
    sources=['modernal/modernal.cpp'],
    extra_compile_args=['-fpermissive'],
    depends=['setup.py'],
)

setup(
    name='modernal',
    version='0.1.0',
    ext_modules=[ext],
)
