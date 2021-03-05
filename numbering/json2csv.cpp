/*
 * Mask R-CNN JSON format ==> CSV
 * Copyright (C) 2021, K.Kita  All rights reserved.
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include "json.h"

using namespace std;
using namespace boost::filesystem;
using json = nlohmann::json;

static void	json2csv(const path file);

int	main(int argc, char **argv)
{
	string	input_file;

	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s file/directory\n", argv[0]);
		exit(1);
	}
	input_file = argv[1];

	if(is_directory(input_file))
	{
	    BOOST_FOREACH(const path &file,
		make_pair(directory_iterator(input_file), directory_iterator()))
//		make_pair(recursive_directory_iterator(input_file), recursive_directory_iterator()))
	    {
		const char	*ext = file.extension().c_str();
		if(strcasecmp(ext, ".json") == 0)
			json2csv(file);
	    }
	}
	else
		json2csv(input_file);

	exit(EXIT_SUCCESS);
}

static void	json2csv(const path file)
{
	std::ifstream ifs(file);
	json	Json;
	ifs >> Json;
	double	xmin, ymin, xmax, ymax;
//	double	height = Json["height"].get<double>();
//	double	width = Json["width"].get<double>();

	for(auto s: Json["shapes"])
	{
		char	*p;
		char	label[BUFSIZ];
		strcpy(label, s["label"].get<string>().c_str());
		if((p = strchr(label, '_')) != nullptr)
			*p = '\0';
		xmin = ymin = 99999.0;
		xmax = ymax = 0.0;
		for(auto point: s["points"])
		{
			vector<double> v = point;
			xmin = fmin(xmin, v[1]);
			xmax = fmax(xmax, v[1]);
			ymin = fmin(ymin, v[0]);
			ymax = fmax(ymax, v[0]);
		}
		printf("%s,%lf,%lf,%lf,%lf,%s\n",
			file.filename().replace_extension("").c_str(),
			ymin, xmin, ymax, xmax, label);
//			xmin, ymin, xmax, ymax, label);
	}
}
