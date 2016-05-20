////
////  kmeans-test.cpp
////  K-means-lzy
////
////  Created by cslzy on 16/5/16.
////  Copyright © 2016年 CY. All rights reserved.
////
//

#include "Headers.h"




template <typename T, int N>
int KMeansTest<T, N>::get_centers(vector<T> point)
{
    int center_i = 0;
    T min = (point[0] - centers[0][0]) * (point[0] - centers[0][0]);
    
    for (int i = 1; i < N; i++) {
        min += (point[i] - centers[0][i]) * (point[i] - centers[0][i]);
    }
    
    
    for (int c = 1; c < k_centers; c++) {
        T sum = (point[0] - centers[c][0]) * (point[0] - centers[c][0]);
        
        for (int i = 1; i < N; i++) {
            sum += (point[i] - centers[c][i]) * (point[i] - centers[c][i]);
        }
        
        if (sum < min) {
            min = sum;
            center_i = c;
        }
    }
    
    
    return center_i;
}

template <typename T, int N>
void KMeansTest<T, N>::init_k(vector<vector<T>> points, int k)
{
    if(!data_is_ok(points, k))
    {
        // in data_is_ok, test points number great than k,
        //test every point has the same dimension
        
        cout<<"--!Error: Initialization failed!--";
        return;
    }
    k_centers = k;
    // initialize centers
    centers.clear();
    if (random_initial_centers) {
        
        for (int i = 0; i < k; i++) {
            int iSecret;
            /* initialize random seed: */
            srand (time(0)+i);// use current time as seed for random generator
            /* generate secret number between 1 and 10: */
            iSecret = rand() % points.size();
            centers.push_back(points[iSecret]);
        }
    }
    else
    {
        for (int i = 0; i < k; i++) {
            centers.push_back(points[i]);
        }
    }
    show_info();
    // test calculate_center_once
    T total_sum = calculate_center_once(points);
    ////
    //    Total_Sum = total_sum;
    //    cout<<"Total Sum:"<<total_sum<<endl;
    //    show_info();
    
    T pre_sum;// = calculate_center_once(points);
    // clear clusters for every stage.
    //    T total_sum;
    
    vector<vector<T>> tem_centers;
    
    switch (end_modal) {
        case 0:
        {
            do{
                pre_sum = total_sum;
                //        show_info();
                total_sum = calculate_center_once(points);
            }while (pre_sum-total_sum);
            
        }
            break;
        case 1:
        {
            T min_sum = total_sum;
            tem_centers = centers;
            do{
                pre_sum = total_sum;
                show_info();
                total_sum = calculate_center_once(points);
                
                if (min_sum > total_sum) {
                    min_sum = total_sum;
                    //                     tem_centers.clear();
                    tem_centers = centers;
                }
            }while (pre_sum-total_sum);
            
            //            centers.clear();
            centers = tem_centers;
            Total_Sum_Sqrt = min_sum;
            
        }
            break;
        default:
            break;
    }
    
    // sort the sum value in each point's dimension in ascend order.
    sort_ascend();
    
    cout<<"\n\n--------RESULT----------\n";
    show_info_flag = true;
    show_info();
    
    // then test for convergence
    
    
}

