#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <assert.h>
#include <math.h>

using namespace std;

template <class Item>
class node //c большой
{
public:
	Item element;	
	node *left;		
	node *right;	
	int height;		
};

template <class Item>
class AVLtree
{
	public:
		void insert(Item, node<Item>* &); //Вставить новый узел
		int find(Item, node<Item>* &); //проверить, есть ли элемент в дереве 
		node<Item>* findmin(node<Item>* p); //минимальный элемент
		node<Item>* findmax(node<Item>*); //максимальный элемент
		void del(Item, node<Item>* &); //удаление по ключу
		int deletemin(node<Item>* &); 
		int height_r(node<Item>* p); //возвращает высоту
		void makeempty(node<Item>* &); 
		node<Item>* drl(node<Item>* &); 
		node<Item>* srl(node<Item>* &); //левый поворот
		node<Item>* drr(node<Item>* &); 
		node<Item>* srr(node<Item>* &); //левый поворот
		void preorder(node<Item>*); //КЛП
		void inorder(node<Item>*); //ЛКП
        int inorder_check(node<Item>*, int); //ЛКП
		void postorder(node<Item>*); //ЛПК
		int max(int, int); 
};

template <class Item>
void AVLtree<Item>::insert(Item x, node<Item>* &p)
{
	if (p == NULL)
	{
		p = new node<Item>;
		p->element = x;
		p->left = NULL;
		p->right = NULL;
		p->height = 0;
		if (p == NULL)
		{
			cout << "Аварийная нехватка памяти! Операция прервана!\n"<<endl;
		}
	}
	else
	{
		if (x < p->element)
		{
			insert(x, p->left);
			if ((height_r(p->left) - height_r(p->right)) == 2)
			{
				if (x < p->left->element)
				{
					p=srl(p);
				}
				else
				{
					p = drl(p);
				}
			}
		}
		else if (x>p->element)
		{
			insert(x,p->right);
			if ((height_r(p->right) - height_r(p->left)) == 2)
			{
				if (x > p->right->element)
				{
					p=srr(p);
				}
				else
				{
					p = drr(p);
				}
			}
		}
		else
		{
			cout << "Элемент с таким ключом уже присутствует в дереве! Вставка дубликата невозможна!\n";
		}
	}
	int m, n, d;
	m = height_r(p->left);
	n = height_r(p->right);
	d = max(m, n);
	p->height = d + 1;
}

template <class Item>
node<Item>* AVLtree<Item>::findmin(node<Item>* p)
{
	if (p == NULL)
	{
		cout<<"В дереве нет элементов. Минимального элемента физически не существует!\n"<<endl;
		return p;
	}
	else
	{
		while(p->left != NULL)
			p = p->left;
		return p;
	}
}

template <class Item>
node<Item>* AVLtree<Item>::findmax(node<Item>* p)
{
	if (p==NULL)
	{
		cout<<"В дереве нет элементов. Максимального элемента физически не существует!\n"<<endl;
		return p;
	}
	else
	{
		while(p->right !=NULL)
			p = p->right;
		return p;
	}
}

template <class Item>
int AVLtree<Item>::find(Item x, node<Item>* &p)
{
	if (p == NULL)
	{
		cout<<"Искомого элемента в AVL-дереве не обнаружено!\n"<<endl;
        return 0;
	}
	else
	{
		if (x < p->element)
		{
			find(x, p->left);
		}
		else
		{
			if (x > p->element)
			{
				find(x, p->right);
			}
			else
			{
				cout << "Элемент, который вы искали, НАЙДЕН в AVL-дереве!\n" << endl;
                return 1;
			}
		}
	}
};

template <class Item>
void AVLtree<Item>::del(Item x, node<Item>* &p)
{
	node<Item>* d;
	if (p == NULL)
	{
		cout << "AVL-дерево не содержит узла с таким ключом." << endl;
	}
	else if ( x < p->element)
	{
		del(x, p->left);
	}
	else if (x > p->element)
	{
		del(x, p->right);
	}
	else if ((p->left == NULL) && (p->right == NULL))
	{
		d = p;
		free(d); //заменить на delete
		p = NULL;
		cout << "Элемент успешно удален\n" << endl;
	}
	else if (p->left == NULL)
	{
		d = p;
		free(d);
		p = p->right;
		cout<<"Элемент успешно удален\n"<<endl;
	}
	else if (p->right == NULL)
	{
		d = p;
		p = p->left;
		free(d);
		cout << "Элемент успешно удален\n" << endl;
	}
	else
	{
		p->element = deletemin(p->right);
	}
}

