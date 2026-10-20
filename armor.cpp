#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main(){
    Mat frame;
    VideoCapture vio("video.text");
    Mat hsv, mask;
    while (vio.read(frame))
    
    Mat hsv, mask;
     cvtColor(frame ,hsv,COLOR_BGR2HSV);
     inRange(hsv,Scalar(100,120,120),Scalar(130,225,225),mask);
     dilate(mask,mask,getStructuringElement(MORPH_RECT, Size(3, 3)));
     vector<vector<Point>>counious;
     vector<RotatedRect>bar;
     for(auto&c:counious){
        RotatedRect r=minAreaRect(c);
        float w=min(r.size.height ,r.size.width);
        float m=max(r.size.height,r.size.width);
        if(m/w>2&&m>2){
            bar.push_back(r);
        }
    for(size_t i=0;i<bar.size();i++){
        for (size_t j=0;j<bar.size();i++){
       Point2f c1=bar[i].center ,c2=bar[i].center;
       if(c1.x>c2.x)swap(c1,c2);
       float dy=abs(c1.y-c2.y);
       float asd=(bar[i].size.height-bar[i].size.height)/2.0;
       float dx=c2.x-c1.x;
       if(dy<asd*0.5&&dx>asd*1.5&&dx<asd*4){
        Rect box(c1.x - bar[i].size.width/2, c1.y - asd/2, dx + bar[i].size.width, asd);
        rectangle(frame,box,Scalar(0,0,225),2);
        circle(frame, (c1+c2)/2, 3, Scalar(0,0,255), -1);
        Mat roi=frame(box);
        putText(frame, "3", Point(box.x, box.y - 5), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255), 2);

       };
        }
    }
if(waitKey(30)==27)break;
return 0;
     
}