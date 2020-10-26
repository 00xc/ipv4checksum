import os
import pathlib
from setuptools import setup
from distutils.core import Extension

if __name__ == "__main__":

	current_directory = pathlib.Path(__file__).parent.absolute()
	module = Extension('ipv4checksum', sources = [os.path.join(current_directory, "src", "ipv4checksum.c")])

	setup(
		name="ipv4checksum",
		version="1.0.0",
		description="Python bindings for IPv4 checksum computation",
		author="https://github.com/00xc",
		author_email="00xc@protonmail.com",
		setup_requires=['wheel'],
		ext_modules=[module],
	)