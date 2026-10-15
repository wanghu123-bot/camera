#include<opencv2/opencv.hpp>
#include<iostream>
class myCamera{
    private:
    cv::VideoCapture cap;
    public:
    myCamera(){
        if(!cap.open(0)){
            std::cout<<"Error opening camera"<<std::endl;
        } else{
            std::cout<<"sycessfully"<<std::endl;
         }
    };
    bool read(cv::Mat& frame){
         return cap.read(frame);};
        
       
    ~myCamera(){
        cap.release();
         
        }
    };
int main(){
        myCamera camera;
        // bool ok = camera.cap.read(frame);
        cv::Mat frame;

        while(true){
            bool ok=camera.read(frame);
           if(!ok){
            std::cout<<"Error reading"<<std::endl;
            }else{
            std::cout<<"Successfully read"<<std::endl;
        }
        // cv::imshow("Camera",frame);
            int key =cv::waitKey(1);
            if(key==27){
             std::cout<<"exit"<<std::endl;
               break;
            };
    }
           
        
        return 0;
    }

