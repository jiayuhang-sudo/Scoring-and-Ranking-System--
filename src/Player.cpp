#include "Player.h"

//类定义

//构造和析构函数, 类内声明, 类外初始化
Player::Player(/* args */) :mName(""), mAverageScore(0.0) {};
Player::~Player() {};


//函数定义

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