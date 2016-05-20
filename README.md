# toy-k-means

This is a toy program for testing k-means algorithm to cluster pixel points in a picture.

In this program, you can define the dimension of each data point by: 
  - KMeansTest\<DATATYPE, 3\> km; // 3-dimension data point

And define the center number k by:
  - #define K 10

Define data type is avaible, however, only float and integer type can be used.
  - #define DATATYPE float

Before testing this program, you should rewrite the pictures' path, and make sure that you have reconfigurated OpenCV's header and library path.  

This toy project works in OpenCV 3.1.0 and macbook air 13.

这是一个测试k-means算法的小程序，我用它来给图像中的点聚类。
里面的数据点的维度、中心点的个数可以自定义。
定义中心点个数的方式：
  - #define K 10
  
数据类型也可以，不过目前只能从浮点数和整数里面选。像下面这样定义数据类型和数据维度。
  - #define DATATYPE float
  - KMeansTest\<DATATYPE, 3\> km; // 3-dimension data point

使用前，确保图片路径配置成你的机器路径。OpenCV的头文件、库文件路径也要配置。
我的工作环境是Opencv 3.1.0，macbook air 13。
