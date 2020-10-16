//
// Created by xtcsun on 2020/10/16.
//
#include <string>
#include <chrono>   // for time stamp
#include <iostream>
#include <include/System.h>

using namespace std;

string parameterFile = "/home/xtcsun/Github/ORBSLAM2_detailed_comments/Examples/Monocular/KITTI04-12.yaml";
string vocFile = "/home/xtcsun/Github/ORBSLAM2_detailed_comments/Vocabulary/ORBvoc.txt";
string videoFile = "/home/xtcsun/Github/ORBSLAM2_detailed_comments/test.mp4";
int main(){
    // 声明 ORB-SLAM2 系统
    ORB_SLAM2::System SLAM(vocFile, parameterFile, ORB_SLAM2::System::MONOCULAR, true);

    // 获取视频图像
    cv::VideoCapture cap(videoFile);    // change to 1 if you want to use USB camera.
    // 记录系统时间
    auto start = chrono::system_clock::now();
    while (1) {
        cv::Mat frame;
        cap >> frame;   // 读取相机数据
        if ( frame.data == nullptr )
            break;
        // rescale because image is too large
        cv::Mat frame_resized;
        cv::resize(frame, frame_resized, cv::Size(640,360));
        auto now = chrono::system_clock::now();
        auto timestamp = chrono::duration_cast<chrono::milliseconds>(now - start);
        SLAM.TrackMonocular(frame_resized, double(timestamp.count())/1000.0);
        cv::waitKey(30);
    }
    SLAM.Shutdown();

    return 0;
}