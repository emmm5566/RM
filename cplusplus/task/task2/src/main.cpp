#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Robot.h"

enum Color
{
    RED,
    BLUE,
};

enum Target
{
    BUILDINGS,
    ROBOTS,
};


int main()
{
    //生成一个种子用于随机数的生成
    auto seed = time(0);
    srand(seed);

    //使用vector容器存放红蓝双方机器人及建筑物
    //这里四个参数分别为 机器人类型 生命值 攻击力 命中率
    auto guard = Robot("Guard", 600, 5, 0.7);       //0哨兵
    auto infantry = Robot("Infantry", 200, 5, 0.8); //1步兵
    auto hero = Robot("Hero", 250, 100, 0.5);       //2英雄
    std::vector<Robot> half_robots = {guard, infantry, hero};
    std::vector<decltype(half_robots)> robots(2, half_robots);

    //参数为 建筑物类型 生命值
    auto outpost = Building("Outpost", 2000); //0前哨站
    auto base = Building("Base", 5000);       //1基地
    std::vector<Building> half_buildings = {outpost, base};
    std::vector<decltype(half_buildings)> buildings(2, half_buildings);

    int i = 0;

    while (1)
    {
        //基地无敌机制 不需要可以直接注释掉。（在比赛中，在前哨战摧毁之前，基地处于无敌状态），大家可以先注释掉。
        //等做完没有无敌和护盾机制的任务后再开启。
        buildings[RED][1].Invincible = buildings[RED][0].Survive();
        buildings[BLUE][1].Invincible = buildings[BLUE][0].Survive();

        //基地护盾机制 不需要可以直接注释掉。（在比赛中，只要哨兵还在巡逻区域，基地护甲就不会打开）
        buildings[RED][1].Protected = robots[RED][0].Survive();
        buildings[BLUE][1].Protected = robots[BLUE][0].Survive();

        //决定进攻方->在进攻方vector中随机选取事件主体->随机选取受击对象进行攻击
        Color color = static_cast<Color>(rand() % 2);    //决定进攻方（0红/1蓝）
        Target target = static_cast<Target>(rand() % 2); //决定进攻对象（0建筑物/1机器人）

        //进攻方和防守方随机生成
        auto& attacker = robots[color][rand() % 3];
        //判断进攻对象
        if (target == BUILDINGS)
        {   //进攻对象为建筑物，随机选取一个建筑物作为目标
            auto &building_target = buildings[!color][rand() % 2];
            attacker.Hit(building_target);
        }
        else
        {   //进攻对象为机器人，随机选取一个机器人作为目标
            auto &robot_target = robots[!color][rand() % 3];
            attacker.Hit(robot_target);
        }

        //胜利判断条件
        if (!(buildings[BLUE][1].Survive()))
        {
            std::cout << "蓝方基地摧毁，红方获胜" << std::endl;
            break;
        }
        else if (!(buildings[RED][1].Survive()))
        {
            std::cout << "红方基地摧毁，蓝方获胜" << std::endl;
            break;
        }
        
        i++;
        //每循环100次输出当前状态
        if (i % 100 == 0)
        {
            std::cout << "当前循环次数为" << i << std::endl;
            std::cout << "B_Outpost HP:" << buildings[BLUE][0].Health_ << std::endl;
            std::cout << "R_Outpost HP:" << buildings[RED][0].Health_ << std::endl;
            std::cout << "R_Guard HP:" << robots[RED][0].Health_ << std::endl;
            std::cout << "B_Guard HP:" << robots[BLUE][0].Health_ << std::endl;
            std::cout << "R_Base HP:" << buildings[RED][1].Health_ << std::endl;
            std::cout << "B_Base HP:" << buildings[BLUE][1].Health_ << std::endl;
            std::cout << std::endl;
        }
    }
}
