//////Variable-definition//////

///////Bit-definition//////////
sbit MotorOneLeft = P2^0;	   
sbit MotorOneRight = P2^1;
sbit MotorTwoLeft = P2^2;
sbit MotorTwoRight = P2^3;

//////Function-definition//////
void Go();			  //前进
void Back();		  //后退
void Turn_Left();	  //左转
void Turn_Right();	  //右转
void Stop();		  //停止
void SStop();		  //急停