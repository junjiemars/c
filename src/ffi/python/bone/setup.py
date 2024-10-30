from setuptools import setup, Extension

# Define the extension module
nore_module = Extension("nore", sources=["foo.c"])

# Setup the module
setup(
    name="nore",
    version="1.0",
    description="A simple example C dynamic extension for Python",
    ext_modules=[nore_module],
)