template <typename T, int N>
T KMeansTest<T, N>::calculate_center_once(vector<vector<T>> points)
{
    T total_sum = 0;
    
    // initialize clusters storage
    //    vector<vector<vector<T>>> clusters(N, vector<vector<T>>);
    
    map<int, vector<vector<T>>> clusters;
    // calculate square sum
    for (typename vector<vector<T>>::iterator it = points.begin(); it!=points.end(); it++) {
        
        ////////////// BEGIN: find the nearest center, and the minimum squared distance///////////////
        T min = ((*it)[0]-centers[0][0]) * ((*it)[0]-centers[0][0]); // how to find the maximum of Type T, and initialize 0 to T?
        //
        for (int i=1; i<N; i++) {
            min += ((*it)[i]-centers[0][i]) * ((*it)[i]-centers[0][i]);
        }
        
        //        cout<<"Begin min:"<<min<<endl;
        int min_i = 0;// the nearest center's index
        
        for (int i = 1; i<k_centers; i++) { // k, centers
            // test
            
            T sum = ((*it)[0]-centers[i][0]) * ((*it)[0]-centers[i][0]);
            //            cout<<"sum: "<<sum<<"\t";
            for (int j = 1; j<N; j++) { // N, dimension
                // WRONG FORMAT:                sum += (*it[j]-centers[i][j]) * (*it[j]-centers[i][j]);
                sum += ((*it)[j]-centers[i][j]) * ((*it)[j]-centers[i][j]);
                //                cout<<sum<<"\t";
            }
            //            cout<<"compare sum and min||sum:"<<sum<<"||min:"<<min<<"||sum<min:"<<(sum<min)<<endl;
            if (sum < min) {
                //                waitKey(0);
                min = sum;
                min_i = i;
                //                cout<<"EXCANG: min:"<<min<<"\t min_i:"<<min_i<<"\t";
            }
            //            cout<<endl;
        }
        /////////////// END: find the nearest center, and the minimum squared distance///////////////
        
        /////////////// store points for cluster min_i /////////////////////////
        clusters[min_i].push_back(*it); // save point to cluster min_i
        total_sum += min;
        //        cout<<"min: "<<min<<"\ttotal_sum:"<<total_sum<<endl;
    }
    
    //////////////////// update centers /////////////////////
    
    for (int i = 0; i < k_centers; i++) {
        
        if (clusters.find(i)==clusters.end()) // if there is no point assigned to this center, do nothing about it. You can also change this center by random, or some also policy.®
        {
            continue;
        }
        vector<T> center = clusters[i][0];
        
        
        
        int c_i_size = (int)clusters[i].size(); // might be wrong , when initial centers are same
        
        // if there is no point in cluster[i], continue
        //        if (c_i_size==0) {
        //            continue;
        //        }
        
        for (int j=1; j<c_i_size; j++) {
            for (int d = 0; d < N; d++) {
                center[d] += clusters[i][j][d]; // might be wrong , when initial centers are same.
            }
        }
        
        // update centers
        centers[i].clear();
        for (int d = 0; d < N; d++) {
            centers[i].push_back(center[d]/c_i_size);
        }
    }
    
    Total_Sum_Sqrt = sqrt(total_sum);
    //    Total_Sum = total_sum;
    //    return total_sum;
    return Total_Sum_Sqrt;
}

template <typename T, int N>
bool KMeansTest<T, N>::data_is_ok(vector<vector<T>> points, int k)
{
    if (points.size()<k) {
        cout<<"--!Error: centers' number great than points'"<<endl;
        //exit(-1);
        return false;
    }
    //dimension = points[0].size();
    for (typename vector<vector<T>>::iterator it = points.begin(); it != points.end(); it++) {
        if (it->size()!=N) {
            cout<<"--!Error: error in points dimension!--"<<endl;
            return false;
        }
    }
    return true;
}

//template <typename T, int N>
//KMeansTest<T, N>::KMeansTest(vector<vector<T>> points, int k)
//{
//    init_k(points, k);
//}

template <typename T, int N>
KMeansTest<T, N>::KMeansTest()
{
    //    cout<<"--!Info: k means class not initialized!--"<<endl;
}

template <typename T, int N>
void KMeansTest<T, N>::show_info()
{
    if (!show_info_flag) {
        return;
    }
    cout<<"\ncenters:"<<endl;
    for (int i = 0; i < centers.size(); i++) {
        cout<<"CENTER "<<i+1<<": ";
        for (int j = 0; j < N; j++) {
            cout<<centers[i][j]<<"\t\t";
        }
        cout<<endl;
    }
    cout<<"Total_Sum: "<<Total_Sum_Sqrt<<endl;
}

template <typename T, int N>
void KMeansTest<T, N>::sort_ascend()
{
    vector<vector<T>> tem_centers = centers;
    centers.clear();
    
    // iterate time
    int iter_time = tem_centers.size();
    for (int i = 0; i < iter_time; i++) {
        
        // get the minimum sum of each point's dimension.
        T min = tem_centers[0][0];
        for (int j = 1; j < N; j++)
        {
            min += tem_centers[0][j];
        }
        int min_i = 0;
        
        for (int j = 1; j < tem_centers.size(); j++) {
            T sum = tem_centers[j][0];
            for (int d = 1; d < N; d++) {
                sum += tem_centers[j][d];
            }
            
            if (sum < min) {
                min = sum;
                min_i = j;
            }
            
        }
        
        centers.push_back(tem_centers[min_i]);// add back to centers
        tem_centers.erase(tem_centers.begin() + min_i);// remove from tem_centers.
    }
}

