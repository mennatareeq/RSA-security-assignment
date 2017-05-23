#include <iostream>
#include <string>
#include "stdio.h"

using namespace std;

const short CAPACITY = 1024;



void add(short p[], short q[], short sum[], short t1, short t2, short &size)
{
	short carry = 0;
	short t = 0;

	short diff;
	size = 0;

	if (t2 > t1)
	{
		t = t2;
		diff = t2 - t1;
	}
		
	else
	{
		t = t1;
		diff = t1 - t2;
	}
		




	for (short i = 0; i < t; i++)
	{

		if ((t1 > t2) && (i >= t2))
			q[i] = 0;


		if ((t2 > t1) && (i >= t1))
			p[i] = 0;

		short temp = 0;

		temp = p[i] + q[i] + carry;


		if (temp >= 10)
		{
			temp = temp - 10;
			sum[i] = temp;
			carry = 1;
		}
		else
		{
			sum[i] = temp;
			carry = 0;
		}

		if (i == t - 1)
		{
			if (carry == 1)
			{
				sum[i+1] = 1;
				size++;
			}
		}
		size++;

	}

}




void minuus(short p[], short q[], short min[], short t1, short t2, short &minsize, bool &neeg)
{

	minsize = 0;

	short answer [CAPACITY];

	short m[CAPACITY];


	if (t1<t2 || ((t1 == t2) && (q[t2 - 1] > p[t1 - 1])))
	{
		neeg = true;
		minsize = t1;

		for (short i = 0; i < t1; i++)
		{
			min[i] = p[i];
		}

		return;
	}

	for (short i = 0; i < t1; i++)
	{
		answer[i] = p[i];
	}

	short t = t2;

	for (short i = 0; i < t2; i++)
	{
		short temp = 0;

		temp = answer[i] - q[i];

		if (temp < 0)
		{
			if (i != t1 - 1)
			{
				temp = temp + 10;

				if (answer[i + 1] != 0)
				{
					answer[i + 1]--;
				}

				else
				{
					for (short j = i + 1; j < t1; j++)
					{

						if (answer[j] != 0)
						{
							answer[j]--;
							break;
						}
						else
						{
							answer[j] = 9;
						}


					}
				}


				m[i] = temp;
				minsize++;
			}

			else
			{
				temp = -temp;
				neeg = true;
				m[i] = temp;
				minsize++;


				for (short i = 0; i < t1; i++)
				{
					m[i] = p[i];
				}
				minsize = t1;

			}
			
		}

		else
		{
			m[i] = temp;
			minsize++;
		}

	}



	// if there is an error check here 
	if (t1 > t2)
	{
		for (short i = t2; i < t1; i++)
		{
			

			m[i] = answer[i];
			minsize++;


		}

	}


	for (short i = minsize - 1; i >= 0; i--)
	{
		if ((m[i] == 0) && ( minsize>1))
			minsize--;
		else
			break;
	}

	

	for (short i = 0; i < minsize; i++)
	{
		min[i] = m[i];
	}

}



