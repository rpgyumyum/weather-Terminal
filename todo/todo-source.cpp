#include <iostream>
#include <fstream>

#include <string>
#include <cstring>

#include <algorithm>
#include <iterator>




void displayList()
{
  std::string line;
  std::fstream list ("/home/Lukas/Documents/todo.txt");

  if (list.is_open())
  {


    std::cout << '\n';

    int linesInFile{0};

    while (std::getline(list, line))
    {
        linesInFile++;
    }

    int index {1};

    list.clear();
    list.seekg(0);

    while (std::getline (list, line))
    {
      std::cout << index++ << " - " << line << '\n';
    }




    std::cout << '\n';

    list.close();
  }
  else
  {
    std::cout << "unable to open file\n";
  }
}





void addListItem(std::string newItem)
{
  std::ofstream list("/home/Lukas/Documents/todo.txt", std::ios::app);

  if (list.is_open())
  {
    list << newItem << '\n';
    list.close();
  }
  else
  {
    std::cout << "unable to open file\n";
  }
}






void changeListItem(std::string string_index, std::string newLine)
{
  int index = atoi(string_index.c_str());

  std::fstream list("/home/Lukas/Documents/todo.txt");
  std::ofstream temp("temp.txt");

  if (list.is_open() && temp.is_open())
  {
    std::string line;
    int current_line = 1;
    bool lineFound = false;

    while (std::getline(list, line))
    {
      if (current_line == index)
      {
        if (!newLine.empty())
        {
          temp << newLine << '\n';
        }
        lineFound = true;
      }
      else
      {
        temp << line << '\n';
      }
      current_line++;
    }

    list.close();
    temp.close();

    std::remove("/home/Lukas/Documents/todo.txt");
    std::rename("temp.txt", "/home/Lukas/Documents/todo.txt");

    if (!lineFound)
    {
      std::cout << "Line not found\n";
    }
  }
  else
  {
    std::cout << "Unable to open file\n";
  }
}






int main(int argc, char const *argv[])
{

  if (argc != 1 && argc != 3 && argc != 4)
  {
    std::cout << "invalid numbers of arguments \n";
  }

  if (argc ==  1) //DISPLAY LIST
  {
    displayList();
  }
  else if (argc == 3)
  {
    if(!strcmp(argv[1], "-add")) //ADD
    {
      addListItem(argv[2]);
    }
    else if (!strcmp(argv[1], "-done")) //DONE
    {
      changeListItem(argv[2], "");
    }
  }
  else if (argc == 4 && !strcmp(argv[1], "-mod")) //CHANGE A LINE
  {
    changeListItem(argv[2], argv[3]);
  }
  else
  {
    std::cout << "Invalid arguments";
  }

  return 0;
}
