#include <iostream>

#include <algorithm>
#include <iterator>
#include <fstream>

#include <string>
#include <vector>
#include <unordered_map>

#include "func.h"

#define uint unsigned int

bool importData(const std::string &file, std::vector<std::string> &data)
{
	std::ifstream input;
	input.open(file);

	std::string temp = "";

	if (input.is_open())
	{
		while (std::getline(input, temp))
		{
			data.push_back(temp);
			temp = "";
		}
		input.close();
		return true;
	}
	else
	{
		std::cerr << file << " failed to open" << std::endl;
	}
	return false;
}

struct Transaction
{
public:
	Transaction() {}
	Transaction(const std::string &name, const std::string &buyDate, const std::string &cost, const std::string &sellDate, const std::string &sellPrice)
		: assetName(name), dateBought(buyDate), dateSold(sellDate)
	{
		Func::checkDouble(cost, costBasis);
		Func::checkDouble(sellPrice, proceeds);
	}
	~Transaction() {}

	//ASSET NAME, RECEIVED DATE, COST BASIS(USD), DATE SOLD, PROCEEDS
	std::string assetName;
	std::string dateBought;
	double costBasis; //USD
	std::string dateSold;
	double proceeds;

};

int main(int argc, char** argv)
{
	std::string fileName = "";
	std::string fileDir = "";
	std::string filePath = "";

	if (argc == 1)
	{
		std::string programPath = argv[0];
		fileDir = programPath.substr(0, programPath.rfind('\\'));
		std::cout << "Enter file name:" << std::endl;
		std::getline(std::cin, fileName);
		filePath = fileDir + '/' + fileName;
	}
	else
	{
		filePath = argv[1];
	}

	std::vector<std::string> fileData;
	if (importData(filePath, fileData))
	{
		std::vector<Transaction> transactionInfo;

		for (uint dataIndex = 7; dataIndex < fileData.size(); ++dataIndex)
		{
			std::vector<uint> commaPositions;
			if (Func::delimFinder(fileData[dataIndex], ',', commaPositions))
			{
				std::vector<std::string> courier;
				courier.emplace_back(fileData[dataIndex].substr(0, commaPositions[0]));
				uint commaCount = commaPositions.size();
				for (uint commaIndex = 0; commaIndex < commaCount - 1; ++commaIndex)
				{
					courier.emplace_back(fileData[dataIndex].substr(commaPositions[commaIndex] + 1, commaPositions[commaIndex + 1] - commaPositions[commaIndex] - 1));
				}
				courier.emplace_back(fileData[dataIndex].substr(commaPositions[commaCount - 1] + 1));
				transactionInfo.emplace_back(Transaction(courier[0], courier[1], courier[2], courier[3], courier[4]));

			}
		}
		std::unordered_map<std::string, double> sumCost;
		std::unordered_map<std::string, double> sumProceeds;

		for (auto & trans : transactionInfo)
		{
			sumCost[trans.assetName] += trans.costBasis;
			sumProceeds[trans.assetName] += trans.proceeds;
		}

		std::cout << std::endl;
		for (auto & pair : sumCost)
		{
			std::cout << pair.first << " total cost     = " << pair.second << "\n";
		}
		for (auto & pair : sumProceeds)
		{
			std::cout << pair.first << " total proceeds = " << pair.second << "\n";
		}
		std::cout << std::endl;
	}

	std::cin.get();
	return 0;
}