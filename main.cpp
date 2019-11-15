#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include "png_toolkit.h"
#include "filters_collection.h"
#include "coefficients.h"

using namespace std;

vector<pair<string, coefficients>> cfgParser(string cfg_name) {
	ifstream file(cfg_name);
	if (!file.is_open()) {
		throw "Can't create file-stream";
	}
	vector<pair<string, coefficients>> task_list;
	string cur_line;
	while (getline(file, cur_line)) {
		istringstream iss(cur_line);
		vector <string> result;
		for (string str; iss >> str;) {
			result.push_back(str);
		}
		if (result.size() != 5) {
			continue;
			//throw "Not valid config line";
		}
		try {
			coefficients coef(result);
			task_list.push_back(make_pair(result[0], coef));
		}
		catch (const std::invalid_argument& ia) {
			throw "Not valid config line";
		}
	}
	file.close();
	return task_list;
}

int main( int argc, char *argv[] )
{
    // toolkit filter_name base_pic_name sudent_tool student_pic_name limitPix limitMSE
    // toolkit near test images!
	try
	{
		if (argc != 4)
			throw "Not correct number of arguments";
		vector<pair<string, coefficients>> task_list = cfgParser(argv[1]);
        png_toolkit studTool;
        studTool.load(argv[2]);
		image_data img_data = studTool.getPixelData();
		filters_collections filters;
		for (auto& task_item : task_list) {
			task_item.second.transformToArea(img_data.w, img_data.h);
			filters.getFilter(task_item.first)->setFilter(img_data, task_item.second);
		}
        studTool.save(argv[3]);

    }
    catch (const char *str)
    {
        std::cout << "Error: " << str << std::endl;
        return 1;
    }

    return 0;
}