void multiply(short p[], short q[], short mul[], short t1, short t2, short &mulsize, short &size)
{
	short carry = 0;
	mulsize = 0;
	size = 0;
	short nsize = 0;

	short p1[CAPACITY];
	short q1[CAPACITY];
	short tempmul[CAPACITY];


	if (t1 < t2)
	{
		for (short i = 0; i < t2; i++)
		{
			p1[i] = q[i];
			
		}

		for (short i = 0; i < t1; i++)
		{
			q1[i] = p[i];
		}


		int temp = t1;
		t1 = t2;
		t2 = temp;
	}

	else 
	{
		for (short i = 0; i < t1; i++)
		{
			p1[i] = p[i];

		}

		for (short i = 0; i < t2; i++)
		{
			q1[i] = q[i];
		}
	}
	

	short n[CAPACITY];

	short i = 0;


	while (i < t2)
	{

		carry = 0;
		nsize = 0;
		//adding zeros at the beginning
		for (short v = 0; v < i; v++)

		{
			n[v] = 0;
			nsize++;
		}

		for (short j = 0; j < t1; j++)
		{
			short temp = 0;

			temp = (q1[i] * p1[j]) + carry;

			if (temp >= 10)
			{
				n[nsize] = temp % 10;

				carry = temp / 10;
				nsize++;
			}


			else
			{
				n[nsize] = temp;
				carry = 0;
				nsize++;

			}


			if (j == t1 - 1)
			{
				if (carry > 0)
				{
					*(n + nsize) = carry;
					nsize++;
				}
			}


		}


		//adding zeros at end 
		if (t2 > 1)
		{
			for (short v = i; v < t2 - 1; v++)
			{
				n[nsize] = 0;
				nsize++;
			}
		}



		if (i == 0)
		{
			for (short x = 0; x < nsize; x++)
			{
				tempmul[x] = n[x];
			}

			mulsize = nsize;
		}
		else
		{


			add(tempmul, n, tempmul, mulsize, nsize, mulsize);
		}


		i++;

		

	}

	for (int i = mulsize-1; i > 0; i--)
	{
		if (tempmul[i] != 0)
			break;
		mulsize--;
	}

	for (int i = 0; i < mulsize; i++)
	{
		mul[i] = tempmul[i];
	}
	
}





void diviide(short p[], short q[], short div[], short remainder[], short t1, short t2, short &devsize, short &size)
{
	
	bool test = false;

	short mulsize = 0;
	size = 0;
	devsize = 0;


	short m[CAPACITY];

	short cycleone[CAPACITY];


	short cycletwo[CAPACITY];

	short y[CAPACITY];
	short y1 = 1;


	for (int i = 0; i < CAPACITY; i++)
	{
		div[i] = 0;
	}

	short tempdiv[CAPACITY];
	short tempdiv1;

	short padding = t1 - t2;
	// if dividing 8/13 remainder will = 13 and divide = 1
	if (padding < 0)
	{
		for (short i = 0; i < t1; i++)
		{
			remainder[i] = p[i];
			
		}

		// the answer
		devsize = 1;
		div[0] = 1;
		size = t1;


		return;
	}

	//if not < than
	else
	{

		short doublee[1] = { 1 };
		short addsize = devsize = 1;
		short mulsize = 0;
		bool check = false;
		bool flag = false;
		short x = 1;

		

		// m is the temp array for divisor and here padding is added at first 


		for (short i = 0; i < t1; i++)
		{
			remainder[i] = p[i];
		}

		size = t1;
		short temp = t1;
		
		//to check for the whole minus process
		while (check == false)
		{

			//padding 
			short padding = temp - t2;

			if (padding < 0)
			{
				return;
			}

			for (short i = 0; i < padding; i++)
			{
				m[i] = 0;
			}

			x = 1;
			flag = false;

			//to check for each minus process

			for (short i = 0; i < size; i++)
			{
				cycleone[i] = remainder[i];
			}

			while (flag == false)
			{
				doublee[0] = { x };
				multiply(q, doublee, y, t2, 1, y1, mulsize);

				short addpadding = padding + y1;

				//if reached a large number before negative to save time
				if (addpadding > t1)
				{
					break;
				}

				//here
				//adding no to the padded number
				for (short i = padding, j = 0; i < addpadding; i++, j++)
				{
					m[i] = y[j];
				}

				minuus(remainder, m, cycleone, size, addpadding, mulsize, flag);

				if (flag == false)
				{
					x = x * 2;
				}
				

				//to stop after 8 only 
				if (x == 16)
				{
					break;
				}
			}

			//outer loop
			x = x / 2;
			temp = size;

			//stopping 
			if ((x == 0) && (padding == 0))
			{
				break;
			}

			else if ((x == 0) && (padding != 0))
			{
				temp--;
				continue;
			}

			doublee[0] = { x };
			multiply(q, doublee, y, t2, 1, y1, mulsize);
			short addpadding = padding + y1;

			for (short i = padding, j = 0; i < addpadding; i++, j++)
			{
				m[i] = y[j];
			}

			minuus(remainder, m, remainder, size, addpadding, size, check);
			temp = size;
			

			//divisor

			for (int i = 0; i < padding; i++)
			{
				tempdiv[i] = 0;
			}

			tempdiv[padding] = x;

			tempdiv1 = 1 + padding;

			if (test == false)
				devsize = tempdiv1;

			add(div, tempdiv, div, devsize, tempdiv1, devsize);

			test = true;
		}






	}

}





