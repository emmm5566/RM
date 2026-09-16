from setuptools import find_packages, setup

package_name = 'autopartol_robot'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        # 拷贝到install目录下
        ('share/' + package_name+"/config", ['config/partol_config.yaml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='emmm',
    maintainer_email='18924532087@163.com',
    description='TODO: Package description',
    license='Apache-2.0',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [ 
            # 添加可执行节点
            'partol_node = autopartol_robot.partol_node:main',
        ],
    },
)
