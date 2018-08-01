#include <bits/stdc++.h>
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

int main(){
    int imageNumber=0,delay;
    double start_clock = clock();
    double length =0 ;
    cout << "total time ( s ): ";
    cin >> length;  length*=1000;
    cout << length <<endl;

    cout << "Gap between spanshot ( ms ) : ";
    cin >> delay;
    
    while(true){
        double cur_clock = clock();
        if(cur_clock - start_clock > length ) break;
        system(formatImportCommand(delay,imageNumber++).c_str());
    }
    system("ffmpeg -framerate 15 -i .screenshot-%05d.jpg -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p output1.mp4");
    system("rm .screenshot-*");
    return 0;
}
