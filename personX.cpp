#include <ros/ros.h>
#include <iostream>
#include <game_cut_pkg/personX.h>
#include<game_cut_pkg/personY.h>

using namespace std;
class PersonX
{
private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;
public:
  PersonX(){
    //Topic you want to publish 需要改的地方<> ""内
    pub_ = n_.advertise<game_cut_pkg::personX>("/pesonX_topic", 10);
    //Topic you want to subscribe
    sub_ = n_.subscribe("/personY_topic", 10,&PersonX::callback,this);
    ros::Rate loop_rate(5);
    while (n_.ok()) {
       game_cut_pkg::personX personx_msg;
      cout<<"输入动作 1：石头 2：剪刀 3：布"<<endl;
      char personx='0';
      cin>>personx;
      personx_msg.personX=personx;
      pub_.publish(personx_msg);
      ros::spinOnce();
      loop_rate.sleep();
	cout<<"bbb"<<endl;
    }
  }
 
  void callback(const game_cut_pkg::personY &personY_msg){
    //.... do something with the input and generate the output...
    //PUBLISHED_MESSAGE_TYPE output;  PUBLISHED_MESSAGE_TYPE为msg type 如：learning_topic::Person person_msg
    //pub_.publish(output);
    if(personY_msg.personY==1){
        cout<<"you win"<<endl;
    }else if(personY_msg.personY==2){
        cout<<"you lost"<<endl;
    }else if(personY_msg.personY==3){
        cout<<"win win"<<endl;
    }else{
        cout<<"没考虑的情况"<<endl;
    }
  }
};
 
int main(int argc, char **argv)
{
  //Initiate ROS "节点名称"
  ros::init(argc, argv, "personX");
  //Create an object of class SubscribeAndPublish that will take care of everything
  PersonX personx;
  //ros::spin();
 
  return 0;
}
