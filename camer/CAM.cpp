#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(){
    Mat img;
    img=imread("test.jpg");
    if(img.empty()){
        cout<<"Image not found:"<<endl;
        return -1;
    }
vector<Mat>imger;
split(img,imger);
equalizeHist(imger[0],imger[0]);
equalizeHist(imger[1],imger[1]);
equalizeHist(imger[2],imger[2]);
Mat chanl;
merge(imger,chanl);
GaussianBlur(chanl,chanl,Size(3,3),0);
imwrite("修正好的图片.jpg",chanl);
    cout<<"已经完成了"<<endl;


return 0;




}