template <class Item>
int AVLtree<Item>::deletemin(node<Item>* &p)
{
	int c;
	cout << "Выбрано удаление минимального значения.\n" << endl;
	if (p->left == NULL)
	{
		c = p->element;
		p = p->right;
		return c;
	}
	else
	{
		c = deletemin(p->left);
		return c;
	}
}

template <class Item>
int AVLtree<Item>::height_r(node<Item>* p)
{
	int t;
	if (p == NULL)
	{
		return -1;
	}
	else
	{
		t = p->height;
		return t;
	}
}

template <class Item>
void AVLtree<Item>::makeempty(node<Item>* &p)
{
	node<Item>* d;
	if (p != NULL)
	{
		makeempty(p->left);
		makeempty(p->right);
		d = p;
		free(d);
		p = NULL;
	}
}

template <class Item>
node<Item>* AVLtree<Item>::drl(node<Item>* &p1)
{
	p1->left=srr(p1->left);
	return srl(p1);
}


//правый поворот
template <class Item>
node<Item>* AVLtree<Item>::srl(node<Item>* &p1)
{
	node<Item>* p2;
	p2 = p1->left;
	p1->left = p2->right;
	p2->right = p1;
	p1->height = max(height_r(p1->left),height_r(p1->right)) + 1;
	p2->height = max(height_r(p2->left),p1->height) + 1;
	return p2;
}

template <class Item>
node<Item>* AVLtree<Item>::drr(node<Item>* &p1)
{
	p1->right = srl(p1->right);
	return srr(p1);
}

//левый поворот
template <class Item>
node<Item>* AVLtree<Item>::srr(node<Item>* &p1)
{
	node<Item>* p2;
	p2 = p1->right;
	p1->right = p2->left;
	p2->left = p1;
	p1->height = max(height_r(p1->left),height_r(p1->right)) + 1;
	p2->height = max(p1->height,height_r(p2->right)) + 1;
	return p2;
}

template <class Item>
int AVLtree<Item>::max(int value1, int value2)
{
	return ((value1 > value2) ? value1 : value2);
}

// КЛП
template <class Item>
void AVLtree<Item>::preorder(node<Item>* p)
{
	if (p != NULL)
	{
		cout << "\t" << p->element;
		preorder(p->left);
		preorder(p->right);
	}
}

// ЛКП
template <class Item>
void AVLtree<Item>::inorder(node<Item>* p)
{
	if (p != NULL)
	{
		inorder(p->left);
		cout << "\t" << p->element;
		inorder(p->right);
	}
}

// template <class Item>    
// int AVLtree<Item>::inorder_check(node<Item>* p, int count)
// {
// 	if (p != NULL)
// 	{
// 		count = inorder_check(p->left, count);
// 		cout << "\t" << p->element;
//         count += 1;
//         if(p->left){
//             if((p->element < p->left->element) and (p->element > p->right->element)){
//                 cout << "ERROR" <<endl;
//             }
//         }
// 		count = inorder_check(p->right, count);
// 	}
//     return count;
// }

// ЛПК
template <class Item>
void AVLtree<Item>::postorder(node<Item>* p)
{
	if (p != NULL)
	{
		postorder(p->left);
		postorder(p->right);
		cout << "\t" << p->element;
	}
}

int submenu(void)
{
	int select;
	do
	{
		cout << "Выберите тип данных ключевых значений узлов AVL-дерева" << endl << endl;
		cout << "1. Значения ключей - целые числа" << endl;
		cout << "2. Значения ключей - дробные числа" << endl;
		cout << "3. Значения ключей - символы" << endl;
		cout << "0. Выход из программы" << endl;
		cout << "Выбор: ";
		cin >> select;
	}
	while((select < 0) || (select > 3));

	return select;
}

int mainmenu(void)
{
	int select;
	do
	{

		cout<<""<<endl;
		cout<<"1 Вставить новый узел"<<endl;
		cout<<"2 Найти минимальный элемент"<<endl;
		cout<<"3 Найти максимальный элемент"<<endl;
		cout<<"4 Поиск по значению"<<endl;
		cout<<"5 Удалить элемент"<<endl;
		cout<<"6 Обход дерева (корень-левый-правый)"<<endl;
		cout<<"7 Обход дерева (левый-корень-правый)"<<endl;
		cout<<"8 Обход дерева (левый-правый-корень)"<<endl;
		cout<<"9 Получить высоту дерева"<<endl;
		cout<<"10 Выход (сменить тип данных)"<<endl;
		
		cout << "Ваш выбор: ";
		cin >> select;
	}
	while((select < 1) || (select > 10));
	cout << endl;

	return select;
}

