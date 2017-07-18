#include <iostream>
#include <cstdlib>
#include <ctime>

//Модифицировать программу CardAray так. чтобы колода после перемешивания делилась на 4 части по 13 карт
//каждая из групп потом должна быть выведена
//
//
enum Suit {clubs, diamonds, hearts, spades};
//от 2 до 10 обычные числа
const int jack = 11;
const int queen = 12;
const int king = 13;
const int ace = 14;

class Card{
private:
  int number;
  Suit suit;
public:
  Card()
  {}
  void set(int n, Suit s)
  {suit = s; number = n;}
  void display();
};

void Card::display()
{
  if(number >=2 && number <=10)
  {std::cout << number;}
  else 
  {
    switch(number)
    {
      case jack: std::cout << 'J'; break;
      case queen: std::cout << 'Q'; break;
      case king: std::cout << 'K'; break;
      case ace: std::cout << 'A'; break;
    }
  }
  switch(suit)
  {
    case clubs: std::cout << "c"; break;
    case diamonds: std::cout << "d"; break;
    case hearts: std::cout << "h"; break;
    case spades: std::cout << "s"; break;
      
  }
}

int main() {
    Card deck[52];
    Card player1[13];
    Card player2[13];
    Card player3[13];
    Card player4[13];
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    std::cout << std::endl;
    for(int j = 0; j <52; j++)
    {
      int num = (j%13) + 2;
      Suit su = Suit(j/13);
      deck[j].set(num, su);   
    }
    //показываем колоду
    std::cout << "Исходная колода: " << std::endl;
    for(int j = 0; j<52; j++)
    {
      deck[j].display();
      std::cout << " ";
      if(!((j+1)%13))
	std::cout << std::endl; //новая строка после каждой 13-й карты
    }
    std::cout << std::endl;
    
    srand(std::time(NULL));
    for(int j = 0; j < 52; j++)
    {
      int k = rand() % 52;
      Card temp = deck[j];
      deck[j] =deck[k];
      deck[k] = temp;
    }
    
    //показываем перемешанную колоду
    std::cout << "Перемешанная колода: " << std::endl;
    for(int j = 0; j<52; j++)
    {
      deck[j].display();
      std::cout << " ";
      if(!((j+1)%13))
	std::cout << std::endl; //новая строка после каждой 13-й карты
    }
    std::cout << std::endl;
    
    //раздаём перемешанную колоду
    for(int j=0; j<52; j++)
    {
      
      if(!(j%4))
      {
	player1[p1] = deck[j];
	p1++;
      }
      else if(!((j+1)%4))
      {
	player2[p2] = deck[j];
	p2++;
      }
      else if(!(j%2))
      {
	player3[p3] = deck[j];
	p3++;
      }
      else if(!((j+1)%2))
      {
	player4[p4] = deck[j];
	p4++; 
      }
    }
   
   
   for(int i = 1; i <=4; i++)
   {
    std::cout << "Игрок " << i << std::endl;
    for(int j = 0; j<13; j++)
      {
	 switch(i)
	{
	  case 1: player1[j].display(); break;
	  case 2: player2[j].display(); break;
	  case 3: player3[j].display(); break;
	  case 4: player4[j].display(); break;
	}
	std::cout << " ";
      }
	std::cout << std::endl; 
      }
      
      
    return 0;
}
