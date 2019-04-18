#include	<fstream>
#include	<iostream>
#include	<string>
#include	"Catalog.h"

using namespace std;

Catalog::~Catalog(){
	
	categorylist.clear();
}


bool	Catalog::AddCategory(uint64_t categoryNumber, const string& name)
{
	
  if(categorylist.find(categoryNumber) == categorylist.end()){
		
    categorylist[categoryNumber].categoryName = name;
		return true;
  }

  else
		return false;
}

bool	Catalog::AddProduct(uint64_t categoryNumber, uint64_t productNumber, const string& name)
{
	
  if(categorylist.find(categoryNumber) != categorylist.end() &&  categorylist[categoryNumber].productList.find(productNumber) == categorylist[categoryNumber].productList.end()){
			//Add to the productList
    	categorylist[categoryNumber].productList[productNumber] = name;
			return true;
  }

	else
			return false;
}

uint64_t	Catalog::GetCategoryCount()
{
  return categorylist.size();

}

int64_t	Catalog::GetProductCount(uint64_t categoryNumber)
{

  if(categorylist.find(categoryNumber) != categorylist.end())
    return categorylist[categoryNumber].productList.size();
  else
  	return -1;

}

bool	Catalog::Load(const string& fileName)
{

  ifstream file;
	string input;
	uint64_t id;
	file.open(fileName);
	if (file.is_open())
	{
		while(file >> input)
    {
			
			if (input == "Category")
      {
				string _categoryName;
				file >> id;
				file.ignore();
				GetLine(file, _categoryName);
				AddCategory(id,_categoryName);
      }
			else
      {
				//We need to convert the string to an int because the string we read in represents the id for a product
				//Getline reads input as string, stoi is used to convert the input it's reading in to int
  			int productNum = stoi(input); 
  			string productName;
      	file.ignore();
        GetLine(file, productName);
        AddProduct(id,productNum,productName);
      }
    }
		file.close();
		return true;
  }
		file.close();
		return false;
}

bool	Catalog::ShowProduct(ostream& stream, uint64_t categoryNumber, uint64_t productNumber)
{
	
  if(categorylist.find(categoryNumber) != categorylist.end() &&  categorylist[categoryNumber].productList.find(productNumber) != categorylist[categoryNumber].productList.end())
  {
		stream << productNumber << "\t" << categorylist[categoryNumber].productList[productNumber] << endl;
  	return true;
  }
	else
		return false;
}

bool	Catalog::ShowCategory(ostream& stream, uint64_t categoryNumber)
{
	

   if(categorylist.find(categoryNumber) != categorylist.end())
   {
		stream << "Category\t" << categoryNumber << "\t" << categorylist[categoryNumber].categoryName << endl;
 
		for(map<int, string>::iterator it = categorylist[categoryNumber].productList.begin(); it != categorylist[categoryNumber].productList.end(); it++)
    {
    	stream << it->first << "\t" << it->second << endl;
    }
    return true;
   }
	else
		return false;
}

bool	Catalog::ShowAll(ostream& stream)
{
	
  if(!categorylist.empty())
  {
  	for( map<int, Categoryinfo>::iterator it = categorylist.begin(); it != categorylist.end(); it++)
  	{
    	 stream << "Category\t" << it->first << "\t" << it->second.categoryName << endl;
       for (map<int, string>::iterator it2 = it->second.productList.begin(); it2 != it->second.productList.end(); it2++)
       {
         stream << it2->first << "\t" << it2->second << endl;
       }
  	}
    return true;
  }
	return false;
}