void test(void)
{
	AVLtree<int> int_avl;
	node<int>* int_root = NULL;

	assert(int_root == NULL);
	int_avl.insert(17, int_root);
	node<int>* max = int_avl.findmax(int_root);
	assert(max->element == 17);
	assert(int_avl.height_r(int_root) == 0);
	int_avl.insert(-6, int_root);
	assert(int_avl.height_r(int_root) == 1);
	node<int>* min = int_avl.findmin(int_root);
	assert(min->element == -6);

	AVLtree<float> float_avl;
	node<float>* float_root = NULL;
	float_avl.insert(3.14, float_root);
	node<float>* maxf = float_avl.findmax(float_root);
	const double EPS = 0.00001;
	assert(fabs(maxf->element - 3.14) <= EPS);
	assert(float_avl.height_r(float_root) == 0);
	float_avl.makeempty(float_root);
	assert(float_root == nullptr);

	AVLtree<char> char_avl;
	node<char>* char_root = nullptr;
	char_avl.insert('F', char_root);
	char_avl.insert('b', char_root);
	node<char>* minc = char_avl.findmin(char_root);
	assert(minc->element == 'F');
	char_avl.insert('z', char_root);
	assert(char_avl.height_r(char_root) == 1);
	char_avl.makeempty(char_root);
	assert(float_root == nullptr);
}


