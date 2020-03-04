/*Author :		1. นายกิตติกรณ์  บรรจงปรุ
				2. นายยุทธศาสตร์  นอขุนทด
				3. นายปกรณ์ ถาวรสันต์
Code :			1. 59172110122-0
				2. 59172110214-1
				3. 59172110223-9
Section :		CPE.59241
Lab No. :		Lab Stack (ข้อ 10)
Course :		04-061-212 Data Structures and Algorithms Laboratory
Due Date :		18/3/2561
Instruction :	A. Supattra Kerdmec
Description :	เพื่อได้ศึกษาโครงสร้างข้อมูลแบบ Stack และการประยุกต์ใช้งาน Stack
*/

#include<iostream>
#include<string>
#include<stack>

using namespace std;

string InfixToPostfix(string infix);  //ประกาศฟังก์ชัน InfixToPostfix ใช้ในการแปลง Infix เป็น Postfix
string CheckError(string ce);		//ประกาศฟังก์ชัน CheckError ใช้ในการตรวจสอบวงเล็บ
int Operand(char ch);				//ประกาศฟังก์ชัน Operand เพื่อตรวจสอบตัวดำเดินการ

int main()
{
	string infix;		//ประกาศตัวแปร infix เพื่อเก็บ

	do
	{
		cout << "Input : ";
		cin >> infix;
	} while (CheckError(infix) == ""); //วนรับค่าจนกว่าฟังก์ชัน CheckError จะไม่เท่ากับช่องว่าง

	cout << "Output : " << InfixToPostfix(infix) << endl; 
	return 0;
}

string CheckError(string ce) // ประกาศฟังก์ชัน CheckError ใช้ในการตรวจสอบหา Error ของวงเล็บ
{
	string Er = "";
	char cha;
	int B = 0, A = 0, C; 

	for (int i = 0; ce[i]; i++) //วนรอบเพื่อทำการตรวจสอบข้อมูลใน Stack แต่ละตัว
	{
		cha = ce[i];
		if (cha == '(') //ถ้า cha เท่ากับ วงเล็บเปิด
			A += 1; //เป็นจำนวนวงเล็บเปิด
		if (cha == ')') //ถ้า cha เท่ากับ วงเล็บปิด
			B += 1; //เป็นจำนวนวงเล็บปิด
	}
	if (A != B) //ถ้า วงเล็บเปิด ไม่เท่ากับ วงเล็บปิด
	{
		cout << "Syntex Error !!" << endl; 
		return Er; //ส่งค่า Er กลับไป
	}
	return ce; //ส่งค่า ce กลับไป

}

string InfixToPostfix(string infix) //ประกาศฟังก์ชัน InfixToPostfix เพื่อใช้ในการเปลี่ยนจาก Infix เป็น Postfix
{
	string postfix = "";
	stack <char> Stack;
	char ch;

	for (int i = 0; infix[i]; i++) //
	{
		ch = infix[i];//กำหนดให้ตัวแปร ch เก็บตัวแปร infix ในแต่ล่ะช่อง
		if (ch == '(') //ถ้าเจอวงเล็บเปิด
			Stack.push(ch); //เก็บลงใน stack
		else if (ch == ')') //ถ้าเจอวงเล็บปิด
		{
			while (!Stack.empty() && Stack.top() != '(') //หากสแตกไม่ว่างและสะแตกบนสุดไม่ใช้วงเล็บเปิด
			{
				postfix = postfix + Stack.top(); //เพิ่มสแตกบนสุดลงในตัว postfix
				Stack.pop(); //ทำการ pop สแตกออก
			}

			if (!Stack.empty() && Stack.top() == '(') //ถ้าตกไม่ว่างและสะแตกบนสุดเป็นวงเล็บเปิด
				Stack.pop(); //ทำการ pop สแตกออก

		}
		else
		{
			int priority = Operand(ch); //กำหนดให้ตัวแปร priority มีค่าเท่ากับเรียกใช้ฟังชั้น operand และส่งค่าตัวแปร ch ไป
			if (priority == 0) //ถ้าไม่พบตัวดำเนินการ
				postfix = postfix + ch; //ให้เพิ่มตัวดำเนินการลงใน postfix
			else
			{
				if (Stack.empty()) //ถ้า stack ว่าง
					Stack.push(ch);//เก็บลงใน stack
				else
				{
					while (!Stack.empty() && Stack.top() != '('&& priority<Operand(Stack.top())) //หากสแตกไม่ว่างและสะแตกบนสุดไม่เท่ากับวงเล็บเปิดและ priority น้อยกว่า operand
					{
						postfix = postfix + Stack.top(); //เพิ่มสแตกบนสุดลงในตัว postfix
						Stack.pop(); //ทำการ pop สแตกออก
					}
					Stack.push(ch); //เก็บลงใน stack
				}

			}
		}
	}

	while (!Stack.empty()) //วนรอบจนกว่า Stack จะว่าง
	{
		postfix += Stack.top(); //เพิ่มสแตกบนสุดลงในตัว postfix
		Stack.pop(); //ทำการ pop สแตกออก
	}

	return postfix; //ส่งค่า postfix กลับไป 
}

int Operand(char ch) //ประกาศฟังก์ชัน Operand เพื่อใช้ในการตรวจสอบตัวดำเดินการต่างๆ
{
	if (ch == '^' || ch == '**') //ถ้า ch เท่ากับ ^ หรือ ch เท่ากับ ** 
		return 3; //ส่งค่า 3 กลับไป
	else if (ch == '/' || ch == '*') //มิฉะนั้นแล้ว ถ้า ch เท่ากับ / หรือ ch เท่ากับ * 
		return 2; //ส่งค่า 2 กลับไป
	else if (ch == '+' || ch == '-') //มิฉะนั้นแล้ว ถ้า ch เท่ากับ + หรือ ch เท่ากับ -
		return 1; //ส่งค่า 1 กลับไป
	else //มิฉะนั้นแล้ว
		return 0; //ส่งค่า 0 กลับไป
}
