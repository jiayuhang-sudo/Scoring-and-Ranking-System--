#define PlayerNumber 5
#define JudgeNumber 10

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

using std::string;
using std::vector;
using std::deque;
using std::cout;
using std::endl;

//评委打分案例（sort算法排序）
//创建5个选手（姓名，得分），10个评委对5个选手进行打分
//得分规则：去除最高分，去除最低分，取出平均分
//按得分对5名选手进行排名

//选手（姓名，得分）//使用类的明显标志!!!
class Player
{
public:
    /* data */
    string mName;
    deque<double> mAllScore;//去除最高分，去除最低分//双端处理用deque
    double mAverageScore;

public:
    Player(/* args */);
    ~Player();
};

//构造和析构函数, 类内声明, 类外初始化
Player::Player(/* args */) :mName(""), mAverageScore(0.0) {};
Player::~Player() {};

void PlayerNameInit(vector<Player>& vTemp)
{
    for (int i = 0; i < PlayerNumber; i++)
    {
        char Number = i + 1;
        vTemp[i].mName = "Player " + std::to_string(Number);//第一处错误: 需要用to_string将char转为string才能连接
    }
    cout << "已录入选手姓名!" << endl;
    cout << endl;
}

void JudgeScoring(vector<Player>& vTemp)
{
    for (int i = 0; i < PlayerNumber; i++)
    {
        for (int j = 0; j < JudgeNumber; j++)
        {
            double temp = (rand() % 21 + 80) / 10.0;//第二处错误: 想要得到小数, 不能是两个整数相除(默认取整), 用10.0
            vTemp[i].mAllScore.push_back(temp);//第三处错误: 容器初始化为空, 需要用push_back添加, 不能直接用下标
        }
    }
    cout << "已登记每位选手的所有成绩!" << endl;
    cout << endl;
}

void GetAversgeScore(vector<Player>& vTemp)
{
    for (int i = 0; i < PlayerNumber; i++)
    {
        sort(vTemp[i].mAllScore.begin(), vTemp[i].mAllScore.end());
        double TotalScaore = 0.0;//规范: double类型初始化用0.0
        for (int j = 1; j < JudgeNumber - 1; j++)
        {
            TotalScaore += vTemp[i].mAllScore[j];//第四处错误: 下标写错(尽量避免)
        }
        vTemp[i].mAverageScore = TotalScaore / (JudgeNumber - 2);
    }
    cout << "已计算出每位选手的平均成绩!" << endl;
    cout << endl;
}

//比较函数
bool ComparedByAverageScore(const Player& first,const Player& second)//用const保证不被修改, 用&避免拷贝, 提高效率, 也是规范
{
    return first.mAverageScore > second.mAverageScore;//第五处错误: 不能将自定义的类当基础类型比较
}

void RankingAndOutput(vector<Player>& vTemp)
{
    sort(vTemp.begin(), vTemp.end(), ComparedByAverageScore);//1.比较函数 2.仿函数 3.lambda
    for (int i = 0; i < PlayerNumber; i++)
    {
        cout << "第" << i + 1 << "名选手的姓名为 " << vTemp[i].mName << endl;
        cout << "最终成绩(去除最高分，去除最低分，取出平均分)为" << vTemp[i].mAverageScore << endl;
        cout << "所有成绩如下: (按从大到小排列)" << endl;
        for (int j = 0; j < JudgeNumber; j++)
        {
            cout << vTemp[i].mAllScore[j] << " ";
        }
        cout << endl << endl;
    }
    cout << endl << "成绩公示完毕!" << endl << endl;
}

void test()
{
    //创建5个选手（姓名，得分），10个评委对5个选手进行打分
    vector<Player> vRanking(PlayerNumber);//第六处错误: 用reserve方法只是预留空间, 并没有初始化对象, 所以用vector要默认构造
                                          //注意: 直接初始化的方式, 必须有默认构造, 适用于已知数量
    // Player p1, p2, p3, p4, p5;
    // vRanking.push_back(p1);
    // vRanking.push_back(p2);
    // vRanking.push_back(p3);
    // vRanking.push_back(p4);
    // vRanking.push_back(p5);
    PlayerNameInit(vRanking);
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