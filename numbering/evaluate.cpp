/*
 * Compute precision and recall for teeth numbering
 * Copyright (C) 2021, K.Kita  All rights reserved.
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>

using namespace std;
using namespace cv;
using namespace boost::program_options;
using namespace boost::filesystem;

typedef struct
{
	string	fname;
	double	x1, y1;
	double	x2, y2;
	int	label;
	double	score;
} bbox;

// 画像のあるディレクトリ
static const string	img_dir = "/home/kk/work/work_git/numbering/test_images";
static const double	IoU_thresh = 0.5;
static void	show_result(string fname, vector<bbox> gt, vector<bbox> pred);
static double	compute_IoU(bbox boxA, bbox boxB);
static int	read_bbox_file(string file, vector<bbox> &bv);
static void	screen_resolution(int &width, int &height);

int	main(int argc, char** argv)
{
	bool	verbose = false;
	vector<string>	input;
	vector<bbox>	gt;
	vector<bbox>	pred;

	options_description opt("options");
	opt.add_options()
		("verbose,v", "verbose mode")
		("input-file,I", value<vector<string> >(&input)->multitoken(),
		 "Gt-file Pred-file");
	positional_options_description opt2;
	opt2.add("input-file", -1);
	options_description opt_hidden("hidden options");
	opt_hidden.add_options()
		("help,h", "show options");
	options_description all_options("all options");
	all_options.add(opt).add(opt_hidden);

	if(argc < 3)
	{
		fprintf(stderr, "Usage: %s Gt-file Pred-file\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	variables_map vm;
	try
	{
		store(command_line_parser(argc, argv).
			options(all_options).positional(opt2).run(), vm);
	}
	catch(exception &e)
	{
		cout << "Error: " << e.what() << endl;
		exit(EXIT_FAILURE);
	}
	notify(vm);
	if(vm.count("verbose"))
	{
		verbose = true;
	}

	if(!read_bbox_file(input[0], gt))
	{
		fprintf(stderr, "fail to read ground truth file: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(!read_bbox_file(input[1], pred) || pred[0].score < 0.0)
	{
		fprintf(stderr, "fail to read predicted result file: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	int	n = 0;
	string	fname_prev = "";
	for(size_t i = 0; i < pred.size(); i++)
	{
		if(verbose && pred[i].fname != fname_prev)
		{
			show_result(pred[i].fname, gt, pred);
			fname_prev = pred[i].fname;
		}
		for(size_t j = 0; j < gt.size(); j++)
		{
			if(pred[i].fname == gt[j].fname
			&& compute_IoU(pred[i], gt[j]) > IoU_thresh
			&& pred[i].label == gt[j].label)
			{
				n++;
				break;
			}
		}
	}

	printf("Precision = %lf [%d/%zu]\n",
		(double)n/(double)pred.size(), n, pred.size());
	printf("Recall = %lf [%d/%zu]\n",
		(double)n/(double)gt.size(), n, gt.size());

	exit(EXIT_SUCCESS);
}

static void	show_result(string fname, vector<bbox> gt, vector<bbox> pred)
{
	string	fn = img_dir + fname + ".jpg";
	if(!exists(path(fn)))
	{
		fprintf(stderr, "can't find %s\n", fname.c_str());
		return;
	}
	Mat	img = imread(fn);

	for(size_t i = 0; i < gt.size(); i++)
	{
		if(gt[i].fname == fname)
		{
			putText(img, to_string(gt[i].label), Point(gt[i].x1,gt[i].y1-10),
			FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0,0,255), 2);
			rectangle(img, Point(gt[i].x1,gt[i].y1), Point(gt[i].x2,gt[i].y2),
			Scalar(0,0,255), 3, LINE_8);
		}
	}
	for(size_t i = 0; i < pred.size(); i++)
	{
		if(pred[i].fname == fname)
		{
			putText(img, to_string(pred[i].label), Point(pred[i].x1+25,pred[i].y1-10),
			FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255,0,0), 2);
			rectangle(img, Point(pred[i].x1,pred[i].y1), Point(pred[i].x2,pred[i].y2),
			Scalar(255,0,0), 3, LINE_8);
		}
	}

	int	width;
	int	height;
	screen_resolution(width, height);
	double	scale = (double)width/(double)img.cols;
	printf("%s: [%d:%d] --> [%d:%d]\n",
		fname.c_str(), img.cols, img.rows, width, (int)(img.rows*scale));
	resize(img, img, Size(width,img.rows*scale));
	string win_title = "Teeth numbering";
	namedWindow(win_title, WINDOW_AUTOSIZE);
	moveWindow(win_title, 0, 0);
	imshow(win_title, img);
	if(waitKey(0) == 27)
		exit(EXIT_SUCCESS);
	destroyAllWindows();
}

static double	compute_IoU(bbox boxA, bbox boxB)
{
	double	xA = fmax(boxA.x1, boxB.x1);
	double	yA = fmax(boxA.y1, boxB.y1);
	double	xB = fmin(boxA.x2, boxB.x2);
	double	yB = fmin(boxA.y2, boxB.y2);
	double	interArea = fmax(0, xB - xA)*fmax(0, yB - yA);
	double	boxAArea = (boxA.x2 - boxA.x1)*(boxA.y2 - boxA.y1);
	double	boxBArea = (boxB.x2 - boxB.x1)*(boxB.y2 - boxB.y1);
	double	IoU = interArea/(boxAArea + boxBArea - interArea);
	return(IoU);
}

static void	split(string &s, char delim, vector<string> &v)
{
	istringstream	stream(s);
	string field;

	while(getline(stream, field, delim))
		v.push_back(field);
}

static int	read_bbox_file(string file, vector<bbox> &bv)
{
	std::ifstream ifs(file);
	if(!bool(ifs))
	{
		fprintf(stderr, "can't open %s\n", file.c_str());
		return(0);
	}
	string	line;
	while(getline(ifs, line))
	{
		vector<string>	v;
		split(line, ',', v);
		if(v.size() < 6)
		{
			fprintf(stderr, "num elements: %zu\n", v.size());
			continue;
		}
		bbox	b;
		b.fname = v[0];
		b.x1 = stod(v[1]);
		b.y1 = stod(v[2]);
		b.x2 = stod(v[3]);
		b.y2 = stod(v[4]);
		b.label = stoi(v[5]);
		if(v.size() == 7)
			b.score = stod(v[6]);
		else
			b.score = -1.0;
		bv.push_back(b);
        }
	return(1);
}

static void	screen_resolution(int &width, int &height)
{
	Display	*display = XOpenDisplay(NULL);
	Screen	*screen = DefaultScreenOfDisplay(display);
	width  = screen->width;
	height = screen->height;
}
