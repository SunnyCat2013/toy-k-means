//
//  Headers.h
//  K-means-lzy
//
//  Created by cslzy on 16/5/20.
//  Copyright © 2016年 CY. All rights reserved.
//


//#include "kmeans-test.hpp"
//#include "KMeansTest.cpp"
#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/highgui.hpp" // header files for: Mat
#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <math.h>

using namespace std;

using namespace cv;
#define DATATYPE float

// brute-force k-means
template <typename T, int N> class KMeansTest
{
private:
    vector<vector<T>> centers;
    bool data_is_ok(vector<vector<T>> points, int k);
    T calculate_center_once(vector<vector<T>> points);// calculate center for once, and return the total sum
    int k_centers = 0;
    T Total_Sum = 0; // sum of square, or square root of sum
    T Total_Sum_Sqrt = 0; // sum of square, or square root of sum
public:
    int end_modal = 0;
    bool random_initial_centers = false; // trye: get random points as centers; else, get top k points as initial centers.
    bool show_info_flag = false; // true: show kmeans object centers' information; false: show output only.
    KMeansTest();
    KMeansTest(vector<vector<T>> points, int k);
    void init_k(vector<vector<T>> points, int k);
    int get_centers(vector<T> point); // return the center index and center point
    void show_info();
    void sort_ascend(); // sort average of each point in ascend order.
};

void bruteKmeans_test();

void bruteKmeans_test_hsl();