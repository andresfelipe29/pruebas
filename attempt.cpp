#include <iostream>
#include <vector>
#include <algorithm>

struct body{
  int x = 0;
  int y = 0;
};

struct domain{
  int max = 0;
  int local_size = 0;
  int ball_share_up = 0;
  int ball_share_down = 0;
  std::vector<body> balls;
};


int main()
{
  body ball0; ball0.x = 0;
  body ball1; ball1.x = 1;
  body ball2; ball2.x = 2;
  body ball3; ball3.x = 3;
  body ball4; ball4.x = 4;
  body ball5; ball5.x = 5;
  body ball6; ball6.x = 6;
  body ball7; ball7.x = 7;
  body ball8; ball8.x = 8;
  body ball9; ball9.x = 9;

  int rad_b = 1;
  
  domain section;
  section.max = 3;
  section.local_size = 10;
  section.ball_share_up = 7;
  section.ball_share_down = 4;
  section.balls;
  section.balls.emplace_back(ball0);
  section.balls.emplace_back(ball1);
  section.balls.emplace_back(ball2);
  section.balls.emplace_back(ball3);
  section.balls.emplace_back(ball4);
  section.balls.emplace_back(ball5);
  section.balls.emplace_back(ball6);
  section.balls.emplace_back(ball7);
  section.balls.emplace_back(ball8);
  section.balls.emplace_back(ball9);

  int N_send[4] = {0,0,0,0};

  std::vector<body> balls_send_up;

  section.balls.erase( std::remove_if( section.balls.begin(), section.balls.begin()+section.local_size,
				       [&section, &N_send, &balls_send_up](body ball){
					 if (section.max <= ball.x){
					   std::cout << ball.x << " actually deleted\n";
					   N_send[1]++;
					   section.local_size--;
					   balls_send_up.emplace_back(ball);
					   return true;
					 } else {return false;}
				       })
		       ,section.balls.begin()+section.local_size
		       );

  std::copy_if( section.balls.begin(), section.balls.begin()+section.local_size, std::back_inserter(balls_send_up), 
		[&section, &N_send, &balls_send_up, &rad_b](body ball){
		  if (section.max-rad_b<=ball.x && ball.x<section.max){ //Upper limit shared balls
		    std::cout << ball.x << " actaully shared\n";
		    N_send[3]++;
		    return true;
		  } else {return false;}
		});

  std::vector<body> ball_send_up;
  std::vector<body> ball_send_down;

  section.local_size = 10;
  
  int first = section.local_size-section.ball_share_up;
  std::copy_n( section.balls.begin()+first, section.ball_share_up, std::back_inserter(ball_send_up));
  std::copy_n( section.balls.begin(), section.ball_share_down, std::back_inserter(ball_send_down));

  std::cout << "local_size = " << section.local_size << "\n";
  std::cout << "size = " << section.balls.size() << "\n";
  std::cout << "sent = " << N_send[1]+N_send[3] << "\n";
  std::cout << "erased = " << N_send[1] << "\n";
  std::cout << "shared = " << N_send[3] << "\n";

  for (auto ball: section.balls){
    std::cout << "x = " << ball.x << "\n";
  }
  for (int i = 0; i < N_send[1]; i++){
    std::cout << "xsent = " << balls_send_up[i].x << "\n";
  }
  for (int i = N_send[1]; i < N_send[1]+N_send[3]; i++){
    std::cout << "xshared = " << balls_send_up[i].x << "\n";
  }

  section.balls.resize(section.local_size);
  for (auto ball: section.balls){
    std::cout << "x = " << ball.x << "\n";
  }

  for (auto ball: ball_send_up){
    std::cout << "up = " << ball.x << "\n";
  }
  for (auto ball: ball_send_down){
    std::cout << "down = " << ball.x << "\n";
  }
  
  return 0;
}
