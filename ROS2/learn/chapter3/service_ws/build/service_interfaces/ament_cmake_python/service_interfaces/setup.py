from setuptools import find_packages
from setuptools import setup

setup(
    name='service_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('service_interfaces', 'service_interfaces.*')),
)
