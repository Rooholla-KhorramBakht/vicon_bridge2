# from setuptools import setup

# setup()

from setuptools import find_packages
from distutils.core import setup

setup(
    name='ViconBridge',
    version='1.0.0',
    author='Rooholla Khorrambakht',
    license="BSD-3-Clause",
    packages=find_packages(),
    author_email='rk4342@nyu.edu',
    description='A DDS interface to get the tracking information from the vicon_bridge2.',
    install_requires=[
    ]
)