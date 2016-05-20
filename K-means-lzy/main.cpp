//
//  main.cpp
//  K-means-lzy
//
//  Created by cslzy on 16/5/16.
//  Copyright © 2016年 CY. All rights reserved.
//
//
#include "KMeansTest.cpp"
string test_png1 = "/sample/images/k-means-1.png";
string test_png2 = "/sample/images/k-means-2.png";
string test_png3 = "/Users/cslzy/Desktop/monkey.jpg";
string test_png4 = "/Users/cslzy/Desktop/keys.jpg";

#define K 20

int main ()
{
    bruteKmeans_test();
    return 0;
}


void bruteKmeans_test()
{
#define DATATYPE float
    Mat img = imread(test_png4); // need imgcodecs3.1.0.dylib
    
    // read all the pixels
    vector<vector<DATATYPE>> points;
    
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            //            float colors[3];
            vector<DATATYPE> one_point;
            //            cout<<img.at<Vec3b>(i, j)<<endl;
            DATATYPE b = img.at<Vec3b>(i,j)[0];
            DATATYPE g = img.at<Vec3b>(i,j)[1];
            DATATYPE r = img.at<Vec3b>(i,j)[2];
            one_point.push_back(b);
            one_point.push_back(g);
            one_point.push_back(r);
            
            points.push_back(one_point);
        }
    }
    
    KMeansTest<DATATYPE, 3> km; // 3-dimension data point
    km.random_initial_centers = true;
    km.end_modal = 1;
    km.show_info_flag = true;
    km.init_k(points, K); // find K centers
    
    DATATYPE scolor[K][3];
    for (int i = 0; i < K; i++) {
        RNG rng(i + 123456); // random color
        for (int j = 0; j < 3; j++) {
            scolor[i][j] = rng.uniform(0, 255);
        }
    }
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            vector<DATATYPE> colors;
            colors.push_back(img.at<Vec3b>(i,j)[0]);
            colors.push_back(img.at<Vec3b>(i,j)[1]);
            colors.push_back(img.at<Vec3b>(i,j)[2]);
            //            cout<<img.at<Vec3b>(i, j)<<endl;
            int center_i = km.get_centers(colors);
            img.at<Vec3b>(i,j)[0] = scolor[center_i][0];
            img.at<Vec3b>(i,j)[1] = scolor[center_i][1];
            img.at<Vec3b>(i,j)[2] = scolor[center_i][2];
//
            // if you want a color picture, run below
//            RNG rng(0xFFFFFFFF); // random color
//            img.at<Vec3b>(i,j)[0] = rng.uniform(0, 255);
//            img.at<Vec3b>(i,j)[1] = rng.uniform(0, 255);
//            img.at<Vec3b>(i,j)[2] = rng.uniform(0, 255);
            
        }
    }
    
    imshow("test", img);
    char file_path[255];
    sprintf(file_path, "/Users/cslzy/Desktop/keys_km%d.jpg", K);
    imwrite(file_path, img);
    waitKey(0);
}

