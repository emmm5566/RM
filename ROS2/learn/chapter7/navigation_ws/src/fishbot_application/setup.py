from setuptools import find_packages, setup

package_name = 'fishbot_application'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
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
    #添加可执行文件
    entry_points={
        'console_scripts': [
            #配置节点启动项
            #将fishbot_application功能包下init_robot_pose.py中的main函数注册为可执行文件，命令名称为init_robot_pose
            #节点可执行文件名=功能包名.Python模块文件文件名:入口函数名
            "init_robot_pose = fishbot_application.init_robot_pose:main",
            "get_robot_pose = fishbot_application.get_robot_pose:main",
            "nav_to_pose = fishbot_application.nav_to_pose:main",
            "waypoint_follower = fishbot_application.waypoint_follower:main"
        ],
    },
)
