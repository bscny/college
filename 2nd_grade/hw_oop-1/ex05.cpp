#include<iostream>
#include<string>
#include<cstdarg>
#include<cstdlib>
using namespace std;

//DEBUG SETTINGS
#define   Debug   //THE SWITCH IS HERE

#define L0(fmt, args...)
#define L1(fmt, args...)        log_print("\033[1;31m", fmt, ## args)
#define L2(fmt, args...)        log_print("\033[1;33m", fmt, ## args)
#define L3(fmt, args...)        log_print("\033[1;34m", fmt, ## args)
#define L4(fmt, args...)        log_print("\033[1;35m", fmt, ## args)
void log_print(string color,const char *fmt, ...) {
#ifdef Debug
	va_list ap;
	unsigned int len=0;
	char buf[200], *p=NULL;
	va_start(ap, fmt);
	len = vsnprintf(buf, sizeof(buf), fmt, ap);
	if(len < sizeof(buf)) { // enough buf
		p = buf;
		if(len > 0) buf[len] = '\0';
	} else {
		p = new char[len+1];
		if(p) {
			vsnprintf(p, len, fmt, ap);
			if(len > 0) p[len] = '\0';
		} else printf("%s:error. new %dB\n", __func__, len+1);
	}
	if(len > 0) cout<<color<<p<<"\033[m";
	va_end(ap);
	if(p != buf) delete [] p;
#endif
}
//END OF DEBUG SETTINGS

class Subject{
	public:
		int grade;
};

class Student{
	public:
		void init(int s_n);
		void getname(string in_name);
		void getgrade(Subject g, int j);
		void sort();
		void avgcalculator();
		void display();
		double show_avg();
	private:
		int subject_num;
		string name;
		int *grades;
		double avg;
};

int cmpfunc1 (const void * a, const void * b)
{
	return ( *(int*)b - *(int*)a );
}

int cmpfunc2 (const void * a, const void * b)
{
	double aa,bb;

	aa = ((Student*)a)->show_avg();
	bb = ((Student*)b)->show_avg();

	return (int)( bb - aa );
}

void Student::init(int s_n){
	subject_num = s_n;

	grades = new int[s_n];
	avg = 0;
}

void Student::getname(string in_name){
	name = in_name;
}

void Student::getgrade(Subject g, int j){
	grades[j] = g.grade;

	avg += g.grade;
}

void Student::sort(){
	qsort(grades, subject_num, sizeof(int), cmpfunc1);
}

void Student::avgcalculator(){
	avg /= subject_num;
}

void Student::display(){
	cout << name << ":";
	for(int i = 0; i < subject_num; i++){
		cout << grades[i] << " ";
	}
	cout << avg << "\n";
}

double Student::show_avg(){
	return avg;
}

int main(int argc,char **argv){
	int class_num;
	int classmate_num, subject_num;
	Subject temp;
	string name;
	Student *students;
	Student t;

	cin >> class_num;
	for(int i = 0; i < class_num; i++){
		cin >> classmate_num;
		cin >> subject_num;

		students = new Student[classmate_num];

		//each class
		for(int k = 0; k < classmate_num; k++){
			students[k].init(subject_num);

			cin >> name;
			students[k].getname(name);
			for(int j = 0; j < subject_num; j++){
				cin >> temp.grade;
				students[k].getgrade(temp, j);
			}

			students[k].sort();
			students[k].avgcalculator();
			//students[k].display();
		}

		/*qsort(students, classmate_num, sizeof(Student), cmpfunc2);

		for(int k = 0; k < classmate_num; k++){
			students[k].display();
		}*/

		for(int ii = 0; ii < classmate_num; ii++){
			for(int kk = 0; kk < classmate_num-1; kk++){
				if(students[kk].show_avg() < students[kk+1].show_avg()){
					t = students[kk];
					students[kk] = students[kk+1];
					students[kk+1] = t;
				}
			}
		}
		

		for(int k = 0; k < classmate_num; k++){
			students[k].display();
		}
		cout << "==========\n";


		//print
	}


	return 0;
}