void divideByTwo(short p[], short q[], short t1, short &twosize)
{
	short carry = 0;
	twosize = 0;

	short n[CAPACITY];
	
	for (short i = 0; i < t1; i++)
	{
		short temp = p[i] % 2;
		short x = p[i] / 2;

		if (temp == 0)
		{
			q[i] = x;
		}

		else
		{
			q[i] = x;
			if (i != t1 - 1)
				p[i + 1] = p[i + 1] + 10;
		}
		twosize++;


	}

	
	
}



void power(short p[], short q[], short l[], short mul[], short t1, short t2,short l1, short &mulsize, short &size)
{

	short b[CAPACITY] ;
	short b1 = t1;

	short e[CAPACITY];
	short e1 = t2;

	short m[CAPACITY];
	short m1 = l1;

	bool tt = false;

	for (int i = 0; i < t1; i++)
	{
		b[i] = p[i];
	}

	for (short i = t2 - 1, j = 0; i >= 0; i--, j++)
	{
		e[i] = q[j] ;

	}

	for (int i = 0; i < l1; i++)
	{
		m[i] = l[i];
	}

	short remainder[CAPACITY];
	short remsize = 0;

	//x is the mul
	short x[CAPACITY] = {1};

	short check = 0;

	short one[1] = { 1 };
	one[0] = 1;
	short minsize = t2;
	mulsize = t1;
	bool a = false;

	short twosize = 0;

	short tempe[CAPACITY];

	mul[CAPACITY];

	for (int i = 0; i < CAPACITY; i++)
	{
		mul[i] = 1;
	}

	//minuus(q, one, q, minsize, 1, minsize, a);

	short counter = 0;

	short two[1] = { 2 };


	short etemp[CAPACITY];

	if (e1 == 1)
	{
		if (e[0] == 0)
			a = true;
	}

	while (a == false)
	{

		//minuus(q, one, q, minsize, 1, minsize, a);

		if (a == false)
		{
			

			for (short i = e1 - 1, j = 0; i >= 0; i--, j++)
			{
				etemp[i] = e[j];

			}


			diviide(etemp, two, x, remainder, e1, 1, size, remsize);

			divideByTwo(e, e, e1, e1);
			
			check = 0;
			for (int i = 0; i < e1; i++)
			{
				if (e1 != 1)
				{
					if (e[i] != 0)
						break;
					check++;
				}
				
			}

			e1 = e1 - check;

			if (check != 0)
			{
				for (short i = 0, j = check; i < e1; i++, j++)
				{
					e[i] = e[j];
				}

			}

			if (remsize == 1)
			{
				if (remainder[0] == 1)
				{
					//here
					
					if (tt == false)
					{
						mulsize = 1;
					}

					multiply(mul, b, mul, mulsize, b1, mulsize, size);
					diviide(mul, m, x, mul, mulsize, m1, size, mulsize);

					tt = true;
				}
			}

			//look here hereeeeeee
			multiply(b, b, b, b1, b1, b1, size);
			diviide(b, m, x, b, b1, m1, size, b1);

		}

		if (e1 == 1)
		{
			if (e[0] == 0)
				a = true;
		}
	}

	
}


