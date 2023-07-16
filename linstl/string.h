class string
{
    //限定 = 左侧必须是左值
    string& operator=(const string&) &;
};