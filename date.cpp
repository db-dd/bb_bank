#include<iostream>
#include "date.h"

using namespace std;
Date::Date(int Year, int Month, int Day)
{
    year=Year;
    month=Month;
    day=Day;
    int Days=0;
    for(int i=0;i<year;i++)
    {
        if(isLeapYear(i))
            Days=Days+366;
        else
            Days=Days+365;
    }
    switch(month){
        case 1:Days+=0;break;
        case 2:Days+=31;break;
        case 3:Days+=59;break;
        case 4:Days+=90;break;
        case 5:Days+=120;break;
        case 6:Days+=151;break;
        case 7:Days+=181;break;
        case 8:Days+=212;break;
        case 9:Days+=243;break;
        case 10:Days+=273;break;
        case 11:Days+=304;break;
        case 12:Days+=334;break;
//        default:cout<< "month error!"<<endl;
    }
    totalDays=Days+day;
}
void  Date::show() const
{
    cout<<getYear()<<"/"<<getMonth()<<"/"<<getDay()<<endl;
}	//输出当前日期
bool  Date::isLeapYear(int year)
{
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return true;
    else
        return false;
}	//判断当年是否为闰年