int main(void)
{

	int select_data_type;
	int choice;
    test();

    // AVLtree<int> int_avl;
	// node<int>* int_root = NULL;
    // int i, count;

    // for(int k = 0; k<10000; k++){
    //     i = rand() %  + 1;
    //     while(int_avl.find(i, int_root) == 1){
    //         i = rand() % 10000000000000000 + 1;
    //     }
    //     int_avl.insert(i, int_root);
    //     if(k%10 == 0){
    //         int_avl.del(i, int_root);
    //     }
    // }
    
    // int k = int_avl.height_r(int_root);

    // cout << "Высота: " << k <<endl;

    // count = int_avl.inorder_check(int_root, 0);
    // cout << "\nВсего элементов: " << count <<endl;

	do
	{
		select_data_type = submenu();
		if(!select_data_type)
			break;

		AVLtree<int> int_avl;
		node<int>* int_root = NULL;
		AVLtree<float> float_avl;
		node<float>* float_root = NULL;
		AVLtree<char> char_avl;
		node<char>* char_root = NULL;

		do
		{
			choice = mainmenu();
			switch(choice)
			{
			case 1:		// добавление в дерево
				{
					int i;
					float f;
					char c;
					cout << "Введите ключ добавляемого узла: ";
					switch(select_data_type)
					{
					case 1:
						{
							cin >> i;
							int_avl.insert(i, int_root);
							break;
						}
					case 2:
						{
							cin >> f;
							float_avl.insert(f, float_root);
							break;
						}
					case 3:
						{
							cin >> c;
							char_avl.insert(c, char_root);
							break;
						}
					}
					cout << "Новый элемент успешно добавлен в AVL-дерево (если он был НЕ дубликатом)\n" << endl;
					break;
				}
			case 2:		// поиск минимального
				{
					switch(select_data_type)
					{
					case 1:
						{
							if(int_root)
							{
								node<int>* min = int_avl.findmin(int_root);
								cout << "Минимальный элемент в дереве: " << min->element << endl;
							}
							else
								cout << "AVL-дерево пустое, т е не содержит ни одного узла. Поиск невозможен!" << endl;
							break;
						}
					case 2:
						{
							if(float_root)
							{
								node<float>* min = float_avl.findmin(float_root);
								cout << "Минимальный элемент в дереве: " << min->element << endl;
							}
							else
								cout << "AVL-дерево пустое, т е не содержит ни одного узла. Поиск невозможен!" << endl;
							break;
						}
					case 3:
						{
							if(char_root)
							{
								node<char>* min = char_avl.findmin(char_root);
								cout << "Минимальный элемент в дереве: " << min->element << endl;
							}
							else
								cout << "AVL-дерево пустое, т е не содержит ни одного узла. Поиск невозможен!" << endl;
							break;
						}
					}
					break;
				}
			case 3:
				{
					switch(select_data_type)
					{
					case 1:
						{
							if(int_root)
							{
								node<int>* max = int_avl.findmax(int_root);
								cout << "Максимальный элемент в дереве: " << max->element << endl;
							}
							else
								cout << "AVL-дерево пустое, т е не содержит ни одного узла. Поиск невозможен!" << endl;
							break;
						}
					case 2:
						{
							if(float_root)
							{
								node<float>* max = float_avl.findmax(float_root);
								cout << "Максимальный элемент в дереве: " << max->element << endl;
							}
							else
								cout << "AVL-дерево пустое, т е не содержит ни одного узла. Поиск невозможен!" << endl;
							break;
						}
					case 3:
						{
							if(char_root)
							{
								node<char>* max = char_avl.findmax(char_root);
								cout << "Максимальный элемент в дереве: " << max->element << endl;
							}
							else
								cout << "AVL-дерево пустое, т е не содержит ни одного узла. Поиск невозможен!" << endl;
							break;
						}
					}
					break;
				}
			case 4:		// поиск конкретного элемента в дереве
				{
					cout << "Введите значение искомого элемента: ";
					switch(select_data_type)
					{
					case 1:
						{
							int i;
							cin >> i;
							if(int_root)
								int_avl.find(i, int_root);
							else
								cout << "AVL-дерево пустое, т е не содержит ни одного узла. Поиск невозможен!" << endl;
							break;
						}
					case 2:
						{
							float f;
							cin >> f;
							if(float_root)
								float_avl.find(f, float_root);
							else
								cout << "AVL-дерево пустое, т е не содержит ни одного узла. Поиск невозможен!" << endl;
							break;
						}
					case 3:
						{
							char c;
							cin >> c;
							if(char_root)
								char_avl.find(c, char_root);
							else
								cout << "AVL-дерево пустое, т е не содержит ни одного узла. Поиск невозможен!" << endl;
							break;
						}
					}
					break;
				}
			case 5:		// удаление элемента
				{
					cout << "Введите значение удаляемого элемента: ";
					switch(select_data_type)
					{
					case 1:
						{
							int i;
							cin >> i;
							int_avl.del(i, int_root);
							int_avl.inorder(int_root);
							break;
						}
					case 2:
						{
							float f;
							cin >> f;
							float_avl.del(f, float_root);
							float_avl.inorder(float_root);
							break;
						}
					case 3:
						{
							char c;
							cin >> c;
							char_avl.del(c, char_root);
							char_avl.inorder(char_root);
							break;
						}
					}
					cout << endl;
					break;
				}
			case 6:		// КЛП
				{
					cout<<"Вариант обхода (корень-левый-правый): ";
					switch(select_data_type)
					{
					case 1:
						{
							int_avl.preorder(int_root);
							break;
						}
					case 2:
						{
							float_avl.preorder(float_root);
							break;
						}
					case 3:
						{
							char_avl.preorder(char_root);
							break;
						}
					}
					cout << endl;
					break;
				}
			case 7:		// ЛКП
				{
					cout<<"Вариант обхода (левый-корень-правый): ";
					switch(select_data_type)
					{
					case 1:
						{
							int_avl.inorder(int_root);
							break;
						}
					case 2:
						{
							float_avl.inorder(float_root);
							break;
						}
					case 3:
						{
							char_avl.inorder(char_root);
							break;
						}
					}
					cout << endl;
					break;
				}
			case 8:		// ЛПК
				{
					cout<<"Вариант обхода (левый-правый-корень): ";
					switch(select_data_type)
					{
					case 1:
						{
							int_avl.postorder(int_root);
							break;
						}
					case 2:
						{
							float_avl.postorder(float_root);
							break;
						}
					case 3:
						{
							char_avl.postorder(char_root);
							break;
						}
					}
					cout << endl;
					break;
				}
			case 9:
				{
					cout << "AVL-дерево имеет высоту: ";
					switch(select_data_type)
					{
					case 1:
						{
							cout << int_avl.height_r(int_root);
							break;
						}
					case 2:
						{
							cout << float_avl.height_r(float_root);
							break;
						}
					case 3:
						{
							cout << char_avl.height_r(char_root);
							break;
						}
					}
					cout << endl;
					break;
				}
			case 10:
				break;
			}
		}
		while(choice != 10);
		// делаем очитку памяти
		if(int_root)
			int_avl.makeempty(int_root);
		if(float_root)
			float_avl.makeempty(float_root);
		if(char_root)
			char_avl.makeempty(char_root);
	}
	while(select_data_type);

	return 0;
}