bool millerRabin(short p[], short t1)
{

	if (p[0] % 2 == 0)
		return false;

	short one[1] = { 1 };
	one[0] = 1;

	short twosize;

	short n[CAPACITY];

	short m[CAPACITY];

	short s[CAPACITY];

	short div[CAPACITY];

	short remainder[CAPACITY];

	short minsize;
	bool neeg;

	bool flag = false;
	short k = 0;

	minuus(p, one, n, t1, 1, minsize, neeg);

	twosize = minsize;

	//b3dlha 3ashan td5ol fl divide by two
	for (short i = minsize - 1, j = 0; i >= 0; i--, j++)
	{
		s[i] = n[j];
	}


	short mulsize = 0, size = 0;

	while (s[twosize - 1] % 2 == 0)
	{
		divideByTwo(s, s, twosize, twosize);
		k++;

		if (s[0] == 0)
		{
			twosize--;
			for (int i = 0; i < twosize; i++)
			{
				s[i] = s[i + 1];
			}
		}
	}


	short devsize = 0;
	short remsize = 0;

	short tempsize = twosize;


	//ha2lbha tany 
	for (short i = twosize -1 , j = 0; i >= 0; i--, j++)
	{
		m[i] = s[j];
	}

	//twosize = tempsize;

	bool check = false;

	one[0] = 2;

	//ASHTA3'ALOOO
	power(one, m, p, remainder, 1, twosize,t1, remsize, mulsize);

	if (remsize == 1)
	{
		if (remainder[0] == 1)
		{
			return true;
		}
	}

	//HNAA MSH SHA3'AL FL 37!!!
	for (short i = 0; i<k; i++)
	{
		one[0] = 2;
		//hhnaaa
		power(remainder, one, p, remainder, remsize, 1, t1, remsize, mulsize);

		if (remsize == 1)
		{
			if (remainder[0] == 1)
			{
				return true;
			}
		}

	}

	
	return false;
}


//extended euclid algo

void extended(short B[],short M[] , short B2[] ,short b,short m, short &b2)
{
	short A2[CAPACITY];
	short A3[CAPACITY];
	//short B2[CAPACITY];
	short B3[CAPACITY];

	short T2[CAPACITY];
	short t2 = 0;

	short T3[CAPACITY];
	short t3 = 0;

	short a2, a3, b3;

	short Q[CAPACITY];
	short q = 0;
	short temp[CAPACITY];
	short t = 0;
	bool check = false;

	short counter = 0;

	short QB2[CAPACITY];
	short QB3[CAPACITY];
	short qb2;
	short qb3;

	bool flag = false;

	for (int i = 0; i < CAPACITY; i++)
	{
		A2[i] = 0;
	}
	a2 = 1;

	for (int i = 0; i < CAPACITY; i++)
	{
		B2[i] = 1;
	}
	b2 = 1;

	for (int i = 0; i < m; i++)
	{
		A3[i] = M[i];
	}

	a3 = m;

	for (int i = 0; i < b; i++)
	{
		B3[i] = B[i];
	}

	b3 = b;



	while (check == false)
	{
		if (b3 == 1)
		{
			if (B3[0] == 0)
				return;
		}

		if (b3 == 1)
		{
			if (B3[0] == 1)
			{

				/*/if (counter % 2)
				{
					short tempo;
					minuus(M, B2, B2, m, b3, tempo,flag);
					b2 = tempo;
				}/*/

				return;

			}
				
			
		}


		//Q = A3/B3
		//B3 = A3/B3

		diviide(A3, B3, Q, temp, a3, b3, q, t3);
		
		

		
		//T2 = A1 - QB1
		multiply(Q, B2, QB2, q, b2, qb2, t);
		//multiply(Q, B3, QB3, q, b3, qb3, t);

		//if (counter % 2)
		//{
			
			add(A2,QB2,T2,a2,qb2,t2);
			//minuus(A3,QB3,T3,a3, qb3, t3, flag);
		//}
		
		/*/else
		{
			minuus(QB2, A2, T2, qb2, a2, t2, flag);
			//minuus(QB3, A3, T3, qb3, a3, t3, flag);
		}/*/

		//B3


		//A is B
		for (int i = 0; i < b2; i++)
		{
			A2[i] = B2[i];
		}
		a2 = b2;

		for (int i = 0; i < b3; i++)
		{
			A3[i] = B3[i];
		}
		a3 = b3;

		for (int i = 0; i < t2; i++)
		{
			B2[i] = T2[i];
		}
		b2 = t2;

		
		for (int i = 0; i < t3; i++)
		{
			B3[i] = temp[i];
		}
		b3 = t3;

		counter++;
	}

	


}


