#include <ros/ros.h>
#include <iostream>
#include <game_cut_pkg/personX.h>
#include<game_cut_pkg/personY.h>

using namespace std;

class PersonY
{
private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;
public:
  PersonY(){
    //Topic you want to publish 需要改的地方<> ""内
    pub_ = n_.advertise<game_cut_pkg::personY>("/pesonY_topic", 10);
 
    //Topic you want to subscribe
    sub_ = n_.subscribe("/personX_topic", 10, 
    &PersonY::callback, this);
  }
 
  void callback(const game_cut_pkg::personX& personX_msg){
    //.... do something with the input and generate the output...
    //PUBLISHED_MESSAGE_TYPE output;  PUBLISHED_MESSAGE_TYPE为msg type 如：learning_topic::Person person_msg
    //pub_.publish(output);
	cout<<"aaa"<<endl;
    game_cut_pkg::personY personY_msg;
    char persony='0';
    cout<<"输入你的动作，1：石头 2：剪刀 3：布";
    cin>>persony;
    if(persony<personX_msg.personX){
		  cout<<"you win";
        personY_msg.personY=2;
	  }else if(persony==personX_msg.personX){
        cout<<"you win";
        personY_msg.personY=3;
    }else{
		  if(persony==3&&personX_msg.personX==1){
			  cout<<"you win";
            personY_msg.personY=1;
		  }else{
			  cout<<"you lost";
           personY_msg.personY=1;
		  }
	  }
    pub_.publish(personY_msg);
  }
};
 
int main(int argc, char **argv)
{
  //Initiate ROS "节点名称"
  ros::init(argc, argv, "personY");
  //Create an object of class SubscribeAndPublish that will take care of everything
  PersonY persony;
  ros::spin();
  return 0;
}
