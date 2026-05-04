#include "Player.h"
#include <vector>
#include <ctime>

using std::vector;

void test()
{
    //创建5个选手
    vector<Player> vRanking(PLAYER_NUM);//第六处错误: 用reserve方法只是预留空间, 并没有初始化对象, 所以用vector要默认构造
                                          //注意: 直接初始化的方式, 必须有默认构造, 适用于已知数量
    // Player p1, p2, p3, p4, p5;
    // vRanking.push_back(p1);
    // vRanking.push_back(p2);
    // vRanking.push_back(p3);
    // vRanking.push_back(p4);
    // vRanking.push_back(p5);

    //初始化选手姓名
    PlayerNameInit(vRanking);

    //10个评委对5个选手进行打分
    JudgeScoring(vRanking);

    //去除最高分，去除最低分，取出平均分
    GetAversgeScore(vRanking);

    //按得分对5名选手进行排名并输出成绩
    RankingAndOutput(vRanking);
}

int main()
{
    srand( (unsigned int)time(NULL) );
    test();

    return 0;
}

//总结:

//总耗时130分钟, 共出现六处错误
//收获:
//1.练习了宏定义 
//2.知到sort算法属于algorithm库 
//3.学会生成随机数的方法并使用随机种子 
//4.了解构造和析构函数, 类内声明, 类外初始化的规范
//5.string和char连接方法
//6.想要得到小数, 不能是两个整数相除(默认取整), 需要有小数
//7.容器初始化为空, 需要用push_back添加, 不能直接用下标
//8.double类型初始化用0.0的规范
//9.比较函数参数规范, 与仿函数的区别
//10.reserve函数的本质, 以及deque没有reserve方法
//11.写完代码最好先自检, 锻炼自己的严谨性和编程能力
//12.auto的用法