short main()
{
	

	string s1, s2 , s3;
	cout << "P=";
	cin >> s1;
	cout << "Q=";
	cin >> s2;
	cout << "E=";
	cin >> s3;

	short t1 = s1.length();
	short t2 = s2.length();
	short t3 = s3.length();


	short size = 0;
	short mulsize = 0;


	short P[CAPACITY];

	short Q[CAPACITY];

	short E[CAPACITY];

	
	 short N[CAPACITY];

	 short PHI[CAPACITY];

	 short D[CAPACITY];

	for (short i = t1 - 1, j = 0; i >= 0; i--, j++)
	{
		P[i] = s1[j] - '0';

	}

	for (short i = t2 - 1, j = 0; i >= 0; i--, j++)
	{
		Q[i] = s2[j] - '0';
	}

	for (short i = t3 - 1, j = 0; i >= 0; i--, j++)
	{
		E[i] = s3[j] - '0';
	}


	bool neeg = false;


	//divideByTwo(P, Q, t1);

	bool p = false;
	p = millerRabin(P, t1);

	


	bool q = false;
	q = millerRabin(Q, t2);

	


	cout << "ISPPRIME\n";
	if (p)
		cout << "YES\n";
	else
		cout << "NO\n";


	cout << "IsQPrime\n";
	if (p)
		cout << "YES\n";
	else
		cout << "NO\n";


	short n;
	//N
	multiply(P, Q, N, t1, t2, n, size);

	cout << "PrintN\n";
	for (short i = n - 1; i >= 0; i--)
	{
		
		cout << N[i];
	}

	cout << endl;

	//phi
	short one[1] = { 1 };
	short TEMP1[CAPACITY];
	short TEMP2[CAPACITY];
	short temp1, temp2;



	minuus(P, one, TEMP1, t1, 1, temp1, neeg);
	minuus(Q, one, TEMP2, t2, 1, temp2, neeg);

	multiply(TEMP1, TEMP2, PHI, temp1, temp2, size, mulsize);

	cout << "PrintPhi\n";
	for (short i = size - 1; i >= 0; i--)
	{
		cout << PHI[i];
	}


	cout << endl;

	short d;
	//D
	extended(E, PHI, D, t3, size, d);

	cout << "PrintD\n";
	for (int i = d-1; i >= 0 ; i--)
	{
		cout << D[i];
	}


	string message;
	cout << "Message is:";
	cin >> message;
	short ml = message.length();

	cout << "Encrpted message = ";
	

	short ME[CAPACITY];
	short CE[CAPACITY];
	short ce;
	for (short i = ml - 1, j = 0; i >= 0; i--, j++)
	{
		ME[i] = message[j] - '0';
	}

	power(ME,E,N,CE,ml,t3,n,ce,size);

	for (int i = ce-1; i >= ce; i--)
	{
		cout << CE[i];
	}


	cout << "Message decryption";

	short S[CAPACITY];
	short s;

	power(CE, D, N, S, ce, d, n, s, size);

	for (int i = s - 1; i >= s; i--)
	{
		cout << S[i];
	}



	cout << endl;
	cout << endl;


	cout << "QUIT";
	cout << endl;

	system("pause");
	return 0;
	


}