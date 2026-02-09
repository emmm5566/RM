from setuptools import find_packages
from setuptools import setup

setup(
    name='example_ros2_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('example_ros2_interfaces', 'example_ros2_interfaces.*')),
)
