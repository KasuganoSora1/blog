// data.cpp : 定义控制台应用程序的入口点。
//读取csv中的钻孔 并根据钻孔空间关系 判断是否存在埋藏岩熔

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <set>
#include <iomanip>
using namespace std;
class stratum {
public:
	string stratum_name;
	float stratum_hei;

	stratum():stratum_name(""),stratum_hei(0.0f){}
	stratum(string stratum_name,float stratum_hei):stratum_name(stratum_name),stratum_hei(stratum_hei){}
	stratum(const stratum& st){
		this->stratum_name = st.stratum_name;
		this->stratum_hei = st.stratum_hei;
	}

	const stratum& operator=(const stratum& st) {
		this->stratum_name = st.stratum_name;
		this->stratum_hei = st.stratum_hei;
		return (*this);
	}
	bool operator>(const stratum& other) const{
		if (abs(this->stratum_hei-other.stratum_hei)>0.001 && this->stratum_hei < other.stratum_hei) {
			return true;
		}
		else {
			return false;
		}
	}
};
class borehole {
public:
	int i;
	double X;
	double Y;
	string project_name;
	set<stratum> stratums;
	
	borehole():i(-1),X(0.0f),Y(0.0f),project_name(""),stratums(){}
	borehole(int i, double X, double Y, string project_name)\
	:i(i),X(X),Y(Y),project_name(project_name),stratums(){
	}
	borehole(const borehole& bh) {
		this->i = bh.i;
		this->X = bh.X;
		this->Y = bh.Y;
		this->project_name = bh.project_name;
		this->stratums.insert(bh.stratums.cbegin(), bh.stratums.cend());
		//this->stratums = bh.stratums;
	}

	bool operator <(const borehole& other) const{
		if (abs(this->X-other.X>0.0001) && this->X < other.X) {
			return true;
		}
		else if(abs(this->Y - other.Y)>0.0001 && this->Y < other.Y) {
			return true;
		}
		else {
			return false;
		}
	}
};

void str2stratum(const char* str,set<borehole>& sb) {
	int len = strlen(str);
	string cppstr = string(str);
	size_t first=cppstr.find(',', 0);
	size_t second = cppstr.find(',', first+1);
	size_t third = cppstr.find(',', second+1);
	size_t forth = cppstr.find(',', third+1);
	size_t fifth = cppstr.find(',', forth+1);
	size_t sixth = cppstr.find(',', fifth+1);
	int id = atoi(cppstr.substr(0, first).c_str());
	//cout << "id:" << id<<" ";
	string project_name = string(cppstr.substr(first + 1, second - first - 1).c_str());
	//cout << "project_name:" << project_name.c_str() <<" ";
	double stratum_hei = atof(cppstr.substr(third + 1, forth - third - 1).c_str());
	//cout << "stratum_hei:" << stratum_hei  <<" ";
	string stratum_name = cppstr.substr(forth + 1, fifth - forth - 1).c_str();
	//cout << "stratum_name:" << stratum_name.c_str()  <<" ";
	double X =strtod(cppstr.substr(fifth + 1, sixth - fifth - 1).c_str(),NULL);
	//cout << "X:" << X <<fixed <<" ";
	double Y = strtod(cppstr.substr(sixth+ 1,cppstr.size()-sixth).c_str(),NULL);
	//cout << "Y:" << Y<<fixed << endl;
	borehole bh(id,X,Y,project_name);

	set<borehole>::const_iterator ite = sb.find(bh);
	if (ite != sb.end()) {
		stratum st(stratum_name,(float)stratum_hei);
		set<stratum>::iterator site = ite->stratums.find(st);
		if (site == ite->stratums.end()) {
			const_cast<set<stratum>&>(ite->stratums).insert(st);
		}
	}
	else {
		stratum st(stratum_name,(float)stratum_hei);
		set<stratum>::iterator site = bh.stratums.find(st);
		if (site == bh.stratums.end()) {
			bh.stratums.insert(st);
		}
		sb.insert(bh);
	}
}
bool is_mc(const borehole& b) {
	bool is_yr=false;
	bool is_mc = false;
	set<stratum>::const_iterator ite = b.stratums.cbegin();
	for (set<stratum>::iterator ite = b.stratums.cbegin(); \
		ite!=b.stratums.cend();\
		ite++
		) {
		if (ite->stratum_name.find("大理岩") != -1 || \
			ite->stratum_name.find("灰岩") != -1 || \
			ite->stratum_name.find("溶洞") != -1 || \
			ite->stratum_name.find("白云岩") != -1
			) {
			is_yr = true;
			break;
		}
	}
	if (is_yr) {
		for (; ite !=b.stratums.cend(); ite++) {
			if(ite->stratum_name.find("泥岩")!=-1 || \
				ite->stratum_name.find("砂岩") != -1 || \
				ite->stratum_name.find("页岩") != -1
				){
				return true;
			}
		}
	}else {
		return false;
	}
}
int main()
{
	string line;
	fstream fs("./lg-all.csv");
	char str[500];
	set<borehole> sb;
	memset(str, 0, 500 * sizeof(char));
	cout << "start reading csv file" << endl;
	while (!fs.eof()) {
		fs.getline(str, 500);
		str2stratum(str, sb);
	}
	fs.flush(); fs.close();
	ofstream fos("./result.txt",ofstream::out);
	cout << "end reading csv file,there are " << sb.size() << " borehole in this csv" << endl;
	for (set<borehole>::const_iterator ite = sb.cbegin(); \
		ite != sb.cend();ite++) {
		if (is_mc(*ite)) {
			cout <<fixed<< ite->X << "," <<fixed<< ite->Y << "     borehole is mcyr" << endl;
			fos << fixed << ite->X << "," << fixed << ite->Y << "\n";
		}
	}
	fos.flush(); fos.close();
	system("PAUSE");
	return 0;
}

