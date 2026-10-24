#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace cv::dnn;
using namespace std;

int main()
{
    Net net = readNetFromONNX("best.onnx");
    VideoCapture cap(0);
    Mat frame;

    while (cap.read(frame))
    {
        Mat blob;
        blobFromImage(frame, blob, 1.0/255, Size(640,640), Scalar(0,0,0), true, false);
        net.setInput(blob);
        Mat out = net.forward();

        vector<int> ids;
        vector<float> confs;
        vector<Rect> boxes;
        float* data = (float*)out.data;

        for(int i=0;i<out.size[1];i++)
        {
            if(data[4]>0.5)
            {
                int id = data[5]>data[6] ? 0 : 1;
                float conf = data[4] * max(data[5],data[6]);
                if(conf>0.5)
                {
                    float cx=data[0], cy=data[1], w=data[2], h=data[3];
                    float sx = (float)frame.cols/640;
                    float sy = (float)frame.rows/640;
                    int x = (cx - w/2)*sx;
                    int y = (cy - h/2)*sy;
                    boxes.push_back(Rect(x,y,w*sx,h*sy));
                    confs.push_back(conf);
                    ids.push_back(id);
                }
            }
            data +=7;
        }

        vector<int> idx;
        NMSBoxes(boxes, confs, 0.5,0.4,idx);
        for(auto i : idx)
        {
            rectangle(frame, boxes[i], ids[i]==0 ? Scalar(255,0,0):Scalar(0,0,255),2);
            Point c(boxes[i].x + boxes[i].width/2, boxes[i].y + boxes[i].height/2);
            circle(frame,c,4,Scalar(0,255,0),-1);
            cout << "中心点：" << c.x << " " << c.y << endl;
        }

        imshow("YOLO检测",frame);
        if(waitKey(1)==27) break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
