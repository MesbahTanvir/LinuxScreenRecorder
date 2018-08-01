#include <bits/stdc++.h>
#include <time.h>
#include <unistd.h>
using namespace std;
#define MAX_NAME_SIZE 1024

// sudo apt-get update
// sudo apt-get install ffmpeg

string imageName(int num){
    char str[MAX_NAME_SIZE];
    sprintf(str,"%05d",num);
    string name = ".screenshot-";
    name+=str;
    name+=".jpg";    
    return name;
}
string formatImportCommand(int delayTime , int imageNumber){
    char str[1024]; 
    string cmd = "import -window root -delay ";    
    sprintf(str,"%d ",delayTime);
    cmd += str; 
    cmd += imageName(imageNumber);
    return cmd;
}
string formatedTime(){
    time_t     now;
    struct tm  ts;
    char       buf[80];
    time(&now);
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d_%H:%M:%S", &ts);
    return (string)buf;
}
void startRecorder(int length, int delay,string outputName){
    int imageNumber = 0 , start_time = time(NULL);
    while(true){
        int cur_time = time(NULL);
        if(cur_time - start_time > length ) break;
        system(formatImportCommand(20,imageNumber++).c_str());
        usleep(delay);
    }
    system(("ffmpeg -framerate 15 -i .screenshot-%05d.jpg -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p " + outputName).c_str());
    system("rm .screenshot-*"); 

}
string makeOutputFileName(){
    return "screenCapture-"+formatedTime()+".mp4";
}
int main(){
    int delay,length=0;

    cout << "total time ( s ): ";
    cin >> length; 
    cout << length <<endl;
    cout << "Gap between spanshot ( ms ) : ";
    cin >> delay;

    startRecorder(length,delay*1000,makeOutputFileName());
   
    return 0;
}
